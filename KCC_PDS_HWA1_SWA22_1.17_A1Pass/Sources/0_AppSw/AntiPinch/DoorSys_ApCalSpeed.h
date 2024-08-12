/*
 * DoorSys_AntiPinch.h
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_APCALVELOCITY_H_
#define _0_APPSW_DOORSYS_APCALVELOCITY_H_
#include <OsTypedefs.h>
#include "cpu.h"
#include "DoorSys_ApAdapt.h"

#define K_UMOT_SHIFT_SCALE     (7)
#define K_APSPEED_SHIFT_SCALE  (0)
#define K_VOLTAGE_AD_MIN         (30)
#define K_VOLTAGE_AD_MAX         (160)

#define K_AP_VELOCITY_UBAT_SCALING  (60)
#define K_AP_CALSPEED_ARRAY_LEN  (4)
extern uint16_t u16ApSpeed[K_AP_CALSPEED_ARRAY_LEN];

uint16_t Ap_ApSpeed(uint16_t u16Velocity,uint8_t u8Voltage, uint8_t u8Duty);
void Ap_ApSpeedReset(void);
#endif /* _0_APPSW_DOORSYS_APCALVELOCITY_H_ */
