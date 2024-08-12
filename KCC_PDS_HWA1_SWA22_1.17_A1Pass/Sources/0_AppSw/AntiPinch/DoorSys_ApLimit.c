/*
 * DoorSys_AntiPinch.c
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#include "DoorSys_Aplimit.h"
#include <Roll_Pitch_Parameter.h>



int16_t  DoorSys_ApLimit(uint16_t u16RtPos,uint8_t b_dir_open,uint16_t startup_cnt)
{
	int16_t i16RetLimit = 0;

	if(K_AP_POS_ZONE_BASE < u16RtPos)
	{
		uint16_t pos = u16RtPos - K_AP_POS_ZONE_BASE;

		if(b_dir_open)
		{
			/*********************************
			 *  Open Direction *
			 ********************************/
			i16RetLimit = K_DOOR_APSUM_OPEN_THRESHOLD;

			if(startup_cnt < K_STARTUP_COUNT_OPEN)
			{
				i16RetLimit += K_APSUM_STARTUP_OPEN;
			}

			if(pos < K_AP_POS_OPEN_ZONE_0)
			{
				i16RetLimit += K_AP_POS_OPEN_OFFSET_0;
				i16RetLimit += gOpen_Roll_Pitch_ParaSet.ApPosOffset[0];
			}
			else if(pos < K_AP_POS_OPEN_ZONE_1)
			{
				i16RetLimit += K_AP_POS_OPEN_OFFSET_1;
				i16RetLimit += gOpen_Roll_Pitch_ParaSet.ApPosOffset[1];
			}
			else if(pos < K_AP_POS_OPEN_ZONE_2)
			{
				i16RetLimit += K_AP_POS_OPEN_OFFSET_2;
				i16RetLimit += gOpen_Roll_Pitch_ParaSet.ApPosOffset[2];
			}
			else if(pos < K_AP_POS_OPEN_ZONE_3)
			{
				i16RetLimit += K_AP_POS_OPEN_OFFSET_3;
				i16RetLimit += gOpen_Roll_Pitch_ParaSet.ApPosOffset[3];
			}
			else if(pos < K_AP_POS_OPEN_ZONE_4)
			{
				i16RetLimit += K_AP_POS_OPEN_OFFSET_4;
				i16RetLimit += gOpen_Roll_Pitch_ParaSet.ApPosOffset[4];
			}
			else if(pos < K_AP_POS_OPEN_ZONE_5)
			{
				i16RetLimit += K_AP_POS_OPEN_OFFSET_5;
				i16RetLimit += gOpen_Roll_Pitch_ParaSet.ApPosOffset[5];
			}
			else if(pos < K_AP_POS_OPEN_ZONE_6)
			{
				i16RetLimit += K_AP_POS_OPEN_OFFSET_6;
				i16RetLimit += gOpen_Roll_Pitch_ParaSet.ApPosOffset[6];
			}
			else if(pos < K_AP_POS_OPEN_ZONE_7)
			{
				i16RetLimit += K_AP_POS_OPEN_OFFSET_7;
				i16RetLimit += gOpen_Roll_Pitch_ParaSet.ApPosOffset[7];
			}
			else
			{
				/* No Offset */
			}
		}
		else
		{
			/*********************************
			 *  Close Direction    *
			 ********************************/
			i16RetLimit = K_DOOR_APSUM_CLOSE_THRESHOLD;
			if(startup_cnt < K_STARTUP_COUNT_CLOSE)
			{
				i16RetLimit += K_APSUM_STARTUP_CLOSE;

			}
			if(pos > K_AP_POS_CLOSE_ZONE_0)
			{
				i16RetLimit += K_AP_POS_CLOSE_OFFSET_0;
				i16RetLimit += gClose_Roll_Pitch_ParaSet.ApPosOffset[0];
			}
			else if(pos > K_AP_POS_CLOSE_ZONE_1)
			{
				i16RetLimit += K_AP_POS_CLOSE_OFFSET_1;
				i16RetLimit += gClose_Roll_Pitch_ParaSet.ApPosOffset[1];
			}
			else if(pos > K_AP_POS_CLOSE_ZONE_2)
			{
				i16RetLimit += K_AP_POS_CLOSE_OFFSET_2;
				i16RetLimit += gClose_Roll_Pitch_ParaSet.ApPosOffset[2];
			}
			else if(pos > K_AP_POS_CLOSE_ZONE_3)
			{
				i16RetLimit += K_AP_POS_CLOSE_OFFSET_3;
				i16RetLimit += gClose_Roll_Pitch_ParaSet.ApPosOffset[3];
			}
			else if(pos > K_AP_POS_CLOSE_ZONE_4)
			{
				i16RetLimit += K_AP_POS_CLOSE_OFFSET_4;
				i16RetLimit += gClose_Roll_Pitch_ParaSet.ApPosOffset[4];
			}
			else if(pos > K_AP_POS_CLOSE_ZONE_5)
			{
				i16RetLimit += K_AP_POS_CLOSE_OFFSET_5;
				i16RetLimit += gClose_Roll_Pitch_ParaSet.ApPosOffset[5];
			}
			else if(pos > K_AP_POS_CLOSE_ZONE_6)
			{
				i16RetLimit += K_AP_POS_CLOSE_OFFSET_6;
				i16RetLimit += gClose_Roll_Pitch_ParaSet.ApPosOffset[6];
			}
			else if(pos > K_AP_POS_CLOSE_ZONE_7)
			{
				i16RetLimit += K_AP_POS_CLOSE_OFFSET_7;
				i16RetLimit += gClose_Roll_Pitch_ParaSet.ApPosOffset[7];
			}
			else
			{
				/* No Offset */
			}
		}
	}

     return i16RetLimit;
}



