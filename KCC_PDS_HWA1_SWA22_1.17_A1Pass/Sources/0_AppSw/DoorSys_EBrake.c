/*
 * DoorSys_Velocity.c
 *
 *  Created on: 11.12.2023
 *      Author: Administrator
 */
#include <DoorSys.h>
#include <MotAct.h>
#include "DoorSys_Ebrake.h"
#include <Roll_Pitch_Parameter.h>
stEBrakeControl g_ebrake;

void DoorSys_eBrakeInit(void)
{
	stEBrakeControl *ebrake = &g_ebrake;

	ebrake->b_eBrakEnable = 0;
	ebrake->u16eBrakeDuty = K_EBRAKE_DUTY_OPEN;
	ebrake->u16eBrakeTimeCount = 0;
	ebrake->b_eBrake = 0;

	ebrake->i16eBrake_count=0;

	ebrake->u16eBreakPosMax = K_EBRAKE_POS_MAX;
	ebrake->u16eBreakPosMin = K_EBRAKE_POS_MIN;

	ebrake->u16Realtime_Pos = 0;
	ebrake->u16Lasttime_Pos = 0;

	ebrake->u16eBrakeTimeout = 0;

}

void DoorSys_eBrakeCheck(void)
{
	DoorControl_t *door=&g_door;
	stEBrakeControl *ebrake = &g_ebrake;
	MotorActator_Control *motor = &g_motor;

    ebrake->u16Realtime_Pos = door->u16Realtime_Pos;

	if((ebrake->u16Realtime_Pos < ebrake->u16eBreakPosMax)&&
			(ebrake->u16Realtime_Pos > ebrake->u16eBreakPosMin)&&(gOpen_Roll_Pitch_ParaSet.EbrakEnable))
	{

		if((MOTOR_STATUE_STOP == motor->state)&&(motor->u16MotStopCount < K_EBRAKE_CHECK_END_COUNT))
		{
			if(ebrake->u16eBrakeTimeCount >= K_EBRAKE_CHECK_COUNT)
			{
				ebrake->u16eBrakeTimeCount = 0;

				if(ebrake->u16Lasttime_Pos > ebrake->u16Realtime_Pos)
				{
					ebrake->i16eBrake_count++;
				}
				else if(ebrake->u16Lasttime_Pos < ebrake->u16Realtime_Pos)
				{
					ebrake->i16eBrake_count--;
				}

				if(ebrake->i16eBrake_count > (int16_t)K_EBRAKE_COUNT_MIN)
				{
					if(ebrake->i16eBrake_count < (int16_t)K_EBRAKE_COUNT_MAX)
					{
						ebrake->eBrakeDir=K_EBRAKE_DIR_OPEN;
						ebrake->i16eBrake_count= 0;
						door->event = DOOR_EVENT_EBRAKE;

					    g_i16DoorDutyPercent =-5;

					}

				}
				else if(ebrake->i16eBrake_count < (int16_t)(-K_EBRAKE_COUNT_MIN))
				{
					 ebrake->eBrakeDir=K_EBRAKE_DIR_CLOSE;

					 ebrake->i16eBrake_count= 0;
					 door->event = DOOR_EVENT_EBRAKE;
					 g_i16DoorDutyPercent = -5;
				}


				ebrake->u16Lasttime_Pos =  door->u16Realtime_Pos;
			}
			else
			{
				if(ebrake->u16eBrakeTimeCount == 0)
				{
					ebrake->u16Lasttime_Pos = ebrake->u16Realtime_Pos;
				}
				ebrake->u16eBrakeTimeCount++;
			}

		}
		else
		{
			 ebrake->i16eBrake_count= 1;
		}

	}

}

void DoorSys_EventeBrakeHandler(DoorControl_t *door)
{
	 stEBrakeControl *ebrake = &g_ebrake;

	 ebrake->b_eBrakEnable = 1; /*Comment for Disable on purpose*/

	 door->b_ebrake = 1;
}





void DoorSys_eBrakeControl(void)
{
	 stEBrakeControl *ebrake = &g_ebrake;
	 MotorActator_Control *motor = &g_motor;

	 DoorControl_t *door=&g_door;
	 if(MOTOR_STATUE_STOP != motor->state)
	 {
		 ebrake->b_eBrakEnable = 0;

		 ebrake->u16eBrakeTimeCount = 0;
	 }

	 if(ebrake->b_eBrakEnable)
	 {
		 if((door->u16Velocity > K_VELOCITY_BRAKE))
		 {
			 if(K_EBRAKE_DIR_OPEN == ebrake->eBrakeDir)
			 {

				if(door->b_dir_close_fbk)
				{
					motor->dir_cmd = K_DOOR_DIR_CMD_CLOSE;
					g_i16DoorDutyPercent -=K_EBRAKE_DIR_OPEN_DELTA_PERCENT;

				}
				g_i16DoorDutyPercent = (g_i16DoorDutyPercent > (int16_t)K_EBRAKE_DUTY_MAX) ? (int16_t)K_EBRAKE_DUTY_MAX :g_i16DoorDutyPercent;
				g_i16DoorDutyPercent = (g_i16DoorDutyPercent < (int16_t)(-K_EBRAKE_DUTY_MAX)) ? (int16_t)(-K_EBRAKE_DUTY_MAX) :g_i16DoorDutyPercent;
				MotorActator_UpdateDuty(g_i16DoorDutyPercent);
			 }
			 else if(K_EBRAKE_DIR_CLOSE == ebrake->eBrakeDir)
			 {
				 if(door->b_dir_open_fbk)
				 {
				 	motor->dir_cmd = K_DOOR_DIR_CMD_OPEN;
				 	g_i16DoorDutyPercent-=K_EBRAKE_DIR_CLOSE_DELTA_PERCENT;
				 }
				 g_i16DoorDutyPercent = (g_i16DoorDutyPercent > (int16_t)K_EBRAKE_DUTY_MAX) ? (int16_t)K_EBRAKE_DUTY_MAX :g_i16DoorDutyPercent;
				 g_i16DoorDutyPercent = (g_i16DoorDutyPercent < (int16_t)(-K_EBRAKE_DUTY_MAX)) ? (int16_t)(-K_EBRAKE_DUTY_MAX) :g_i16DoorDutyPercent;
				 MotorActator_UpdateDuty(g_i16DoorDutyPercent);
			 }
		 }
		 else
		 {
		 }

		 if((ebrake->u16eBrakeTimeCount < K_EBRAKE_TIMEOUT))
		 {
			 ebrake->u16eBrakeTimeCount++;
		 }
		 else
		 {
			 ebrake->u16eBrakeTimeCount = 0;
			 /*Exit Ebrake due to time out */

			 g_i16DoorDutyPercent =10;
		     MotorActator_Stop();
		     ebrake->b_eBrakEnable = 0;
		 }
	 }

}

