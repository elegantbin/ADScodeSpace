/*
 * DoorSysDef.h
 *
 *  Created on: 2023��12��9��
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYSDEF_H_
#define _0_APPSW_DOORSYSDEF_H_

#include "OsTypedefs.h"


typedef enum DoorCmd
{
	DOOR_CMD_NOCMD,
	DOOR_CMD_STOP,
	DOOR_CMD_OPEN,
	DOOR_CMD_AP_OPEN,
	DOOR_CMD_CLOSE

}DoorCmd_t;


typedef enum DoorState
{
	DOOR_STATE_STOP,
	DOOR_STATE_OPENNING,
	DOOR_STATE_CLOSING,
	DOOR_STATE_UNKNOWN

}enDoorState_t;


typedef enum DoorEvent
{
	DOOR_EVENT_NULL,
	DOOR_EVENT_AP,
	DOOR_EVENT_TIP2RUN,
	DOOR_EVENT_ASSIST_MODE,
	DOOR_EVENT_BLOCK,
	DOOR_EVENT_EBRAKE

}enDoorEvent_t;

typedef struct DoorControl
{
	DoorCmd_t DoorCmd;

	volatile uint16_t  u16Realtime_Pos;
	uint16_t  u16Target_Pos;
	uint16_t  u16Lasttime_Pos;
	enDoorState_t state;
	enDoorEvent_t event;

	uint16_t u16BlockCount;
	int16_t i16Tip2run_Count;
	uint16_t u16Tip2run_Width;

	boolean  b_PosCloseLearned;
	boolean  b_PosOpenLearned;

	boolean  b_open_block;
	boolean  b_close_block;
	boolean  b_open_antipinch;
	boolean  b_close_antipinch;
	boolean  b_assisting;
	boolean  b_tip2run;
	boolean  b_ebrake;


	boolean  b_dir_open;
	boolean  b_dir_close;
	volatile boolean  b_dir_open_fbk;
	volatile boolean  b_dir_close_fbk;

	uint16_t u16Tip2RunPosMax;

	uint16_t u16ManualAssistPosMax;
	uint16_t u16ManualAssistPosMin;

	uint16_t u16SoftClosePos;
	uint16_t u16SoftOpenPos;

	uint16_t u16HardClosePos;
	uint16_t u16HardOpenPos;

	uint16_t u16PosMax;
	uint16_t u16PosMin;

	uint16_t u16Velocity;
	volatile boolean  b_VelocityUpdate;
	volatile boolean  b_BlockUpdated;



}DoorControl_t;

extern DoorControl_t g_door;


#endif /* 0_APPSW_DOORSYSDEF_H_ */

