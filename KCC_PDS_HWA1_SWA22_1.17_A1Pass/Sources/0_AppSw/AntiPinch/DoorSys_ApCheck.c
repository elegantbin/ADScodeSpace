/*
 * DoorSys_AntiPinch.c
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#include <DoorSys_ApCalSpeed.h>
#include <MotAct.h>
#include "DoorSys.h"
#include "DoorSys_AntiPinch.h"
#include "DoorSys_ApCheck.h"
#include "DoorSys_ApAdaptCurve.h"
#include "DoorSys_ApLimit.h"
#include "DoorSys_ApIf.h"

int16_t  i16SpeedDiff1,i16SpeedDiff2;
int16_t  i16ApSum = 0;
int16_t  i16ApThreshold = -5000;
int16_t  i16ApAdapt = 0;

static void DoorSys_ApSum(void);


void Doorsys_ApCheck(void)
{
	MotorActator_Control *motor = &g_motor;
	sAntiPinch_t *p_antipinch = &g_antipinch;

	uint8_t  lu8RunningDir = ApIf_DoorOpening();

	DoorSys_ApSum();

	i16ApThreshold = DoorSys_ApLimit(p_antipinch->position,lu8RunningDir,p_antipinch->lu16ApCalCounter);


	if(i16ApSum < i16ApThreshold)
	{
		if(MOTOR_STATUE_RUNNING == motor->state)
		{
			ApIf_ApEventSet();
		}
		else
		{
            /* Motor is not running, no ap event occured */
		}
	}
	else
	{
		/* Ap limit is not trigger */
	}
}

void DoorSys_ApDiff(void)
{
    uint16_t u16Speed = ApIf_GetVelocity();
	sAntiPinch_t *p_antipinch = &g_antipinch;

	Ap_ApSpeed(u16Speed,p_antipinch->voltage,(uint8_t)g_i16DoorDutyPercent);

	i16SpeedDiff1 = u16ApSpeed[2] - u16ApSpeed[0]; /*  diff1 */
	i16SpeedDiff2 = u16ApSpeed[3] - u16ApSpeed[1];

	 i16SpeedDiff1 = i16SpeedDiff1 + i16SpeedDiff2; /*     Motor speed diff  */

	 if(ApIf_DoorOpening())
	 {
		 i16ApAdapt =(int16_t) DoorSys_getDiffAdapt(p_antipinch->position,i16SpeedDiff1,&i8ApAdaptCurveOpen[0]);
	 }
	 else
	 {
		 i16ApAdapt =(int16_t) DoorSys_getDiffAdapt(p_antipinch->position,i16SpeedDiff1,&i8ApAdaptCurveClose[0]);
	 }

	 i16SpeedDiff1 += i16ApAdapt;

	 i16SpeedDiff1 = (i16SpeedDiff1 > K_SPEEDDIFF1_MAX)?K_SPEEDDIFF1_MAX:i16SpeedDiff1;
	 i16SpeedDiff1 = (i16SpeedDiff1 < K_SPEEDDIFF1_MIN)?K_SPEEDDIFF1_MIN:i16SpeedDiff1;

	 if(i16SpeedDiff1 > K_AP_SUM_RESET)
	 {
		 i16ApSum = 0;
	 }
}

static void DoorSys_ApSum(void)
{

	i16ApSum += i16SpeedDiff1;

	i16ApSum = (i16ApSum > K_DOOR_APSUM_MAX)?K_DOOR_APSUM_MAX:i16ApSum;
	i16ApSum = (i16ApSum < K_DOOR_APSUM_MIN)?0               :i16ApSum;

}




