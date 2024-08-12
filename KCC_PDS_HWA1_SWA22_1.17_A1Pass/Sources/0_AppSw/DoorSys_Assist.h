/*
 * DoorSys_Assist.h
 *
 *  Created on: 2023Äê12ÔÂ8ÈÕ
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_MANUALASSIST_H_
#define _0_APPSW_DOORSYS_MANUALASSIST_H_
#include "cpu.h"
#include <OsTypedefs.h>
#include "DoorSysDef.h"
#include <DoorSysCfg_Assist.h>
typedef enum enOperationSetting
{
	OPERTION_MANUAL,
	OPERTION_AUTO,

}enOperationSetting_t;

typedef enum enDoorPositionStatus
{
	OTHER_AREA,
	BEYOND_REVERSE,
	TOGGLE_AREA,
	CLOSING_ONLY

}enDoorPositionStatus_t;

typedef struct stManualAsist
{

	 boolean b_Manual_Movement_Detected;

}stManualAsist_t;

extern stManualAsist_t  g_ManualAssist;

void DoorSys_ManaualAssitCheck(void);

void DoorSys_EventManaualAssitHander(DoorControl_t *door);
#endif /* 0_APPSW_DOORSYS_MANUALASSIST_H_ */
