/*
 * Copyright (c) 2015 - 2016 , Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "clockMan1.h"
#include "Flash.h"


volatile int exit_code = 0;
/* User includes (#include below this line is not maintained by Processor Expert) */

#include <stdint.h>
#include <stdbool.h>

/* Declare a FLASH config struct which initialized by FlashInit, and will be used by all flash operations */
flash_ssd_config_t flashSSDConfig;

/* Data source for program operation */
#define BUFFER_SIZE         0x100u          /* Size of data source */
uint8_t sourceBuffer[BUFFER_SIZE];

/* Function declarations */
void CCIF_Handler(void);
/* If target is flash, insert this macro to locate callback function into RAM */
START_FUNCTION_DECLARATION_RAMSECTION
void CCIF_Callback(void)
END_FUNCTION_DECLARATION_RAMSECTION

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
  /* Write your local variable definition here */
    status_t ret;        /* Store the driver APIs return code */
    uint32_t address;
    uint32_t size;
    uint32_t failAddr;
    uint32_t i;
    flash_callback_t pCallBack;
#if (FEATURE_FLS_HAS_PROGRAM_PHRASE_CMD == 1u)
#ifndef FLASH_TARGET
    uint8_t unsecure_key[FTFx_PHRASE_SIZE] = {0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFEu, 0xFFu, 0xFFu, 0xFFu};
#endif
#else   /* FEATURE_FLASH_HAS_PROGRAM_LONGWORD_CMD */
    uint8_t unsecure_key[FTFx_LONGWORD_SIZE] = {0xFEu, 0xFFu, 0xFFu, 0xFFu};
#endif  /* FEATURE_FLS_HAS_PROGRAM_PHRASE_CMD */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */

    /* Initialize and configure clocks
     *  -   see clock manager component for details
     */
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
            g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

    /* Init source data */
    for (i = 0u; i < BUFFER_SIZE; i++)
    {
        sourceBuffer[i] = i;
    }

    /* Disable cache to ensure that all flash operations will take effect instantly,
     * this is device dependent */
#ifndef FLASH_TARGET
#ifdef S32K142_SERIES
    MSCM->OCMDR[0u] |= MSCM_OCMDR_OCM1(0x3u);
    MSCM->OCMDR[1u] |= MSCM_OCMDR_OCM1(0x3u);
#endif /* S32K142_SERIES */
#endif /* FLASH_TARGET */
    /* Install interrupt for Flash Command Complete event */
    INT_SYS_InstallHandler(FTFC_IRQn, CCIF_Handler, (isr_t*) 0);
    INT_SYS_EnableIRQ(FTFC_IRQn);

    /* Enable global interrupt */
    INT_SYS_EnableIRQGlobal();

    /* Always initialize the driver before calling other functions */
    ret = FLASH_DRV_Init(&Flash_InitConfig0, &flashSSDConfig);
    DEV_ASSERT(STATUS_SUCCESS == ret);

#if ((FEATURE_FLS_HAS_FLEX_NVM == 1u) & (FEATURE_FLS_HAS_FLEX_RAM == 1u))
    /* Config FlexRAM as EEPROM if it is currently used as traditional RAM */
    if (flashSSDConfig.EEESize == 0u)
    {
#ifndef FLASH_TARGET
        /* First, erase all Flash blocks if code is placed in RAM to ensure
         * the IFR region is blank before partitioning FLexNVM and FlexRAM */
        ret = FLASH_DRV_EraseAllBlock(&flashSSDConfig);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Verify the erase operation at margin level value of 1 */
        ret = FLASH_DRV_VerifyAllBlock(&flashSSDConfig, 1u);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Reprogram secure byte in Flash configuration field */
#if (FEATURE_FLS_HAS_PROGRAM_PHRASE_CMD == 1u)
        address = 0x408u;
        size = FTFx_PHRASE_SIZE;
#else   /* FEATURE_FLASH_HAS_PROGRAM_LONGWORD_CMD == 1u */
        address = 0x40Cu;
        size = FTFx_LONGWORD_SIZE;
#endif /* FEATURE_FLS_HAS_PROGRAM_PHRASE_CMD */
        ret = FLASH_DRV_Program(&flashSSDConfig, address, size, unsecure_key);
        DEV_ASSERT(STATUS_SUCCESS == ret);
#endif /* FLASH_TARGET */

        /* Configure FlexRAM as EEPROM and FlexNVM as EEPROM backup region,
         * DEFlashPartition will be failed if the IFR region isn't blank.
         * Refer to the device document for valid EEPROM Data Size Code
         * and FlexNVM Partition Code. For example on S32K142:
         * - EEEDataSizeCode = 0x02u: EEPROM size = 4 Kbytes
         * - DEPartitionCode = 0x08u: EEPROM backup size = 64 Kbytes */
        ret = FLASH_DRV_DEFlashPartition(&flashSSDConfig, 0x0Fu, 0x00u, 0x0u, false, true);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Re-initialize the driver to update the new EEPROM configuration */
        ret = FLASH_DRV_Init(&Flash_InitConfig0, &flashSSDConfig);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Make FlexRAM available for EEPROM */
        ret = FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, NULL);
        DEV_ASSERT(STATUS_SUCCESS == ret);
    }
    else    /* FLexRAM is already configured as EEPROM */
    {
        /* Make FlexRAM available for EEPROM, make sure that FlexNVM and FlexRAM
         * are already partitioned successfully before */
        ret = FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, NULL);
        DEV_ASSERT(STATUS_SUCCESS == ret);
    }
#endif /* (FEATURE_FLS_HAS_FLEX_NVM == 1u) & (FEATURE_FLS_HAS_FLEX_RAM == 1u) */

    /* Set callback function before a long time consuming flash operation
     * (ex: erasing) to let the application code do other tasks while flash
     * in operation. In this case we use it to enable interrupt for
     * Flash Command Complete event */
    pCallBack = (flash_callback_t)CCIF_Callback;
    flashSSDConfig.CallBack = pCallBack;

    /* Erase the last PFlash sector */
    address = FEATURE_FLS_PF_BLOCK_SIZE - FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
    size = FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
    ret = FLASH_DRV_EraseSector(&flashSSDConfig, address, size);
    DEV_ASSERT(STATUS_SUCCESS == ret);

    /* Disable Callback */
    flashSSDConfig.CallBack = NULL_CALLBACK;

    /* Verify the erase operation at margin level value of 1, user read */
    ret = FLASH_DRV_VerifySection(&flashSSDConfig, address, size / FTFx_DPHRASE_SIZE, 1u);
    DEV_ASSERT(STATUS_SUCCESS == ret);

    /* Write some data to the erased PFlash sector */
    size = BUFFER_SIZE;
    ret = FLASH_DRV_Program(&flashSSDConfig, address, size, sourceBuffer);
    DEV_ASSERT(STATUS_SUCCESS == ret);

    /* Verify the program operation at margin level value of 1, user margin */
    ret = FLASH_DRV_ProgramCheck(&flashSSDConfig, address, size, sourceBuffer, &failAddr, 1u);
    DEV_ASSERT(STATUS_SUCCESS == ret);

    /* Try to write data to EEPROM if FlexRAM is configured as EEPROM */
    if (flashSSDConfig.EEESize != 0u)
    {
        address = flashSSDConfig.EERAMBase;
        size = sizeof(uint32_t);
        ret = FLASH_DRV_EEEWrite(&flashSSDConfig, address, size, sourceBuffer);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Verify the written data */
        if (*((uint32_t *)sourceBuffer) != *((uint32_t *)address))
        {
            /* Failed to write data to EEPROM */
            exit_code = 1u;
            return exit_code;
        }

        /* Try to update one byte in an EEPROM address which isn't aligned */
        address = flashSSDConfig.EERAMBase + 1u;
        size = sizeof(uint8_t);
        sourceBuffer[0u] = 0xFFu;
        ret = FLASH_DRV_EEEWrite(&flashSSDConfig, address, size, sourceBuffer);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Then verify */
        if (sourceBuffer[0u] != *((uint8_t *)address))
        {
            /* Failed to update data to EEPROM */
            exit_code = 1u;
            return exit_code;
        }
    }
    else
    {
#if (FEATURE_FLS_HAS_FLEX_NVM == 1u)
        /* Erase a sector in DFlash */
        address = flashSSDConfig.DFlashBase;
        size = FEATURE_FLS_DF_BLOCK_SECTOR_SIZE;
        ret = FLASH_DRV_EraseSector(&flashSSDConfig, address, size);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Verify the erase operation at margin level value of 1, user read */
        ret = FLASH_DRV_VerifySection(&flashSSDConfig, address, size / FTFx_PHRASE_SIZE, 1u);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Write some data to the erased DFlash sector */
        address = flashSSDConfig.DFlashBase;
        size = BUFFER_SIZE;
        ret = FLASH_DRV_Program(&flashSSDConfig, address, size, sourceBuffer);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Verify the program operation at margin level value of 1, user margin */
        ret = FLASH_DRV_ProgramCheck(&flashSSDConfig, address, size, sourceBuffer, &failAddr, 1u);
        DEV_ASSERT(STATUS_SUCCESS == ret);
#endif /* FEATURE_FLS_HAS_FLEX_NVM */
    }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/

/*!
  \brief Interrupt handler for Flash Command Complete event
*/
void CCIF_Handler(void)
{
    /* Disable Flash Command Complete interrupt */
    FTFx_FCNFG &= (~FTFx_FCNFG_CCIE_MASK);

    return;
}

/*!
  \brief Callback function for Flash operations
*/
START_FUNCTION_DEFINITION_RAMSECTION
void CCIF_Callback(void)
{
    /* Enable interrupt for Flash Command Complete */
    if ((FTFx_FCNFG & FTFx_FCNFG_CCIE_MASK) == 0u)
    {
        FTFx_FCNFG |= FTFx_FCNFG_CCIE_MASK;
    }
}
END_FUNCTION_DEFINITION_RAMSECTION

/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/
