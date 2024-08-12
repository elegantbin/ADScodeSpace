
#include <AppScheduler.h>
#include <AppTaskFu.h>
#include "Ifx_Types.h"
#include "IfxCpu_Intrinsics.h"

#include "General_Defines.h"
#include "Ifx_reg.h"

#include "IfxGtm_reg.h"
#include "IfxScuWdt.h"
#include "bsptime.h"

#include "Ifx_Cfg_Scheduler.h"

IFX_EXTERN AppScheduler_task g_tasks_core0[AppScheduler_Task_count];
/** \brief Initialize the position sensor interfaces */


void BSW_mainInit(void)
{
	__disable();

	// Initialize time constants for Time functions see bsptime.c
	initTime();

	// Initialize resolver Interface and Encoder Interface
	//initPosIf();

    // Initialize VAdc Driver
	//AppVadc_init();

}


int BSW_main(void)
{
	uint32 i = 0;

	BSW_mainInit();
    // Initialize App Tasks
    appTaskfu_init();

    __enable ();
    while (1)
    {
    	AppScheduler_process(&g_tasks_core0[i++]);
    	if(i == AppScheduler_Task_count)
    	{
    		i = 0;
    	}
    }
    return (1);
}
