/*
 * DoorSysDef.h
 *
 *  Created on:  
 *      Author: Administrator
 */

#ifndef _0_APPSW_DOORSYS_APDEF_H_
#define _0_APPSW_DOORSYS_APDEF_H_

#include "OsTypedefs.h"
 
typedef struct sAntiPinch_def
{
	boolean  b_open_antipinch;
	boolean  b_close_antipinch;

	volatile boolean  b_ApCalEnable;
	boolean b_ApInfoSend;

	boolean b_PosCalibrated;
	uint16_t  lu16ApCalCounter;

	uint16_t position;
	uint16_t voltage;
	uint16_t current;

}sAntiPinch_t;
 
#endif /* 0_APPSW_DOORSYS_APDEF_H_ */
