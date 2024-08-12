/*
 * DoorSys_Block.c
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */
#include <MotAct.h>
#include "DoorSys.h"
#include "DualHall.h"
#include "DoorSys_Block.h"

boolean DoorSys_BlockCheck(void)  //5ms Task
{
	DoorControl_t* door = &g_door;
    boolean b_block;
	if (door->b_BlockUpdated != FALSE)
	{
		door->u16BlockCount = K_BLOCK_COUNT;
		door->b_BlockUpdated = 0;
	}
	else
	{
		if (door->u16BlockCount > 0)
		{
			door->u16BlockCount--;


			if (door->u16BlockCount == 0)
			{
				if(DOOR_STATE_OPENNING==door->state)
				{
				     door->event = DOOR_EVENT_BLOCK;
				}
				else if(DOOR_STATE_CLOSING==door->state)
				{ 
					 door->event = DOOR_EVENT_BLOCK;
				}
			}
		}

	}

	b_block=( DOOR_EVENT_BLOCK == door->event);

	return b_block;
}


void DoorSys_EventBlockHandler(DoorControl_t *door)
{	
	MotorActator_Stop();
	
	if ((door->b_PosCloseLearned != 1)||(door->b_PosOpenLearned != 1))
	{			
			DoorSys_PosLearn(door);   
	}
	else
	{
		if(door->state == DOOR_STATE_OPENNING)
		{
			if((door->b_close_antipinch!=1)&&(door->b_open_antipinch!=1)&&
							(door->b_open_block !=1 )&&(door->b_close_block !=1 )&&
							(door->b_assisting !=1 )&&(door->b_tip2run !=1 ))
			{
/*				door->u16Target_Pos = door->u16Realtime_Pos - K_AP_OPEN_REVERSE_LEN;

				MotorActator_Start(K_DOOR_DIR_CMD_CLOSE);

				door->state = DOOR_STATE_CLOSING;
				door->u16BlockCount = K_BLOCK_COUNT;
				
				door->b_dir_open = 0;
				door->b_dir_close = 1;*/
			}
			else
			{
				MotorActator_Stop();
			}
               
			door->b_open_block = 1;
			
		}
		else if(door->state == DOOR_STATE_CLOSING)
		{
			if((door->b_close_antipinch!=1)&&(door->b_open_antipinch!=1)&&
							(door->b_open_block !=1 )&&(door->b_close_block !=1 )&&
							(door->b_assisting !=1 )&&(door->b_tip2run !=1 ))
			{
				door->u16Target_Pos = door->u16Realtime_Pos + K_AP_CLOSE_REVERSE_LEN;

				MotorActator_Start(K_DOOR_DIR_CMD_OPEN);

				door->state = DOOR_STATE_OPENNING;
				door->u16BlockCount = K_BLOCK_COUNT; 

				door->b_dir_open = 1;
				door->b_dir_close = 0;
			}
			else
			{
				MotorActator_Stop();
			}


			door->b_close_block = 1;
		}
	}
}
