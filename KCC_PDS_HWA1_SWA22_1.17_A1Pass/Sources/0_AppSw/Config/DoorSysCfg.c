/*
 * DoorCfg.c
 *
 *  Created on: 2023Äê12ÔÂ7ÈÕ
 *      Author: Administrator
 */

#include <Config/DoorSysCfg.h>


const DoorSysPosCfg_t g_DoorSysPosCfg =
{
		.Open_Door_Soft_STOP  = 3150,
		.Close_Door_Soft_STOP = 2100,
		.P2 = 0,
		.P3 = 0,
		.P4 = 0,
		.u16PosPowerUpInit = 2000,
		.u16PosMax = 5000,
		.u16PosMin = 100
};
