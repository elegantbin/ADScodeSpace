/*
 * CanIf.c
 *
 *  Created on: 7.12.2023
 *      Author: Administrator
 */
#include <DoorSys.h>
#include "can_pal.h"
#include "CAN0can_pal1.h"
#include "DualHall.h"
#include "CanIf.h"
/*CAN*/  
can_message_t g_RecvMsg_CAN0;
can_message_t g_TransmitMsg_CAN0;


boolean b_Can0DebugMsgRx = 0;
boolean b_Can0MsgRx = 0;
/*************************************************************************
   *FUNCTION NAME:			CAN0_Callback_Func
   *FUNCTION DESCRIPTION:		CAN send and receive callback functions
   *PAPRAMETER:		uint32_t instance,can_event_t event,uint32_t buffIdx,void *flexcanState
   *RETURN VALUE:		void	VALUENAME:void
   *EDITOR:			ReaveGan
   *DATE:				2023.12.07
   *VERSION:			1.0
   *************************************************************************/
 void CanIf0_Callback_Func (uint32_t instance,can_event_t event,uint32_t buffIdx,void *flexcanState)
{
	(void)flexcanState;
	(void)instance;
	(void)buffIdx;
	 CAN_Receive(&CAN0can_pal1_instance,RX_MAILBOX_CAN0,&g_RecvMsg_CAN0);

	switch(event)
	{
		case CAN_EVENT_RX_COMPLETE:
		{
			if(g_RecvMsg_CAN0.id == 0x311)
			{

				b_Can0DebugMsgRx = 1;
			}
			else
			{

				b_Can0MsgRx = 1;
			}
		}
		break;
		case CAN_EVENT_TX_COMPLETE:

		break;
		default:
			break;
	}
}


 /*************************************************************************
   *FUNCTION NAME:			CAN0_Init
   *FUNCTION DESCRIPTION:		CAN0_Init
   *PAPRAMETER:		void
   *RETURN VALUE:		void	VALUENAME:void
   *EDITOR:			ReaveGan
   *DATE:				2023.12.07
   *VERSION:			1.0
   *************************************************************************/
 void CanIf0_Init(void)
 {
 	CAN_Init(&CAN0can_pal1_instance, &CAN0can_pal1_Config0);
	can_buff_config_t Rx_buffCfg =
	{
	  .enableFD = false,
	  .enableBRS = false,
	  .fdPadding = 0U,
	  .idType = CAN_MSG_ID_STD,
	  .isRemote = false
	};

	can_buff_config_t Tx_buffCfg =
	{
	  .enableFD = false,
	  .enableBRS = false,
	  .fdPadding = 0U,
	  .idType = CAN_MSG_ID_STD,
	  .isRemote = false
	};

 	CAN_ConfigRxBuff(&CAN0can_pal1_instance,RX_MAILBOX_CAN0,&Rx_buffCfg,Rx_Filter);
 	CAN_ConfigTxBuff(&CAN0can_pal1_instance,TX_MAILBOX_CAN0,&Tx_buffCfg);

 	CAN_SetRxFilter(&CAN0can_pal1_instance,CAN_MSG_ID_STD,RX_MAILBOX_CAN0,0);
 	CAN_InstallEventCallback(&CAN0can_pal1_instance,&CanIf0_Callback_Func,(void*)0);
 	CAN_Receive(&CAN0can_pal1_instance,RX_MAILBOX_CAN0,&g_RecvMsg_CAN0);

 	CanIf0_Msg_Init();
 }


 void CanIf0_Send(can_message_t *message )
 {
		CAN_Send(&CAN0can_pal1_instance,TX_MAILBOX_CAN0, message);
 }
