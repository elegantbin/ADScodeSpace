/*
 * MotorMgtSwc.c
 *
 *  Created on: 2024Äê1ÔÂ5ÈÕ
 *      Author: Brook.Wu
 */
#include "Vadc_VIT.h"
#include "AppTorquecontrol.h"
#include "MotorMgtSwc.h"

void PhaseCurrent_Check(void)
{
    if(g_motor.analogCurrentInputs.currentA->limits.status != AppVadc_LimitsStatus_Ok||
       g_motor.analogCurrentInputs.currentB->limits.status != AppVadc_LimitsStatus_Ok||
       g_motor.analogCurrentInputs.currentC->limits.status != AppVadc_LimitsStatus_Ok )
    {
        g_motor.control.hadEmergency = TRUE;
        g_motor.diag.u32DiagCode = MOTOR_DIAG_CODE_CURRENT_FAIL;
    }
    else
    {

    }
}
