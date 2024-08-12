/*
 * FlashIf.c
 *
 *  Created on: 2024年3月20日
 *      Author: lenovo
 */

#include "FlashIf.h"
#include "DoorSys.h"

#include <CanIf_Msg.h>
#include <CanIfCfg_Msg.h>
#include "CanIf.h"

#define EEPROM
#define DFLASH_STARTING_ADDRESS_CloPos		(0x10000000U)
#define DFLASH_STARTING_ADDRESS_OpnPos		(0x10000000U + 0x08U)
#define DFLASH_STARTING_ADDRESS_CurPos		(0x10000000U + 0x10U)

/* Declare a FLASH config struct which initialized by FlashInit, and will be used by all flash operations */
flash_ssd_config_t flashSSDConfig;

/* Data source for program operation */
#define BUFFER_SIZE         0x20u          /* Size of data source */
uint8_t sourceBuffer[BUFFER_SIZE];

#define MEM(address)                *((uint32 *)(address))      /* Macro to simplify the access to a memory address */

/* Function declarations
void CCIF_Handler(void);*/

status_t ret;

uint32_t address;

uint32_t size;
uint32_t failAddr;
uint32_t i;
flash_callback_t pCallBack;

static uint8_t flashResult = 0;

uint32_t EEPROM_BaseAddress = 0;

Pos_Storage_t Pos_Storage;


void Flash_Init(void)
{


	//	/* Disable cache to ensure that all flash operations will take effect instantly, this is device dependent */
//	    MSCM->OCMDR[0u] |= MSCM_OCMDR_OCM1(0x3u);
//	    MSCM->OCMDR[1u] |= MSCM_OCMDR_OCM1(0x3u);

	    flashResult = FLASH_DRV_Init(&Flash1_InitConfig0, &flashSSDConfig);
	#ifdef LOG_printf
		SEGGER_RTT_printf(0,"flash init T(0)/F(!0) %d\n", flashResult);
	#endif

	// 将flexRAM配置为EEPROM用于保存用户数据
	#ifdef EEPROM
		if(flashSSDConfig.EEESize == 0u)
		{
			/* Configure FlexRAM as EEPROM and FlexNVM as EEPROM backup region,
			 * DEFlashPartition will be failed if the IFR region isn't blank.
			 * Refer to the device document for valid EEPROM Data Size Code
			 * and FlexNVM Partition Code. For example on S32K142:
			 * - EEEDataSizeCode = 0x02u: EEPROM size = 4 Kbytes
			 * - DEPartitionCode = 0x08u: EEPROM backup size = 64 Kbytes */
			ret = FLASH_DRV_DEFlashPartition(&flashSSDConfig, 0x02u, 0x08u, 0x0u, false, true);
	#ifdef DEBUG_printf
		SEGGER_RTT_printf(0,"DEFlashPartition T(0)/F(!0) %d\n", flashResult);
	#endif
			/* Re-initialize the driver to update the new EEPROM configuration */
		flashResult = FLASH_DRV_Init(&Flash1_InitConfig0, &flashSSDConfig);
	#ifdef DEBUG_printf
		SEGGER_RTT_printf(0,"flash init T(0)/F(!0) %d\n", flashResult);
	#endif
			/* Make FlexRAM available for EEPROM */
			flashResult = FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, NULL);
	#ifdef DEBUG_printf
		SEGGER_RTT_printf(0,"SetFlexRamFunction T(0)/F(!0) %d\n", flashResult);
	#endif
		}
	    else  /* FLexRAM is already configured as EEPROM */
	    {
	        /* Make FlexRAM available for EEPROM, make sure that FlexNVM and FlexRAM
	         * are already partitioned successfully before */
	    	flashResult = FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, NULL);
	#ifdef DEBUG_printf
		SEGGER_RTT_printf(0,"SetFlexRamFunction T(0)/F(!0) %d\n", flashResult);
	#endif
	    }
		EEPROM_BaseAddress = flashSSDConfig.EERAMBase;
	#endif


   /*  Always initialize the driver before calling other functions
    ret = FLASH_DRV_Init(&Flash1_InitConfig0,&flashSSDConfig);
    DEV_ASSERT(STATUS_SUCCESS == ret);

#if ((FEATURE_FLS_HAS_FLEX_NVM == 1u) & (FEATURE_FLS_HAS_FLEX_RAM == 1u))
     Config FlexRAM as EEPROM if it is currently used as traditional RAM
    if (flashSSDConfig.EEESize == 0u)
    {
         Configure FlexRAM as EEPROM and FlexNVM as EEPROM backup region,
         * DEFlashPartition will be failed if the IFR region isn't blank.
         * Refer to the device document for valid EEPROM Data Size Code
         * and FlexNVM Partition Code. For example on S32K142:
         * - EEEDataSizeCode = 0x02u: EEPROM size = 4 Kbytes
         * - DEPartitionCode = 0x08u: EEPROM backup size = 64 Kbytes
        ret = FLASH_DRV_DEFlashPartition(&flashSSDConfig, 0x02u, 0x08u, 0x0u, false, true);
        DEV_ASSERT(STATUS_SUCCESS == ret);

         Re-initialize the driver to update the new EEPROM configuration
        ret = FLASH_DRV_Init(&Flash1_InitConfig0, &flashSSDConfig);
        DEV_ASSERT(STATUS_SUCCESS == ret);

         Make FlexRAM available for EEPROM
        ret = FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, NULL);
        DEV_ASSERT(STATUS_SUCCESS == ret);
    }
    else     FLexRAM is already configured as EEPROM
    {
         Make FlexRAM available for EEPROM, make sure that FlexNVM and FlexRAM
         * are already partitioned successfully before
        ret = FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, NULL);
        DEV_ASSERT(STATUS_SUCCESS == ret);
    }
#endif  (FEATURE_FLS_HAS_FLEX_NVM == 1u) & (FEATURE_FLS_HAS_FLEX_RAM == 1u) */
}

void DFlash_Write(void)
{
	INT_SYS_DisableIRQGlobal();
	DFlash_Erase_All();
	for (i = 0u; i < BUFFER_SIZE; i++)
	{
	    sourceBuffer[i] = i;
	}
	/*dest form 0 to add ，Offset address from base address */
	address = flashSSDConfig.DFlashBase;
	ret = FLASH_DRV_Program(&flashSSDConfig, address, BUFFER_SIZE, sourceBuffer);
	DEV_ASSERT(STATUS_SUCCESS == ret);
/*	FLASH_DRV_Program(&flashSSDConfig, address, size, sourceBuffer);*/
	INT_SYS_EnableIRQGlobal();
}

void DFlash_Erase_All(void)
{
	 /* Erase a sector in DFlash */
	address = flashSSDConfig.DFlashBase;
	size = FEATURE_FLS_DF_BLOCK_SECTOR_SIZE;
	ret = FLASH_DRV_EraseSector(&flashSSDConfig, address, size);
	DEV_ASSERT(STATUS_SUCCESS == ret);

}


void DFlash_Write_Bytes(uint32_t dest, uint32_t size, const uint8_t * pData)
{
	address = flashSSDConfig.DFlashBase + dest;
/*	8 consecutive bytes (for program phrase command) on P-Flash or D-Flash block.*/
	FLASH_DRV_Program(&flashSSDConfig, address, size, pData);
}

void DFlash_Read(void)
{
	Pos_Storage.Close_Pos_Learned = MEM(DFLASH_STARTING_ADDRESS_CloPos);
	Pos_Storage.Open_Pos_Learned = MEM(DFLASH_STARTING_ADDRESS_OpnPos);
	Pos_Storage.Door_Cur_Pos = MEM(DFLASH_STARTING_ADDRESS_CurPos);
}

void CanDFlash_TxMessage(void)
{
        can_message_t Tx_msg7 = {
                 .cs = 0U,
                 .id = 0x01,
                 .data[0] = 0,
				 .data[1] = 0,
                 .data[2] = 0x2,
                 .data[3] = 0x3,
                 .data[4] = 0x4,
				 .data[5] = 0x5,
				 .data[6] = 0x6,
				 .data[7] = 0x7,
				 .length = 8
                 };

                can_message_t* tx_msg = &Tx_msg7;
                tx_msg->id = 0X7FF;
                tx_msg->length = 8;

                tx_msg->data[0] = (uint8_t*)Pos_Storage.Close_Pos_Learned;
                tx_msg->data[1] = (uint8_t*)Pos_Storage.Close_Pos_Learned;
                tx_msg->data[2] = (uint8_t*)Pos_Storage.Close_Pos_Learned;
                tx_msg->data[3] = (uint8_t*)Pos_Storage.Close_Pos_Learned;

                tx_msg->data[4] = Pos_Storage.Open_Pos_Learned;
                tx_msg->data[5] = (Pos_Storage.Open_Pos_Learned>>8);
                tx_msg->data[6] = (Pos_Storage.Open_Pos_Learned>>16);
                tx_msg->data[7] = (Pos_Storage.Open_Pos_Learned>>24);

                CAN_Send(&CAN0can_pal1_instance,TX_MAILBOX_CAN0, tx_msg);

}

