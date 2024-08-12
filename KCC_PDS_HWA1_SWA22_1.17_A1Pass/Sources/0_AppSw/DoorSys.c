/*
 * Door.c
 *
 *  Created on: 7.12.2023
 *      Author: Administrator
 */
#include <MotAct.h>
#include "DoorSys.h"
#include "DoorSys_Block.h"
#include "DoorSysCfg.h"
#include "DualHall.h"
#include "DoorSys_Velocity.h"

void DoorSys_StateMachine(void)
{
	DoorControl_t *door = &g_door;
	switch (door->state)
	{
		case DOOR_STATE_STOP:
		{

			break;
		}
		case DOOR_STATE_OPENNING:
		{
			boolean b_DoorOpeningStopped = 0;

			DoorSys_VelocityOpeningControl();

			if (DoorSys_OpeningPosCheck(door))
			{
				b_DoorOpeningStopped = 1;
			}

			if (b_DoorOpeningStopped)
			{
				MotorActator_SlowDown();
				door->state = DOOR_STATE_STOP;
				door->DoorCmd = DOOR_CMD_STOP;
			}

			break;
		}
		case DOOR_STATE_CLOSING:
		{
			boolean b_DoorClosingStopped = 0;

			DoorSys_VelocityClosingControl();

			if (DoorSys_ClosingPosCheck(door))
			{
				b_DoorClosingStopped = 1;
			}

			if (b_DoorClosingStopped)
			{
				MotorActator_SlowDown();
				door->state = DOOR_STATE_STOP;
				door->DoorCmd = DOOR_CMD_STOP;

				door->b_tip2run = 0;
			}

			break;
		}
		default:
		{
			door->event = DOOR_STATE_STOP;
			break;
		}
	}
}

void DoorSys_CmdHandle(void)
{
	DoorControl_t *door = &g_door;
	switch (door->DoorCmd)
	{
	case DOOR_CMD_AP_OPEN:

			door->u16Target_Pos = K_AP_OPEN_POS;

			if(door->u16Target_Pos > door->u16Realtime_Pos)
			{
				MotorActator_Start(K_DOOR_DIR_CMD_OPEN);
				door->b_dir_open = 1;
				door->b_dir_close = 0;

				door->state = DOOR_STATE_OPENNING;
				door->event = DOOR_EVENT_NULL;
				door->u16BlockCount = K_BLOCK_COUNT;

				door->b_open_block = 0;
				door->b_close_block = 0;
				door->b_tip2run = 0;
				door->b_assisting=0;
				door->b_ebrake = 0;
			}
			door->DoorCmd = DOOR_CMD_NOCMD;
			break;
	case DOOR_CMD_OPEN:

		door->u16Target_Pos = door->u16SoftOpenPos;

		if(door->u16Target_Pos > door->u16Realtime_Pos)
		{
			MotorActator_Start(K_DOOR_DIR_CMD_OPEN);
			door->b_dir_open = 1;
			door->b_dir_close = 0;

			door->state = DOOR_STATE_OPENNING;
			door->event = DOOR_EVENT_NULL;
			door->u16BlockCount = K_BLOCK_COUNT;

			door->b_open_antipinch=0;
			door->b_close_antipinch=0;
			door->b_open_block = 0;
			door->b_close_block = 0;
			door->b_tip2run = 0;
			door->b_assisting=0;
			door->b_ebrake = 0;
		}
		door->DoorCmd = DOOR_CMD_NOCMD;
		break;
	case DOOR_CMD_CLOSE:

		door->u16Target_Pos = door->u16SoftClosePos;

		if(door->u16Target_Pos < door->u16Realtime_Pos)
		{
			MotorActator_Start(K_DOOR_DIR_CMD_CLOSE);
			door->b_dir_open = 0;
			door->b_dir_close = 1;

			door->state = DOOR_STATE_CLOSING;
			door->event = DOOR_EVENT_NULL;
			door->u16BlockCount = K_BLOCK_COUNT;

			door->b_open_antipinch=0;
			door->b_close_antipinch=0;
			door->b_open_block = 0;
			door->b_close_block = 0;
			door->b_assisting=0;
			door->b_ebrake = 0;
		}

		door->DoorCmd = DOOR_CMD_NOCMD;
		break;
	case DOOR_CMD_STOP:

		if((DOOR_STATE_OPENNING == door->state)||
				(DOOR_STATE_CLOSING == door->state))
		{
		  MotorActator_SlowDown();

		}

		door->event = DOOR_EVENT_NULL;
		door->state = DOOR_STATE_STOP;

		door->DoorCmd = DOOR_CMD_NOCMD;
		break;

	case DOOR_CMD_NOCMD:

		door->event = DOOR_CMD_NOCMD;
		break;
	default:

		door->event = DOOR_CMD_NOCMD;
		break;
	}
}

void DoorSys_EventHandle(void)
{
	DoorControl_t *door = &g_door;
	switch (door->event)
	{
	case DOOR_EVENT_NULL:

		break;
	case DOOR_EVENT_AP:
	    
		DoorSys_EventApHandler(door);
		
		door->event = DOOR_EVENT_NULL;
		break;

	case DOOR_EVENT_ASSIST_MODE:
		DoorSys_EventManaualAssitHander(door);

		door->event=DOOR_EVENT_NULL;
		break;
	case DOOR_EVENT_TIP2RUN:
		DoorSys_EventTipToRunHander(door);

		door->event=DOOR_EVENT_NULL;
		break;

	case DOOR_EVENT_BLOCK:	

		DoorSys_EventBlockHandler(door);

		door->event = DOOR_EVENT_NULL;
		break;

	case DOOR_EVENT_EBRAKE:
		DoorSys_EventeBrakeHandler(door);

		door->event=DOOR_EVENT_NULL;

	default:

		door->event = DOOR_EVENT_NULL;
		break;
	}
} 
