/*
 * AppScheduler.h
 *
 *  Created on: 19.09.2013
 *
 */

#ifndef APPSCHEDULER_H_
#define APPSCHEDULER_H_


#include "Ifx_Types.h"

typedef void (*schedulerCallback)(void);

typedef struct
{
	uint32 taskoffset;
	uint32 taskreload;
	boolean countinous;
	schedulerCallback  callback;   /**< \brief Specifies callback routine */
}AppScheduler_cfg_tasks;

typedef struct
{
	uint32 taskcounter;
	uint32 taskreload;
	boolean countinous;
	uint32 overflow;
	boolean run;
	schedulerCallback  callback;   /**< \brief Specifies callback routine */
}AppScheduler_task;


void AppScheduler_initTask(AppScheduler_task *handle,AppScheduler_cfg_tasks *config);

void AppScheduler_tick(AppScheduler_task *handle);

void AppScheduler_process(AppScheduler_task *handle);

void AppScheduler_init(void);

#endif /* APPSCHEDULER_H_ */
