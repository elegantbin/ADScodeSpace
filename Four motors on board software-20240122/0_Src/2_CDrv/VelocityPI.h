

#ifndef VELOCITY_PI_H_
#define VELOCITY_PI_H_

#include "Cpu/Std/Ifx_Types.h"
#include "IfxStdIf.h"

typedef struct
{
    float32 kp;                        /**< \brief A0 parameter */
    float32 ki;                        /**< \brief A1 parameter */
    float32 uk;                        /**< \brief high resolution PI output value高分辨率PI输出值 */
    float32 ik;                        /**< \brief PI last error value */
    float32 lower;                     /**< \brief PI min limit */
    float32 upper;                     /**< \brief PI max limit */
    uint8   hitLimits;                 /**< \brief PI limit hit flag PI极限到达标志 */
}  velocity_Pic;

typedef struct
{
    velocity_Pic pic;      /**< \brief Speed PI controller */
    sint16     speed_ref;      /**< \brief Speed reference in rad/s */
    sint16     value;    /**< \brief Actual speed in rad/s */
    sint16     refLimit; /**< \brief Absolute value of the max allowed speed reference in rad/s. Range=[0, +INF] */
    boolean     enabled;  /**< \brief Speed control enable flag. TRUE: the velocity control is enabled. FALSE the velocity control is disabled */
    float32     period;   /**< \brief Speed controller sample period in seconds. */
} VelocityCtrl;
void Pic_param_init(void);
float32 Pic_controlstep(velocity_Pic *pic, sint16 Input);
float32 Pic_VelocityControl(VelocityCtrl *vc, uint16 raw_speed);
float32 VelocityPIDControl(uint16 speed_ref,uint16 raw_speed);
//extern float32 delta_uk;

#endif /* VELOCITY_PI_H_ */
