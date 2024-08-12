/*
 * DoorSys_AntiPinch.h
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_ANTIPINCH_ADAPT_H_
#define _0_APPSW_DOORSYS_ANTIPINCH_ADAPT_H_
#include <OsTypedefs.h>
#include "cpu.h"


#define AP_ADAPT_CURVE_LEN   128

#define K_ADAPT_POS_MASK     (0x000FU)
#define K_ADAPT_SHIFT_POS      4
#define K_ADA_AP_MAX        (int8_t)(0x7F)

extern int8_t i8ApAdaptCurveOpen[AP_ADAPT_CURVE_LEN];
extern int8_t i8ApAdaptCurveClose[AP_ADAPT_CURVE_LEN];

void DoorsSys_ApAdaptCurveInit(void);

#endif /* _0_APPSW_DOORSYS_ANTIPINCH_ADAPT_H_ */
