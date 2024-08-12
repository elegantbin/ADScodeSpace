/*
 * DoorSysCfg_ManualAsist.h
 *
 *  Created on: 8.12.2023
 *      Author: Administrator
 */

#ifndef _0_APPSW_CONFIG_DOORSYSCFG_MANUALASIST_H_
#define _0_APPSW_CONFIG_DOORSYSCFG_MANUALASIST_H_
#include "cpu.h"

typedef enum enAsistParamterGroup
{
	ASSIST_PARA_LIGHT,
	ASSIST_PARA_STANDARD,
	ASSIST_PARA_HEAVY,
	ASSIST_PARA_COUNTS
}enAsistParamterGroup;


typedef struct stManualAssistCfg
{
	uint32_t AssistOperationForce_Cfg;

}stManualAssistCfg_t;

extern stManualAssistCfg_t doorManualAsssitCfg;

#endif /* 0_APPSW_CONFIG_DOORSYSCFG_MANUALASIST_H_ */
