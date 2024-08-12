/*
 * OsCfg_Scheduler.c
 * Created on: 06.12.2023
 *
 */

#include "OsTypedefs.h"
#include "OsCfg_Scheduler.h"


const osScheduler_cfg_tasks osScheduler_task_config[OsScheduler_Task_count] =
{
		{// 1ms Task
			.taskoffset = 0,
			.taskreload = 1,
			.countinous = TRUE,
			.callback = NULL_PTR,
		},
		{// 10ms Task
			.taskoffset = 0,
			.taskreload = 10,
			.countinous = TRUE,
			.callback = NULL_PTR,
		},
		{// 100ms Task
			.taskoffset = 0,
			.taskreload = 100,
			.countinous = TRUE,
			.callback = NULL_PTR,
		},
		{// 200ms Task
			.taskoffset = 0,
			.taskreload = 200,
			.countinous = TRUE,
			.callback = NULL_PTR,
		}
};
