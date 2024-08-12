/*
 * DCU.c
 *
 *  Created on: 2024Äê1ÔÂ2ÈÕ
 *      Author: lenovo
 */

#include "DCU.h"
#include "TCU.h"
#include "CanIf_SigTypedefs.h"

DCU_t DCU;

void DCU_Handler(void)
{
	DoorControl_t *door = &g_door;
	Vehicle_Speed_Status = Get_Vechicle_Speed_Status();
	static DCU_MovementReq_t DCU_MovementReq_Old = Stop;
	static DCU_MovementReq_t DCU_Movement_Cmd ;
	DCU_Movement_Cmd = DCU.MovementReq;

	if((DCU_Movement_Cmd != DCU_MovementReq_Old))
	{
		if((DCU_Movement_Cmd == Opening)  && (DCU.PDS_SETINGS == AUTO)
											&& (DCU.LatchState == LatchState_Opened)
											&& (TCU.Vehicle_speed_valid == Valid)
											&& (Vehicle_Speed_Status == SLOW))
		{
			door->DoorCmd = DOOR_CMD_OPEN;
		}
		else if ((DCU_Movement_Cmd == Closing) && (DCU.PDS_SETINGS == AUTO)
												&& ((TCU.Vehicle_speed_valid == Valid)))
		{
			door->DoorCmd = DOOR_CMD_CLOSE;
		}
		else if ((DCU_Movement_Cmd == Stop) && (door->state == DOOR_STATE_OPENNING))
		{
			door->DoorCmd = DOOR_CMD_STOP;
		}
		else if ((DCU_Movement_Cmd == Stop) && (door->state == DOOR_STATE_CLOSING))
		{
			door->DoorCmd = DOOR_CMD_STOP;
		}
		DCU_MovementReq_Old = DCU_Movement_Cmd;
		DCU_Movement_Cmd ;
	}
	if ((Vehicle_Speed_Status == HIGH) && (DCU.PDS_SETINGS == AUTO)
										&& (TCU.Vehicle_speed_valid == Valid)
										&& ((door->state == DOOR_STATE_OPENNING)
										|| (door->state == DOOR_STATE_STOP)))
	{
		door->DoorCmd = DOOR_CMD_CLOSE;
	}


}
