/*
 * Ifx_Cfg_Vadc.c
 *
 *  Created on: 27.08.2013
 *
 */


#include "Ifx_Cfg_Vadc.h"
#include "ConfigurationIsr.h"
#include "IfxVadc.h"

// Initialization constants for VADC Module
IfxVadc_Adc_Config IfxVadc_adc_module_config =
{
    .vadc   = (&MODULE_VADC),                        /**< \brief VADC_Module is used   */
    .digitalFrequency = (100000000U),                 /**< \brief digital clock = 100MHz   */
    .analogFrequency = (IFXVADC_DEFAULT_ANALOG_FREQ),                  /**< \brief analog clock = 20MHz   */
    .moduleFrequency = (20000000U),//10M??

   .globalInputClass[0].resolution = IfxVadc_ChannelResolution_12bit,
   .globalInputClass[0].sampleTime = 1.0e-6,
   .globalInputClass[1].resolution = IfxVadc_ChannelResolution_12bit,
   .globalInputClass[1].sampleTime = 1.0e-6,
   .startupCalibration             = FALSE,
   .supplyVoltage                  = IfxVadc_LowSupplyVoltageSelect_5V,
};

// Initialization constants for VADC Groups

IfxVadc_Adc_GroupConfig IfxVadc_adc_group_config[IFXVADC_NUM_ADC_GROUPS]=
{
 /****************************************  GROUP 0 ************************************************************/
    {
        .groupId = IfxVadc_GroupId_0,
        .master  = IfxVadc_GroupId_0,
        .module  = NULL_PTR,
        .arbiter                        =
        {
            .arbiterRoundLength = IfxVadc_ArbitrationRounds_4_slots,
            .requestSlotQueueEnabled             = FALSE,         /* Disable Queue mode */
            .requestSlotScanEnabled              = FALSE,        /* Disable Scan mode */
            .requestSlotBackgroundScanEnabled    = FALSE,        /* Disable Background scan */
        },
        .backgroundScanRequest              = {
            .autoBackgroundScanEnabled  = FALSE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_disabled,
            .triggerConfig.triggerMode  = IfxVadc_TriggerMode_noExternalTrigger,
            .triggerConfig.gatingSource    = IfxVadc_GatingSource_0,
            .triggerConfig.triggerSource = IfxVadc_TriggerSource_0,
            .requestSlotPrio          =  IfxVadc_RequestSlotPriority_low,
            .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
        },
        .scanRequest                    = {
            .autoscanEnabled             = TRUE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_always,
            .triggerConfig.gatingSource    = IfxVadc_GatingSource_1,
            .triggerConfig.triggerMode  = IfxVadc_TriggerMode_uponFallingEdge,
            .triggerConfig.triggerSource = IfxVadc_TriggerSource_15,
            .requestSlotPrio          =  IfxVadc_RequestSlotPriority_low,
            .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
        },
        .queueRequest                   = {
            .flushQueueAfterInit          = TRUE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_always,
            .triggerConfig.gatingSource   = IfxVadc_GatingSource_0,            /* Use GTM Trigger 0  */
            .triggerConfig.triggerMode    = IfxVadc_TriggerMode_uponFallingEdge,
            .triggerConfig.triggerSource  = IfxVadc_TriggerSource_15,         /* Trigger source taken from Gating Input */
            .requestSlotPrio              = IfxVadc_RequestSlotPriority_high,
            .requestSlotStartMode         = IfxVadc_RequestSlotStartMode_waitForStart,
        },
        .inputClass[0].resolution = IfxVadc_ChannelResolution_12bit,
        .inputClass[0].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
        .inputClass[1].resolution = IfxVadc_ChannelResolution_12bit,
        .inputClass[1].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
        .disablePostCalibration  = TRUE,
    },
    /****************************************  GROUP 1 ************************************************************/
    {
        .groupId = IfxVadc_GroupId_1,
        .master  = IfxVadc_GroupId_0,
        .module  = NULL_PTR,
        .arbiter=
        {
            .arbiterRoundLength = IfxVadc_ArbitrationRounds_4_slots,
            .requestSlotQueueEnabled             = FALSE,         /* Disable Queue mode */
            .requestSlotScanEnabled              = FALSE,        /* Disable Scan mode */
            .requestSlotBackgroundScanEnabled    = FALSE,        /* Disable Background scan */
        },
        .backgroundScanRequest=
        {
            .autoBackgroundScanEnabled  = FALSE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_disabled,
            .triggerConfig.triggerMode  = IfxVadc_TriggerMode_noExternalTrigger,
            .triggerConfig.gatingSource    = IfxVadc_GatingSource_0,
            .triggerConfig.triggerSource = IfxVadc_TriggerSource_0,
            .requestSlotPrio          =  IfxVadc_RequestSlotPriority_low,
            .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
        },
        .scanRequest=
        {
            .autoscanEnabled             = TRUE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_always,
            .triggerConfig.gatingSource    = IfxVadc_GatingSource_0,
            .triggerConfig.triggerMode  = IfxVadc_TriggerMode_uponFallingEdge,
            .triggerConfig.triggerSource = IfxVadc_TriggerSource_15,
            .requestSlotPrio          =  IfxVadc_RequestSlotPriority_low,
            .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
        },
        .queueRequest=
        {
            .flushQueueAfterInit        = TRUE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_always,
            .triggerConfig.gatingSource    = IfxVadc_GatingSource_0,            /* Use GTM Trigger 0  */
            .triggerConfig.triggerMode  =  IfxVadc_TriggerMode_uponFallingEdge,
            .triggerConfig.triggerSource = IfxVadc_TriggerSource_15,         /* Trigger source taken from Gating Input */
            .requestSlotPrio          =  IfxVadc_RequestSlotPriority_high,
            .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
        },
        .inputClass[0].resolution = IfxVadc_ChannelResolution_12bit,
        .inputClass[0].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
        .inputClass[1].resolution = IfxVadc_ChannelResolution_12bit,
        .inputClass[1].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
        .disablePostCalibration  = TRUE,
    },
    /****************************************  GROUP 2 Not Used************************************************************/
    {
        .groupId = IfxVadc_GroupId_2,
        .master  = IfxVadc_GroupId_0,
        .module  = NULL_PTR,
        .arbiter=
        {
            .arbiterRoundLength = IfxVadc_ArbitrationRounds_4_slots,
            .requestSlotQueueEnabled             = FALSE,         /* Enable Queue mode */
            .requestSlotScanEnabled              = FALSE,        /* Disable Scan mode */
            .requestSlotBackgroundScanEnabled    = FALSE,        /* Disable Background scan */
        },
        .backgroundScanRequest=
        {
            .autoBackgroundScanEnabled  = FALSE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_disabled,
            .triggerConfig.triggerMode  = IfxVadc_TriggerMode_noExternalTrigger,
            .triggerConfig.gatingSource    = IfxVadc_GatingSource_0,
            .triggerConfig.triggerSource = IfxVadc_TriggerSource_0,
            .requestSlotPrio          =  IfxVadc_RequestSlotPriority_low,
            .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
       },
        .scanRequest                    = {
            .autoscanEnabled             = FALSE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_disabled,
            .triggerConfig.gatingSource    = IfxVadc_GatingSource_0,
            .triggerConfig.triggerMode  = IfxVadc_TriggerMode_noExternalTrigger,
            .triggerConfig.triggerSource = IfxVadc_TriggerSource_0,
            .requestSlotPrio          =  IfxVadc_RequestSlotPriority_low,
            .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
       },
        .queueRequest                   = {
            .flushQueueAfterInit        = FALSE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_disabled,
            .triggerConfig.gatingSource    = IfxVadc_GatingSource_0,            /* Use GTM Trigger 0  */
            .triggerConfig.triggerMode    = IfxVadc_TriggerMode_uponFallingEdge,
            .triggerConfig.triggerSource  = IfxVadc_TriggerSource_15,         /* Trigger source taken from Gating Input */
            .requestSlotPrio          =  IfxVadc_RequestSlotPriority_high,
            .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
       },
        .inputClass[0].resolution = IfxVadc_ChannelResolution_12bit,
        .inputClass[0].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
        .inputClass[1].resolution = IfxVadc_ChannelResolution_12bit,
        .inputClass[1].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
        .disablePostCalibration  = TRUE,
    },
    /****************************************  GROUP 3 ************************************************************/
    {
        .groupId = IfxVadc_GroupId_3,
        .master  = IfxVadc_GroupId_3,
        .module  = NULL_PTR,
        .arbiter   =
        {
            .arbiterRoundLength = IfxVadc_ArbitrationRounds_4_slots,
            .requestSlotQueueEnabled             = TRUE,         /* Enable Queue mode */
            .requestSlotScanEnabled              = FALSE,        /* Disable Scan mode */
            .requestSlotBackgroundScanEnabled    = FALSE,        /* Disable Background scan */
        },
        .backgroundScanRequest  =
        {
            .autoBackgroundScanEnabled  = FALSE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_disabled,
            .triggerConfig.triggerMode  = IfxVadc_TriggerMode_noExternalTrigger,
            .triggerConfig.gatingSource    = IfxVadc_GatingSource_0,
            .triggerConfig.triggerSource = IfxVadc_TriggerSource_0,
            .requestSlotPrio          =  IfxVadc_RequestSlotPriority_low,
            .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
        },
        .scanRequest  =
        {
            .autoscanEnabled             = FALSE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_always,
            .triggerConfig.gatingSource    = IfxVadc_GatingSource_0,  /* Use GTM Trigger 0  */
            .triggerConfig.triggerMode  = IfxVadc_TriggerMode_noExternalTrigger,
            .triggerConfig.triggerSource = IfxVadc_TriggerSource_0,
            .requestSlotPrio          =  IfxVadc_RequestSlotPriority_high,
            .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
        },
        .queueRequest   =
        {
            .flushQueueAfterInit        = TRUE,
            .triggerConfig.gatingMode     = IfxVadc_GatingMode_always,
            .triggerConfig.gatingSource    = IfxVadc_GatingSource_0,            /* Use GTM Trigger 0( IfxGtm_Trig_AdcTrig_0)  */
            .triggerConfig.triggerMode  = IfxVadc_TriggerMode_uponFallingEdge,
            .triggerConfig.triggerSource = IfxVadc_TriggerSource_15,         /* Trigger source taken from Gating Input */
            .requestSlotPrio          =  IfxVadc_RequestSlotPriority_high,
            .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_cancelInjectRepeat,
       },
        .inputClass[0].resolution = IfxVadc_ChannelResolution_12bit,
        .inputClass[0].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
        .inputClass[1].resolution = IfxVadc_ChannelResolution_12bit,
        .inputClass[1].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
        .disablePostCalibration  = TRUE,
    },

    /****************************************  GROUP 4************************************************************/
    {
           .groupId = IfxVadc_GroupId_4,
           .master  = IfxVadc_GroupId_4,
           .module  = NULL_PTR,
           .arbiter                        =
           {
               .arbiterRoundLength = IfxVadc_ArbitrationRounds_4_slots,
               .requestSlotQueueEnabled             = TRUE,         /* Enable Queue mode */
               .requestSlotScanEnabled              = FALSE,        /* Enable Scan mode */
               .requestSlotBackgroundScanEnabled    = FALSE,        /* Disable Background scan */
           },
           .backgroundScanRequest              = {
               .autoBackgroundScanEnabled  = FALSE,
               .triggerConfig.gatingMode     = IfxVadc_GatingMode_disabled,
               .triggerConfig.triggerMode  = IfxVadc_TriggerMode_noExternalTrigger,
               .triggerConfig.gatingSource    = IfxVadc_GatingSource_0,
               .triggerConfig.triggerSource = IfxVadc_TriggerSource_0,
               .requestSlotPrio          =  IfxVadc_RequestSlotPriority_low,
               .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
           },
           .scanRequest                    = {
               .autoscanEnabled             = TRUE,
               .triggerConfig.gatingMode     = IfxVadc_GatingMode_always,
               .triggerConfig.gatingSource    = IfxVadc_GatingSource_1,
               .triggerConfig.triggerMode  = IfxVadc_TriggerMode_uponFallingEdge,
               .triggerConfig.triggerSource = IfxVadc_TriggerSource_15,
               .requestSlotPrio          =  IfxVadc_RequestSlotPriority_low,
               .requestSlotStartMode     =  IfxVadc_RequestSlotStartMode_waitForStart,
           },
           .queueRequest                   = {
               .flushQueueAfterInit          = TRUE,
               .triggerConfig.gatingMode     = IfxVadc_GatingMode_always,
               .triggerConfig.gatingSource   = IfxVadc_GatingSource_0,            /* Use GTM Trigger 0( IfxGtm_Trig_AdcTrig_0)  */
               .triggerConfig.triggerMode    = IfxVadc_TriggerMode_uponFallingEdge,
               .triggerConfig.triggerSource  = IfxVadc_TriggerSource_15,         /* Trigger source taken from Gating Input */
               .requestSlotPrio              = IfxVadc_RequestSlotPriority_high,
               .requestSlotStartMode         = IfxVadc_RequestSlotStartMode_cancelInjectRepeat,
           },
           .inputClass[0].resolution = IfxVadc_ChannelResolution_12bit,
           .inputClass[0].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
           .inputClass[1].resolution = IfxVadc_ChannelResolution_12bit,
           .inputClass[1].sampleTime = 1.0e-6,                        /* Set sample time to 1us */
           .disablePostCalibration  = TRUE,
       }

};

/******************************************************************************************************/
/***       AN35 / VADCG4.3      U相电流检测                  IfxVadc_G4_3_AN35_IN  ***/
/***        VADCG3.2  / AN26 	母线48V电压检测              IfxVadc_G3_2_AN26_IN   */
/***       VADCG4.7 / AN39   	V相电流检测                  IfxVadc_G4_7_AN39_IN  ***/
/***        VADCG4.6 / AN38	  W相电流检测                    IfxVadc_G4_6_AN38_IN  ***/
/******************************************************************************************************/
AppVadc_AnalogInput_cfg IfxVadc_cfg_adc_channel[AppVadc_ChannelCount]= {

    /****************************************  CHANNEL 0************************************************************/
    /***************************************AppVadc_Ch_I_U************************************************************/
    {
        .groupId                 = IfxVadc_GroupId_4,
        .hwChannel =
        {
            .channelId           = IfxVadc_ChannelId_3,
            .group               = NULL_PTR,
            .inputClass          = IfxVadc_InputClasses_group0,
            .reference           = IfxVadc_ChannelReference_standard,
            .resultRegister      = IfxVadc_ChannelResult_15,
            .globalResultUsage   = FALSE,
            .lowerBoundary       = IfxVadc_BoundarySelection_group0,
            .upperBoundary       = IfxVadc_BoundarySelection_group0,
            .boundaryMode        = IfxVadc_BoundaryExtension_standard,
            .limitCheck          = IfxVadc_LimitCheck_noCheck,
            .synchonize          = FALSE,
            .backgroundChannel   = FALSE,
            .rightAlignedStorage = FALSE,
            .resultPriority      = INTERRUPT_VADC_RESULT_GROUP3,
            .resultSrcNr         = IfxVadc_SrcNr_group0,
            .resultServProvider  = IfxSrc_Tos_cpu0,
            .channelPriority     = 0,
            .channelSrcNr        = IfxVadc_SrcNr_group0,
            .channelServProvider = IfxSrc_Tos_cpu0
        },
        .coversionSetup =
        {
            .requestSource = IfxVadc_RequestSource_queue,
            .priority   = 1,
            .refill     = TRUE,
            .trigger    = TRUE
        },
        .limits =
        {
                .min = APPVADC_CFG_IMOTOR_MIN,
                .max = APPVADC_CFG_IMOTOR_MAX,
                .status = AppVadc_LimitsStatus_Ok,
                .onOutOfRange   = NULL_PTR,
                .object         = NULL_PTR,
                .info           = 0
        },
        .gain   =   APPVADC_CFG_IMOTOR_GAIN_U,
        .offset =   APPVADC_CFG_IMOTOR_OFFSET_U,
    },
    /****************************************  CHANNEL 1************************************************************/
    /****************************************AppVadc_Ch_V_Vro************************************************************/
    {
    .groupId                 = IfxVadc_GroupId_3,
    .hwChannel =
    {
        .channelId           = IfxVadc_ChannelId_2,
        .group               = NULL_PTR,
        .inputClass          = IfxVadc_InputClasses_group0,
        .reference           = IfxVadc_ChannelReference_standard,
        .resultRegister      = IfxVadc_ChannelResult_2,
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
        .priority   = 2,
        .refill     = TRUE,
        .trigger    = TRUE
    },
    .limits =
    {
            .min = APPVADC_CFG_VMOTOR_MIN,
            .max = APPVADC_CFG_VMOTOR_MAX,
            .status = AppVadc_LimitsStatus_Ok,
            .onOutOfRange   = NULL_PTR,
            .object         = NULL_PTR,
            .info           = 0
    },
    .gain   =   APPVADC_CFG_VMOTOR_GAIN,
    .offset =   APPVADC_CFG_IMOTOR_OFFSET_U,
    },

    /****************************************  CHANNEL 2************************************************************/
    /****************************************AppVadc_Ch_I_V*********************************************************/
    {
        .groupId                 = IfxVadc_GroupId_4,
        .hwChannel =
        {
            .channelId           = IfxVadc_ChannelId_7,
            .group               = NULL_PTR,
            .inputClass          = IfxVadc_InputClasses_group0,
            .reference           = IfxVadc_ChannelReference_standard,
            .resultRegister      = IfxVadc_ChannelResult_7,
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
            .priority   = 3,
            .refill     = TRUE,
            .trigger    = TRUE
        },
        .limits =
        {
                .min = APPVADC_CFG_IMOTOR_MIN,
                .max = APPVADC_CFG_IMOTOR_MAX,
                .status = AppVadc_LimitsStatus_Ok,
                .onOutOfRange   = NULL_PTR,
                .object         = NULL_PTR,
                .info           = 0
        },
        .gain   =   APPVADC_CFG_IMOTOR_GAIN_V,
        .offset =   APPVADC_CFG_IMOTOR_OFFSET_V,
    },
    /****************************************  CHANNEL 3************************************************************/
    /****************************************AppVadc_Ch_I_W*********************************************************/
    {
        .groupId                 = IfxVadc_GroupId_4,
        .hwChannel =
        {
            .channelId           = IfxVadc_ChannelId_6,
            .group               = NULL_PTR,
            .inputClass          = IfxVadc_InputClasses_group0,
            .reference           = IfxVadc_ChannelReference_standard,
            .resultRegister      = IfxVadc_ChannelResult_6,
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
            .priority   = 4,
            .refill     = TRUE,
            .trigger    = TRUE
        },
        .limits =
        {
                .min = APPVADC_CFG_IMOTOR_MIN,
                .max = APPVADC_CFG_IMOTOR_MAX,
                .status = AppVadc_LimitsStatus_Ok,
                .onOutOfRange   = NULL_PTR,
                .object         = NULL_PTR,
                .info           = 0
        },
        .gain   =   APPVADC_CFG_IMOTOR_GAIN_W,
        .offset =   APPVADC_CFG_IMOTOR_OFFSET_W,
    }
};


