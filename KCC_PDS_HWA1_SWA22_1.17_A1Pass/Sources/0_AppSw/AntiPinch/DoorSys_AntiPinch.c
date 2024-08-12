/*
 * DoorSys_AntiPinch.c
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#include <DoorSys_ApCalSpeed.h>
#include <MotAct.h>
#include "Doorsys_ApDef.h"
#include "DoorSys.h"
#include "DoorSys_AntiPinch.h"
#include "DualHall.h"
#include "DoorSys_velocity.h"
#include "DoorSys_ApCheck.h"
#include "DoorSys_ApAdaptCurve.h"
#include "DoorSys_ApIf.h"
sAntiPinch_t g_antipinch;


void DoorSys_ApInit(void)
{
	DoorsSys_ApAdaptCurveInit();
    DoorSys_AntipinchReset();
}

void DoorSys_ApEventCheck(void)
{
	DoorControl_t *door = &g_door;
	MotorActator_Control *motor = &g_motor;
	boolean lb_check = 0;
	sAntiPinch_t *p_antipinch = &g_antipinch;

	p_antipinch->b_PosCalibrated = ((door->b_PosCloseLearned)&&(door->b_PosOpenLearned));
	p_antipinch->position = door->u16Realtime_Pos;
	p_antipinch->voltage = 120;

	if(p_antipinch->b_PosCalibrated)
	{
		if((p_antipinch->position > K_AP_POS_MIN)&&
				(p_antipinch->position < K_AP_POS_MAX))
		{
			if(p_antipinch->b_ApCalEnable)
			{
				p_antipinch->b_ApCalEnable = 0;
			    lb_check = 1;
			}
			else
			{
				/* Pos is not updated, antipinch check is not actiavted */
			}
		}
		else
		{
			/* Pos is not in the Antipinch scope */
		}
	}
	else
	{
		/* Pos is not calibrated */
	}

	if(lb_check)
	{
		lb_check = 0;
		p_antipinch->lu16ApCalCounter++;
		DoorSys_ApDiff();

		if((!door->b_tip2run)&&
				(p_antipinch->b_close_antipinch!=1)&&
				(p_antipinch->b_open_antipinch!=1))
		{
			if(MOTOR_STATUE_RUNNING == motor->state)
			{
				  Doorsys_ApCheck();
			}
			else
			{
			   /* waiting until  the valid check count */
			}
		}
		else
		{
			if(p_antipinch->lu16ApCalCounter > K_AP_CHECK_START_COUNT)
			{
				Doorsys_ApCheck();
			}
			else
			{

			}

		}

		p_antipinch->b_ApInfoSend = 1;
	}
	else
	{
		/* Check condition is not satified */
	}

	if(MOTOR_STATUE_RUNNING  != motor->state)
	{
       DoorSys_AntipinchReset();
	}

}


void DoorSys_EventApHandler(DoorControl_t *door)
{
	sAntiPinch_t *p_antipinch = &g_antipinch;
	MotorActator_Stop();
	if(ApIf_DoorOpening())
	{
	    ApIf_ApCmdStop();

		    p_antipinch->b_open_antipinch = 1;
		    ApIf_DoorSysApOpenFlagSet(1);
	}
	else if(ApIf_DoorClosing())
	{
		if((p_antipinch->b_close_antipinch!=1)&&(p_antipinch->b_open_antipinch!=1)&&
						(door->u16Realtime_Pos < K_AP_POS_CLOSE_REVERSE))
		{

		ApIf_ApCmdOpen();
		}
		else
		{
		ApIf_ApCmdStop();
		}

		p_antipinch->b_close_antipinch = 1;
		ApIf_DoorSysApCloseFlagSet(1);
	}
}


/**** reset the using variables */
void DoorSys_AntipinchReset(void)
{
	sAntiPinch_t *p_antipinch = &g_antipinch;
	p_antipinch->b_open_antipinch = 0;
	p_antipinch->b_close_antipinch = 0;
	p_antipinch->b_ApCalEnable = 0;
	p_antipinch->b_ApInfoSend  = 0;

	i16ApSum  = 0;
	p_antipinch->lu16ApCalCounter = 0;
	Ap_ApSpeedReset();

}

