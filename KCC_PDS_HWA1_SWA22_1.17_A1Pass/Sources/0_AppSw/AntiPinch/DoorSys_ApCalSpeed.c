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
#include "DualHall.h"
#include "DoorSys_velocity.h"


uint16_t u16ApSpeed[K_AP_CALSPEED_ARRAY_LEN] = {0,0,0,0};
uint16_t u16LocalApCalSpeed = 0;

uint16_t Ap_ApSpeed(uint16_t u16Vel,uint8_t u8Voltage, uint8_t u8Duty)
{
	uint16_t u16RetApVelocity = 0;

	uint16_t delta_u = 0;
	uint16_t u16Speed_VoltageOffset;
	u16LocalApCalSpeed = u16Vel;

	/*Scope: u8Voltage:0 ~ 200, u16Duty:0 ~ 100*/
	uint16_t u16Voltage = u8Voltage * u8Duty;
	u16Voltage >>= K_UMOT_SHIFT_SCALE;
	/* base on K_VOLTAGE_AD_MAX conditions for offset*/
	if (u16Voltage < K_VOLTAGE_AD_MIN)
	{
		delta_u = K_VOLTAGE_AD_MAX - K_VOLTAGE_AD_MIN;
	}
	else
	{
		if (u16Voltage >= K_VOLTAGE_AD_MAX)
		{
			delta_u = 0;
		}
		else
		{
			delta_u = K_VOLTAGE_AD_MAX - u16Voltage; /*   */
		}
	}

	u16Speed_VoltageOffset = (uint16_t)(K_AP_VELOCITY_UBAT_SCALING * delta_u);

	u16LocalApCalSpeed += u16Speed_VoltageOffset;
	u16LocalApCalSpeed >>=K_APSPEED_SHIFT_SCALE;

	u16ApSpeed[0] = u16ApSpeed[1];
	u16ApSpeed[1] = u16ApSpeed[2];
	u16ApSpeed[2] = u16ApSpeed[3];
	u16ApSpeed[3] = u16LocalApCalSpeed;

	u16RetApVelocity = u16LocalApCalSpeed;

	return u16RetApVelocity;
}

void Ap_ApSpeedReset(void)
{
	for(uint8_t i = 0; i < K_AP_CALSPEED_ARRAY_LEN; i++)
	{
		u16ApSpeed[i] = 0;
	}

	u16LocalApCalSpeed = 0;
}
