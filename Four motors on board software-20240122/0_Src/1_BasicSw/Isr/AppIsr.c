/**
 * \file AppIsr.c
 * \brief Application interrupts.
 *
 * \license
 * You can use this file under the terms of the IFX License.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * IFX License for more details (IFX_License.txt).
 *
 * This file may be used, copied, and distributed, with or without
 * modification, provided that all copyright notices are retained;
 * that all modifications to this file are prominently noted in the
 * modified file; and that this paragraph is not modified.
 *
 * \copyright Copyright (C) 2012 Infineon Technologies AG
 *
 *
 * $Revision: 559 $
 * $Date: 2013-01-16 14:16:15 +0100 (Wed, 16 Jan 2013) $
 *
 */
//________________________________________________________________________________________
// INCLUDES

#include "AppIsr.h"
#include "AppTorqueControl.h"
#include "ConfigurationIsr.h"
#include "Ifx_Cfg_FocControl.h"
#include "EncoderGpt12.h"
#include "MotorMgtSwc.h"
#include "GTM_ATOM_PWM_6Step.h"
#include "PositionControl.h"
/* ---------------------------------------------------------------------------*/

volatile sint16 g_TotalCountAcircle = 0;

IFX_INLINE void TotalCountsPerCycle_ValidCheck(void);
//________________________________________________________________________________________
// DEFINES

//________________________________________________________________________________________
// FUNCTION PROTOTYPES
/** \addtogroup application
 * \{ */
/** \} */
#if (Resolver == SensorMode)
IFX_INTERRUPT(ISR_RdcDs_0, 0, INTERRUPT_RDC_DS_0);
#else
IFX_INTERRUPT(ISR_Encoder_Gpt12_T4, 0, INTERRUPT_ENCODER_GPT12_T4);

IFX_INTERRUPT(ISR_Encoder_Gpt12_T2, 0, INTERRUPT_ENCODER_GPT12_T2);
#endif
//________________________________________________________________________________________
// INTERRUPT SERVICE ROUTINES

#if (Resolver == SensorMode)
/** \brief Handle the DSADC resolver interrupt (\ref IfxDsadc_Rdc) */
void ISR_RdcDs_0(void)
{
    IfxDsadc_Rdc* rdc = &g_motor.sensors.rdcDsadc;
    IfxDsadc_Rdc_updateStep1(rdc);
}
#else


/** \brief Handle the encoder zero interrupt (priority = \ref ISR_PRIORITY(INTERRUPT_ENCODER_GPT12)).
 *
 * This interrupt is raised each time the encoder zero event occurs.
 */
//IFX_EXTERN void blinkLED1(void);
IFX_EXTERN volatile uint8 b_ZeroDetected;

void ISR_Encoder_Gpt12_T4(void)
{
    //IfxGpt12_IncrEnc_isrOnZeroPulse(&g_motor.sensors.encoder);
    //IfxStdIf_Pos_onZeroIrq(&g_motor.sensors.encoder);

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
    if((b_PulseFilter)&&(IfxPort_getPinState(ENCODER_PINZ.pin.port, ENCODER_PINZ.pin.pinIndex)==TRUE))
    {

       g_TotalCountAcircle=EncoderUpdatePosition();

       if (b_ZeroDetected)//start validcheck when the second zero pulse  detected
       {
           TotalCountsPerCycle_ValidCheck();
       }

       b_ZeroDetected=TRUE;
       EncoderReset();

       cycle_total++;
       cycle_speed++;
//       g_bldc.testcount = 0;

    }

    __enable();
}

void ISR_Encoder_Gpt12_T2(void)
{
    Ifx__NOP(1);
    g_bldc.testcount++;
//    g_bldc.rot_dir_fbk =  RotDirectionFeedback(IfxPort_getPinState(ENCODER_PINA.pin.port, ENCODER_PINA.pin.pinIndex),
//                                                  IfxPort_getPinState(ENCODER_PINB.pin.port, ENCODER_PINB.pin.pinIndex));

    __enable();
}

#define K_TOTAL_COUNTS_PER_CYCLE_MAX  (1200)
#define K_TOTAL_COUNTS_PER_CYCLE_MIN  (900)
IFX_INLINE void TotalCountsPerCycle_ValidCheck(void)
{
    uint32 absTotalCountAcircle = 0;
    volatile uint8  b_TotalCountsPerCycleValideCheck =0;



    if(MOTOR_STATE_RUNNING == g_bldc.state)
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
       if(absTotalCountAcircle > K_TOTAL_COUNTS_PER_CYCLE_MAX||
               absTotalCountAcircle<K_TOTAL_COUNTS_PER_CYCLE_MIN)
        {
           b_TotalCountsPerCycleValideCheck = TRUE;

           g_bldc.state = MOTOR_STATE_FAIL;
           CommutationDriver_Stop();

           g_bldc.u32DiagCode |= MOTOR_DIAG_CODE_UPDATAPOSITION_FAIL;
        }
       }
    }
}



#endif
