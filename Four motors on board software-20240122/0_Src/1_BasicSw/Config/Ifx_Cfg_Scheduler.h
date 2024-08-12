/*
 * Ifx_Cfg_Scheduler.h
 *
 *
 */

#ifndef IFX_CFG_SCHEDULER_H_
#define IFX_CFG_SCHEDULER_H_



#include "AppScheduler.h"



typedef enum
{
//    AppScheduler_Task_1us = 0,
    AppScheduler_Task_1ms = 0,
    AppScheduler_Task_2ms,
	AppScheduler_Task_10ms,
	AppScheduler_Task_100ms,
	AppScheduler_Task_200ms,
	AppScheduler_Task_count
}AppScheduler_tasks;



IFX_EXTERN const AppScheduler_cfg_tasks appScheduler_task_config[AppScheduler_Task_count];


#endif /* IFX_CFG_SCHEDULER_H_ */
