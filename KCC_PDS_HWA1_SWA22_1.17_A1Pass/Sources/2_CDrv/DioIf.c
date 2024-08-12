/*
 * DioIf.c
 *
 *   Created on: 7.12.2023
 *      Author: Administrator
 */

#include "DioIf.h"



void DioIf_Init(void)
{
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);


}
