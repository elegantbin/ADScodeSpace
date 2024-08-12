/*
 * OsMain.c
 *
 *  Created on: 06.12.2023
 *
 */
#include "OsTypedefs.h"
#include "OsTaskFu.h"
#include "OsTimerTick.h"
#include "0_AppSW/Components/Roll_Pitch_Parameter.h"
#include "IMU.h"



/** \brief Initialize the position sensor interfaces */ 

void OsMainInit(void)
{
	OsTimerTick_Init();
	OsScheduler_init();
}


void OsMain(void)
{
    // Initialize Tasks
    OsTaskfu_init();
	OsMainInit();
	Roll_Pitch_Adjust();


    while (1)
    {

    	Roll_Pitch_Adjust();

    	if(timer1ms_counter>K_TIMER_1MS_COUNT)
    	{
    		timer1ms_counter = 0;
    		OsTaskfu_1ms();
    	}

    	if(timer5ms_counter>K_TIMER_5MS_COUNT)
    	{
    		timer5ms_counter=0;

    		OsTaskfu_5ms();

    	}

    	if(timer10ms_counter>K_TIMER_10MS_COUNT)
    	{
    		timer10ms_counter=0;
    		OsTaskfu_10ms();
    	}

    	if(timer100ms_counter>K_TIMER_100MS_COUNT)
    	{
    		timer100ms_counter=0;
    		OsTaskfu_100ms();

    	}

    	if(timer200ms_counter>K_TIMER_200MS_COUNT)
    	{
    		timer200ms_counter=0;
    		OsTaskfu_200ms();
    	}

    	OsTaskfu_cyclic();

    }
}
