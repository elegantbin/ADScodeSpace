/*
 * DoorSys_Velocity.c
 *
 *  Created on: 11.12.2023
 *      Author: Administrator
 */
#include <DoorSys_VelocityControl.h>
#include "DoorSys_Velocity.h"
#include "DoorSysCfg_Velocity.h"
#include <Roll_Pitch_Parameter.h>

uint16_t u16Pwx[K_PWX_LEN] ={0};
uint16_t u16VelocityArray[K_SPEED_ARRAY_LEN]={0};

int16_t DoorSys_VelocityUpdate(void);
void DoorSys_VelocityReset(void);

void DoorSys_VelocityInit(void)
{
	VelocityControl_Init();
	DoorSys_VelocityReset();

}


 void DoorSys_VelocityClosingControl(void)
{
	DoorControl_t *door = &g_door;

	VelocityControl *velocityControl = &g_velocityControl;

	if(door->b_PosCloseLearned)
	{
		//VelocityControl_SetKpKi(velocityControl, CLOSE_VELOCITY_CONTROL_KP, CLOSE_VELOCITY_CONTROL_KI, VELOCITY_CONTROL_PERIOD,0, 0);
		//VelocityControl_SetRefSpeed(velocityControl, CLOSE_VELOCITY_CONTROL_REF_NORM);

		VelocityControl_SetRefSpeed(velocityControl, gClose_Roll_Pitch_ParaSet.Referspeed); //!

		VelocityControl_SetKpKi(velocityControl, (gClose_Roll_Pitch_ParaSet.Kp*VELOCITY_Kp_FACTOR),
				                                 (gClose_Roll_Pitch_ParaSet.Ki*VELOCITY_Ki_FACTOR),
			VELOCITY_CONTROL_PERIOD,0, 0);  //!

		 VelocityControl_Task();
	}
	else
	{
		 g_i16DoorDutyPercent = K_VELOCITY_DUTY_PERCENT;
	}

}


 void DoorSys_VelocityOpeningControl(void)
 {
	 DoorControl_t *door = &g_door;

	 VelocityControl *velocityControl = &g_velocityControl;

	 if(door->b_PosOpenLearned)
	 {
		// VelocityControl_SetRefSpeed(velocityControl,  OPEN_VELOCITY_CONTROL_REF_NORM);
		// VelocityControl_SetRefSpeed(velocityControl,  gOpen_Roll_Pitch_ParaSet.Referspeed);

		 VelocityControl_SetKpKi(velocityControl, OPEN_VELOCITY_CONTROL_KP, OPEN_VELOCITY_CONTROL_KI, VELOCITY_CONTROL_PERIOD,0, 0);
		 VelocityControl_SetKpKi(velocityControl, (gOpen_Roll_Pitch_ParaSet.Kp*VELOCITY_Kp_FACTOR)
				 	                ,(gOpen_Roll_Pitch_ParaSet.Ki*VELOCITY_Ki_FACTOR), VELOCITY_CONTROL_PERIOD,0, 0);  //!

		 VelocityControl_Task();
	 }
	 else
	 {
		 g_i16DoorDutyPercent = K_VELOCITY_DUTY_PERCENT;
	 }

 }

 void DoorSys_VelocityEvaluate(void)
{
	DoorControl_t *door = &g_door;
	if(door->b_VelocityUpdate)
	{
		door->b_VelocityUpdate = 0;
		door->u16Velocity = DoorSys_VelocityUpdate();
	}
	else
	{

	}
 }

 int16_t DoorSys_VelocityUpdate(void)
 {
 	uint32_t u32Pw;
 	volatile uint16_t u16Velocity = 0;
    uint32_t pulseWidth = 0;

 	pulseWidth=hall_A.HallWidth;
 	u32Pw = (uint32_t)pulseWidth;

 	/* Shift pulse width array*/
 	for (uint8_t i = (uint8_t)(K_PWX_LEN - 1); i > 0; i--)
 	{
 		u32Pw += (uint32_t)u16Pwx[i];

 		u16Pwx[i] = u16Pwx[i - 1];
 	}
 	u16Pwx[0] = pulseWidth; /* new value push   */

 	u32Pw>>=2;

 	u32Pw = (u32Pw > K_PULSE_WIDTH_MAX)?(K_PULSE_WIDTH_MAX):u32Pw;
 	u32Pw = (u32Pw < K_PULSE_WIDTH_MIN)?(K_PULSE_WIDTH_MIN):u32Pw;

 	if (u32Pw != 0)
 	{
 		/* -------------- Speed from pulse width Calibration ----------------*/
 		u16Velocity = (uint32_t)((uint32_t)AP_PW_TO_N_NUMERATOR / (uint32_t)u32Pw);
 	}

 	if (u16Velocity > K_VELOCITY_MAX)
 	{
 			u16Velocity=K_VELOCITY_MAX;
 	}
 	else
 	{
 		if (u16Velocity < K_VELOCITY_MIN+1)
 		{
 			u16Velocity = K_VELOCITY_MIN;
 		}
 	}

 	u16VelocityArray[0] = u16VelocityArray[1];
 	u16VelocityArray[1] = u16VelocityArray[2];
 	u16VelocityArray[2] = u16VelocityArray[3];
 	u16VelocityArray[3] = u16Velocity;

 	return u16Velocity;
 }

 void DoorSys_VelocityReset(void)
 {
	 	DoorControl_t *door = &g_door;

		for (uint8_t i = (uint8_t)(K_PWX_LEN - 1); i > 0; i--)
		{
		   u16Pwx[i] = K_PULSE_WIDTH_MAX;
		}

		u16VelocityArray[0] = 0;
		u16VelocityArray[1] = 0;
		u16VelocityArray[2] = 0;
		u16VelocityArray[3] = 0;

		door->u16Velocity = 0;
 }


 uint16_t* DoorSys_getVelocityArray(void)
 {
	 return (uint16_t*)u16VelocityArray;
 }
