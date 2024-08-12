/*
 * IMU.h
 *
 *  Created on: 2024Äê1ÔÂ2ÈÕ
 *      Author: lenovo
 */

#ifndef _0_APPSW_IMU_H_
#define _0_APPSW_IMU_H_

#include "Cpu.h"
#include <CanMsgHandler/CanIf_MsgHandler.h>
#include "CanIf_Msg.h"
#include "CanIfCfg_Msg.h"


typedef enum LatAccelSigSta
{
	No_failure,
	IMU_Lateral_acceleration_failure,
	Initialization_is_running,
	IMU_Lateral_acceleration_failure_AND_Initialization_is_running,
}LatAccelSigSta_t;


typedef struct IMU
{
	LatAccelSigSta_t LatAccelSigSta;
	LatAccelSigSta_t LongAccelSigSta;
	uint8_t LatAccelVal;
	uint8_t LongAccelVal;
}IMU_t;


typedef enum Roll_level
{
	null_roll	,		//No Signal
	left_roll_high,   	//[-6,-3)
	left_roll_light,	//[-3,-1)
	no_roll,			//[-1,1)
	right_roll_light,	//[1,3)
	right_roll_high,	//[3,6]


}Roll_level_t;


typedef enum Pitch_level
{
	null_pitch,
	up_pitch_high,		//[12,8)
	up_pitch_light,		//[8, 3)
	no_pitch,			//[3,-3)
	low_pitch_light,   	//[-3,8)
	low_pitch_high,    //[-8,-12]


}Pitchl_level_t;


extern Roll_level_t  g_Roll_level;
extern Pitchl_level_t  g_Pitch_level;


extern IMU_t IMU;
extern float b_Roll;
extern float b_Pitch;

void IMU_Handler(void);

#endif /* 0_APPSW_IMU_H_ */
