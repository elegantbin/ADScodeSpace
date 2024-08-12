/*
 * OsTaskFu.c
 *
 *  Created on: 06.12.2023
 *
 */


#include <MotAct.h>
#include <Switch.h>
#include "OsTypedefs.h"

#include "DioIf.h"
#include "SpiIf.h"
#include "CanIf.h"
#include "UartIf.h"
#include "AdcIf.h"
#include "DualHall.h"
#include "DoorSys.h"
#include"Current.h"
#include "DCU.h"
#include "TCU.h"
#include "IMU.h"
#include "TLE926x.h"
#include "FlashIf.h"

extern uint32_t counter;

void OsTaskfu_cyclic(void)
{

	DoorSys_VelocityEvaluate();
	DoorSys_ApEventCheck();

	DoorSys_EventHandle();

	CanIf0_DebugMsgRxProcessing();
	CanIf0_RxMessagePocessing();

	DCU_Handler();

	//MotorCurrent_Adc_Average(100);
}

void OsTaskfu_1ms(void)
{
	MotorActator_StateMachine();

	CanIf0_ApInfoTransmit();


	CanIf0_DebugMsgTransmit();

	DoorSys_eBrakeControl();

	IMU_Handler();

	DoorSys_eBrakeCheck();


}


void OsTaskfu_5ms(void)
{
	//MotorActator_StateMachine();

	Switch_Check();
	Switch_CmdHandler();

	DoorSys_CmdHandle();
	DoorSys_StateMachine();

	DoorSys_BlockCheck();
	//DoorSys_eBrakeCheck();

//DoorSys_eBrakeControl();



}

void OsTaskfu_10ms(void)
{

	DoorSys_ManaualAssitCheck();

	DoorSys_TipToRunCheck();

	CanIf0_TxMessage();



}

void OsTaskfu_100ms(void)
{


}

void OsTaskfu_200ms(void)
{

	NOP();
	NOP();

}


void OsTaskfu_init(void)
{
    // Initialize Timer for OS Scheduler
	__disable();
	DioIf_Init();
	CanIf0_Init();
	//UartIf_Init();
	//AdcIf_Init();
	//MotorCurrent_Init();

	__enable();
	SpiIf_SbcInit();
	DualHall_Init();
	MotorActator_Init();
	DoorSys_Init();

	SpiIf_sendSbc();

	Switch_Init();

	sbc_init();
	/*sbc_can_mode(CAN_NORMAL_SWK);*/
	Flash_Init();
	DFlash_Write();
}




