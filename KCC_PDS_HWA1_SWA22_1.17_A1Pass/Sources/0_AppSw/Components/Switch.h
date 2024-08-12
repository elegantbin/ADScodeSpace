/*
 * DoorSys_Switch.h
 *
 *  Created on: 2023Äê12ÔÂ12ÈÕ
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_SWITCH_H_
#define _0_APPSW_DOORSYS_SWITCH_H_
#include "cpu.h"
#include <SpiIf.h>
#include "OsTypedefs.h"
#define K_SWTICH_DEBOUNCE_COUNT   (20)
#define K_SWTICH_DEBOUNTCE_MAX    (6000)

typedef enum SwitchCmd
{
	SWITCH_CMD_NOCMD,
	SWITCH_CMD_STOP,
	SWITCH_CMD_OPEN,
	SWITCH_CMD_CLOSE

}enSwitchCmd_t;

typedef struct SwichStrut
{
	enSwitchCmd_t cmd;
	uint16      u16DebounceCount;
	boolean     b_actived;

	uint16_t adVal;

	uint8_t cmdIndex;

}stSwich_t;

extern stSwich_t g_switch;

void Switch_Init(void);
uint16_t Switch_Check(void);
void Switch_CmdHandler(void);


#endif /* 0_APPSW_DOORSYS_SWITCH_H_ */
