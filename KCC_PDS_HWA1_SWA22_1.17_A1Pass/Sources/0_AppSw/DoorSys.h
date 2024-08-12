/*
 * Door.h
 *
 *  Created on: 7.12.2023
 *      Author: Administrator
 */

#ifndef _APPSW_DOOR_H_
#define _APPSW_DOOR_H_

#include <OsTypedefs.h>
#include "DoorSysDef.h"
#include "DoorSysCfg.h"

#include "DoorSys_AntiPinch.h"
#include "DoorSys_Tip2run.h"
#include "DoorSys_Block.h"
#include "DoorSys_Pos.h"
#include <DoorSys_Assist.h>
#include "DoorSys_Velocity.h"
#include "DoorSys_Ebrake.h"
#include "DoorSys_Velocity.h"

void DoorSys_Init(void);
void DoorSys_CmdHandle(void);
void DoorSys_EventHandle(void);
void DoorSys_StateMachine(void);

#endif /* 0_APPSW_DOOR_H_ */
