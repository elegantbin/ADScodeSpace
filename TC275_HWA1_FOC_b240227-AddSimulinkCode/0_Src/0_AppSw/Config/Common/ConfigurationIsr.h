/**
 * \file ConfigurationIsr.h
 * \brief Interrupts configuration.
 *
 *
 * \version iLLD_Demos_0_1_0_11
 * \copyright Copyright (c) 2014 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Demo_QspiDmaDemo_SrcDoc_InterruptConfig Interrupt configuration
 * \ingroup IfxLld_Demo_QspiDmaDemo_SrcDoc
 */

#ifndef CONFIGURATIONISR_H
#define CONFIGURATIONISR_H

#include "IfxSrc_cfg.h"
/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/** \brief Build the ISR configuration object
 * \param no interrupt priority
 * \param cpu assign CPU number
 */
#define ISR_ASSIGN(no, cpu)  ((no << 8) + cpu)

/** \brief extract the priority out of the ISR object */
#define ISR_PRIORITY(no_cpu) (no_cpu >> 8)

/** \brief extract the service provider  out of the ISR object */
#define ISR_PROVIDER(no_cpu) (no_cpu % 8)
/**
 * \addtogroup IfxLld_Demo_QspiDmaDemo_SrcDoc_InterruptConfig
 * \{ */

/**
 * \name Interrupt priority configuration.
 * The interrupt priority range is [1,255]
 * \{
 */

#define ISR_PRIORITY_QSPI0_TX       3  /**< \brief Define the Qspi0 transmit interrupt priority.  */             // CPU
#define ISR_PRIORITY_QSPI0_DMA      0  /**< \brief Define the Qspi0 transmit interrupt priority.  */             // DMA
#define ISR_PRIORITY_QSPI0_ER       12 /**< \brief Define the Qspi0 error interrupt priority.  */                // CPU

#define ISR_PRIORITY_DMA_CH1        50 /**< \brief Define the Dma channel1 interrupt priority.  */               // CPU
#define ISR_PRIORITY_DMA_CH2        51 /**< \brief Define the Dma channel2 interrupt priority.  */               // CPU

#define ISR_PRIORITY_DMA_CH3        52 /**< \brief Define the Dma channel1 interrupt priority.  */               // CPU

#define ISR_CPUSRV0		      		5  /**< \brief Define the touch data receive interrupt priority.  */         // CPU

#define ISR_OS_TICK		     		64 /**< \brief Define the TFT refresh interrupt priority.  */           	 // CPU

#define INTERRUPT_SSC_1_TX          30  /**< \brief Define the Ssc1 transmit interrupt priority.  */
#define INTERRUPT_SSC_1_RX          32  /**< \brief Define the Ssc1 receive interrupt priority.  */
#define INTERRUPT_SSC_1_ERR         0    //(88)  /**< \brief Define the Ssc1 error interrupt priority.  */

#define STM0_ISR_PRIORITY 			165	/**< \brief Define the  timer interrupt priority. for Core 0  */

#define INTERRUPT_M0_PWM_TRIGGER   (50)//70

#define INTERRUPT_VADC_RESULT_GROUP0 0
#define INTERRUPT_VADC_RESULT_GROUP1 0
#define INTERRUPT_VADC_RESULT_GROUP2 0
#define INTERRUPT_VADC_RESULT_GROUP3 103
#define INTERRUPT_VADC_RESULT_GROUP4 0

#define INTERRUPT_RDC_DS_0       35 /**< \brief Define the resolver (RDC) interrupt priority. */

#define INTERRUPT_ENCODER_GPT12 20

#define INTERRUPT_ENCODER_GPT12_T4  6
#define INTERRUPT_ENCODER_GPT12_T2  10

#define ISR_PRIORITY_QSPI2_TX       1  /**< \brief Define the Qspi2 transmit interrupt priority.  */             // DMA
#define ISR_PRIORITY_QSPI2_RX       2  /**< \brief Define the Qspi2 receive interrupt priority.  */              // DMA
#define ISR_PRIORITY_QSPI2_ER       11 /**< \brief Define the Qspi2 error interrupt priority.  */                // CPU

#define ISR_PRIORITY_CAN_debug_RX   2                           /* Define the CAN RX interrupt priority */
#define ISR_PRIORITY_CAN_RX         1                           /* Define the CAN RX interrupt priority              */
/** \} */

/**
 * \name Interrupt service provider configuration.
 * \{ */
#define ISR_PROVIDER_QSPI0_TX       0//IfxSrc_Tos_cpu0     /**< \brief Define the Qspi0 transmit interrupt provider.  */
#define ISR_PROVIDER_QSPI0_DMA		1//IfxSrc_Tos_dma      /**< \brief Define the Qspi0-DMA transmit interrupt provider.  */
#define ISR_PROVIDER_QSPI0_ER       0//IfxSrc_Tos_cpu0     /**< \brief Define the Qspi0 error interrupt provider.  */

#define ISR_PROVIDER_QSPI2_TX       1//IfxSrc_Tos_dma      /**< \brief Define the Qspi2 transmit interrupt provider.  */
#define ISR_PROVIDER_QSPI2_RX       1//IfxSrc_Tos_dma      /**< \brief Define the Qspi2 receive interrupt provider.  */
#define ISR_PROVIDER_QSPI2_ER       0//IfxSrc_Tos_cpu0     /**< \brief Define the Qspi2 error interrupt provider.  */

#define ISR_PROVIDER_DMA_CH1        0//IfxSrc_Tos_cpu0     /**< \brief Define the Dma Channel1 interrupt provider.  */
#define ISR_PROVIDER_DMA_CH2        0//IfxSrc_Tos_cpu0     /**< \brief Define the Dma Channel2 interrupt provider.  */

#define ISR_PROVIDER_DMA_CH3        0//IfxSrc_Tos_cpu0     /**< \brief Define the Dma Channel3 interrupt provider.  */

#define ISR_PROVIDER_CPUSRV0      	0//IfxSrc_Tos_cpu0  	/**< \brief Define the touch data receive interrupt provider.  */

#define ISR_PROVIDER_OS_TICK    	0//IfxSrc_Tos_cpu0 	/**< \brief Define the tft refresh interrupt provider.  */

/** \} */

/**
 * \name Interrupt configuration.
 * \{ */
#define INTERRUPT_QSPI0_TX          ISR_ASSIGN(ISR_PRIORITY_QSPI0_TX, ISR_PROVIDER_QSPI0_TX)             /**< \brief Define the QSPI0 transmit interrupt priority.  */
#define INTERRUPT_QSPI0_ER          ISR_ASSIGN(ISR_PRIORITY_QSPI0_ER, ISR_PROVIDER_QSPI0_ER)             /**< \brief Define the QSPI0 error interrupt priority.  */

#define INTERRUPT_QSPI2_TX          ISR_ASSIGN(ISR_PRIORITY_QSPI2_TX, ISR_PROVIDER_QSPI2_TX)             /**< \brief Define the QSPI2 transmit interrupt priority.  */
#define INTERRUPT_QSPI2_RX          ISR_ASSIGN(ISR_PRIORITY_QSPI2_RX, ISR_PROVIDER_QSPI2_RX)             /**< \brief Define the QSPI2 receive interrupt priority.  */
#define INTERRUPT_QSPI2_ER          ISR_ASSIGN(ISR_PRIORITY_QSPI2_ER, ISR_PROVIDER_QSPI2_ER)             /**< \brief Define the QSPI2 error interrupt priority.  */

#define INTERRUPT_DMA_CH1           ISR_ASSIGN(ISR_PRIORITY_DMA_CH1, ISR_PROVIDER_DMA_CH1)               /**< \brief Define the Dma channel1 interrupt priority.  */
#define INTERRUPT_DMA_CH2           ISR_ASSIGN(ISR_PRIORITY_DMA_CH2, ISR_PROVIDER_DMA_CH2)               /**< \brief Define the Dma channel2 interrupt priority.  */

#define INTERRUPT_DMA_CH3           ISR_ASSIGN(ISR_PRIORITY_DMA_CH3, ISR_PROVIDER_DMA_CH3)               /**< \brief Define the Dma channel3 interrupt priority.  */

#define INTERRUPT_OS_TICK			ISR_ASSIGN(ISR_PRIORITY_OS_TICK, ISR_PROVIDER_OS_TICK)				 /**< \brief Define the TFT refresh interrupt priority.  */


#define INTERRUPT_CPUSRV0 			ISR_ASSIGN(ISR_PRIORITY_CPUSRV0, ISR_PROVIDER_CPUSRV0)				 /**< \brief Define the touch data receive interrupt priority.  */


/** \} */

/** \} */
//------------------------------------------------------------------------------

#endif
