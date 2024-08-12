/*
 * AppScheduler.c
 *
 *  Created on: 19.09.2013
 *
 */


#include <AppScheduler.h>
#include <AppTaskFu.h>
#include "Ifx_Cfg_Scheduler.h"

AppScheduler_task g_tasks_core0[AppScheduler_Task_count];

void AppScheduler_init(void)
{
    // Initialize AppScheduler Tasks
        AppScheduler_cfg_tasks config = appScheduler_task_config[AppScheduler_Task_10ms];
        config.callback = (schedulerCallback) & appTaskfu_10ms;
        AppScheduler_initTask(&g_tasks_core0[AppScheduler_Task_10ms],&config);

        config = appScheduler_task_config[AppScheduler_Task_100ms];
        config.callback = (schedulerCallback) &appTaskfu_100ms;
        AppScheduler_initTask(&g_tasks_core0[AppScheduler_Task_100ms],&config);

        config = appScheduler_task_config[AppScheduler_Task_200ms];
        config.callback = (schedulerCallback) &appTaskfu_200ms;
        AppScheduler_initTask(&g_tasks_core0[AppScheduler_Task_200ms],&config);

        config = appScheduler_task_config[AppScheduler_Task_1ms];
        config.callback = (schedulerCallback) &appTaskfu_1ms;
        AppScheduler_initTask(&g_tasks_core0[AppScheduler_Task_1ms],&config);
}


void AppScheduler_initTask(AppScheduler_task *handle,AppScheduler_cfg_tasks *config)
{
	handle->taskcounter = config->taskoffset + config->taskreload;
	handle->taskreload = config->taskreload;
	handle->countinous = config->countinous;
	handle->callback = config->callback;
}



 void AppScheduler_tick(AppScheduler_task *handle)
{
	uint32 i;
	for(i=0;i<AppScheduler_Task_count;i++)
	{
		if(handle->taskcounter)
		{

			handle->taskcounter--;
			if(handle->taskcounter == 0)
			{
				if(handle->countinous)
				{
					handle->taskcounter = handle->taskreload;
				}
				if(handle->run != FALSE)
				{
					handle->overflow++;
				}
				handle->run = TRUE;
			}
		}
		handle++;
	}
}



void AppScheduler_process(AppScheduler_task *handle)
{

	if(handle->run != FALSE)
	{
		handle->run = FALSE;
		handle->callback();
	}

}

