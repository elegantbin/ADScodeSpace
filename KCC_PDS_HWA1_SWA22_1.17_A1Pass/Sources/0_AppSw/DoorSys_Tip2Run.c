/*
 * DoorSys_Tip2Run.c
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */
#include <MotAct.h>
#include "DoorSysCfg.h"
#include "DoorSys.h"
#include "DoorSys_Tip2Run.h"


void DoorSys_TipToRunCheck(void)
{
	DoorControl_t *door=&g_door;

	MotorActator_Control *motor = &g_motor;

	/* Tip2run zone check*/
	if((door->u16Realtime_Pos < door->u16Tip2RunPosMax)&&
			(door->u16Realtime_Pos > door->u16SoftClosePos)&&
			(motor->state == MOTOR_STATUE_STOP)&&
			(motor->u16MotStopCount > K_TIP2RUN_START_COUNT))
	{
			if(door->u16Tip2run_Width < K_TIP2RUN_CHECK_POINT1)
			{
				door->u16Tip2run_Width++;
				if(door->u16Tip2run_Width == 1)
				{
					door->u16Lasttime_Pos = door->u16Realtime_Pos;
					door->i16Tip2run_Count = 0;
				}

				if(door->u16Tip2run_Width == 2)
				{
					door->i16Tip2run_Count = 5;
				}
				if(door->u16Tip2run_Width == 3)
				{
					door->i16Tip2run_Count = 0;
				}

				if(door->u16Tip2run_Width == K_TIP2RUN_CHECK_POINT0)
				{

					if(door->u16Lasttime_Pos  > door->u16Realtime_Pos)  /* Tip2Run only check close direction*/
					{
						door->i16Tip2run_Count = door->u16Lasttime_Pos - door->u16Realtime_Pos;

						if((door->i16Tip2run_Count > K_TIP2RUN_COUNT_MIN0)&&
								(door->i16Tip2run_Count < K_TIP2RUN_COUNT_MAX0))
						{
								/* Passed the 1st check */
								door->u16Lasttime_Pos = door->u16Realtime_Pos;
						}
						else
						{
							/*Reset */
							door->u16Tip2run_Width = 0;
							door->u16Lasttime_Pos = door->u16Realtime_Pos;
						}
				    }
				}

			}
			else
			{
				door->u16Tip2run_Width = 0;

				if(door->u16Lasttime_Pos > door->u16Realtime_Pos)
				{
					door->i16Tip2run_Count = door->u16Lasttime_Pos - door->u16Realtime_Pos;

					if(door->i16Tip2run_Count > K_TIP2RUN_COUNT_MIN1)
					{
						if(door->i16Tip2run_Count < K_TIP2RUN_COUNT_MAX1)
						{

							/* Trigger the event when 2nd chek */
							door->event = DOOR_EVENT_TIP2RUN;

						}
						else
						{
							door->u16Lasttime_Pos = door->u16Realtime_Pos;
						}
					}
					else
					{
						 door->u16Lasttime_Pos = door->u16Realtime_Pos;
					}
				}
				else
				{
					/*Tips:
					 * Pos is not change:
					 * door->u16Lasttime_Pos == door->u16Realtime_Pos
					 * Reset the counter
					 */
				}
		   }
	}
	else
	{
		/* Tips:
		 * 1.There is not the tip2run zone
		 * 2.The motor state is not in stop state,
		 * 3.The motor is not stop cmpletely
		 * Do nothing.
		 */
		door->u16Tip2run_Width = 0;
	}

}


void DoorSys_EventTipToRunHander(DoorControl_t *door)
{
	if(door->event == DOOR_EVENT_TIP2RUN)
	{
		door->u16Target_Pos = door->u16SoftClosePos;

		if (door->u16Realtime_Pos > door->u16Target_Pos)
		{

			door->DoorCmd = DOOR_CMD_CLOSE;

			door->u16BlockCount = K_BLOCK_COUNT;
		}
	}

	door->b_tip2run = 1;
}
