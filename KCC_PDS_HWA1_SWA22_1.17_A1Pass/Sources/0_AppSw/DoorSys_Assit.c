/*
 * DoorSys_ManualAssit.c
 *
 *  Created on: 8.12.2023
 *      Author: Administrator
 */
#include <DoorSys_Assist.h>
#include <DoorSysCfg_Assist.h>
#include "DoorSysCfg.h"
#include "DoorSys.h"
#include "DoorSys_AntiPinch.h"


stManualAsist_t  g_ManualAssist;
void DoorSys_ManaualAssitCheck(void)
{
	DoorControl_t *door = &g_door;
	/* ManualAssist zone check*/
	if((door->u16Realtime_Pos < door->u16ManualAssistPosMax)&&
			(door->u16Realtime_Pos > door->u16ManualAssistPosMax))
	{

	}

}


void DoorSys_EventManaualAssitHander(DoorControl_t *door)
{
   door->b_assisting = 1;

}
