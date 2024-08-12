/*
 * AppVadc.c
 *
 *  Created on: 04.07.2012
 *
 */

#include "appVadc.h"
#include "Ifx_Cfg_Vadc.h"
#include "ConfigurationIsr.h"
#include "AppTorqueControl.h"
#include "Ifx_Cfg_FocControl.h"


#define AppVadc_SH_FREQUENCY	(120000000U)

void vadc_conversionEndGroup0(void);
//Name VADC interrupts
IFX_INTERRUPT(vadcgroup0ISR, 0, INTERRUPT_VADC_RESULT_GROUP0)
{
	vadc_conversionEndGroup0();
}

typedef struct
{
	uint8 channelIndex[9];
	uint8 used[9];
	uint16 options[9];
}AppVadc_queuedMode;

typedef struct
{
	IfxVadc_Adc		  module;
	IfxVadc_Adc_Group group[IFXVADC_NUM_ADC_GROUPS];
	AppVadc_AnalogInput_1	channel[AppVadc_ChannelCount];
}AppVadc_Kernel;
//________________________________________________________________________________________
// GLOBAL VARIABLES

AppVadc_Kernel g_appVadc_kernel;

//________________________________________________________________________________________
// FUNCTION IMPLEMENTATIONS



void AppVadc_init(void)
{
#if(APP_VADC_FUNCTION_ON)
	uint8 i,j;
	uint8 groupId;
	uint32 	frequency = IfxScuCcu_getAdcFrequency();
	IfxVadc_Adc_GroupConfig		groupConfig;
	IfxVadc_Adc_ChannelConfig 	channelConfig;

	AppVadc_queuedMode lcl_queued[IFXVADC_NUM_ADC_GROUPS];
	uint32 lcl_scanSource[IFXVADC_NUM_ADC_GROUPS] = {0};

	for(i=0; i< 9; i++)
	{
		for(j=0;j<IFXVADC_NUM_ADC_GROUPS;j++)
		{
			lcl_queued[j].channelIndex[i] = 0;
			lcl_queued[j].used[i] = 0;
			lcl_queued[j].options[i] = 0;
		}
	}

	// Check ADC Frequency if switched off, Setup the ADC Frequency to 120000000MHz and Select PLL2
	frequency = IfxScuCcu_getAdcFrequency();
	if(frequency == 0)
	{
		IfxScuCcu_setPll2Frequency(120000000U);
		IfxScuCcu_selectAdcClock(IfxScuCcu_AdcClockSelection_fpll2);
	}else
	{
		// do nothing, the clock was set somewhere
	}

	// initialize VADC Module
	IfxVadc_Adc_initModule(&g_appVadc_kernel.module, &IfxVadc_adc_module_config);

	// initialize Group
	for(i = 0; i < IFXVADC_NUM_ADC_GROUPS; i++)
	{
		groupConfig = IfxVadc_adc_group_config[i];
		groupConfig.module =& g_appVadc_kernel.module;
		IfxVadc_Adc_initGroup(&g_appVadc_kernel.group[i], &groupConfig);
	}

	// initialize Vadc Channels

	for(i = 0; i < AppVadc_ChannelCount; i++)
	{
		groupId = IfxVadc_cfg_adc_channel[i].groupId;
		channelConfig = IfxVadc_cfg_adc_channel[i].hwChannel;
		channelConfig.group = &g_appVadc_kernel.group[groupId];
		IfxVadc_Adc_initChannel(&g_appVadc_kernel.channel[i].input, &channelConfig);
		g_appVadc_kernel.channel[i].limits = IfxVadc_cfg_adc_channel[i].limits;
		g_appVadc_kernel.channel[i].gain = IfxVadc_cfg_adc_channel[i].gain;
		g_appVadc_kernel.channel[i].offset = IfxVadc_cfg_adc_channel[i].offset;
		g_appVadc_kernel.channel[i].rawvalue = 0U;
		g_appVadc_kernel.channel[i].value = 0.0;
		switch(IfxVadc_cfg_adc_channel[i].coversionSetup.requestSource)
		{
		case IfxVadc_RequestSource_queue:
			if(groupId<IFXVADC_NUM_ADC_GROUPS)	// for local Group Ids
			{
				uint16 options = 0;
				lcl_queued[groupId].channelIndex[IfxVadc_cfg_adc_channel[i].coversionSetup.priority] = i;	// Set channel
				lcl_queued[groupId].used[IfxVadc_cfg_adc_channel[i].coversionSetup.priority] = 1;	// Set Indicator
				if(IfxVadc_cfg_adc_channel[i].coversionSetup.refill == TRUE)
				{
					options = IFXVADC_QUEUE_REFILL;
				}
				if(IfxVadc_cfg_adc_channel[i].coversionSetup.trigger == TRUE)
				{
					options |= IFXVADC_QUEUE_EXT_TRIGGER;
				}
				lcl_queued[groupId].options[IfxVadc_cfg_adc_channel[i].coversionSetup.priority]	= options;	// store the options for this channel
			}
		break;
		case IfxVadc_RequestSource_scan:
			if(groupId<IFXVADC_NUM_ADC_GROUPS)	// for local Group Ids
				lcl_scanSource[groupId] |= 0x1<<channelConfig.channelId;
		break;
		case IfxVadc_RequestSource_background:
		break;
		default: break;
		}
	}

	// Fill queue with requested channels, Oversampling for Current measurement

		// Add Oversampling of I_U at Group 0
		IfxVadc_Adc_addToQueue(&g_appVadc_kernel.channel[AppVadc_Ch_I_U].input, IFXVADC_QUEUE_REFILL|IFXVADC_QUEUE_EXT_TRIGGER);	//  Trigger just refill
		IfxVadc_Adc_addToQueue(&g_appVadc_kernel.channel[AppVadc_Ch_I_U].input, IFXVADC_QUEUE_REFILL);	// No Trigger just refill
		IfxVadc_Adc_addToQueue(&g_appVadc_kernel.channel[AppVadc_Ch_I_U].input, IFXVADC_QUEUE_REFILL);	// No Trigger just refill
		IfxVadc_Adc_addToQueue(&g_appVadc_kernel.channel[AppVadc_Ch_I_U].input, IFXVADC_QUEUE_REFILL);	// No Trigger just refill

		// Add Oversampling of I_V at Group 1
		IfxVadc_Adc_addToQueue(&g_appVadc_kernel.channel[AppVadc_Ch_I_V].input, IFXVADC_QUEUE_REFILL|IFXVADC_QUEUE_EXT_TRIGGER);	//  Trigger just refill
		IfxVadc_Adc_addToQueue(&g_appVadc_kernel.channel[AppVadc_Ch_I_V].input, IFXVADC_QUEUE_REFILL);	// No Trigger just refill
		IfxVadc_Adc_addToQueue(&g_appVadc_kernel.channel[AppVadc_Ch_I_V].input, IFXVADC_QUEUE_REFILL);	// No Trigger just refill
		IfxVadc_Adc_addToQueue(&g_appVadc_kernel.channel[AppVadc_Ch_I_V].input, IFXVADC_QUEUE_REFILL);	// No Trigger just refill

		// Add Oversampling of I_VRO at Group 0
		IfxVadc_Adc_addToQueue(&g_appVadc_kernel.channel[AppVadc_Ch_V_Vro].input, IFXVADC_QUEUE_REFILL);	// No Trigger just refill

		// Enable Datareduction
		g_appVadc_kernel.channel[AppVadc_Ch_I_U].input.group->module.vadc->G[0].RCR[0].B.DRCTR = 3; //Accumulate 4 result
		g_appVadc_kernel.channel[AppVadc_Ch_I_U].input.group->module.vadc->G[0].RCR[0].B.DMM = 0; //Standard data reduction

		g_appVadc_kernel.channel[AppVadc_Ch_I_V].input.group->module.vadc->G[1].RCR[0].B.DRCTR = 3; //Accumulate 4 result
		g_appVadc_kernel.channel[AppVadc_Ch_I_V].input.group->module.vadc->G[1].RCR[0].B.DMM = 0;


	// Fill Scan source with requested channels
	for(j=0; j < IFXVADC_NUM_ADC_GROUPS;j++)
	{
		IfxVadc_Adc_setScan(&g_appVadc_kernel.group[j], lcl_scanSource[j], lcl_scanSource[j], TRUE);
	}
#endif

}


float32 AppVadc_limits_float32_Execute(AppVadc_Limits_1_float32* limits, float32 in)
{
#if(APP_VADC_FUNCTION_ON)
    if (in > limits->max)
    {
        limits->status = AppVadc_LimitsStatus_Max;
        if(limits->onOutOfRange != NULL_PTR)
        {
        	limits->onOutOfRange(limits->object, limits->status,limits->info);
        }
    }
    else if (in < limits->min)
    {
        limits->status = AppVadc_LimitsStatus_Min;
        if(limits->onOutOfRange != NULL_PTR)
		{
			limits->onOutOfRange(limits->object, limits->status,limits->info);
		}
    }
    else
    {
        limits->status = AppVadc_LimitsStatus_Ok;
    }
    return in;
#else
    return 0;
#endif
}


float32 AppVadc_updateAnalogInput(AppVadc_AnalogInput_1 *input)
{
#if(APP_VADC_FUNCTION_ON)
	float32 value;
	uint32 rawValue;
	rawValue = IfxVadc_Adc_getResult(&input->input).B.RESULT;

	// Scale Input
	value = ((float32)input->gain * rawValue + input->offset);
	 /* Check limits */
	value = AppVadc_limits_float32_Execute(&input->limits, value);
	/* Store value */
	input->rawvalue = rawValue;
	input->value = value;
	return value;
#else
	return 0;
#endif
}


float32 AppVadc_updateAnalogInput_DRC(AppVadc_AnalogInput_1 *input)
{

#if(APP_VADC_FUNCTION_ON)
	float32 value;
	uint32 rawValue;
	rawValue = IfxVadc_Adc_getResult(&input->input).B.RESULT>>2;

	// Scale Input
	value = ((float32)input->gain * rawValue + input->offset);
	 /* Check limits */
	value = AppVadc_limits_float32_Execute(&input->limits, value);
	/* Apply filter
	if (Input->FilterEnabled == TRUE)
	{
		value = LowPass_PT1_Do(&Input->Filter, value);
	}
	*/
	/* Store value */
	input->rawvalue = rawValue;
	input->value = value;
	return value;
#else
	return 0;
#endif
}


void vadc_conversionEndGroup0(void)
{

#if(APP_VADC_FUNCTION_ON)
	__enable();
	AppVadc_updateAnalogInput(&g_appVadc_kernel.channel[AppVadc_Ch_V_Vro]);
	AppVadc_updateAnalogInput_DRC(&g_appVadc_kernel.channel[AppVadc_Ch_I_U]);
	AppVadc_updateAnalogInput_DRC(&g_appVadc_kernel.channel[AppVadc_Ch_I_V]);

	TorqueControl_startMotor(&g_motor);

	if(IsCurrentSensorCalibrated(&g_motor))
	{
		g_motor.currents.u = g_motor.analogInputs.currentA->value;
		g_motor.currents.v = g_motor.analogInputs.currentB->value;
		g_motor.currents.w = -(g_motor.currents.u + g_motor.currents.v);

		TorqueControl_FocStep(&g_motor, &g_motor.currents, 0.0);

	}else
	{
		ZeroCurrentSensor(&g_motor,g_motor.analogInputs.currentA,g_motor.analogInputs.currentB,g_motor.analogInputs.currentB,g_motor.analogInputs.sensorOffset);
	}
#endif

}


AppVadc_AnalogInput_1* AppVadc_getCurrentPhaseU_object(void)
{
	return(&g_appVadc_kernel.channel[AppVadc_Ch_I_U]);
}

AppVadc_AnalogInput_1* AppVadc_getCurrentPhaseV_object(void)
{
	return(&g_appVadc_kernel.channel[AppVadc_Ch_I_V]);
}

AppVadc_AnalogInput_1* AppVadc_getCurrentOffset_object(void)
{
	return(&g_appVadc_kernel.channel[AppVadc_Ch_V_Vro]);
}
