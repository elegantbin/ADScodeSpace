/*
 * AppTaskFu.c
 *
 *  Created on: 19.09.2013
 *
 */


#include "Vadc_vit.h"
#include "AppScheduler.h"
#include "AppTimerOS.h"
#include "MULTICAN_FD.h"
#include "MultiCan_DebugCanMsg.h"
#include "MultiCan_CanfdMsg.h"
#include "GTM_TOM_3_Phase_Inverter_PWM.h"
#include "IfxVadc_Adc.h"
#include "AppTorqueControl.h"
#include "App_VelocityControl.h"
#include "SPI_ENCODER.h"
#include <GPT12_Encoder.h>
#include "Vadc_LowPassPT1.h"
#include "Torque_Calibration.h"

void appTaskfu_1ms(void)
{

//     DebugCanMsg_transmitCurrentMsg();
      DebugCanMsg_transimitNormalMsg();
      VelocityControl_Task();
}


void appTaskfu_10ms(void)
{


}


void appTaskfu_100ms(void)
{
    Actual_Torque_Calculation();
}

void appTaskfu_200ms(void)
{

    Re_initMultican();
//    Current_Iq_Incr();

}


void appTaskfu_init(void)
{
    // Initialize Timer for OS Scheduler
    AppTimerOs_interruptsInit();
    AppScheduler_init();

    //Initialize TorqueControl
    AppTorqueControl_initControl(&g_motor, 20000);

    //Initialize VelocityControl
    VelocityControl_Init(&g_velocityControl);

    //Init MultiCan
    initMultican();

    // Initialize PWM Driver
    initGtmTomPwm();

    Vadc_VIT_init();

    IfxCpu_enableInterrupts();

    GPT12_EncoderInit();

    SpiEncoder_init();

}




