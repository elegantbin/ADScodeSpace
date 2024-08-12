/*
 * Ifx_Cfg_Vadc.c
 *
 *  Created on: 27.08.2013
 *
 */


#include "Ifx_Cfg_Vadc.h"
#include "ConfigurationIsr.h"

#if(CFG_VADC_FUNCTION_ON) /*TODO: ready to port to new platform*/
// Initialization constants for VADC Module
const IfxVadc_Adc_Config IfxVadc_adc_module_config =
{
	.vadc	= (&MODULE_VADC),						 /**< \brief VADC_Module is used   */
	.moduleFrequency = (100000000U),				 /**< \brief digital clock = 100MHz   */
	.analogFrequency = (20000000U),					 /**< \brief analog clock = 20MHz   */
	.disablePostCalibrationGroup[0] = FALSE,			 /**< \brief post calibration enabled   */
	.disablePostCalibrationGroup[1] = FALSE,
	.disablePostCalibrationGroup[2] = FALSE,
	.disablePostCalibrationGroup[3] = FALSE,
};


// Initialization constants for VADC Groups

const IfxVadc_Adc_GroupConfig IfxVadc_adc_group_config[IFXVADC_NUM_ADC_GROUPS] =
{
	{
		.groupId = IfxVadc_GroupId_0,
		.module  = NULL_PTR,
		.arbiter                        = {
			.arbiterRoundLength = IfxVadc_ArbitrationMode_4_slots,
			.reqSlotMode[0]     = IfxVadc_RequestSlotStartMode_cancelInjectRepeat,
			.reqSlotMode[1]     = IfxVadc_RequestSlotStartMode_waitForStart,
			.reqSlotMode[2]     = IfxVadc_RequestSlotStartMode_waitForStart,
			.reqSlotPrio[0]     = IfxVadc_ReqSlotPrio_highest,
			.reqSlotPrio[1]     = IfxVadc_ReqSlotPrio_low,
			.reqSlotPrio[2]     = IfxVadc_ReqSlotPrio_lowest,
			.usedReqSlots[0]    = TRUE, 		/* Enable Queue mode */
			.usedReqSlots[1]    = FALSE,     	/* Disable Scan mode */
			.usedReqSlots[2]    = FALSE,        /* Disable Background scan */
		},
		.backgroundScanReq              = {
			.autoscanEnable             = FALSE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_disabled,
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_noExternalTrigger,
			.triggerConfig.gateInput    = IfxVadc_GatingSource_0,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_0,
		},
		.scanRequest                    = {
			.autoscanEnable             = FALSE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_disabled,
			.triggerConfig.gateInput    = IfxVadc_GatingSource_0,
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_noExternalTrigger,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_0,
		},
		.queueRequest                   = {
			.flushQueueAfterInit        = TRUE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_always,
			//.triggerConfig.gateInput    = IfxVadc_GatingSource_0,            /* Use GTM Trigger 1  */
			.triggerConfig.gateInput    = IfxVadc_GatingSource_1,            /* Use GTM Trigger 1  */
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_uponFallingEdge,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_15,         /* Trigger source taken from Gating Input */
		},
		.inputClass[0].resolution = IfxVadc_ChannelResolution_12bit,
		.inputClass[0].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
		.inputClass[1].resolution = IfxVadc_ChannelResolution_12bit,
		.inputClass[1].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
	},

//
	{
		.groupId = IfxVadc_GroupId_1,
		.module  = NULL_PTR,
		.arbiter                        = {
			.arbiterRoundLength = IfxVadc_ArbitrationMode_4_slots,
			.reqSlotMode[0]     = IfxVadc_RequestSlotStartMode_cancelInjectRepeat,
			.reqSlotMode[1]     = IfxVadc_RequestSlotStartMode_waitForStart,
			.reqSlotMode[2]     = IfxVadc_RequestSlotStartMode_waitForStart,
			.reqSlotPrio[0]     = IfxVadc_ReqSlotPrio_highest,
			.reqSlotPrio[1]     = IfxVadc_ReqSlotPrio_low,
			.reqSlotPrio[2]     = IfxVadc_ReqSlotPrio_lowest,
			.usedReqSlots[0]    = TRUE,         /* Enable Queue mode */
			.usedReqSlots[1]    = FALSE,         /* Disable Scan mode */
			.usedReqSlots[2]    = FALSE,         /* Disable Background scan */
		},
		.backgroundScanReq              = {
			.autoscanEnable             = FALSE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_disabled,
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_noExternalTrigger,
			.triggerConfig.gateInput    = IfxVadc_GatingSource_0,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_0,
		},
		.scanRequest                    = {
			.autoscanEnable             = FALSE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_disabled,
			.triggerConfig.gateInput    = IfxVadc_GatingSource_0,
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_noExternalTrigger,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_0,
		},
		.queueRequest                   = {
			.flushQueueAfterInit        = TRUE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_always,
			.triggerConfig.gateInput    = IfxVadc_GatingSource_1,
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_uponFallingEdge,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_15,
		},
		.inputClass[0].resolution = IfxVadc_ChannelResolution_12bit,
		.inputClass[0].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
		.inputClass[1].resolution = IfxVadc_ChannelResolution_12bit,
		.inputClass[1].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
	},

	{
		.groupId = IfxVadc_GroupId_2,
		.module  = NULL_PTR,
		.arbiter                        = {
			.arbiterRoundLength = IfxVadc_ArbitrationMode_4_slots,
			.reqSlotMode[0]     = IfxVadc_RequestSlotStartMode_cancelInjectRepeat,
			.reqSlotMode[1]     = IfxVadc_RequestSlotStartMode_waitForStart,
			.reqSlotMode[2]     = IfxVadc_RequestSlotStartMode_waitForStart,
			.reqSlotPrio[0]     = IfxVadc_ReqSlotPrio_highest,
			.reqSlotPrio[1]     = IfxVadc_ReqSlotPrio_low,
			.reqSlotPrio[2]     = IfxVadc_ReqSlotPrio_lowest,
			.usedReqSlots[0]    = FALSE,          /* Disable Queue mode */
			.usedReqSlots[1]    = FALSE,         /* Disable Scan mode */
			.usedReqSlots[2]    = FALSE,         /* Disable Background scan */
		},
		.backgroundScanReq              = {
			.autoscanEnable             = FALSE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_disabled,
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_noExternalTrigger,
			.triggerConfig.gateInput    = IfxVadc_GatingSource_0,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_0,
		},
		.scanRequest                    = {
			.autoscanEnable             = FALSE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_disabled,
			.triggerConfig.gateInput    = IfxVadc_GatingSource_0,
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_noExternalTrigger,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_0,
		},
		.queueRequest                   = {
			.flushQueueAfterInit        = FALSE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_disabled,
			.triggerConfig.gateInput    = IfxVadc_GatingSource_0,   			/* Use GTM Trigger 0  */
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_uponFallingEdge,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_0, /* Trigger source taken from Gating Input */
		},
		.inputClass[0].resolution = IfxVadc_ChannelResolution_12bit,
		.inputClass[0].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
		.inputClass[1].resolution = IfxVadc_ChannelResolution_12bit,
		.inputClass[1].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
	},
	{
		.groupId = IfxVadc_GroupId_3,
		.module  = NULL_PTR,
		.arbiter                        = {
			.arbiterRoundLength = IfxVadc_ArbitrationMode_4_slots,
			.reqSlotMode[0]     = IfxVadc_RequestSlotStartMode_cancelInjectRepeat,
			.reqSlotMode[1]     = IfxVadc_RequestSlotStartMode_waitForStart,
			.reqSlotMode[2]     = IfxVadc_RequestSlotStartMode_waitForStart,
			.reqSlotPrio[0]     = IfxVadc_ReqSlotPrio_highest,
			.reqSlotPrio[1]     = IfxVadc_ReqSlotPrio_low,
			.reqSlotPrio[2]     = IfxVadc_ReqSlotPrio_lowest,
			.usedReqSlots[0]    = FALSE,          /* Enable Queue mode */
			.usedReqSlots[1]    = FALSE,         /* Disable Scan mode */
			.usedReqSlots[2]    = FALSE,         /* Disable Background scan */
		},
		.backgroundScanReq              = {
			.autoscanEnable             = FALSE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_disabled,
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_noExternalTrigger,
			.triggerConfig.gateInput    = IfxVadc_GatingSource_0,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_0,
		},
		.scanRequest                    = {
			.autoscanEnable             = FALSE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_disabled,
			.triggerConfig.gateInput    = IfxVadc_GatingSource_0,
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_noExternalTrigger,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_0,
		},
		.queueRequest                   = {
			.flushQueueAfterInit        = FALSE,
			.triggerConfig.gatemode     = IfxVadc_GatingMode_always,
			.triggerConfig.gateInput    = IfxVadc_GatingSource_1,   			/* Use GTM Trigger 1  */
			.triggerConfig.triggermode  = IfxVadc_TriggerMode_uponFallingEdge,
			.triggerConfig.triggerInput = IfxVadc_TriggerSource_15, /* Trigger source taken from Gating Input */
		},
		.inputClass[0].resolution = IfxVadc_ChannelResolution_12bit,
		.inputClass[0].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
		.inputClass[1].resolution = IfxVadc_ChannelResolution_12bit,
		.inputClass[1].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
	}

};
const AppVadc_AnalogInput_cfg IfxVadc_cfg_adc_channel[AppVadc_ChannelCount] = {
		//AppVadc_Ch_I_U,
	{
		.groupId				 = IfxVadc_GroupId_0,
		.hwChannel = {
			.channelId           = IfxVadc_ChannelId_0,
			.group               = NULL_PTR,
			.inputClass          = IfxVadc_InputClass_group0,
			.reference           = IfxVadc_ChannelReference_standard,
			.resultRegister      = IfxVadc_ChannelResult_0,
			.globalResultUsage   = FALSE,
			.lowerBoundary       = IfxVadc_BoundarySelection_group0,
			.upperBoundary       = IfxVadc_BoundarySelection_group0,
			.boundaryMode        = IfxVadc_BoundaryExtension_standard,
			.limitCheck          = IfxVadc_LimitCheck_noCheck,
			.synchonize          = FALSE,
			.backgroundChannel   = FALSE,
			.rightAlignedStorage = FALSE,
			.resultPriority      = 0,
			.resultSrcNr         = IfxVadc_SrcNr_group0,
			.resultServProvider  = IfxSrc_Tos_cpu0,
			.channelPriority     = 0,
			.channelSrcNr        = IfxVadc_SrcNr_group0,
			.channelServProvider = IfxSrc_Tos_cpu0
		},
		.coversionSetup =
		{
			.requestSource = IfxVadc_RequestSource_queue,
			.priority	= 1,
			.refill 	= TRUE,
			.trigger    = TRUE
		},
		.limits = {
				.min = APPVADC_CFG_IMOTOR_MIN,
				.max = APPVADC_CFG_IMOTOR_MAX,
				.status = AppVadc_LimitsStatus_Ok,
				.onOutOfRange	= NULL_PTR,
				.object			= NULL_PTR,
				.info			= 0
		},
		.gain	=	APPVADC_CFG_IMOTOR_GAIN,
		.offset	= 	APPVADC_CFG_IMOTOR_OFFSET,
	},
	//AppVadc_Ch_V_Vro,
{
	.groupId				 = IfxVadc_GroupId_0,
	.hwChannel = {
		.channelId           = IfxVadc_ChannelId_1,
		.group               = NULL_PTR,
		.inputClass          = IfxVadc_InputClass_group0,
		.reference           = IfxVadc_ChannelReference_standard,
		.resultRegister      = IfxVadc_ChannelResult_1,
		.globalResultUsage   = FALSE,
		.lowerBoundary       = IfxVadc_BoundarySelection_group0,
		.upperBoundary       = IfxVadc_BoundarySelection_group0,
		.boundaryMode        = IfxVadc_BoundaryExtension_standard,
		.limitCheck          = IfxVadc_LimitCheck_noCheck,
		.synchonize          = FALSE,
		.backgroundChannel   = FALSE,
		.rightAlignedStorage = FALSE,
		.resultPriority      = INTERRUPT_VADC_RESULT_GROUP0,
		.resultSrcNr         = IfxVadc_SrcNr_group0,
		.resultServProvider  = IfxSrc_Tos_cpu0,
		.channelPriority     = 0,
		.channelSrcNr        = IfxVadc_SrcNr_group0,
		.channelServProvider = IfxSrc_Tos_cpu0
	},
	.coversionSetup =
	{
		.requestSource = IfxVadc_RequestSource_queue,
		.priority	= 2,
		.refill 	= TRUE,
		.trigger    = FALSE
	},
	.limits = {
			.min = APPVADC_CFG_VMOTOR_MIN,
			.max = APPVADC_CFG_VMOTOR_MAX,
			.status = AppVadc_LimitsStatus_Ok,
			.onOutOfRange	= NULL_PTR,
			.object			= NULL_PTR,
			.info			= 0
	},
	.gain	=	APPVADC_CFG_VMOTOR_GAIN,
	.offset	= 	APPVADC_CFG_VMOTOR_OFFSET,
},
	//AppVadc_Ch_I_V,
	{
		.groupId				 = IfxVadc_GroupId_1,
		.hwChannel = {
			.channelId           = IfxVadc_ChannelId_0,
			.group               = NULL_PTR,
			.inputClass          = IfxVadc_InputClass_group0,
			.reference           = IfxVadc_ChannelReference_standard,
			.resultRegister      = IfxVadc_ChannelResult_0,
			.globalResultUsage   = FALSE,
			.lowerBoundary       = IfxVadc_BoundarySelection_group0,
			.upperBoundary       = IfxVadc_BoundarySelection_group0,
			.boundaryMode        = IfxVadc_BoundaryExtension_standard,
			.limitCheck          = IfxVadc_LimitCheck_noCheck,
			.synchonize          = FALSE,
			.backgroundChannel   = FALSE,
			.rightAlignedStorage = FALSE,
			.resultPriority      = 0,
			.resultSrcNr         = IfxVadc_SrcNr_group0,
			.resultServProvider  = IfxSrc_Tos_cpu0,
			.channelPriority     = 0,
			.channelSrcNr        = IfxVadc_SrcNr_group0,
			.channelServProvider = IfxSrc_Tos_cpu0
		},
		.coversionSetup =
		{
			.requestSource = IfxVadc_RequestSource_queue,
			.priority	= 1,
			.refill 	= TRUE,
			.trigger    = TRUE
		},
		.limits = {
				.min = APPVADC_CFG_IMOTOR_MIN,
				.max = APPVADC_CFG_IMOTOR_MAX,
				.status = AppVadc_LimitsStatus_Ok,
				.onOutOfRange	= NULL_PTR,
				.object			= NULL_PTR,
				.info			= 0
		},
		.gain	=	APPVADC_CFG_IMOTOR_GAIN,
		.offset	= 	APPVADC_CFG_IMOTOR_OFFSET,
	},
};

#endif

