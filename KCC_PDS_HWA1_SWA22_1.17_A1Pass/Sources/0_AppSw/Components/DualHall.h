/*
 * DualHall.h
 *
 *   Created on: 7.12.2023
 *      Author: Administrator
 */

#ifndef _2_CDRV_DUALHALL_H_
#define _2_CDRV_DUALHALL_H_

#include "cpu.h"

typedef struct stHallObject
{
	boolean   b_level;
	uint16_t  HallCount;
	uint16_t  HallWidth;


}stHall_t;

extern stHall_t hall_A,hall_B;

void DualHall_Init(void);

#endif /* 2_CDRV_DUALHALL_H_ */
