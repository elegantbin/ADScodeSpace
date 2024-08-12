/*
 * DoorSys_AntiPinch.h
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_AP_CHECK_H_
#define _0_APPSW_DOORSYS_AP_CHECK_H_
#include <OsTypedefs.h>
#include "cpu.h"
#include "DoorSys_ApAdapt.h"

#define K_SPEEDDIFF1_MIN     (-300)
#define K_SPEEDDIFF1_MAX     (200)
#define K_AP_SUM_RESET   (120)

#define K_DOOR_APSUM_MIN   (-5000)
#define K_DOOR_APSUM_MAX   (50)



extern int16_t  i16SpeedDiff1,i16SpeedDiff2;
extern int16_t  i16ApSum;
extern int16_t  i16ApThreshold;

void Doorsys_ApCheck(void);
void DoorSys_ApDiff(void);
#endif /* _0_APPSW_DOORSYS_AP_CHECK_H_ */
