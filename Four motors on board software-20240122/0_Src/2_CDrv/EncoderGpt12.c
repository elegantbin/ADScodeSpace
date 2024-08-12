
#include <EncoderGpt12.h>
#include "IfxGpt12_PinMap.h"
#include "Ifx_Types.h"

#include "IfxPort.h"
#include "IfxGpt12.h"
#include "IfxGpt12_reg.h"
#include "ConfigurationIsr.h"
#include "configuration.h"
#include "PosIf.h"
#include "AppPositionAquisition.h"
#include "Commutationpoint.h"
#include "SPI_ENCODER.h"

sint16 Encoder_RawPosition;
sint16 Encoder_RawPositionOld;
sint16 spiEndcoderPos;

void EncoderInit(void)
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
#define T2_MODE        (COUNTER_MODE)

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
    IfxGpt12_T2_setIncrementalInterfaceInputMode(gpt12, IfxGpt12_IncrementalInterfaceInputMode_bothEdgesTxIN);
    IfxGpt12_T2_setDirectionSource(gpt12, IfxGpt12_TimerDirectionSource_external);
    IfxGpt12_T2_setTimerDirection(gpt12, IfxGpt12_TimerDirection_up);
    IfxGpt12_T2_run(gpt12, IfxGpt12_TimerRun_start);

#endif

    /* T2 Interrupt*/
#define  GPT12_T2_INTERRUPT_ENABLE   (1)
#if(GPT12_T2_INTERRUPT_ENABLE==TRUE)
    {
       IfxGpt12_T2_setInterruptEnable(gpt12, TRUE);
       IfxGpt12_T2_setRemoteControl(gpt12, IfxGpt12_TimerRemoteControl_off);
       /* setup interrupt */
       volatile Ifx_SRC_SRCR *src = IfxGpt12_T2_getSrc(gpt12);
       IfxSrc_init(src, IfxSrc_Tos_cpu0, INTERRUPT_ENCODER_GPT12_T2);
       IfxSrc_enable(src);
    }
#endif

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

    /* T4 Interrupt*/
    {

        IfxGpt12_T4_setInterruptEnable(gpt12, TRUE);
        IfxGpt12_T4_setRemoteControl(gpt12, IfxGpt12_TimerRemoteControl_off);
        /* setup interrupt */
        volatile Ifx_SRC_SRCR *src = IfxGpt12_T4_getSrc(gpt12);
        IfxSrc_init(src, IfxSrc_Tos_cpu0, INTERRUPT_ENCODER_GPT12_T4);
        IfxSrc_enable(src);
    }
}


sint16 EncoderUpdatePosition(void)
{
    Ifx_GPT12 *gpt12=&MODULE_GPT120;

	Encoder_RawPosition = (sint16)IfxGpt12_T2_getTimerValue(gpt12);

	return Encoder_RawPosition;
}


void EncoderReset(void)
{
    Ifx_GPT12 *gpt12=&MODULE_GPT120;
    IfxGpt12_T2_setTimerValue(gpt12, 0);
}

#define K_PULSES_TO_RPM_FACTOR  (5.86)
/****************************************************************************************************************************************
 * Tips:
 *  1. If more than one circle in 10ms, the RPM should big than 1r/0.01s=100 r/s(6000 rpm)
 *  In fact the motor max speed is not more than 6000 rpm,
 *  So the counts value should limited in a circle.
 * 2.Acc.to 1 circle = 1024 count,there is 1 rpm  = 1024 counts/60s = 1024 counts/(60x100 (10ms)) = 1/(5.859375) ~= 1/5.86  counts/(10ms)
 *  That means if 1 count received in 10ms,then is equal to 1/(1/5.86) = 5.86 rpm
 *  (That is what the define the factor macro K_PULSES_TO_RPM_FACTOR is).
 *
 *****************************************************************************************************************************************/
uint16 g_absMotSpeed;

uint16 absMotSpeed_raw,old_absMotSpeed_raw;
uint8 cycle_speed;
IFX_EXTERN sint16 g_TotalCountAcircle;
void  PreStartUp_UpdateSpeed(void)   /* 10ms task*/
{
   static sint16 DeltaPositons_10ms = 0;
   static sint16 updateEncoder_RawPosition = 0;
   static sint16 old_updateEncoder_RawPosition = 0;
   updateEncoder_RawPosition = Encoder_RawPosition;

   if(updateEncoder_RawPosition +g_TotalCountAcircle*cycle_speed> old_updateEncoder_RawPosition)
   {
       g_bldc.rot_dir_fbk = K_ROT_DIR_FBK_CW;
   }
   else if(updateEncoder_RawPosition+g_TotalCountAcircle*cycle_speed < old_updateEncoder_RawPosition)
   {
       g_bldc.rot_dir_fbk = K_ROT_DIR_FBK_CCW;
   }
   else if (Encoder_RawPosition == Encoder_RawPositionOld)
   {
       g_bldc.rot_dir_fbk = K_ROT_DIR_FBK_STOP;
   }

   if( g_bldc.rot_dir_fbk == K_ROT_DIR_FBK_CW)   /*CW,Position is positive value*/
   {
       if(updateEncoder_RawPosition < 0)
       {
           updateEncoder_RawPosition +=K_TOTAL_COUNTS_PER_MECH_ROTATION;
       }
       DeltaPositons_10ms =(updateEncoder_RawPosition+g_TotalCountAcircle*cycle_speed)- old_updateEncoder_RawPosition;

   }
   else if( g_bldc.rot_dir_fbk == K_ROT_DIR_FBK_CCW) /** CCW, Position is negative value**/
   {
       if(Encoder_RawPosition > 0)
       {
           Encoder_RawPosition -=K_TOTAL_COUNTS_PER_MECH_ROTATION;
       }

       DeltaPositons_10ms =  old_updateEncoder_RawPosition-(updateEncoder_RawPosition+g_TotalCountAcircle*cycle_speed);
   }
   else
   {
       DeltaPositons_10ms = 0; /* Do nothing because of unknown rotation direction */
   }
   g_bldc.second_speed = (uint16)((float)DeltaPositons_10ms* K_PULSES_TO_RPM_FACTOR);

   cycle_speed = 0;
   old_updateEncoder_RawPosition = updateEncoder_RawPosition;
}

void EncoderUpdateSpeed(void)   /* 10ms task*/
{
    static sint16 DeltaPositons = 0;

    if(K_ROT_DIR_CW == g_bldc.rot_dir)   /*CW,Position is positive value*/
    {
        if(Encoder_RawPosition < 0)
        {
           Encoder_RawPosition +=K_TOTAL_COUNTS_PER_MECH_ROTATION;
        }

        if(Encoder_RawPosition >=Encoder_RawPositionOld)
        {
            DeltaPositons = Encoder_RawPosition - Encoder_RawPositionOld;
        }
        else
        {
            DeltaPositons = K_TOTAL_COUNTS_PER_MECH_ROTATION - (Encoder_RawPositionOld - Encoder_RawPosition);
        }
    }
    else if(K_ROT_DIR_CCW == g_bldc.rot_dir) /** CCW, Position is negative value**/
    {
        if(Encoder_RawPosition > 0)
        {
            Encoder_RawPosition -=K_TOTAL_COUNTS_PER_MECH_ROTATION;
        }

        if(Encoder_RawPosition <= Encoder_RawPositionOld)
        {
            DeltaPositons = Encoder_RawPosition - Encoder_RawPositionOld;
        }
        else
        {
            DeltaPositons =-(K_TOTAL_COUNTS_PER_MECH_ROTATION + (Encoder_RawPositionOld - Encoder_RawPosition));
        }

    }
    else
    {
        /* Do nothing because of unknown rotation direction */
    }

    g_bldc.RPM_s16MechSpeed = (sint16)((float)DeltaPositons* K_PULSES_TO_RPM_FACTOR);

    Encoder_RawPositionOld = Encoder_RawPosition;

    if(g_bldc.RPM_s16MechSpeed > 0)   /* calculate the absolute speed*/
    {
        absMotSpeed_raw = g_bldc.RPM_s16MechSpeed;
    }
    else
    {
        absMotSpeed_raw =0x00 - (g_bldc.RPM_s16MechSpeed);
    }

    {
        static uint16 speed_filter_array[10]={0};

        uint32 speed_sum = 0;

        speed_filter_array[0]=speed_filter_array[1];
        speed_filter_array[1]=speed_filter_array[2];
        speed_filter_array[2]=speed_filter_array[3];
        speed_filter_array[3]=speed_filter_array[4];
        speed_filter_array[4]=speed_filter_array[5];
        speed_filter_array[5]=speed_filter_array[6];
        speed_filter_array[6]=speed_filter_array[7];
        speed_filter_array[7]=speed_filter_array[8];
        speed_filter_array[8]=speed_filter_array[9];

        speed_filter_array[9]=absMotSpeed_raw;

        for(uint8 i=0;i<10;i++)
        {
            speed_sum+=speed_filter_array[i];
        }

//        g_absMotSpeed =((uint16)((uint16)(speed_sum/10)/10))*10;
        g_absMotSpeed =(uint16)(speed_sum/10);
        if(g_bldc.state == MOTOR_STATE_STOP)
        {
            g_absMotSpeed = g_bldc.second_speed;
        }
    }
}

enMotor_RotationDirState_fbk RotDir = K_ROT_DIR_FBK_STOP;
enMotor_RotationDirState_fbk  RotDirectionFeedback(boolean pinA_Status, boolean pinB_Status)
{
   static boolean pinALastStatus = 0;
   static int CW_pluse_count = 0;
   static int CCW_pluse_count = 0;

   if(pinA_Status == TRUE)
   {
       if(pinB_Status != pinA_Status)
       {
//           CW_pluse_count++;
           RotDir = K_ROT_DIR_FBK_CW;
       }
       else
       {
//           CCW_pluse_count++;
           RotDir = K_ROT_DIR_FBK_CCW;
       }
   }

  pinALastStatus = pinA_Status;

//  if(CW_pluse_count>4)
//  {
//      RotDir = K_ROT_DIR_FBK_CW;
//      CW_pluse_count = 0;
//      CCW_pluse_count = 0;
//  }
//  if(CCW_pluse_count>4)
//  {
//      RotDir = K_ROT_DIR_FBK_CCW;
//      CW_pluse_count = 0;
//      CCW_pluse_count = 0;
//  }

   return RotDir;
}

enum rotaryEncoderDirection
{
    clockWise=0,
    antiClockWise,
    stop
};

enum rotaryEncoderDirection getRotaryEncoderDirection(boolean pinACurrentStatus, boolean pinBCurrentStatus)
{
    enum rotaryEncoderDirection currentDir = stop;
    static boolean pinALastStatus = 0;
    static int clockWiseRotaryEncoderCounter=0;
    static int  antiClockWiseRotaryEncoderCounter=0;

    // If last and current state of pinA are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (pinACurrentStatus != pinALastStatus && pinACurrentStatus == 1)
    {
        // If the pinB state is different than the pinA state then
        // the encoder is rotating CW
        if (pinBCurrentStatus != pinACurrentStatus)
        {
            clockWiseRotaryEncoderCounter++;
        }
        else
        {
            // Encoder is rotating CCW
            antiClockWiseRotaryEncoderCounter++;
        }
    }

    // Remember last pinA status
    pinALastStatus = pinACurrentStatus;

    if(clockWiseRotaryEncoderCounter >=4)
    {
        clockWiseRotaryEncoderCounter = 0;
        antiClockWiseRotaryEncoderCounter = 0;
        currentDir = K_ROT_DIR_FBK_CW;
    }
    else if (antiClockWiseRotaryEncoderCounter>=4)
    {
        clockWiseRotaryEncoderCounter = 0;
        antiClockWiseRotaryEncoderCounter = 0;
        currentDir = K_ROT_DIR_FBK_CCW;
    }
    return currentDir;
}





