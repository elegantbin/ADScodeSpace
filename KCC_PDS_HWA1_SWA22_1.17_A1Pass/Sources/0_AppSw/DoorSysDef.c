/*
 * DoorSysDef.h
 *
 *  Created on: 2023��12��9��
 *      Author: Administrator
 */

#include "OsTypedefs.h"
#include "DoorSysDef.h"
#include "DoorSys.h"

DoorControl_t g_door;

void DoorSys_DoorControlInit(void);

void DoorSys_Init(void)
{
	DoorSys_DoorControlInit();
	DoorSys_VelocityInit();
	DoorSys_eBrakeInit();
}

void DoorSys_DoorControlInit(void)
{
	DoorControl_t *door = &g_door;
	door->DoorCmd = DOOR_CMD_STOP;
	door->state = DOOR_STATE_STOP;
	door->event = DOOR_EVENT_NULL;

	door->u16BlockCount = K_BLOCK_COUNT;
	door->i16Tip2run_Count = 0;
	door->u16Tip2run_Width = 0;


	door->b_PosCloseLearned = 0;
	door->b_PosOpenLearned = 0;
	door->b_close_antipinch = 0;
	door->b_open_antipinch= 0;

	door->b_ebrake =0;
	door->b_dir_close = 0;
	door->b_dir_open = 0;
	door->b_dir_close_fbk = 0;
	door->b_dir_open_fbk = 0;

	door->u16Realtime_Pos = g_DoorSysPosCfg.u16PosPowerUpInit;
	door->u16Target_Pos = g_DoorSysPosCfg.u16PosMin;
	door->u16Lasttime_Pos = door->u16Realtime_Pos;

	door->u16HardClosePos = g_DoorSysPosCfg.u16PosMin;
	door->u16SoftClosePos = g_DoorSysPosCfg.u16PosMin;

	door->u16HardOpenPos = g_DoorSysPosCfg.u16PosMax;
	door->u16SoftOpenPos = g_DoorSysPosCfg.u16PosMax;

	door->u16PosMax = g_DoorSysPosCfg.u16PosMax;
	door->u16PosMin = g_DoorSysPosCfg.u16PosMin;

	door->u16Tip2RunPosMax = g_DoorSysPosCfg.u16PosMax;

	door->u16ManualAssistPosMax = g_DoorSysPosCfg.u16PosMin;
	door->u16ManualAssistPosMin = g_DoorSysPosCfg.u16PosMin;

	door->u16Velocity     = 0;
	door->b_VelocityUpdate =0;

	door->b_BlockUpdated=0;

	g_i16DoorDutyPercent = K_VELOCITY_DUTY_PERCENT;



}
