/**
 * @file app_VelocityControl.c
 * @brief Application implementation: Control.
 * @license
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
 * @copyright Copyright (C) 2009, 2008 Infineon Technologies AG
 *
 *
 * $Revision: 327 $
 * $Date: 2010-07-09 11:50:37 +0200 (ven., 09 juil. 2010) $
 *
 */

//---------------------------------------------------------------------------
#include "App_VelocityControl.h"
#include "AppTorqueControl.h"
#include "Ifx_cfg_VelocityControl.h"

//---------------------------------------------------------------------------


VelocityControl g_velocityControl;

/** @brief Execute the speed PI controller
 *
 * @param VelocityControl Specifies the velocity control object.
 * @param Speed Specifies the current speed.
 *
 * @return the speed controller output.
 * @see Pic()
 * @ingroup app_velocity_control
 */
float32 VelocityControl_Do(VelocityControl *velocityControl, float32 speed)
{
	float32 result;
    if (velocityControl->enabled != FALSE)
    {
        result = Pic_Do(&velocityControl->pi, velocityControl->ref - speed);
//        result = Speed_PI(&velocityControl->pi, velocityControl->ref - speed);
    }
    else
    {
        result = velocityControl->pi.uk;
    }
    return result;
}

float32 FeedforwardController(VelocityControl *velocityControl, float32 speed)
{
    float32 result;
    static float32 last_speed = 0;
    result=0.005*(speed-last_speed);
    last_speed = speed;
    return result;
}
/** @brief Initialize the velocity control object
 *
 * @param VelocityControl Specifies the velocity control object.
 *
 * @return None.
 * @see Pic_Init()
 * @ingroup app_velocity_control
 */
void VelocityControl_Init(VelocityControl *velocityControl)
{
    Pic_Init(&velocityControl->pi);
//    SpeedPI_Init(&velocityControl->pi);
    VelocityControl_Disable(velocityControl);

    VelocityControl_SetKpKi(velocityControl, VELOCITY_CONTROL_KP, VELOCITY_CONTROL_KI, VELOCITY_CONTROL_PERIOD,0, 0);

    VelocityControl_SetLimit(velocityControl, VELOCITY_CONTROL_MIN, VELOCITY_CONTROL_MAX);

    VelocityControl_SetMaxSpeed(velocityControl, VELOCITY_CONTROL_MAX_RPM);
}


void VelocityControl_Task(void)      /* 1ms or 10ms task*/
{
    static float32 last_result = 0;

    if(VelocityControl_IsEnabled(&g_velocityControl))
    {
        // set reference Speed
        VelocityControl_SetRefSpeed(&g_velocityControl, g_velocityControl.ref_receive);

        if(g_velocityControl.ref > 2500)
        {
            VelocityControl_SetKpKi(&g_velocityControl, VELOCITY_CONTROL_KP_HIGH_SPEED, VELOCITY_CONTROL_KI_HIGH_SPEED, VELOCITY_CONTROL_PERIOD,0, 0);
        }
        else
        {
            VelocityControl_SetKpKi(&g_velocityControl, VELOCITY_CONTROL_KP, VELOCITY_CONTROL_KI, VELOCITY_CONTROL_PERIOD,0, 0);
        }

        /*Speed PI controller, the output is (0,1) */
        float32 result = VelocityControl_Do(&g_velocityControl, g_motor.speed);

        /*calculate the Iq_ref*/
        result *=Foc_GetIqLimit(&g_motor.control.foc);

        /* limit the Iq increase speed*/
//        if((result-last_result) > 50)
//        {
//            result += 50;
//        }
//        else if(result-last_result < -50)
//        {
//            result -= 50;
//        }
//        else
//        {
//
//        }
//        last_result = result;

        /*set Iq_ref */
        Foc_SetIq(&g_motor.control.foc, result);
    }
}
