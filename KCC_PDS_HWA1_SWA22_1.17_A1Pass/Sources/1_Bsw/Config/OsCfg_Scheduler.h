/*
 * OsCfg_Scheduler.h
 *
 * Created on: 06.12.2023
 *
 */

#ifndef OS_CFG_SCHEDULER_H_
#define OS_CFG_SCHEDULER_H_

#include "OsScheduler.h"


typedef enum
{
	OsScheduler_Task_1ms = 0,
	OsScheduler_Task_10ms,
	OsScheduler_Task_100ms,
	OsScheduler_Task_200ms,
	OsScheduler_Task_count
}OsScheduler_tasks;



extern const osScheduler_cfg_tasks osScheduler_task_config[OsScheduler_Task_count];


#endif /* OS_CFG_SCHEDULER_H_ */
