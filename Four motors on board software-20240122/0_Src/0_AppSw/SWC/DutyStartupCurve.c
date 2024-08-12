
#include "DutyStartupCurve.h"

#define ACC_DIRECT_MODE (0)
#define ACC_S_CURVE_MODE (1)
#define STARTUP_ACC_MODE (ACC_S_CURVE_MODE)

#define STARTUP_PARA_GROUP_BEFORE_20230927     (20230101)
#define STARTUP_PARA_GROUP_20230927            (20230927)

#define STARTUP_PARA_GROUP  ( STARTUP_PARA_GROUP_BEFORE_20230927 )
#if(STARTUP_PARA_GROUP==STARTUP_PARA_GROUP_BEFORE_20230927)

#define STARTUP_TIMETICKS_MAX (100*2)

#define STARTUP_TIME_PHASE_0 (1*2)
#define STARTUP_TIME_PHASE_1 (15*2)
#define STARTUP_TIME_PHASE_2 (30*2)
#define STARTUP_TIME_PHASE_3 (35*2)
#define STARTUP_TIME_PHASE_4 (65*2)
#define STARTUP_TIME_PHASE_5 (70*2)
#define STARTUP_TIME_PHASE_6 (85*2)
#define STARTUP_TIME_PHASE_7 (100*2)


#define STARTUP_DUTY_DELTA (10)
#define STARTUP_DUTY_INIT  (800)

#define STARTUP_DUTY_DELTA_0 (0)
#define STARTUP_DUTY_DELTA_1 (20)
#define STARTUP_DUTY_DELTA_2 (30)
#define STARTUP_DUTY_DELTA_3 (40)
#define STARTUP_DUTY_DELTA_4 (50)
#define STARTUP_DUTY_DELTA_5 (40)
#define STARTUP_DUTY_DELTA_6 (30)
#define STARTUP_DUTY_DELTA_7 (20)

#elif(STARTUP_PARA_GROUP==STARTUP_PARA_GROUP_20230927)

#define STARTUP_TIMETICKS_MAX (100*1)

#define STARTUP_TIME_PHASE_0 (1)
#define STARTUP_TIME_PHASE_1 (15)
#define STARTUP_TIME_PHASE_2 (30)
#define STARTUP_TIME_PHASE_3 (35)
#define STARTUP_TIME_PHASE_4 (65)
#define STARTUP_TIME_PHASE_5 (70)
#define STARTUP_TIME_PHASE_6 (85)
#define STARTUP_TIME_PHASE_7 (100)


#define STARTUP_DUTY_DELTA (10)
#define STARTUP_DUTY_INIT  (800)

#define STARTUP_DUTY_DELTA_0 (0)
#define STARTUP_DUTY_DELTA_1 (40)
#define STARTUP_DUTY_DELTA_2 (160)
#define STARTUP_DUTY_DELTA_3 (160)
#define STARTUP_DUTY_DELTA_4 (160)
#define STARTUP_DUTY_DELTA_5 (160)
#define STARTUP_DUTY_DELTA_6 (160)
#define STARTUP_DUTY_DELTA_7 (160)
#endif

uint16 g_DutyStarup = 0;
static uint16 u32DutySum = 0;

uint16 DutyStartupCurve(uint16 time_ms)
{
	uint16 ticks = time_ms;

	if (ticks <= STARTUP_TIME_PHASE_0)
	{
		u32DutySum = STARTUP_DUTY_INIT;
	}

#if (ACC_S_CURVE_MODE == STARTUP_ACC_MODE)

	if (ticks < STARTUP_TIMETICKS_MAX)
	{

		if (ticks < STARTUP_TIME_PHASE_1)
		{
			u32DutySum += STARTUP_DUTY_DELTA_1;
		}
		else if(ticks < STARTUP_TIME_PHASE_2)
		{
				u32DutySum += STARTUP_DUTY_DELTA_2;
		}
		else if(ticks < STARTUP_TIME_PHASE_3)
		{
				u32DutySum += STARTUP_DUTY_DELTA_3;
		}
		else if(ticks < STARTUP_TIME_PHASE_4)
		{
				u32DutySum += STARTUP_DUTY_DELTA_4;
		}
		else if(ticks < STARTUP_TIME_PHASE_5)
		{
				u32DutySum += STARTUP_DUTY_DELTA_5;
		}
		else if(ticks < STARTUP_TIME_PHASE_6)
		{
				u32DutySum += STARTUP_DUTY_DELTA_6;
		}
		else if(ticks < STARTUP_TIME_PHASE_7)
		{
				u32DutySum += STARTUP_DUTY_DELTA_7;
		}
		else
		{
		    u32DutySum++;
		}
	}
#else
    if (ticks < STARTUP_TIMETICKS_MAX)
    {
        u32DutySum +=STARTUP_DUTY_DELTA;
    }
    else
    {
        /* No Action */
    }
#endif 

    g_DutyStarup =  (uint16)u32DutySum;
	return g_DutyStarup;
}
