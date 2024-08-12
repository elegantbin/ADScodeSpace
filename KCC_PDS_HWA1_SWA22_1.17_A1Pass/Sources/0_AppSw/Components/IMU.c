/*
 * IMU.c
 *
 *  Created on: 2024Äê1ÔÂ2ÈÕ
 *      Author: lenovo
 */

#include "IMU.h"

float b_Roll = 0;
float b_Pitch = 0;
IMU_t IMU;

Roll_level_t g_Roll_level;
Pitchl_level_t  g_Pitch_level;


void IMU_Init(void)
{
	g_Roll_level = null_roll;
	g_Pitch_level = null_pitch;
}


void IMU_Handler(void)   //task
{
	if((-8<=b_Roll)&&(b_Roll<-3))
	{
		g_Roll_level=left_roll_high;
	}
	if((-3<=b_Roll)&&(b_Roll<-1))
	{
		g_Roll_level=left_roll_light;
	}
	if((-1<=b_Roll)&&(b_Roll<1))
	{
		g_Roll_level=no_roll;
	}
	if((1<=b_Roll)&&(b_Roll<3))
	{
		g_Roll_level=right_roll_light;
	}
	if((3<=b_Roll)&&(b_Roll<8))
	{
		g_Roll_level=right_roll_high;
	}
/******************************************************/
	if((-13<=b_Pitch)&&(b_Pitch<-8))
	{
		g_Pitch_level=low_pitch_high;

	}
	if((-8<=b_Pitch)&&(b_Pitch<-3))
	{
		g_Pitch_level=low_pitch_light;
	}
	if((-3<=b_Pitch)&&(b_Pitch<3))
	{
		g_Pitch_level=no_pitch;
	}
	if((3<=b_Pitch)&&(b_Pitch<8))
	{
		g_Pitch_level=up_pitch_light;
	}
	if((8<=b_Pitch)&&(b_Pitch<=13))
	{
		g_Pitch_level=up_pitch_high;
	}

}
