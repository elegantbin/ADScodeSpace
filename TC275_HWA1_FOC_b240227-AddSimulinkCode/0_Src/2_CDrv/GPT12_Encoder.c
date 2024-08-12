
#include <GPT12_Encoder.h>
#include "IfxGpt12_PinMap.h"
#include "Ifx_Types.h"
#include "Tables.h"
#include "IfxPort.h"
#include "IfxGpt12.h"
#include "ConfigurationIsr.h"
#include "configuration.h"
#include "SPI_ENCODER.h"
#include "AppTorqueControl.h"

IFX_INLINE void TotalCountsPerCycle_ValidCheck(void);
IFX_INLINE void ZeroPulseHandler(void);

/******************* GLOBAL VARIABLES ****************/

IfxGpt12_IncrEnc  g_IncrEnc;
volatile sint16 g_TotalCountAcircle = 0;
sint16 g_Encoder_RawPosition;

/*****************************************************/

IFX_INTERRUPT(ISR_Encoder_Gpt12_T4, 0, INTERRUPT_ENCODER_GPT12_T4);
IFX_INTERRUPT(ISR_Encoder_Gpt12_T2, 0, INTERRUPT_ENCODER_GPT12_T2);
/** \brief Handle the encoder zero interrupt (priority = \ref ISR_PRIORITY(INTERRUPT_ENCODER_GPT12)).
 *
 * This interrupt is raised each time the encoder zero event occurs.
 */
void ISR_Encoder_Gpt12_T4(void)
{
    ZeroPulseHandler();

    __enable();
}

void ISR_Encoder_Gpt12_T2(void)
{
    Ifx__NOP(1);

    __enable();
}


/*****************************************************/
void GPT12_EncoderInit(void)
{
    Ifx_GPT12 *gpt12=&MODULE_GPT120;
    IfxGpt12_enableModule(gpt12);
    IfxGpt12_setGpt1BlockPrescaler(gpt12, IfxGpt12_Gpt1BlockPrescaler_4);
    IfxGpt12_setGpt2BlockPrescaler(gpt12, IfxGpt12_Gpt2BlockPrescaler_4);

    /* T2 Configuration */
    IfxGpt12_initTxInPinWithPadLevel(&ENCODER_PINA, IfxPort_InputMode_noPullDevice, IfxPort_PadDriver_cmosAutomotiveSpeed1);    //PINA
    IfxGpt12_initTxEudInPinWithPadLevel(&ENCODER_PINB, IfxPort_InputMode_noPullDevice,IfxPort_PadDriver_cmosAutomotiveSpeed1); //PINB

#define COUNTER_MODE   (1)
#define CAPTURE_MODE   (2)
#define ENCORDER_MODE  (3)
#define T2_MODE        (ENCORDER_MODE)

#if(COUNTER_MODE ==T2_MODE)
    IfxGpt12_T2_setMode(gpt12, IfxGpt12_Mode_counter);
    IfxGpt12_T2_setCounterInputMode(gpt12, IfxGpt12_CounterInputMode_risingEdgeTxIN );
    IfxGpt12_T2_setDirectionSource(gpt12, IfxGpt12_TimerDirectionSource_external);
    IfxGpt12_T2_setTimerDirection(gpt12, IfxGpt12_TimerDirection_up);
    IfxGpt12_T2_run(gpt12, IfxGpt12_TimerRun_start);

#elif(CAPTURE_MODE == T2_MODE)
    IfxGpt12_T2_setMode(gpt12, IfxGpt12_Mode_capture);
    IfxGpt12_T2_setCaptureInputMode(gpt12, IfxGpt12_CaptureInputMode_risingEdgeTxIN);
    IfxGpt12_T2_setDirectionSource(gpt12, IfxGpt12_TimerDirectionSource_external);
    IfxGpt12_T2_setTimerDirection(gpt12, IfxGpt12_TimerDirection_up);
    IfxGpt12_T2_run(gpt12, IfxGpt12_TimerRun_start);

#elif(ENCORDER_MODE == T2_MODE)
    IfxGpt12_T2_setMode(gpt12, IfxGpt12_Mode_incrementalInterfaceEdgeDetection);
    IfxGpt12_T2_setIncrementalInterfaceInputMode(gpt12, IfxGpt12_IncrementalInterfaceInputMode_bothEdgesTxINOrTxEUD);
    IfxGpt12_T2_setDirectionSource(gpt12, IfxGpt12_TimerDirectionSource_external);
    IfxGpt12_T2_setTimerDirection(gpt12, IfxGpt12_TimerDirection_up);
    IfxGpt12_T2_run(gpt12, IfxGpt12_TimerRun_start);

#endif

    /* T2 Interrupt Configure*/
    {
       IfxGpt12_T2_setInterruptEnable(gpt12, TRUE);
       IfxGpt12_T2_setRemoteControl(gpt12, IfxGpt12_TimerRemoteControl_off);
       /* setup interrupt */
       volatile Ifx_SRC_SRCR *src = IfxGpt12_T2_getSrc(gpt12);
       IfxSrc_init(src, IfxSrc_Tos_cpu0, INTERRUPT_ENCODER_GPT12_T2);
       IfxSrc_enable(src);
    }

    /* T4 Configuration */
    //IfxGpt12_initTxInPinWithPadLevel(&ENCODER_PINZ, IfxPort_InputMode_pullUp, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxGpt12_initTxEudInPinWithPadLevel(&ENCODER_PINZ, IfxPort_InputMode_noPullDevice, IfxPort_PadDriver_cmosAutomotiveSpeed1);//PINZ
    IfxGpt12_T4_setMode(gpt12, IfxGpt12_Mode_incrementalInterfaceRotationDetection);
    IfxGpt12_T4_setIncrementalInterfaceInputMode(gpt12,IfxGpt12_IncrementalInterfaceInputMode_bothEdgesTxINOrTxEUD);

    IfxGpt12_T4_setDirectionSource(gpt12, IfxGpt12_TimerDirectionSource_internal);
    IfxGpt12_T4_run(gpt12, IfxGpt12_TimerRun_start);

#if(PINMAP_TC275LITE_KIT_ENCODER)

    IfxGpt12_initTxInPinWithPadLevel(&ENCODER_PINA, IfxPort_InputMode_pullUp, IfxPort_PadDriver_cmosAutomotiveSpeed1);    //PINA Pull-up in Dev-Kit
    IfxGpt12_initTxEudInPinWithPadLevel(&ENCODER_PINB, IfxPort_InputMode_pullUp,IfxPort_PadDriver_cmosAutomotiveSpeed1); //PINB
    IfxGpt12_initTxEudInPinWithPadLevel(&ENCODER_PINZ, IfxPort_InputMode_pullUp, IfxPort_PadDriver_cmosAutomotiveSpeed1);//PINZ

#endif

    /* T4 Interrupt Configure*/
    {

        IfxGpt12_T4_setInterruptEnable(gpt12, TRUE);
        IfxGpt12_T4_setRemoteControl(gpt12, IfxGpt12_TimerRemoteControl_off);
        /* setup interrupt */
        volatile Ifx_SRC_SRCR *src = IfxGpt12_T4_getSrc(gpt12);
        IfxSrc_init(src, IfxSrc_Tos_cpu0, INTERRUPT_ENCODER_GPT12_T4);
        IfxSrc_enable(src);
    }
}


sint16 GPT12_EncoderUpdatePosition(void)
{
    Ifx_GPT12 *gpt12=&MODULE_GPT120;

	g_Encoder_RawPosition = (sint16)IfxGpt12_T2_getTimerValue(gpt12);
    g_Encoder_RawPosition %= 4096;

	return g_Encoder_RawPosition;
}


void GPT12_EncoderReset(void)
{
    Ifx_GPT12 *gpt12=&MODULE_GPT120;
    IfxGpt12_T2_setTimerValue(gpt12, 0);
}

#define  K_POS_PER_ELE_CYCLE    (819)

#define  K_ELE_ANGLE_OFFSET      (82)   //@motor 17 is 85 or91 @motor 19 is 270  @motor13 is 950 @motor 16 is 82//@motor6 is 656
#define  POS_ANGLE_FACTOR  (float)(1.25)

sint16  eleEcoder_Pos;
sint16  eleAngle_Offset = K_ELE_ANGLE_OFFSET;
sint16  elePos_Offset;
sint16  ele_Angle;//electrical angle is in (0,1023)
sint16 EcoderPosition_EleAgle(void)
{
    GPT12_EncoderUpdatePosition();

    //mechanical pulse count transit to electrical pulse count
    eleEcoder_Pos = g_Encoder_RawPosition % K_POS_PER_ELE_CYCLE;

    // electrical angle offset transition to electrical pulse count offset
    elePos_Offset  =(sint16)((float)(eleAngle_Offset)/POS_ANGLE_FACTOR);

    if(elePos_Offset > K_POS_PER_ELE_CYCLE)
    {
        elePos_Offset %= K_POS_PER_ELE_CYCLE;
    }

    //calibration electrical pulse count
    if(eleEcoder_Pos > elePos_Offset)
    {
        eleEcoder_Pos -= elePos_Offset;
    }
    else
    {
        eleEcoder_Pos += K_POS_PER_ELE_CYCLE;
        eleEcoder_Pos -= elePos_Offset;
    }
    // electrical pulse count transition to electrical angle
    ele_Angle = (sint16)(eleEcoder_Pos * POS_ANGLE_FACTOR);

    if(ele_Angle < 0)
    {
        ele_Angle += COSSIN_TABLE_SIZE;

    }

    return ele_Angle;
}


IFX_INLINE void ZeroPulseHandler(void)
{
    boolean b_PulseFilter = TRUE;

    for(int i=0;i<3;i++)//3us  ( 40 counts == 1us)
    {
        for(int j=0;j<40;j++)
        {
          Ifx__NOP(1);

        }
        if(IfxPort_getPinState(ENCODER_PINZ.pin.port, ENCODER_PINZ.pin.pinIndex)==TRUE)
         {

         }
         else
         {
             b_PulseFilter=FALSE;
         }
    }
//    g_motor.test_count1 = IfxPort_getPinState(ENCODER_PINZ.pin.port, ENCODER_PINZ.pin.pinIndex);

    if((b_PulseFilter)&&(IfxPort_getPinState(ENCODER_PINZ.pin.port, ENCODER_PINZ.pin.pinIndex)==TRUE))
    {
      // blinkLED1();

       g_TotalCountAcircle = GPT12_EncoderUpdatePosition();

       if (g_motor.diag.sync_topzero == TRUE)  //start validcheck when the second zero pulse  detected
       {
           TotalCountsPerCycle_ValidCheck();
       }

       g_motor.diag.sync_topzero = TRUE;

       GPT12_EncoderReset();
    }
}

IFX_INLINE void TotalCountsPerCycle_ValidCheck(void)
{

    uint32 absTotalCountAcircle = 0;

    /*
     * if(MOTOR_STATE_RUNNING == g_bldc.state)
    {
        if(g_TotalCountAcircle>0)
       {
           absTotalCountAcircle = g_TotalCountAcircle;
       }
       else
       {
           absTotalCountAcircle = -g_TotalCountAcircle;
       }

      if(absTotalCountAcircle>5)
      {
       if(absTotalCountAcircle > K_ENCODER_TOTAL_COUNTS_PER_CYCLE_MAX||
               absTotalCountAcircle<K_ENCODER_TOTAL_COUNTS_PER_CYCLE_MIN)
        {
           g_bldc.state = MOTOR_STATE_FAIL;
           CommutationDriver_Stop();
           g_bldc.u32DiagCode |= MOTOR_DIAG_CODE_UPDATAPOSITION_FAIL;
        }
       }
    }

    */
}


