/*
 * CanIfCfg_Message.c
 *
 *  Created on: 2023Äê12ÔÂ16ÈÕ
 *      Author: Administrator
 */
#include <CanMsgHandler/CanIf_MsgHandler.h>
#include "CanIf_Msg.h"
#include "CanIfCfg_Msg.h"

#include "SBC_Handler.h"
#include "FlashIf.h"

const CanMsgCfg_t   canRxMsgCfg[MSG_RX_COUNT] =
{
	{
		.idx = MSG_TCU_1AC,
		.msgId = CAN_MSG_TCU_1AC_0x1AC,
		.msgIdHandlerFunc = CanMsgHandler_TCU_1AC
	},

	{
		.idx = MSG_IMU_350,
		.msgId = CAN_MSG_IMU_350_ID0x350,
		.msgIdHandlerFunc = CanMsgHandler_IMU_350
	},

	{
		.idx = MSG_BCM_365,
		.msgId = CAN_MSG_BCM_365_ID0x365,
		.msgIdHandlerFunc = CanMsgHandler_BCM_365
	},

	{
		.idx = MSG_DATC_380,
		.msgId = CAN_MSG_DATC_380_ID0x380,
		.msgIdHandlerFunc = CanMsgHandler_DATC_380
	},

	{
		.idx = MSG_DCU_FL_310,
		.msgId = CAN_MSG_DCU_FL_310_ID0x310,
		.msgIdHandlerFunc = CanMsgHandler_DCU_FL_310
	},

	{
		.idx = MSG_DCU_FR_320,
		.msgId = CAN_MSG_DCU_FR_320_ID0x320,
		.msgIdHandlerFunc = CanMsgHandler_DCU_FR_320
	},

	{
		.idx = MSG_DCU_RL_330,
		.msgId = CAN_MSG_DCU_RL_330_ID0x330,
		.msgIdHandlerFunc = CanMsgHandler_DCU_RL_330
	},
	{
		.idx = MSG_DCU_RR_340,
		.msgId = CAN_MSG_DCU_RR_340_ID0x340,
		.msgIdHandlerFunc = CanMsgHandler_DCU_RR_340
	},
	{
		.idx = MSG_SBC_TEST,
		.msgId = 0x333,
		.msgIdHandlerFunc = SBC_Sleep_Handler

	}
};











const CanMsgCfg_t   canTxMsgCfg[MSG_TX_COUNT] =
{

#if(PDS_DOOR_SIDE_FL == PDS_DOOR_SIDE_TYPE)
	{
		.idx = MSG_PDS_FL_370,
		.msgId = CAN_MSG_PDS_FL_370_ID0x370,
		.msgIdHandlerFunc = CanMsgHandler_PDS_FL_370
	},

#elif(PDS_DOOR_SIDE_FR == PDS_DOOR_SIDE_TYPE)
	{
		.idx = MSG_PDS_FR_371,
		.msgId = CAN_MSG_PDS_FR_371_ID0x371,
		.msgIdHandlerFunc = CanMsgHandler_PDS_FR_371
	},

#elif(PDS_DOOR_SIDE_RL == PDS_DOOR_SIDE_TYPE)
	{
		.idx = MSG_PDS_RL_372,
		.msgId = CAN_MSG_PDS_RL_372_ID0x372,
		.msgIdHandlerFunc = CanMsgHandler_PDS_RL_372
	},

#elif(PDS_DOOR_SIDE_RR == PDS_DOOR_SIDE_TYPE)
	{
		.idx = MSG_PDS_RR_373,
		.msgId = CAN_MSG_PDS_RR_373_ID0x373,
		.msgIdHandlerFunc = CanMsgHandler_PDS_RR_373
	}
#else
#error "No PDS Door side defined in canTxMsgCfg."
#endif

};

