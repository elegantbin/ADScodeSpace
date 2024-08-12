/*
 * Drive_Motor.c
 *
 *  Created on: 7.12.2023
 *      Author: Administrator
 */

#include <MotAct.h>
#include <MotAct_Startup.h>
#include "Cpu.h"
#include "DoorSys_Velocity.h"
#include "DoorSysCfg_velocity.h"

static void MotorActator_Enable(void);

static int16_t i16SlowDownDutyPercent = 0;
MotorActator_Control g_motor;

void MotorActator_Init(void)
{
	MotorActator_Control *motor = &g_motor;
	motor->mot_cmd= MOTOR_CMD_STOP;
	motor->state = MOTOR_STATUE_STOP;
	motor->dir_cmd = MOTOR_DIR_CW;
    motor->duty = K_DEFAULT_MOTOR_DUTY;

    motor->u16MotStopCount = 0;
	motor->u16SLowdownCount = 0;
	motor->u16MotRunningCount = 0;

	motor->u16StartupCount  = 0;
	MotorActator_Enable();
}



void MotorActator_StateMachine(void)
{
	MotorActator_Control *motor=&g_motor;

	if( MOTOR_STATUE_STOP !=motor->state)
	{
		if(motor->u16MotStopCount != 0)
		{
			motor->u16MotStopCount = 0;
		}
	}

	if(MOTOR_STATUE_SLOWDOWN !=motor->state)
	{
		if(motor->u16SLowdownCount != 0)
		{
		    motor->u16SLowdownCount = 0;
		}
	}

	switch(motor->state)
	{
		case MOTOR_STATUE_STOP:
		{
			 MotorActator_StartupCurveReset();

			 motor->u16MotStopCount++;
			 if( motor->u16MotStopCount > K_MOT_STOP_COUNT_MAX)
			 {
				 motor->u16MotStopCount = K_MOT_STOP_COUNT_MAX;
			 }
			break;
		}
		case MOTOR_STATUE_STARTUP:
		{
			MotorActator_StartUp();




			break;
		}
		case MOTOR_STATUE_RUNNING:
		{
			motor->u16MotRunningCount++;
			if(motor->u16MotRunningCount > K_MOT_RUNNING_TIMEOUT)
			{
				motor->u16MotRunningCount = K_MOT_RUNNING_TIMEOUT;
				motor->state = MOTOR_STATUE_SLOWDOWN;
			}
			/*update duty*/
			MotorActator_UpdateDuty(g_i16DoorDutyPercent);


			break;
		}
		case MOTOR_STATUE_SLOWDOWN:
		{

			motor->u16MotRunningCount=0;
			if( motor->u16SLowdownCount < K_MOT_SLOWDOWN_COUNT-150)
			{
				motor->u16SLowdownCount++;
				MotorActator_SlowDown();
			}
			else if( motor->u16SLowdownCount < K_MOT_SLOWDOWN_COUNT)
			{
				motor->u16SLowdownCount++;
				PWM_UpdateDuty(&pwm_pal1Instance,6,PWM_DUTY_PERIOD);
				PWM_UpdateDuty(&pwm_pal1Instance,7,PWM_DUTY_PERIOD);

			}
			else
			{
				 motor->u16SLowdownCount = 0;
				 MotorActator_Stop();
			}

			break;
		}
		case MOTOR_STATUE_EMERGENCY:
		{
			MotorActator_Stop();

			break;
		}
		default:
		{
			motor->state = MOTOR_STATUE_STOP;
			break;
		}
	}
}


void MotorActator_SlowDown(void)
{
	static int16_t delay_count= 0;
	MotorActator_Control *motor = &g_motor;

	motor->state = MOTOR_STATUE_SLOWDOWN;

	i16SlowDownDutyPercent =(int16_t)(K_VELOCITY_DUTY_100_PERCENT-(motor->duty/PWM_DUTY_PECENT));

	if(delay_count < K_MOT_SLOWDOWN_DELAY_COUNT)
	{
		delay_count++;
	}
	else
	{
		if(i16SlowDownDutyPercent > 0)
		{
			i16SlowDownDutyPercent-=K_MOT_SLOWDOWN_DELTA;
		}

		delay_count = 0;
	}

	MotorActator_UpdateDuty(i16SlowDownDutyPercent);
}
/*************************************************************************
  *FUNCTION NAME:			Set_Drive_Motor_Enable
  *FUNCTION DESCRIPTION:		Function is used to enable motor initialization PWM
  *PAPRAMETER:		void
  *RETURN VALUE:		void	VALUENAME:void
  *EDITOR:			ReaveGan
  *DATE:				2023.12.07
  *VERSION:			1.0
  *************************************************************************/
void MotorActator_Enable(void)
{
	PWM_Init(&pwm_pal1Instance,&pwm_pal1Configs);

	MOTOR_WAKE();
	KL_30_ENABLE();
}

/*
static void MotorActator_Disable(void)
{
	MOTOR_SLEEP();
	KL_30_DISABLE();
}*/
/*************************************************************************
  *FUNCTION NAME:			Set_Drive_Motor_Disable
  *FUNCTION DESCRIPTION:		Disable the drive pin and set PWM to 0
  *PAPRAMETER:		void
  *RETURN VALUE:		void	VALUENAME:void
  *EDITOR:			ReaveGan
  *DATE:				2023.12.07
  *VERSION:			1.0
  *************************************************************************/
void MotorActator_Stop(void)
{
	 MotorActator_Control *motor = &g_motor;


	 motor->state = MOTOR_STATUE_STOP;
	 motor->duty = K_DEFAULT_MOTOR_STOP_DUTY;

	 PWM_UpdateDuty(&pwm_pal1Instance,6,0);
	 PWM_UpdateDuty(&pwm_pal1Instance,7,0);


}

/*************************************************************************
  *FUNCTION NAME:			Motor_Start
  *FUNCTION DESCRIPTION:		Set_Drive_Motor_Speed
  *PAPRAMETER:		uint16_t Speed,motor_dir_t dir
  *RETURN VALUE:		void	VALUENAME:void
  *EDITOR:			ReaveGan
  *DATE:				2023.12.07
  *VERSION:			1.0
  *************************************************************************/
void MotorActator_Start(motor_dir_t dir)
{
	MotorActator_Control *motor = &g_motor;

	motor->state=MOTOR_STATUE_STARTUP;
	motor->dir_cmd = dir;

}


void MotorActator_UpdateDuty(int16_t i16Duty)
{
	MotorActator_Control *motor = &g_motor;

	uint16_t u16DrvDutyPercent;

	if(i16Duty > 0)
	{
		u16DrvDutyPercent = (uint16_t)i16Duty;
	}
	else if(i16Duty < 0)
	{
		u16DrvDutyPercent = (uint16_t)(-i16Duty);
	}
	else
	{
		u16DrvDutyPercent = 0;
	}

	if(u16DrvDutyPercent < K_VELOCITY_DUTY_100_PERCENT)
	{
		motor->duty=(K_VELOCITY_DUTY_100_PERCENT - u16DrvDutyPercent) * PWM_DUTY_PECENT;
		motor->duty=(motor->duty > PWM_DUTY_MAX) ? PWM_DUTY_MAX : motor->duty;
		motor->duty=(motor->duty < PWM_DUTY_MIN) ? PWM_DUTY_MIN : motor->duty;

		if((MOTOR_STATUE_EMERGENCY != motor->state))
		{
			if(motor->dir_cmd == MOTOR_DIR_CCW)
			{
				if(i16Duty > 0)
				{
				  PWM_UpdateDuty(&pwm_pal1Instance,6,motor->duty);
				  PWM_UpdateDuty(&pwm_pal1Instance,7,PWM_DUTY_PERIOD);
				}
				else
				{
					PWM_UpdateDuty(&pwm_pal1Instance,7,motor->duty);
					PWM_UpdateDuty(&pwm_pal1Instance,6,PWM_DUTY_PERIOD);
				}
			}
			else if(motor->dir_cmd == MOTOR_DIR_CW)
			{
				if(i16Duty > 0)
				{
					PWM_UpdateDuty(&pwm_pal1Instance,7,motor->duty);
					PWM_UpdateDuty(&pwm_pal1Instance,6,PWM_DUTY_PERIOD);
				}
				else
				{
					 PWM_UpdateDuty(&pwm_pal1Instance,6,motor->duty);
					 PWM_UpdateDuty(&pwm_pal1Instance,7,PWM_DUTY_PERIOD);
				}

			}
	    }
	}
}



