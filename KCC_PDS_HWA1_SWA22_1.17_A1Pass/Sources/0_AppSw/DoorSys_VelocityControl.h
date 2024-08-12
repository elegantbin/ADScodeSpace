/**
 * @file Doorsys_VelocityControl.h
 * @brief Application implementation: Control.
 *
 *
 * $Revision: 327 $
 * $Date: 2010-07-09 11:50:37 +0200 (ven., 09 juil. 2010) $
 *
 * @defgroup app_velocity_control Velocity control
 *
 * This module implements the velocity control object.
 * @image html "VelocityControl.gif"
 * @ingroup application
 *
 */

/** @page page_src_APP_VELOCITY_CONTROL_H Velocity control module
 *
 * The velocity control module is controlling the speed of the motor. This function
 * can be enabled / disabled.
 *
 * @anchor figure_torque_control
 * @image html "VelocityControl.gif" "Velocity control"
 *
 * Signal definition:
 *     - Ref speed  : Motor mechanical reference speed in radian per second (rad/s)
 *     - Actual speed   : Measured motor speed in radian per second (rad/s)
 *     - Enable : Speed control enable / disable input
 *     - Reset  : Reset the controller internal state
 *     - Kp, Ki : PI controller parameters for the speed controller
 *     - Out min, max   : PI controller output limits
 *     - Iq ref : Quadrature reference current in ampere (A), input of  the torque
 *       control module
 *
 * @sourcecode @ref app_velocity_control
 *
 * @prevnext{page_src_APP_POSITION_ACQUISITION_H,page_src_APP_TORQUE_CONTROL_H}
 */

#if !defined(APP_VELOCITY_CONTROL_H)
#define APP_VELOCITY_CONTROL_H

//---------------------------------------------------------------------------
#include <Pi.h>
//---------------------------------------------------------------------------

/** @brief Velocity control object.
 */
typedef struct
{
    TPic pi;                           /**< @brief Speed PI controller */
    float32 speed;                    /**< @brief Speed acquired from position sensor */
    float32 ref;                      /**< @brief Speed reference in rad/s */
    float32 max;                      /**< @brief Absolute value of the max allowed speed reference in rad/s. Range=[0, +INF] */
    boolean enabled;                      /**< @brief Speed control enable flag. TRUE: the speed control is enabled. FALSE the speed control is disabled */
} VelocityControl;


extern VelocityControl g_velocityControl;

extern int16_t g_i16DoorDutyPercent;
extern int16_t g_i16DoorDutyPercent_1;

void VelocityControl_Init(void);
void VelocityControl_Task(void);
void VelocityControl_close_adjust_curve(void);
void VelocityControl_open_adjust_curve (void);
void VelocityControl_close_adjust_curve1(void);
void VelocityControl_open_adjust_curve1(void);


float32 VelocityControl_Do(VelocityControl *velocityControl, float32 speed);

/** @brief Reset the velocity controller.
 *
 * @param VelocityControl Specifies the velocity control object.
 *
 * @return none
 * @ingroup app_velocity_control
 */
inline void VelocityControl_Reset(VelocityControl *velocityControl)
{
    velocityControl->ref = 0;
    Pic_Reset(&velocityControl->pi);
}

/** @brief Enable the velocity controller.
 *
 * @param VelocityControl Specifies the velocity control object.
 *
 * @return none
 * @ingroup app_velocity_control
 */
inline void VelocityControl_Enable(VelocityControl *velocityControl)
{
    velocityControl->enabled = TRUE;
}
/** @brief Return the status of the velocity controller (Enabled / Disabled).
 *
 * @param VelocityControl Specifies the velocity control object.
 *
 * @retval TRUE Returns TRUE if the velocity controller is enabled
 * @retval FALSE Returns FALSE if the velocity controller is disabled
 * @ingroup app_velocity_control
 */
inline boolean VelocityControl_IsEnabled(VelocityControl *velocityControl)
{
    return velocityControl->enabled;
}
/** @brief Disable the velocity controller.
 *
 * @param VelocityControl Specifies the velocity control object.
 *
 * @return none
 * @ingroup app_velocity_control
 */
inline void VelocityControl_Disable(VelocityControl *velocityControl)
{
    velocityControl->enabled = FALSE;
    VelocityControl_Reset(velocityControl);
}

/** @brief Reset the velocity controller limit flag.
 *
 * @param VelocityControl Specifies the velocity control object.
 *
 * @return none
 * @ingroup app_velocity_control
 */
inline void VelocityControl_ResetLimitFlag(VelocityControl *velocityControl)
{
    Pic_ResetLimitsHit(&velocityControl->pi);
}

/** @brief Set the velocity controller limits.
 *
 * @param VelocityControl Specifies the velocity control object.
 * @param Min Specifies the PI controller min value.
 * @param Max Specifies the PI controller max value.
 *
 * @return none
 * @see Pic_SetLimit()
 * @ingroup app_velocity_control
 */
inline void VelocityControl_SetLimit(VelocityControl *velocityControl, float32 min, float32 max)
{
    Pic_SetLimit(&velocityControl->pi, min, max);
}
/** @brief Set the velocity controller max ref speed.
 *
 * @param VelocityControl Specifies the velocity control object.
 * @param Max Specifies the velocity controller max ref speed value.
 *
 * @return none
 * @ingroup app_velocity_control
 */
inline void VelocityControl_SetMaxSpeed(VelocityControl *velocityControl, float32 max)
{
    velocityControl->max = max;
}

/** @brief Set the velocity controller reference speed.
 *
 * @param VelocityControl Specifies the velocity control object.
 * @param Speed Specifies the velocity controller reference speed value.
 *
 * @retval TRUE Returns TRUE if the reference speed could be set
 * @retval FALSE Returns FALSE if the reference speed is out of range
 * @ingroup app_velocity_control
 */
inline boolean VelocityControl_SetRefSpeed(VelocityControl *velocityControl, float32 speed)
{
    boolean result;
    if ((__absf(speed)) > (velocityControl->max))
    {  
        result = FALSE;
    }
    else
    {
        velocityControl->ref = speed;
        result = TRUE;
    }
    return result;
}

/** @brief Return the velocity controller max ref speed.
 *
 * @param VelocityControl Specifies the velocity control object.
 *
 * @return Return the max allowed ref speed
 * @ingroup app_velocity_control
 */
inline float32 VelocityControl_GetMaxSpeed(VelocityControl *velocityControl)
{
    return velocityControl->max;
}
/** @brief Return the velocity controller ref speed.
 *
 * @param VelocityControl Specifies the velocity control object.
 *
 * @return Return the ref speed
 * @ingroup app_velocity_control
 */
inline float32 VelocityControl_GetRefSpeed(VelocityControl *velocityControl)
{
    return velocityControl->ref;
}
/** @brief Return a copy of the velocity controller PI controller.
 *
 * @param VelocityControl Specifies the velocity control object.
 * @param Pi Specifies the location where the copy must be saved.
 *
 * @return Return the max allowed ref speed
 * @ingroup app_velocity_control
 */
inline void VelocityControl_GetPi(VelocityControl *velocityControl, TPic *pi)
{
    *pi = velocityControl->pi;
}
/** @brief Set the velocity controller PI parameters
 *
 * @param VelocityControl Specifies the velocity control object.
 * @param Kp Specifies the PI controller Kp value.
 * @param Ki Specifies the PI controller Ki value.
 * @param Period Specifies PI controller period time in seconds.
 * @param ShiftCoef position of the fix point for the A0 and A1 parameters. Range = [-256, 255]. In case TStdReal type is float32, this parameter is ignored
 * @param ShiftResult Shift done on the result for fixpoint calculation. Range = [-32, 31]. In case TStdReal type is float32, this parameter is ignored
 *
 * @return None.
 * @see Pic_SetKpKi_StdReal()
 * @ingroup app_velocity_control
 */
inline void VelocityControl_SetKpKi(VelocityControl *velocityControl, float32 kp, float32 ki, float32 period, sint32 shiftCoef, sint8 shiftResult)
{
    Pic_SetKpKi_StdReal(&velocityControl->pi, kp, ki, period, shiftCoef, shiftResult);
}

inline float32 VelocityControl_GetSpeed(VelocityControl *velocityControl)
{
    return velocityControl->speed;
}
/** @brief Return a copy of the velocity controller PI controller.
 *
 * @param VelocityControl Specifies the velocity control object.
 * @param Pi Specifies the location where the copy must be saved.
 *
 * @return Return the max allowed ref speed
 * @ingroup app_velocity_control
 */



//---------------------------------------------------------------------------
#endif
