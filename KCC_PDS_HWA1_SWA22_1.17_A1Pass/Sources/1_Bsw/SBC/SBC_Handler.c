/*
 * SBC_Handler.c
 *
 *  Created on: 2024Äê3ÔÂ6ÈÕ
 *      Author: lenovo
 */

#include <CanIf_Msg.h>
#include "CanIf.h"
#include <CanIfCfg_Msg.h>
#include <CanMsgHandler/CanIf_Signals.h>
#include <CanMsgHandler/CanIf_Unpack.h>
#include "CanIf_Msg.h"
#include "SBC_Handler.h"

void SBC_Sleep_Handler(void)
{
	can_message_t *msg = &g_RecvMsg_CAN0;

	uint8_t SBC_Cmd = 0;

	SBC_Cmd = CanIf_MsgUnpack(msg->data,0,1);

	if (SBC_Cmd == 1)
	{
		SBC_CyclicSense();
		SBC_Sleep_Mode();
		SBC_Cmd = 0;
	}
	else
	{

	}
/*	DCU_RR_340.DCU_RRMovementReq =(DCU_MovementReq_t)CanIf_MsgUnpack(msg->data,4,2);

	if(DCU_RR_340.DCU_RRMovementReq == 	Opening)
	{
		door->DoorCmd = DOOR_CMD_OPEN;
	}
	else if(DCU_RR_340.DCU_RRMovementReq == Closing)
	{
		door->DoorCmd = DOOR_CMD_CLOSE;
	}
	else if(DCU_RR_340.DCU_RRMovementReq == Stop)
	{
		door->DoorCmd = DOOR_CMD_STOP;
	}*/

}
