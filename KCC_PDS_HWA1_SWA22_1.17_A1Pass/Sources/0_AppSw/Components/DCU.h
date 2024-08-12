/*
 * DCU.h
 *
 *  Created on: 2024Äê1ÔÂ2ÈÕ
 *      Author: lenovo
 */

#ifndef _0_APPSW_DCU_H_
#define _0_APPSW_DCU_H_

#include "Cpu.h"
#include <CanMsgHandler/CanIf_MsgHandler.h>
#include "CanIf_Msg.h"
#include "CanIfCfg_Msg.h"
#include "DoorSysDef.h"

typedef struct DCU
{
	DCU_LatchState_t		LatchState;
	DCU_WdState_t 			WdState;
	DCU_MovementReq_t		MovementReq;
	DCU_ManAssistForce_t	ManAssistForce;
	uint16_t				StopAngle;
	uint16_t				RqstOpenVal;
	DCU_PDS_SETINGS_t		PDS_SETINGS;
}DCU_t;

extern DCU_t DCU;

void DCU_Handler(void);

#endif /* 0_APPSW_DCU_H_ */
