/*
 * AppTimerOS.c
 *
 *  Created on: 20.02.2013
 *
 */

#include <AppScheduler.h>
#include "Ifx_Types.h"
#include "IfxPort.h"
#include "IfxSrc.h"
#include "IfxScuCcu.h"
#include "IfxStm.h"
#include "IfxCpu.h"
#include "IfxCpu_Irq.h"
#include "IfxCpu_Intrinsics.h"
#include "ConfigurationIsr.h"

#include "Ifx_Cfg_Scheduler.h"


#define OS_CORE0_INTERVAL_IN_SECONDS 		(0.001)

/*Global variables for CPU0 */

volatile uint32 Core0_Task0_count;
volatile uint8 Core0LedBlink;

volatile uint32 Core0_StmEventPassed = 0;

volatile uint32 *test_a11;

/* *INDENT-OFF* */
#if defined(__DCC__)
asm volatile uint32 *IfxCpu_Trap_getReturnAddress (void)
{
%
!"%a2"
	mov.aa %a2, %a11
}
#elif defined(__GNUC__)
IFX_INLINE uint32 *IfxCpu_Trap_getReturnAddress (void)
{
    uint32 *retAddr;
  __asm ("mov.aa %0, %%a11":"=a" (retAddr));
    return retAddr;
}

#elif defined(__TASKING__)
IFX_INLINE uint32 *IfxCpu_Trap_getReturnAddress (void)
{
	uint32 *retAddr;
  __asm ("mov.aa %0, a11":"=a" (retAddr));
    return retAddr;
}
//#else
//#error Compiler unsupported
#endif
/* *INDENT-ON* */


extern AppScheduler_task g_tasks_core0[AppScheduler_Task_count];

IFX_INTERRUPT (Stm0_Isr, 0, STM0_ISR_PRIORITY)
{
    uint32 stmTicks;
    __enable ();
    stmTicks = (uint32) (OS_CORE0_INTERVAL_IN_SECONDS * IfxStm_getFrequency (&MODULE_STM0));
    IfxStm_updateCompare (&MODULE_STM0, 0, IfxStm_getCompare (&MODULE_STM0, 0) + stmTicks);

    AppScheduler_tick((AppScheduler_task*)&g_tasks_core0);

    test_a11 = IfxCpu_Trap_getReturnAddress ();
}


void AppTimerOs_initialize_StmTicks (void)
{
    IfxStm_CompareConfig stmCompareConfig;

    // suspend by debugger enabled
    IfxStm_enableOcdsSuspend (&MODULE_STM0);

    //Call the constructor of configuration
    IfxStm_initCompareConfig (&stmCompareConfig);

    //Modify only the number of ticks and enable the trigger output
    stmCompareConfig.ticks = (uint32) (OS_CORE0_INTERVAL_IN_SECONDS * IfxStm_getFrequency (&MODULE_STM0));  /*Interrupt */
    stmCompareConfig.triggerPriority = STM0_ISR_PRIORITY;

    stmCompareConfig.typeOfService = IfxSrc_Tos_cpu0;

    //Now Compare functionality is initialized
    IfxStm_initCompare (&MODULE_STM0, &stmCompareConfig);
}

void AppTimerOs_interruptsInit (void)
{
    AppTimerOs_initialize_StmTicks ();
}

