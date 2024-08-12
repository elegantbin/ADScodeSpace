/*
 * FlashIf.h
 *
 *  Created on: 2024Äê3ÔÂ20ÈÕ
 *      Author: lenovo
 */

#ifndef _2_CDRV_FLASHIF_H_
#define _2_CDRV_FLASHIF_H_

#include "Cpu.h"
#include "Flash1.h"


typedef struct
{
	uint32_t Open_Pos_Learned;
	uint32_t Close_Pos_Learned;
	uint32_t Door_Cur_Pos;
}Pos_Storage_t;



void Flash_Init(void);
void DFlash_Erase_All(void);
void FlaxRam_Read(void);
void FlaxRam_Write(void);
void DFlash_Write_Bytes(uint32_t dest, uint32_t size, const uint8_t * pData);
void CanDFlash_TxMessage(void);
#endif /* 2_CDRV_FLASHIF_H_ */
