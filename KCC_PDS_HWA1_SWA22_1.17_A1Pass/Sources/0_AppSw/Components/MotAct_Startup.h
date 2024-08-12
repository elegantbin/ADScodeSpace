

#ifndef __DUTY_STARTUP_CURVE_H__
#define __DUTY_STARTUP_CURVE_H__

#include "OsTypedefs.h"

#define STARTUP_TIMETICKS_MAX (STARTUP_TIME_PHASE_7)

#define STARTUP_TIME_PHASE_0 ((1)*2)
#define STARTUP_TIME_PHASE_1 ((15)*2)
#define STARTUP_TIME_PHASE_2 ((30)*2)
#define STARTUP_TIME_PHASE_3 ((35)*2)
#define STARTUP_TIME_PHASE_4 ((65)*2)
#define STARTUP_TIME_PHASE_5 ((70)*2)
#define STARTUP_TIME_PHASE_6 ((85)*2)
#define STARTUP_TIME_PHASE_7 ((100)*2)


/****************************************/
#define OPEN_STARTUP_DUTY_INIT  (20)
#define CLOSE_STARTUP_DUTY_INIT  (20)
#define STARTUP_DUTY_INIT (20)

/****************************************/



#define OPEN_STARTUP_DUTY_DELTA_0 (1)
#define OPEN_STARTUP_DUTY_DELTA_1 (2)
#define OPEN_STARTUP_DUTY_DELTA_2 (2)
#define OPEN_STARTUP_DUTY_DELTA_3 (3)
#define OPEN_STARTUP_DUTY_DELTA_4 (2)
#define OPEN_STARTUP_DUTY_DELTA_5 (1)
#define OPEN_STARTUP_DUTY_DELTA_6 (1)
#define OPEN_STARTUP_DUTY_DELTA_7 (1)

#define CLOSE_STARTUP_DUTY_DELTA_0 (2)
#define CLOSE_STARTUP_DUTY_DELTA_1 (3)
#define CLOSE_STARTUP_DUTY_DELTA_2 (3)
#define CLOSE_STARTUP_DUTY_DELTA_3 (4)
#define CLOSE_STARTUP_DUTY_DELTA_4 (5)
#define CLOSE_STARTUP_DUTY_DELTA_5 (4)
#define CLOSE_STARTUP_DUTY_DELTA_6 (3)
#define CLOSE_STARTUP_DUTY_DELTA_7 (2)




#define K_SCALE_FACTOR   (10)

void MotorActator_StartUp(void);
void MotorActator_StartupCurveReset(void);


#endif /* __DUTY_STARTUP_CURVE_H__  EndDef*/
