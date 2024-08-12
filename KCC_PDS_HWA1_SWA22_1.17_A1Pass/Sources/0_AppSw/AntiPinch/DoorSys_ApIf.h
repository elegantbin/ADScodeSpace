/*
 * DoorSys_AntiPinch.h
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_AP_IF_H_
#define _0_APPSW_DOORSYS_AP_IF_H_
#include <OsTypedefs.h>
#include "cpu.h"



#define ApIf_ApCmdStop()              {door->DoorCmd = DOOR_CMD_STOP;}
#define ApIf_ApCmdOpen()              {door->DoorCmd = DOOR_CMD_AP_OPEN;}
#define ApIf_ApCmdClose()             {door->DoorCmd = DOOR_CMD_CLOSE;}

#define ApIf_DoorSysApOpenFlagSet(x)   {DoorControl_t *door = &g_door; door->b_open_antipinch = x;}

#define ApIf_DoorSysApCloseFlagSet(x)  {DoorControl_t *door = &g_door;door->b_close_antipinch = x;}

inline void ApIf_ApEventSet()
{
	DoorControl_t *door = &g_door;

	door->event = DOOR_EVENT_AP;
}

inline boolean ApIf_DoorOpening()
{
	DoorControl_t *door = &g_door;

	return (DOOR_STATE_OPENNING == door->state);
}

inline boolean ApIf_DoorClosing()
{
	DoorControl_t *door = &g_door;
	return (DOOR_STATE_CLOSING == door->state);
}

inline uint16_t ApIf_GetVelocity(void)
{
	uint16_t* u16SpeedArray = (uint16_t*)DoorSys_getVelocityArray();

	return u16SpeedArray[3];
}
#endif /* 0_APPSW_DOORSYS_ANTIPINCH_H_ */
