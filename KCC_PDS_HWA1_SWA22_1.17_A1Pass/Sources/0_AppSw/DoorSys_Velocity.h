/*
 * DoorSys_Velocity.h
 *
 *  Created on: 2023Äê12ÔÂ11ÈÕ
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_VELOCITY_H_
#define _0_APPSW_DOORSYS_VELOCITY_H_

#include <OsTypedefs.h>
#include "DoorSysDef.h"
#include "DoorSys.h"
#include "DoorSysCfg_velocity.h"
#define K_PWX_LEN  (8)
#define K_PULSE_WIDTH_MAX   (0xFFFF)
#define K_PULSE_WIDTH_MIN   (1000)

#define AP_PW_TO_N_NUMERATOR (4E7)

#define K_SPEED_ARRAY_LEN    (4)
#define K_VELOCITY_MAX          (6000)
#define K_VELOCITY_MIN          (0)

#define K_VELOCITY_DUTY_60_PERCENT     (60)
#define K_VELOCITY_DUTY_80_PERCENT     (80)
#define K_VELOCITY_DUTY_100_PERCENT    (100)

#define K_VELOCITY_DUTY_STARTUP_END    (K_VELOCITY_DUTY_60_PERCENT)
#define K_VELOCITY_DUTY_PERCENT     (30)

#define K_VELOCITY_DUTY_MAX     (95)
#define K_VELOCITY_DUTY_MIN     (10)

#define K_VELOCITY_CTRL_COUNT (0)

void DoorSys_VelocityInit(void);
void DoorSys_VelocityClosingControl(void);
void DoorSys_VelocityOpeningControl(void);


void DoorSys_VelocityEvaluate(void);
uint16_t* DoorSys_getVelocityArray(void);
void DoorSys_VelocityReset(void);

#endif /* 0_APPSW_DOORSYS_VELOCITY_H_ */
