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
//---------------------------------------------------------------------------
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
    }
    else
    {
        result = velocityControl->pi.uk;
    }
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
}
