/*
 * DoorSys_AntiPinch.h
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_ANTIPINCH_H_
#define _0_APPSW_DOORSYS_ANTIPINCH_H_
#include <OsTypedefs.h>
#include "DoorSys_ApDef.h"
#include "cpu.h"
#include "DoorSys_ApAdapt.h"
#include <Roll_Pitch_Parameter.h>



#define K_AP_CHECK_START_COUNT  (gClose_Roll_Pitch_ParaSet.TiprunStartCout)

#define K_AP_POS_MIN  (2050)
#define K_AP_POS_MAX  (5000)
#define K_AP_POS_CLOSE_REVERSE  (2350)

#define K_AP_POS_OPEN_REVERSE   (5000)
#define K_AP_OPEN_POS         (2550)




extern sAntiPinch_t g_antipinch;

void DoorSys_ApEventCheck(void);
void DoorSys_EventApHandler(DoorControl_t *door);
void DoorSys_ApInit(void);
void DoorSys_AntipinchReset(void);


inline void DoorSys_ApUpdateNotification(void)
{
	sAntiPinch_t *p_antipinch = &g_antipinch;
	p_antipinch->b_ApCalEnable = 1;
}

inline boolean DoorSys_ApInfoSendEnable(void)
{
	sAntiPinch_t *p_antipinch = &g_antipinch;
	return (1==p_antipinch->b_ApInfoSend);
}


inline void DoorSys_ApInfoSendReset(void)
{
	sAntiPinch_t *p_antipinch = &g_antipinch;
	p_antipinch->b_ApInfoSend = 0;
}

#endif /* 0_APPSW_DOORSYS_ANTIPINCH_H_ */
