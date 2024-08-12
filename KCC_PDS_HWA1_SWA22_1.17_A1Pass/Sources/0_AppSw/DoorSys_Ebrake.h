/*
 * DoorSys_Velocity.h
 *
 *  Created on: 2023Äê12ÔÂ11ÈÕ
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_EBRAKE_H_
#define _0_APPSW_DOORSYS_EBRAKE_H_

#include <OsTypedefs.h>
#include "DoorSysDef.h"
#include "DoorSys.h"
#include <Roll_Pitch_Parameter.h>

#define K_EBRAKE_POS_MAX         (4000U)
#define K_EBRAKE_POS_MIN         (2100U)

#define K_VELOCITY_BRAKE        (100U)

#define K_EBRAKE_DUTY_OPEN      (5U)

#define K_EBRAKE_CHECK_COUNT     (1U)

#define K_EBRAKE_COUNT_MIN       (5U)
#define K_EBRAKE_COUNT_MAX       (1000U)

#define K_EBRAKE_TIMEOUT         (5000U)

#define K_EBRAKE_CHECK_END_COUNT (800U)

#define K_EBRAKE_DIR_CLOSE_DELTA_PERCENT   (5U)
#define K_EBRAKE_DIR_OPEN_DELTA_PERCENT    (5U)

#define K_EBRAKE_DUTY_MAX                   (8)
#define K_EBRAKE_DUTY_MAX_IMU				(gOpen_Roll_Pitch_ParaSet.EbrakDuty)


typedef enum enEbrakeDir
{
	K_EBRAKE_DIR_OPEN,
	K_EBRAKE_DIR_CLOSE

}enBbrake_t ;

typedef struct stEBrake
{
	boolean  b_eBrakEnable;
	boolean  b_eBrake;

	enBbrake_t eBrakeDir;
	uint16_t u16eBrakeDuty;

	int16_t i16eBrake_count;

	uint16_t u16eBreakPosMax;
    uint16_t u16eBreakPosMin;

	uint16_t u16eBrakeTimeCount;
	uint16_t u16eBrakeTimeout;

	uint16_t u16Realtime_Pos;
	uint16_t u16Lasttime_Pos;



}stEBrakeControl;

extern stEBrakeControl g_ebrake;
void DoorSys_eBrakeInit(void);
void DoorSys_eBrakeCheck(void);
void DoorSys_EventeBrakeHandler(DoorControl_t *door);



void DoorSys_eBrakeControl(void);

#endif /* 0_APPSW_DOORSYS_VELOCITY_H_ */
