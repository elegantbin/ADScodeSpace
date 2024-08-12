#include "DoorSys_Pos.h"

boolean DoorSys_OpeningPosCheck(DoorControl_t *door)
{
	boolean b_pos_reached = 0;
	if(door->b_PosOpenLearned)
	{
		if (door->u16Realtime_Pos > door->u16Target_Pos)
		{
			b_pos_reached = 1;
		}

		if (door->u16Realtime_Pos > door->u16SoftOpenPos)
		{
			b_pos_reached = 1;
		}
	}

	if (door->u16Realtime_Pos > door->u16PosMax)
	{
		b_pos_reached = 1;
	}

	return b_pos_reached;
}

boolean DoorSys_ClosingPosCheck(DoorControl_t *door)
{
	boolean b_pos_reached = 0;

	if(door->b_PosCloseLearned)
	{
		if (door->u16Realtime_Pos < door->u16Target_Pos)
		{
			b_pos_reached = 1;
		}

		if (door->u16Realtime_Pos < door->u16SoftClosePos)
		{
			b_pos_reached = 1;
		}
	}

	if (door->u16Realtime_Pos < door->u16PosMin)
	{
		b_pos_reached = 1;
	}

	return b_pos_reached;
}

void DoorSys_PosLearn(DoorControl_t *door)
{
	if (door->b_PosCloseLearned != 1)
	{
		if (door->b_dir_close)
		{
			door->u16Realtime_Pos = g_DoorSysPosCfg.u16PosPowerUpInit;
			door->u16HardClosePos = door->u16Realtime_Pos;
			door->u16SoftClosePos = door->u16Realtime_Pos + K_POS_CLOSE_SOFT_DELTA;


		    door->u16ManualAssistPosMin = door->u16Realtime_Pos + K_POS_ASSIT_LEN_MIN;

			door->b_PosCloseLearned = 1;
		}
	}
	else
	{
		/*Close init first, and then Open init is enable*/
		if (door->b_PosOpenLearned != 1)
		{
			if (door->b_dir_open)
			{
				door->u16SoftOpenPos = door->u16Realtime_Pos - K_POS_OPEN_SOFT_DELTA;
				door->u16HardOpenPos = door->u16Realtime_Pos;

				door->u16Tip2RunPosMax =  door->u16SoftOpenPos;
				door->u16ManualAssistPosMax = door->u16SoftOpenPos;

			    door->u16ManualAssistPosMax = door->u16SoftOpenPos;

				door->b_PosOpenLearned = 1;
			}
		}
	}
}
