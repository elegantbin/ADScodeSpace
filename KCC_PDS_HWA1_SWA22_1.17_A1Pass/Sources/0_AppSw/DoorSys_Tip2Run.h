/*
 * DoorSys_Tip2Run.h
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_TIP2RUN_H_
#define _0_APPSW_DOORSYS_TIP2RUN_H_

#include "DoorSysdef.h"
#include "DualHall.h"

#define K_TIP2RUN_COUNT_MIN0    (25)
#define K_TIP2RUN_COUNT_MAX0    (100)


#define K_TIP2RUN_COUNT_MIN1    (18)
#define K_TIP2RUN_COUNT_MAX1    (1000)

#define K_TIP2RUN_CHECK_POINT1         (20)
#define K_TIP2RUN_CHECK_POINT0         (10)

#define K_TIP2RUN_START_COUNT          (800)

void DoorSys_TipToRunCheck(void);
void DoorSys_EventTipToRunHander(DoorControl_t *door);
#endif /* 0_APPSW_DOORSYS_TIP2RUN_H_ */
