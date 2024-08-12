/*
 * DoorSys_AntiPinch.h
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_AP_LIMIT_CHECK_H_
#define _0_APPSW_DOORSYS_AP_LIMIT_CHECK_H_
#include <OsTypedefs.h>
#include "cpu.h"
#include "DoorSys_ApAdapt.h"
#include <Roll_Pitch_Parameter.h>


#define K_DOOR_APSUM_OPEN_THRESHOLD  (-2500)
#define K_DOOR_APSUM_CLOSE_THRESHOLD (-2200)

#define K_APSUM_STARTUP_OPEN     (gOpen_Roll_Pitch_ParaSet.ApSumStartup)
#define K_STARTUP_COUNT_OPEN    (gOpen_Roll_Pitch_ParaSet.ApStartupCout)

#define K_APSUM_STARTUP_CLOSE  (gClose_Roll_Pitch_ParaSet.ApSumStartup)
#define K_STARTUP_COUNT_CLOSE  (gClose_Roll_Pitch_ParaSet.ApStartupCout)

#define K_AP_POS_ZONE_BASE     (2000)
/*********************************
 *  Close Direction
 ********************************/
#define K_AP_POS_CLOSE_ZONE_0    (1600)
#define K_AP_POS_CLOSE_ZONE_1    (1400)
#define K_AP_POS_CLOSE_ZONE_2    (1200)
#define K_AP_POS_CLOSE_ZONE_3    (1000)
#define K_AP_POS_CLOSE_ZONE_4    (800)
#define K_AP_POS_CLOSE_ZONE_5    (600)
#define K_AP_POS_CLOSE_ZONE_6    (400)
#define K_AP_POS_CLOSE_ZONE_7    (200)

#define K_AP_POS_CLOSE_OFFSET_0  (-0)
#define K_AP_POS_CLOSE_OFFSET_1  (-0)
#define K_AP_POS_CLOSE_OFFSET_2  (-0)
#define K_AP_POS_CLOSE_OFFSET_3  (-0)
#define K_AP_POS_CLOSE_OFFSET_4  (-0)
#define K_AP_POS_CLOSE_OFFSET_5  (-0)
#define K_AP_POS_CLOSE_OFFSET_6  (-0)
#define K_AP_POS_CLOSE_OFFSET_7  (-0)

/*********************************
 *  Open Direction *
 ********************************/
#define K_AP_POS_OPEN_ZONE_0    (200)
#define K_AP_POS_OPEN_ZONE_1    (400)
#define K_AP_POS_OPEN_ZONE_2    (600)
#define K_AP_POS_OPEN_ZONE_3    (800)
#define K_AP_POS_OPEN_ZONE_4    (1000)
#define K_AP_POS_OPEN_ZONE_5    (1200)
#define K_AP_POS_OPEN_ZONE_6    (1400)
#define K_AP_POS_OPEN_ZONE_7    (1600)

#define K_AP_POS_OPEN_OFFSET_0  (-0)
#define K_AP_POS_OPEN_OFFSET_1  (-0)
#define K_AP_POS_OPEN_OFFSET_2  (-0)
#define K_AP_POS_OPEN_OFFSET_3  (-0)
#define K_AP_POS_OPEN_OFFSET_4  (-0)
#define K_AP_POS_OPEN_OFFSET_5  (-0)
#define K_AP_POS_OPEN_OFFSET_6  (-0)
#define K_AP_POS_OPEN_OFFSET_7  (-0)


int16_t  DoorSys_ApLimit(uint16_t u16RtPos,uint8_t b_dir_open,uint16_t startup_cnt);
#endif /* _0_APPSW_DOORSYS_AP_CHECK_H_ */
