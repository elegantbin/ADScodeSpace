#include "PositionControl.h"
#include <EncoderGpt12.h>
#include "AppIsr.h"
#include "CommutationControl.h"
#include "MotorMgtSwc.h"


uint8  cycle_total;
sint32 error_position;
uint16 Position_Control(sint16 ref_position,sint16 raw_position)
{
    uint16 uk;
    float Kp = 0.01;
    uint16 upper = 80;
    uint16 lower = 40;

    if( K_ROT_DIR_CW == g_bldc.rot_dir)
    {
       error_position = (ref_position+CYCLE_PLUSE*CYCLE_EXTRA)-(raw_position+cycle_total*CYCLE_PLUSE);
       uk = Kp*error_position;
    }
    else if( K_ROT_DIR_CCW == g_bldc.rot_dir)
    {
        raw_position = raw_position-CYCLE_PLUSE;
        error_position = (raw_position-cycle_total*CYCLE_PLUSE)-(ref_position-CYCLE_PLUSE*CYCLE_EXTRA);
        uk = Kp*error_position;
    }
/*when the position error is smaller than 20 plus ,the motor enters the holding_position state*/
    if(error_position<20)
    {
        g_bldc.state = MOTOR_STATE_HOLDING_POSITION;
        uk=0;
    }
    else
    {
        g_bldc.state = MOTOR_STATE_RUNNING;
    }

    if(uk>upper)
    {
        uk=upper;
    }
    else if(uk<lower)
    {
        uk=lower;
    }

    return uk;

}
