/**
 * \file Bsp.h
 * \brief Board support package
 * \ingroup library_srvsw_bsp_bsp
 *
 *
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
 * $Revision: $1396.3
 * $Date: $2013-06-19 21:48:45 GMT
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
 * \defgroup library_srvsw_bsp_bsp Board support package
 * This module implements the board support package
 * \ingroup library_srvsw_bsp
 *
 */

#ifndef BSP_TIME_H
#define BSP_TIME_H

#include "Ifx_types.h"
#include "Ifx_Cfg.h"                /* Do not remove this include */
#include "IfxCpu_Intrinsics.h"     /* Do not remove this include */
#include "Ifx_Assert.h"  /* Do not remove this include */

#include "IfxCpu.h"
#include "IfxPort.h"
#include "IfxSrc.h"
#include "IfxStm.h"

#ifndef BSP_DEFAULT_TIMER
/** Defined the default timer used */
#define BSP_DEFAULT_TIMER               (&MODULE_STM0)
#endif

/******************************************************************************/
/*                           Function prototypes                              */
/******************************************************************************/

/** \addtogroup library_srvsw_bsp_bsp
 * \{ */
/** \name Interrupt APIs
 * \{ */
IFX_INLINE boolean areInterruptsEnabled(void);
IFX_INLINE boolean disableInterrupts(void);
IFX_INLINE void enableInterrupts(void);
IFX_INLINE void restoreInterrupts(boolean enabled);
/** \} */
/** \} */

/******************************************************************************/
/*                           Functions                                        */
/******************************************************************************/

/** \brief Return the status of the global interrupts
 *
 * \retval TRUE if the global interrupts are enabled.
 * \retval FALSE if the global interrupts are disabled.
 *
 * \see restoreInterrupts(), disableInterrupts()
 */
IFX_INLINE boolean areInterruptsEnabled(void)
{
    return IfxCpu_areInterruptsEnabled();
}

/** \brief Disable the global interrupts
 *
 * \retval TRUE if the global interrupts were enabled before the call to the function.
 * \retval FALSE if the global interrupts are disabled before the call to the function.
 *
 * \see areInterruptsEnabled(), restoreInterrupts()
 */
IFX_INLINE boolean disableInterrupts(void)
{
    return IfxCpu_disableInterrupts();
}

/** \brief enable the global interrupts
 *
 */
IFX_INLINE void enableInterrupts(void)
{
    IfxCpu_enableInterrupts();
}

/** \brief Restore the state of the global interrupts.
 *
 * \param enabled if TRUE, re-enable the global interrupts, else do nothing.
 *
 * \return None.
 *
 * \see areInterruptsEnabled(), disableInterrupts()
 */
IFX_INLINE void restoreInterrupts(boolean enabled)
{
    IfxCpu_restoreInterrupts(enabled);
}

/******************************************************************************/
/*                           Macros                                           */
/******************************************************************************/
#define TIMER_COUNT             (11)                                /**< \internal \brief number of timer values defined */
#define TIMER_INDEX_10NS        (0)                                 /**< \internal \brief Index of the time value 10ns*/
#define TIMER_INDEX_100NS       (1)                                 /**< \internal \brief Index of the time value 100ns*/
#define TIMER_INDEX_1US         (2)                                 /**< \internal \brief Index of the time value 1us*/
#define TIMER_INDEX_10US        (3)                                 /**< \internal \brief Index of the time value 10us*/
#define TIMER_INDEX_100US       (4)                                 /**< \internal \brief Index of the time value 100us*/
#define TIMER_INDEX_1MS         (5)                                 /**< \internal \brief Index of the time value 1ms*/
#define TIMER_INDEX_10MS        (6)                                 /**< \internal \brief Index of the time value 10ms*/
#define TIMER_INDEX_100MS       (7)                                 /**< \internal \brief Index of the time value 100ms*/
#define TIMER_INDEX_1S          (8)                                 /**< \internal \brief Index of the time value 1s*/
#define TIMER_INDEX_10S         (9)                                 /**< \internal \brief Index of the time value 10s*/
#define TIMER_INDEX_100S        (10)                                /**< \internal \brief Index of the time value 100s*/

/** \internal
 *  Array containing the time constants. This variable should not be used in the application. TimeConst_0s, TimeConst_10ns, ...  should be used instead
 *
 */
IFX_EXTERN TTime TimeConst[TIMER_COUNT];

/******************************************************************************/
/*                           Function prototypes                              */
/******************************************************************************/
/** \addtogroup library_srvsw_bsp_bsp
 * \{ */
/** \name Time APIs
 * \{ */
IFX_INLINE TTime addTTime(TTime a, TTime b);
IFX_INLINE TTime elapsed(TTime since);
IFX_INLINE TTime getDeadLine(TTime timeout);
IFX_INLINE TTime getTimeout(TTime deadline);
IFX_EXTERN void initTime(void);
IFX_INLINE boolean isDeadLine(TTime deadLine);
IFX_INLINE TTime now(void);
IFX_INLINE TTime nowWithoutCriticalSection(void);
IFX_INLINE boolean poll(volatile boolean *test, TTime timeout);
IFX_INLINE TTime timingNoInterruptEnd(TTime since, boolean interruptEnabled);
IFX_INLINE TTime timingNoInterruptStart(boolean *interruptEnabled);
IFX_INLINE void wait(TTime timeout);
IFX_EXTERN void waitPoll(void);
IFX_EXTERN void waitTime(TTime timeout);

/** Prototype for wait() functions */
typedef void (*WaitTimeFunction) (TTime timeout);

#define TimeConst_0s            ((TTime)0)                          /**< \brief time constant equal to 1s */
#define TimeConst_10ns          (TimeConst[TIMER_INDEX_10NS])       /**< \brief time constant equal to 10ns */
#define TimeConst_100ns         (TimeConst[TIMER_INDEX_100NS])      /**< \brief time constant equal to 100ns */
#define TimeConst_1us           (TimeConst[TIMER_INDEX_1US])        /**< \brief time constant equal to 1us */
#define TimeConst_10us          (TimeConst[TIMER_INDEX_10US])       /**< \brief time constant equal to 10us */
#define TimeConst_100us         (TimeConst[TIMER_INDEX_100US])      /**< \brief time constant equal to 100us */
#define TimeConst_1ms           (TimeConst[TIMER_INDEX_1MS])        /**< \brief time constant equal to 1ms */
#define TimeConst_10ms          (TimeConst[TIMER_INDEX_10MS])       /**< \brief time constant equal to 10ms */
#define TimeConst_100ms         (TimeConst[TIMER_INDEX_100MS])      /**< \brief time constant equal to 100ms */
#define TimeConst_1s            (TimeConst[TIMER_INDEX_1S])         /**< \brief time constant equal to 1s */
#define TimeConst_10s           (TimeConst[TIMER_INDEX_10S])        /**< \brief time constant equal to 10s */
#define TimeConst_100s          (TimeConst[TIMER_INDEX_100S])       /**< \brief time constant equal to 100s */

/**\}*/
/**\}*/
/******************************************************************************/
/*                           Functions                                        */
/******************************************************************************/

/** \brief Add 2 TTime values and return the result
 *
 * \param a parameter a
 * \param b parameter b
 *
 * \return a + b. If either a or b is TIME_INFINITE, the result is TIME_INFINITE
 */
IFX_INLINE TTime addTTime(TTime a, TTime b)
{
    TTime result;

    if ((a == TIME_INFINITE) || (b == TIME_INFINITE))
    {
        result = TIME_INFINITE;
    }
    else
    {
        result = a + b;         /* FIXME check for overflow */
    }

    return result;
}

/** \brief Return the elapsed time in ticks.
 *
 * Return the elapsed time between the current time and the time passed as parameter
 *
 * \return Returns the elapsed time.
 */
IFX_INLINE TTime elapsed(TTime since)
{
    return now() - since;
}

/** \brief Return the time dead line.
 *
 * \param timeout Specifies the dead line from now: Deadline = Now + Timeout
 *
 * \return Return the time dead line.
 */
IFX_INLINE TTime getDeadLine(TTime timeout)
{
    TTime deadLine;

    if (timeout == TIME_INFINITE)
    {
        deadLine = TIME_INFINITE;
    }
    else
    {
        deadLine = now() + timeout;
    }

    return deadLine;
}

/** \brief Return the time until the dead line.
 *
 * \param deadline Specifies the dead line from now: Deadline = Now + Timeout
 *
 * \return Return the time until the dead line.
 */
IFX_INLINE TTime getTimeout(TTime deadline)
{
    TTime timeout;

    if (deadline == TIME_INFINITE)
    {
        timeout = TIME_INFINITE;
    }
    else
    {
        timeout = deadline - now();
    }

    return timeout;
}

/** \brief Return TRUE if the dead line is over.
 *
 * \param deadLine Specifies the dead line.
 *
 * \retval TRUE Returns TRUE if the dead line is over
 * \retval FALSE Returns FALSE if the dead line is not yet over
 */
IFX_INLINE boolean isDeadLine(TTime deadLine)
{
    boolean result;

    if (deadLine == TIME_INFINITE)
    {
        result = FALSE;
    }
    else
    {
        result = now() >= deadLine;
    }

    return result;
}

/** \brief Return system timer value (critical section).
 *
 * The function IfxStm_get() is called in a critical section, disabling
 * the interrupts. The system timer value is limited to TIME_INFINITE.
 *
 * \return Returns system timer value.
 */
IFX_INLINE TTime now(void)
{
    TTime stmNow;
    boolean interruptState;

    interruptState = disableInterrupts();
    stmNow = (TTime)IfxStm_get(BSP_DEFAULT_TIMER) & TIME_INFINITE;
    restoreInterrupts(interruptState);

    return stmNow;
}

/** \brief Return system timer value (without critical section).
 *
 * The function IfxStm_get() is called. The system timer value is limited to TIME_INFINITE.
 *
 * \return Returns system timer value.
 */
IFX_INLINE TTime nowWithoutCriticalSection(void)
{
    TTime stmNow;

    stmNow = (TTime)IfxStm_get(BSP_DEFAULT_TIMER) & TIME_INFINITE;

    return stmNow;
}

/** \brief Poll a variable for a time.
 *
 * \param test Specifies the variable to test.
 * \param timeout Specifies the maximal time the variable will be tested
 *
 * \retval TRUE Returns TRUE if the variable gets TRUE before the timeout elapse
 * \retval FALSE Returns FALSE if the variable is FALSE as the timeout elapse
 */
IFX_INLINE boolean poll(volatile boolean *test, TTime timeout)
{
    TTime deadLine = getDeadLine(timeout);

    while ((*test == FALSE) && (isDeadLine(deadLine) == FALSE))
    {}

    return *test;
}

/** \brief Return the elapsed time in system timer ticks, and enable the interrupts.
 *
 * The interrupts are enable by the function
 *
 * \param since time returned by timingNoInterruptStart()
 * \param interruptEnabled If TRUE, the interrupts will be enabled before the function exit. This parameter should be set to the value returned by \ref  timingNoInterruptStart()
 *
 * \return Returns the elapsed time.
 *
 * \see timingNoInterruptStart()
 */
IFX_INLINE TTime timingNoInterruptEnd(TTime since, boolean interruptEnabled)
{
    TTime stmNow;

    stmNow = nowWithoutCriticalSection();
    restoreInterrupts(interruptEnabled);

    return stmNow - since;
}

/** \brief Disable the interrupt and return system timer value.
 *
 * The interrupt remains disabled after the function call
 *
 * \return Returns system timer value.
 *
 * \see timingNoInterruptEnd()
 */
IFX_INLINE TTime timingNoInterruptStart(boolean *interruptEnabled)
{
    *interruptEnabled = disableInterrupts();

    return nowWithoutCriticalSection();
}

/** \brief Wait for a while.
 *
 * \param timeout Specifies the waiting time
 *
 * \return None.
 */
IFX_INLINE void wait(TTime timeout)
{
    TTime deadLine = getDeadLine(timeout);

    while (isDeadLine(deadLine) == FALSE)
    {}
}

#define PIN_DRIVER_STRONG_SHARP      IfxPort_PadDriver_cmosAutomotiveSpeed1
#define Pin_setState(pin, mode)       IfxPort_setPinState((pin)->port, (pin)->pinIndex, (mode))
#define Pin_setGroupState(pin, mask, data) IfxPort_setGroupState((pin)->port, (pin)->pinIndex, (mask), (data))
#define Pin_setMode(pin, mode)        IfxPort_setPinMode((pin)->port, (pin)->pinIndex, (mode))
#define Pin_setDriver(pin, mode)      IfxPort_setPinPadDriver((pin)->port, (pin)->pinIndex, (mode))
#define Pin_setStateHigh(pin)        IfxPort_setPinHigh((pin)->port, (pin)->pinIndex)
#define Pin_setStateLow(pin)         IfxPort_setPinLow((pin)->port, (pin)->pinIndex)
#define Pin_getState(pin)            IfxPort_getPinState((pin)->port, (pin)->pinIndex)
#define Pin_setGroupModeOutput(pin, mask, mode)   IfxPort_setGroupModeOutput((pin)->port, (pin)->pinIndex, (mask), (mode))
#define Pin_setGroupModeInput(pin, mask, mode)    IfxPort_setGroupModeInput((pin)->port, (pin)->pinIndex, (mask), (mode))
#define Pin_setGroupState(pin, mask, data)        IfxPort_setGroupState((pin)->port, (pin)->pinIndex, (mask), (data))
#define Pin_getGroupState(pin, mask)             IfxPort_getGroupState((pin)->port, (pin)->pinIndex, (mask))
#define Pin_enableEmgStop(pin)                  IfxPort_enableEmergencyStop((pin)->port, (pin)->pinIndex)
//------------------------------------------------------------------------------

#endif /* BSP_H */
