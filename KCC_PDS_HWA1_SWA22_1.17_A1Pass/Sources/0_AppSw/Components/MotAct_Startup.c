#include <MotAct.h>
#include <MotAct_Startup.h>
#include <Roll_Pitch_Parameter.h>
#include "DoorSys.h"

static uint16 u16DutySum = 0;
static uint16 u16Ticks   = 0;



uint8_t OPEN_STARTUP_DUTY_DELTA[8] = {1,2,2,3,2,1,1,1};
uint8_t CLOSE_STARTUP_DUTY_DELTA[8] = {2,3,3,4,5,4,3,2};



static int16_t in16StartupDutyPercent = 0;

static uint16 MotorActator_StartupCurve(void);

void MotorActator_StartUp(void)
{
	MotorActator_Control *motor = &g_motor;
	DoorControl_t *door = &g_door;

	boolean b_StartupEnd = FALSE;

	motor->u16StartupCount++;

	if(motor->u16StartupCount > K_STARUP_DELAY_COUNT_MAX)
   {
		b_StartupEnd = TRUE;
   }

if(door->b_dir_close_fbk)
{
	if((door->u16Velocity > CLOSE_VELOCITY_CONTROL_REF_NORM))
	{
		if(motor->u16StartupCount >K_STARUP_DELAY_COUNT_CLOSE )
		{
			b_StartupEnd = TRUE;
		}

	}
	else
	{
	}
}

if(door->b_dir_open_fbk)
{
	if((door->u16Velocity > OPEN_VELOCITY_CONTROL_REF_NORM))
	{
		if(motor->u16StartupCount > K_STARUP_DELAY_COUNT_OPEN)
		{
			b_StartupEnd = TRUE;
		}

	}
	else
	{
	}
}

	if( b_StartupEnd )
	{
		b_StartupEnd = FALSE;
		motor->state = MOTOR_STATUE_RUNNING;

		motor->u16StartupCount = 0;
		g_i16DoorDutyPercent=in16StartupDutyPercent;
	}
	else
	{
		in16StartupDutyPercent =  MotorActator_StartupCurve();

		MotorActator_UpdateDuty(in16StartupDutyPercent);
	}

}

void MotorActator_StartupCurveReset(void)
{
	u16DutySum = 0;
	u16Ticks   = 0;
}

static uint16 MotorActator_StartupCurve(void)
{
	DoorControl_t *door = &g_door;
	uint16 retDuty;
	uint16 ticks = 0;

	ticks = u16Ticks++;
	if(door->b_dir_open_fbk)
{

	if (ticks <= STARTUP_TIME_PHASE_0)
	{
		//u16DutySum = OPEN_STARTUP_DUTY_INIT;
		u16DutySum = gOpen_Roll_Pitch_ParaSet.StartUpDuty;  //!
	}


	if (ticks < STARTUP_TIMETICKS_MAX)
	{

		if (ticks < STARTUP_TIME_PHASE_1)
		{
			//u16DutySum += OPEN_STARTUP_DUTY_DELTA[1];
			u16DutySum += gOpen_Roll_Pitch_ParaSet.StartCurve[0];  //!
		}
		else if(ticks < STARTUP_TIME_PHASE_2)
		{
				//u16DutySum += OPEN_STARTUP_DUTY_DELTA[2];
				u16DutySum += gOpen_Roll_Pitch_ParaSet.StartCurve[1];  //!
		}
		else if(ticks < STARTUP_TIME_PHASE_3)
		{
				//u16DutySum += OPEN_STARTUP_DUTY_DELTA[3];
				u16DutySum += gOpen_Roll_Pitch_ParaSet.StartCurve[2];  //!
		}
		else if(ticks < STARTUP_TIME_PHASE_4)
		{
				//u16DutySum += OPEN_STARTUP_DUTY_DELTA[4];
				u16DutySum += gOpen_Roll_Pitch_ParaSet.StartCurve[3];  //!
		}
		else if(ticks < STARTUP_TIME_PHASE_5)
		{
				//u16DutySum += OPEN_STARTUP_DUTY_DELTA[5];
				u16DutySum += gOpen_Roll_Pitch_ParaSet.StartCurve[4];  //!
		}
		else if(ticks < STARTUP_TIME_PHASE_6)
		{
				//u16DutySum += OPEN_STARTUP_DUTY_DELTA[6];
				u16DutySum += gOpen_Roll_Pitch_ParaSet.StartCurve[5];  //!
		}
		else if(ticks < STARTUP_TIME_PHASE_7)
		{
			//	u16DutySum += OPEN_STARTUP_DUTY_DELTA[7];
				u16DutySum += gOpen_Roll_Pitch_ParaSet.StartCurve[6];  //!
		}
		else
		{
		    u16DutySum++;
		}
	}

}

	if(door->b_dir_close_fbk)
{

		if (ticks <= STARTUP_TIME_PHASE_0)
		{
			//u16DutySum = CLOSE_STARTUP_DUTY_INIT;
			u16DutySum = gClose_Roll_Pitch_ParaSet.StartUpDuty ;   //!
		}

	if (ticks < STARTUP_TIMETICKS_MAX)
	{

		if (ticks < STARTUP_TIME_PHASE_1)
		{
			//u16DutySum += CLOSE_STARTUP_DUTY_DELTA[1];
			u16DutySum += gClose_Roll_Pitch_ParaSet.StartCurve[0];    //!
		}
		else if(ticks < STARTUP_TIME_PHASE_2)
		{
			//	u16DutySum += CLOSE_STARTUP_DUTY_DELTA[2];
				u16DutySum += gClose_Roll_Pitch_ParaSet.StartCurve[1];    //!
		}
		else if(ticks < STARTUP_TIME_PHASE_3)
		{
				//u16DutySum += CLOSE_STARTUP_DUTY_DELTA[3];
				u16DutySum += gClose_Roll_Pitch_ParaSet.StartCurve[2];    //!
		}
		else if(ticks < STARTUP_TIME_PHASE_4)
		{
				//u16DutySum += CLOSE_STARTUP_DUTY_DELTA[4];
				u16DutySum += gClose_Roll_Pitch_ParaSet.StartCurve[3];    //!
		}
		else if(ticks < STARTUP_TIME_PHASE_5)
		{
				//u16DutySum += CLOSE_STARTUP_DUTY_DELTA[5];
				u16DutySum += gClose_Roll_Pitch_ParaSet.StartCurve[4];    //!
		}
		else if(ticks < STARTUP_TIME_PHASE_6)
		{
				//u16DutySum += CLOSE_STARTUP_DUTY_DELTA[6];
				u16DutySum += gClose_Roll_Pitch_ParaSet.StartCurve[5];    //!
		}
		else if(ticks < STARTUP_TIME_PHASE_7)
		{
			//	u16DutySum += CLOSE_STARTUP_DUTY_DELTA[7];
				u16DutySum += gClose_Roll_Pitch_ParaSet.StartCurve[6];    //!
		}
		else
		{
		    u16DutySum++;
		}
	}

}

    retDuty = u16DutySum/K_SCALE_FACTOR;
    if(retDuty < STARTUP_DUTY_INIT)
    {
    	retDuty = STARTUP_DUTY_INIT;
    }
	return retDuty;
}
