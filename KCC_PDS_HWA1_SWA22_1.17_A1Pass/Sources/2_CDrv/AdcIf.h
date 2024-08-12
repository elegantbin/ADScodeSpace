/*
 * AdIf.h
 *
 *   Created on: 7.12.2023
 *      Author: Administrator
 */

#ifndef _2_CDRV_ADIF_H_
#define _2_CDRV_ADIF_H_


/* Shunt amplifier gain setting 10V/V*/

#include "Cpu.h"

extern float Current;

void AdcIf_Init(void);
float AdcIf_readCurrent(void);

#endif /* 2_CDRV_ADIF_H_ */
