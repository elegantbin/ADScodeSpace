/*
 * DoorSys_AntiPinch.c
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#include <MotAct.h>
#include "DoorSys.h"
#include "DoorSys_AntiPinch.h"
#include "DualHall.h"
#include "DoorSys_velocity.h"
#include "DoorSys_ApAdapt.h"
#include "DoorSys_ApAdaptCurve.h"


int8_t i8ApAdaptCurveOpen[AP_ADAPT_CURVE_LEN];
int8_t i8ApAdaptCurveClose[AP_ADAPT_CURVE_LEN];


const int8_t NVM_ApAdaptCurveOpen[AP_ADAPT_CURVE_LEN]={	0 };

const int8_t NVM_ApAdaptCurveClose[AP_ADAPT_CURVE_LEN]={ 0 };

void DoorsSys_ApAdaptCurveInit(void)
{
	for(uint8_t i = 0; i< AP_ADAPT_CURVE_LEN; i++)
	{
		i8ApAdaptCurveOpen[i]  = 0 ; /*(int8_t) NVM_ApAdaptCurveOpen[i];*/

		i8ApAdaptCurveClose[i] = 0 ; /*(int8_t) NVM_ApAdaptCurveClose[i];*/

	}
}
