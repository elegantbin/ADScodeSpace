/*
 * DualHall.c
 *
 *   Created on: 7.12.2023
 *      Author: Administrator
 */
#include <DoorSys.h>
#include <MotAct.h>
#include "stdarg.h"
#include "DualHall.h"
#include "DoorSys.h"
uint16_t TimeStamp_Pre = 0;
uint16_t TimeStamp_Lst = 0;
uint16_t Overflow_Counter = 0;
uint16_t Overflow_Counter2 = 0;

stHall_t hall_A,hall_B;

ftm_state_t ftmStateStruct_IC;
ftm_state_t ftmStateStruct_IC2;

void FTM1_Timer_OverflowISR();
void FTM2_Timer_OverflowISR();

void DualHall_Init(void)
{

	/***************************************Interrupt registration******************************************************* */
	FTM_DRV_Init(INST_FLEXTIMER_IC1, &flexTimer_ic1_InitConfig,&ftmStateStruct_IC);
	FTM_DRV_InitInputCapture(INST_FLEXTIMER_IC1, &flexTimer_ic1_InputCaptureConfig);
	INT_SYS_InstallHandler(FTM2_Ovf_Reload_IRQn,&FTM2_Timer_OverflowISR,(isr_t*) 0);
	INT_SYS_EnableIRQ(FTM2_Ch0_Ch1_IRQn);
	INT_SYS_EnableIRQ(FTM2_Ovf_Reload_IRQn);
	FTM_DRV_Init(INST_FLEXTIMER_IC2, &flexTimer_ic2_InitConfig,&ftmStateStruct_IC2);
	FTM_DRV_InitInputCapture(INST_FLEXTIMER_IC2, &flexTimer_ic2_InputCaptureConfig);
	INT_SYS_InstallHandler(FTM1_Ovf_Reload_IRQn,&FTM1_Timer_OverflowISR,(isr_t*) 0);
	INT_SYS_EnableIRQ(FTM1_Ch0_Ch1_IRQn);
	INT_SYS_EnableIRQ(FTM1_Ovf_Reload_IRQn);
	/********************************************************************************************************************* */

	hall_A.HallWidth = 0;
	hall_A.HallCount = 0;
	hall_A.b_level   = 0;

	hall_B.HallWidth = 0;
	hall_B.HallCount = 0;
	hall_B.b_level   = 0;
}
/*************************************************************************
  *FUNCTION NAME:
  *FUNCTION DESCRIPTION:
  *PAPRAMETER:		void
  *RETURN VALUE:		void	VALUENAME:void
  *EDITOR:			ReaveGan
  *DATE:				2023.12.07
  *VERSION:			1.0
  *************************************************************************/
void FTM2_Timer_OverflowISR()
{

	Overflow_Counter++;
	if( Overflow_Counter >10)
	{
		 DoorSys_VelocityReset();
	}


	FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_IC1, (uint32_t)FTM_TIME_OVER_FLOW_FLAG);
}
/*************************************************************************
 *FUNCTION NAME:			FTM2_CH1_Input_Detect
 *FUNCTION DESCRIPTION:
 *PAPRAMETER:		void
 *RETURN VALUE:		void	VALUENAME:void
 *EDITOR:			ReaveGan
 *DATE:				2023.12.07
 *VERSION:			1.0
 *************************************************************************/
void  FTM2_CH1_Input_Detect()
 {

	DoorControl_t *door = &g_door;
	hall_A.HallCount++;

#if(HALL_A_POS_UPDATE_ENABLE!=0)
	hall_A.b_level =(PINS_DRV_ReadPins(PTA)>>0)&0x01;
	hall_B.b_level=(PINS_DRV_ReadPins(PTA)>>1)&0x01;

	if(K_HALL_A_DOOR_DIR_FBK_OPEN)
	{
		g_door.u16Realtime_Pos++;
		g_door.b_dir_open_fbk=1;
		g_door.b_dir_close_fbk=0;
	}
	else
	{
		g_door.b_dir_open_fbk=0;
		g_door.b_dir_close_fbk=1;
		g_door.u16Realtime_Pos--;
	}
#endif

 	TimeStamp_Pre = TimeStamp_Lst;
 	TimeStamp_Lst = FTM_DRV_GetInputCaptureMeasurement(INST_FLEXTIMER_IC1,1);

 	hall_A.HallWidth  = (TimeStamp_Lst + Overflow_Counter * 65535 - TimeStamp_Pre);
 	Overflow_Counter = 0;

 	door->b_BlockUpdated = 1;

 	door->b_VelocityUpdate = 1;
    DoorSys_ApUpdateNotification();
 	g_motor.u32Speed = 60 * 2000000 / 6 / hall_A.HallWidth;

 }

/*************************************************************************
 *FUNCTION NAME:
 *FUNCTION DESCRIPTION:
 *PAPRAMETER:		void
 *RETURN VALUE:		void	VALUENAME:void
 *EDITOR:			ReaveGan
 *DATE:				2023.12.07
 *VERSION:			1.0
 *************************************************************************/
void FTM1_Timer_OverflowISR()
{
	Overflow_Counter2++;
	FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_IC2, (uint32_t)FTM_TIME_OVER_FLOW_FLAG);
}

/*************************************************************************
 *FUNCTION NAME:
 *FUNCTION DESCRIPTION:
 *PAPRAMETER:		void
 *RETURN VALUE:		void	VALUENAME:void
 *EDITOR:			ReaveGan
 *DATE:				2023.12.07
 *VERSION:			1.0
 *************************************************************************/
void  FTM1_CH1_Input_Detect()
 {
	hall_B.HallCount++;

#if(HALL_B_POS_UPDATE_ENABLE!=0)
	hall_A.b_level =(PINS_DRV_ReadPins(PTA)>>0)&0x01;
	hall_B.b_level=(PINS_DRV_ReadPins(PTA)>>1)&0x01;

	if(K_HALL_B_DOOR_DIR_FBK_OPEN)
	{

		g_door.u16Realtime_Pos++;
		g_door.b_dir_open_fbk=1;
		g_door.b_dir_close_fbk=0;

	}
	else
	{

		g_door.b_dir_open_fbk=0;
		g_door.b_dir_close_fbk=1;
		g_door.u16Realtime_Pos--;
	}


#endif


 	Overflow_Counter2 = 0;

 }
