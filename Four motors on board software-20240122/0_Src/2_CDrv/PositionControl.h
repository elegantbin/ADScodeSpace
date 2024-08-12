
#ifndef POSITION_CONTROL_H_
#define POSITION_CONTROL_H_

#include "Ifx_Types.h"

#define        CYCLE_ANGLE        (360.0)    /*the one cycle is 360бу*/
#define        CYCLE_PLUSE        (1024)     /*the one cycle is 1024 plus*/
#define        CYCLE_EXTRA        (40)       /* make the motor reach a low speed by running about 40 cycles or more*/


extern  uint8 cycle_total;
extern  sint32 error_position;

uint16 Position_Control(sint16 ref_position,sint16 raw_position);

#endif /* POSITION_PI_H_ */
