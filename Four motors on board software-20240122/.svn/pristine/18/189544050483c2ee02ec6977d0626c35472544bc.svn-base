/**
 * \file App_Isr.h
 * \brief Application interrupts.
 * \ingroup interrupt
 *
 *
 * \license
 * You can use this file under the terms of the IFX License.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * IFX License for more details (IFX_License.txt).
 *
 * This file may be used, copied, and distributed, with or without
 * modification, provided that all copyright notices are retained;
 * that all modifications to this file are prominently noted in the
 * modified file; and that this paragraph is not modified.
 *
 * \copyright Copyright (C) 2012 Infineon Technologies AG
 *
 *
 * $Revision: 523 $
 * $Date: 2012-12-18 14:40:59 +0100 (Tue, 18 Dec 2012) $
 *
 */


#if !defined(APP_ISR_H)
#define APP_ISR_H
/*----------------------------------------------------------------------------*/
#include "Bsp/Bsp.h"
#include "Math/MinMax.h"
/*----------------------------------------------------------------------------*/

void MotorRPM_Check(void);
enum
{
    Isr_Timer_1ms,
    Isr_Timer_10ms,
    Isr_Timer,
    Isr_RdcDs_0,
    Isr_Adc_M0,
    Isr_Adc_M1,
    Isr_Adc_INx,
    Isr_Adc_PWR,
    Isr_PwmHl_M0,
    Isr_PwmHl_M1,
    Isr_ExtCapture,
    ISR_COUNT
};

typedef union
{
    uint32 A[ISR_COUNT];
    struct
    {
        uint32 Timer_1ms;   /**< \brief Count of ISR_Timer_1ms */
        uint32 Timer_10ms;  /**< \brief Count of ISR_Timer_10ms */
        uint32 Timer;       /**< \brief Count of ISR_Timer */
        uint32 RdcDs_0;     /**< \brief Count of ISR_RdcDs_0 */
        uint32 Adc_M0;      /**< \brief Count of ISR_Adc_M0 */
        uint32 Adc_M1;      /**< \brief Count of ISR_Adc_M1 */
        uint32 Adc_INx;     /**< \brief Count of ISR_Adc_INx */
        uint32 Adc_PWR;     /**< \brief Count of ISR_Adc_PWR */
        uint32 PwmHl_M0;    /**< \brief Count of ISR_PwmHl_M0 */
        uint32 PwmHl_M1;    /**< \brief Count of ISR_PwmHl_M1 */
    } I;
} IsrCount;

typedef union
{
    MinMax A[ISR_COUNT];
    struct
    {
        MinMax timer1ms;    /**< \brief Time stamp of ISR_Timer_1ms */
        MinMax timer10ms;   /**< \brief Time stamp of ISR_Timer_10ms */
        MinMax timer;       /**< \brief Time stamp of ISR_Timer */
        MinMax rdcDs0;      /**< \brief Time stamp of ISR_RdcDs_0 */
        MinMax adcM0;       /**< \brief Time stamp of ISR_Adc_M0 */
        MinMax adcM1;       /**< \brief Time stamp of ISR_Adc_M1 */
        MinMax adcINx;      /**< \brief Time stamp of ISR_Adc_INx */
        MinMax adcPwr;      /**< \brief Time stamp of ISR_Adc_PWR */
        MinMax pwmHlM0;     /**< \brief Time stamp of ISR_PwmHl_M0 */
        MinMax pwmHlM1;     /**< \brief Time stamp of ISR_PwmHl_M1 */
    } I;
} IsrLoad;

#endif
