/*
 * DoorCfg.h
 *
 *  Created on: 7.12.2023
 *      Author: Administrator
 */

#ifndef _0_APPSW_CONFIG_DOORCFG_H_
#define _0_APPSW_CONFIG_DOORCFG_H_
#include <MotAct.h>
#include "cpu.h"
#define K_DIR_DEBUG_MOTOR     (1)
#define K_DIR_DEBUG_KCC_DOOR_SYSTEM   (2)

#define K_DIR_CONFIG   (K_DIR_DEBUG_KCC_DOOR_SYSTEM)

#if(K_DIR_CONFIG == K_DIR_DEBUG_MOTOR)
#define K_DOOR_DIR_CMD_OPEN (MOTOR_DIR_CW)
#define K_DOOR_DIR_CMD_CLOSE (MOTOR_DIR_CCW)
#elif(K_DIR_CONFIG == K_DIR_DEBUG_KCC_DOOR_SYSTEM)

#define K_DOOR_DIR_CMD_OPEN (MOTOR_DIR_CCW)
#define K_DOOR_DIR_CMD_CLOSE (MOTOR_DIR_CW)
#endif

#define K_HALL_A_DOOR_DIR_FBK_OPEN     (hall_A.b_level!=hall_B.b_level)
#define K_HALL_A_DOOR_DIR_FBK_CLOSE    (hall_A.b_level==hall_B.b_level)

#define K_HALL_B_DOOR_DIR_FBK_OPEN     (hall_A.b_level==hall_B.b_level)
#define K_HALL_B_DOOR_DIR_FBK_CLOSE    (hall_A.b_level!=hall_B.b_level)

#define HALL_A_POS_UPDATE_ENABLE   (1)
#define HALL_B_POS_UPDATE_ENABLE   (1)

#define K_POS_OPEN_TOTAL_LEN  (800)

#define K_POS_OPEN_SOFT_DELTA   (220)   /*Open stop interial ~44  @12V40%*/
#define K_POS_CLOSE_SOFT_DELTA   (50)  /*Close stop interia ~25 @12V40%*/

#define K_POS_TIP2RUN_LEN        (1500)

#define K_POS_ASSIT_LEN_MAX      (K_POS_OPEN_TOTAL_LEN)
#define K_POS_ASSIT_LEN_MIN      (100)

#define K_POS_SOFT_OPEN_LEN (K_POS_OPEN_TOTAL_LEN-K_POS_OPEN_SOFT_DELTA-K_POS_CLOSE_SOFT_DELTA)

#define K_BLOCK_COUNT    (90)    /*40*5ms=200 ms*/

#define K_AP_OPEN_REVERSE_LEN   (100)
#define K_AP_CLOSE_REVERSE_LEN   (200)

typedef struct DoorSysPosCfg
{
	uint16_t Close_Door_Soft_STOP;
	uint16_t Open_Door_Soft_STOP;
	uint16_t P2;
	uint16_t P3;
	uint16_t P4;
	uint16_t u16PosPowerUpInit;

	uint16_t u16PosMin;
	uint16_t u16PosMax;
}DoorSysPosCfg_t;

extern const DoorSysPosCfg_t g_DoorSysPosCfg;

#endif /* 0_APPSW_CONFIG_DOORCFG_H_ */
