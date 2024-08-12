/*
 * AppTaskFu.c
 *
 *  Created on: 19.09.2013
 *
 */


#include <EncoderGpt12.h>

#include "AppScheduler.h"
#include "AppTimerOS.h"
#include "MultiCan.h"
#include "PosIf.h"
#include "DIPorts.h"
#include "GTM_ATOM_PWM_6Step.h"
#include "CommutationPoint.h"
#include "CommutationControl.h"
#include "ADC.h"
#include "SPI_ENCODER.h"
#include "IfxVadc_Adc.h"
#include "dutylimit.h"
#include <BackgroundADC.h>
#include <CurrentADC.h>
#include <TempDetect.h>
#include "MULTICAN_FD.h"
#include "TorqueControl.h"
#include <DataFlash_ZeroOffest.h>
#include "TOM_ISR.h"

void appTaskfu_cyclic(void)
{
    //PortABZ_StateCheck();
}



void appTaskfu_1ms(void)
{
    CommutationControl_6StepStart();

    EncoderUpdatePosition();

    MotorPhaseCurrent_Check();

//    updatePWMDutyStartup();  //startup fast

    Current_updateDuty();
//    updatePWMDutyRunning();

}

void appTaskfu_2ms(void)
{

    transmitCanDebugMessage();
    transmitCanMessage();
}


void appTaskfu_10ms(void)
{
    MotorRPM_Check();
//    RealPos_ValidCheck();

    SpeedPID_updateDuty();

    Position_updateDuty();

    DutyLmit_Max(g_absMotSpeed);


    CurrentOffsetDetect();

//    Current_updateDuty();
    updatePWMDutyRunning(); //normally update PWM duty
    updatePWMDutyStartup();//startup slowly
}


void appTaskfu_100ms(void)
{
//    Current_updateDuty();
//    updatePWMDutyRunning();
}


void appTaskfu_200ms(void)
{
    Temp_Voltage_DetectScan();
    Motor_VlotageBus_Check();
    MotorPlateTemp_Detect();
    Over_Temperature_Detect();

    Torque_Calculate();
    Torque_To_Current();

    Re_initMultican();
}


void appTaskfu_init(void)
{

    IfxCpu_disableInterrupts();

    /* Initialize Timer for OS Scheduler*/
    AppTimerOs_interruptsInit();
    AppScheduler_init();

    initMultican();

    initGtmATomPwm_6Step();

    EncoderInit();

    Multi_ADC_init();

    InitCurrentADC_BCMode();

    SpiEncoder_init();

    DataFlash_CalibrationInit();

//    initGtmTom1_Timer();

    IfxCpu_enableInterrupts();

    SPIEncoderInitPosition();
}








