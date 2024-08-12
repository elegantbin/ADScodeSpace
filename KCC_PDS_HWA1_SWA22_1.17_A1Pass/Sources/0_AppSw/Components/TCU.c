/*
 * TCU.c
 *
 *  Created on: 2024Äê1ÔÂ2ÈÕ
 *      Author: lenovo
 */

#include "TCU.h"

TCU_t TCU;
Vehicle_Speed_Status_t Vehicle_Speed_Status;

Vehicle_Speed_Status_t Get_Vechicle_Speed_Status(void)
{
	Vehicle_Speed_Status_t Speed_Status;
	if((TCU.Vehicle_Speed >= VehSlowSpeed_Cfg) || (TCU.Vehicle_speed_valid == Invalid))
	{
		Speed_Status = HIGH;
	}
	else if((TCU.Vehicle_Speed < VehSlowSpeed_Cfg) && (TCU.Vehicle_speed_valid == Valid))
	{
		Speed_Status = SLOW;
	}

	return Speed_Status;
}



