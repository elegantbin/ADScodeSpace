/*
 * TCU.h
 *
 *  Created on: 2024Äê1ÔÂ2ÈÕ
 *      Author: lenovo
 */

#ifndef _0_APPSW_TCU_H_
#define _0_APPSW_TCU_H_

#include "Cpu.h"
#include <CanMsgHandler/CanIf_MsgHandler.h>
#include "CanIf_Msg.h"
#include "CanIfCfg_Msg.h"

#define VehSlowSpeed_Cfg (3U)


typedef enum Vehicle_speed_valid
{
	Valid,
	Invalid,
}Vehicle_speed_valid_t;


typedef struct TCU
{
	uint16_t				Vehicle_Speed;
	Vehicle_speed_valid_t	Vehicle_speed_valid;
	uint8_t		Checksum;
	uint8_t		RollingCounter;
}TCU_t;

typedef enum Vehicle_Speed_Status
{
	HIGH,
	SLOW,
	INVALID,
}Vehicle_Speed_Status_t;

extern TCU_t TCU;
extern Vehicle_Speed_Status_t Vehicle_Speed_Status;

Vehicle_Speed_Status_t Get_Vechicle_Speed_Status(void);

#endif /* 0_APPSW_TCU_H_ */
