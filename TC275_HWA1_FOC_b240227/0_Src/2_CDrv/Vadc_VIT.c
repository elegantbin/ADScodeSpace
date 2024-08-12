/*
 * AppVadc.c
 *
 *  Created on: 04.07.2012
 *
 */
#include <Vadc_VIT.h>
#include "IfxVadc_adc.h"
#include "Ifx_Cfg_Vadc.h"
#include "ConfigurationIsr.h"
#include "AppTorqueControl.h"
#include "Ifx_Cfg_FocControl.h"

#include "IfxGtm_Trig.h"
#include "LowPass_PT1.h"
#include "vadc_lowpasspt1.h"

void vadc_conversionEndGroup0(void);
void get_PhaseCurrent(AppMotor_Motor* motor);

void vadc_SamplesToBuffer(AppMotor_Motor* motor);
//Name VADC interrupts
IFX_INTERRUPT(vadcgroup0ISR, 0, INTERRUPT_VADC_RESULT_GROUP3)
{
    IfxPort_setPinMode(&MODULE_P32, 2,  IfxPort_Mode_outputPushPullGeneral);
    IfxPort_togglePin(&MODULE_P32, 2);

	vadc_conversionEndGroup0();
}
//________________________________________________________________________________________
// GLOBAL VARIABLES

AppVadc_Kernel g_appVadc_kernel;

//________________________________________________________________________________________
// FUNCTION IMPLEMENTATIONS
void Vadc_VIT_init(void)
{
    uint8 i;
	uint8 groupId;
	IfxVadc_Adc_Config adcMouduleConfig;
	IfxVadc_Adc_GroupConfig		groupConfig;
	IfxVadc_Adc_ChannelConfig 	channelConfig;

	// initialize VADC Module
	{
        adcMouduleConfig = IfxVadc_adc_module_config;
        adcMouduleConfig.digitalFrequency               = IfxVadc_getAdcDigitalFrequency(adcMouduleConfig.vadc);
        adcMouduleConfig.moduleFrequency                = IfxScuCcu_getSpbFrequency();

        IfxVadc_Adc_initModule(&g_appVadc_kernel.module, &adcMouduleConfig);
	}

	// initialize Group
	for(i = 0; i < IFXVADC_NUM_ADC_GROUPS - 3; i++)
	{
		groupConfig = IfxVadc_adc_group_config[i];
		groupConfig.module =&g_appVadc_kernel.module;
		IfxVadc_Adc_initGroup(&g_appVadc_kernel.group[i], &groupConfig);
	}

	// initialize Vadc Channels
	for(i = 0; i < AppVadc_ChannelCount; i++)
	{
		groupId = IfxVadc_cfg_adc_channel[i].groupId;
		channelConfig = IfxVadc_cfg_adc_channel[i].hwChannel;
		channelConfig.group = &g_appVadc_kernel.group[groupId];

		IfxVadc_Adc_initChannel(&g_appVadc_kernel.analogInputs[i].adcChannel, &channelConfig);

		g_appVadc_kernel.analogInputs[i].limits = IfxVadc_cfg_adc_channel[i].limits;
		g_appVadc_kernel.analogInputs[i].gain = IfxVadc_cfg_adc_channel[i].gain;
		g_appVadc_kernel.analogInputs[i].offset = IfxVadc_cfg_adc_channel[i].offset;
		g_appVadc_kernel.analogInputs[i].rawvalue = 0U;
		g_appVadc_kernel.analogInputs[i].value = 0.0;

	}

	// Fill queue with requested channels, OverSampling for Current measurement
	{
		// Add Oversampling of I_U at Group 4
		IfxVadc_Adc_addToQueue(&g_appVadc_kernel.analogInputs[AppVadc_Ch_I_U].adcChannel, IFXVADC_QUEUE_REFILL|IFXVADC_QUEUE_EXT_TRIGGER);	//  Trigger and refill//IFXVADC_QUEUE_EXT_TRIGGER

        // Add Oversampling of I_V at Group 4
		IfxVadc_Adc_addToQueue(&g_appVadc_kernel.analogInputs[AppVadc_Ch_I_V].adcChannel, IFXVADC_QUEUE_REFILL);	// no Trigger just refill

		// Add Oversampling of I_W at Group 4
        IfxVadc_Adc_addToQueue(&g_appVadc_kernel.analogInputs[AppVadc_Ch_I_W].adcChannel, IFXVADC_QUEUE_REFILL);  //  Trigger just refill

        // Add Oversampling of V_VRO at Group 3
//        IfxVadc_Adc_addToQueue(&g_appVadc_kernel.analogInputs[AppVadc_Ch_V_Vro].adcChannel, IFXVADC_QUEUE_REFILL|IFXVADC_QUEUE_EXT_TRIGGER);  //  Trigger just refill
	}



    // Enable Datareduction and filtering config
	{

#define DMM_DATA_REDUCTION          0x0     /* Value of DMM bit field to set Standard Data Reduction Mode           */
#define DMM_RESULT_FILTERING        0x1     /* Value of DMM bit field to set Result Filtering Mode                  */

#define DRCTR_DATA_REDUCTION        0x3     /* Value of DRCTR to accumulate 4 conversions                           */
#define DRCTR_FIR_COEFF             0x4     /* Value of DRCTR to apply a FIR filter with coefficients a=1, b=0, c=2 */
#define DRCTR_IIR_COEFF             0xF     /* Value of DRCTR to apply a IIR filter with coefficients a=3, b=4      */

#define	FILTERING              0x0
/* Possible values for FIR/IIR filter coefficients:
 * --------------------------------------------------------------------------------------------------------
 * |          Average filter          | * |          FIR filter         | * |         IIR filter          |
 * ------------------------------------ * ------------------------------- * -------------------------------
 * | DMM | DRCTR | Accumulated values | * | DMM | DRCTR | COEFFICIENTS  | * | DMM | DRCTR | COEFFICIENTS  |
 * ------------------------------------ * ------------------------------- * -------------------------------
 * | 0x0 |  0x0  | Disabled           | * | 0x1 |  0x0  | a=2, b=1, c=0 | * | 0x1 |  0xE  | a=2, b=2      |
 * | 0x0 |  0x1  | 2 results average  | * | 0x1 |  0x1  | a=1, b=2, c=0 | * |>0x1 |  0xF  | a=3, b=4      |
 * | 0x0 |  0x2  | 3 results average  | * | 0x1 |  0x2  | a=2, b=0, c=1 | * |     |       |               |
 * |>0x0 |  0x3  | 4 results average  | * | 0x1 |  0x3  | a=1, b=1, c=1 | * |     |       |               |
 * |     |       |                    | * |>0x1 |  0x4  | a=1, b=0, c=2 | * |     |       |               |
 * |     |       |                    | * | 0x1 |  0x5  | a=3, b=1, c=0 | * |     |       |               |
 * |     |       |                    | * | 0x1 |  0x6  | a=2, b=2, c=0 | * |     |       |               |
 * |     |       |                    | * | 0x1 |  0x7  | a=1, b=3, c=0 | * |     |       |               |
 * |     |       |                    | * | 0x1 |  0x8  | a=3, b=0, c=1 | * |     |       |               |
 * |     |       |                    | * | 0x1 |  0x9  | a=2, b=1, c=1 | * |     |       |               |
 * |     |       |                    | * | 0x1 |  0xA  | a=1, b=2, c=1 | * |     |       |               |
 * |     |       |                    | * | 0x1 |  0xB  | a=2, b=0, c=2 | * |     |       |               |
 * |     |       |                    | * | 0x1 |  0xC  | a=1, b=1, c=2 | * |     |       |               |
 * |     |       |                    | * | 0x1 |  0xD  | a=1, b=0, c=3 | * |     |       |               |
 * --------------------------------------------------------------------------------------------------------
 *
 * When selecting different coefficients, make sure to set the correct DIV_FACTOR.
 */
#if(FILTERING)
		g_appVadc_kernel.analogInputs[AppVadc_Ch_I_U].adcChannel.group->module.vadc->G[4].RCR[15].B.DMM = 1;
        g_appVadc_kernel.analogInputs[AppVadc_Ch_I_U].adcChannel.group->module.vadc->G[4].RCR[15].B.DRCTR = 4;//Accumulate 4 result

		g_appVadc_kernel.analogInputs[AppVadc_Ch_I_V].adcChannel.group->module.vadc->G[4].RCR[7].B.DMM = 1;
        g_appVadc_kernel.analogInputs[AppVadc_Ch_I_V].adcChannel.group->module.vadc->G[4].RCR[7].B.DRCTR = 4;//Accumulate 4 result

//        g_appVadc_kernel.analogInputs[AppVadc_Ch_I_W].adcChannel.group->module.vadc->G[4].RCR[6].B.DMM = DMM_RESULT_FILTERING;
//        g_appVadc_kernel.analogInputs[AppVadc_Ch_I_W].adcChannel.group->module.vadc->G[4].RCR[6].B.DRCTR = DRCTR_FIR_COEFF; //Accumulate 4 result


//        g_appVadc_kernel.analogInputs[AppVadc_Ch_V_Vro].adcChannel.group->module.vadc->G[3].RCR[2].B.DMM = DMM_RESULT_FILTERING;
//        g_appVadc_kernel.analogInputs[AppVadc_Ch_V_Vro].adcChannel.group->module.vadc->G[3].RCR[2].B.DRCTR = DRCTR_FIR_COEFF; //Accumulate 4 result
#endif
	}

	// add PWM trigger in the working groups
	{
        /**Refer to UM-P3580,Infineon-TC27x_D-step-UM-v02_02-EN.pdf**/
//        IfxGtm_Trig_toVadc(&MODULE_GTM, IfxGtm_Trig_AdcGroup_3, IfxGtm_Trig_AdcTrig_0, IfxGtm_Trig_AdcTrigSource_tom0,IfxGtm_Trig_AdcTrigChannel_7);
        IfxGtm_Trig_toVadc(&MODULE_GTM, IfxGtm_Trig_AdcGroup_4, IfxGtm_Trig_AdcTrig_0, IfxGtm_Trig_AdcTrigSource_tom0,IfxGtm_Trig_AdcTrigChannel_7);
	}

	// initlize PT1 filter
	{
	    Vadc_LowPass_PT1_Init();
	}

}


float32 AppVadc_limits_float32_Execute(AppVadc_Limits_1_float32* limits, float32 in)
{
    if (in > limits->max)
    {
        limits->status = AppVadc_LimitsStatus_Max;
//        g_motor.control.hadEmergency = TRUE;
        if(limits->onOutOfRange != NULL_PTR)
        {
        	limits->onOutOfRange(limits->object, limits->status,limits->info);
        }
    }
    else if (in < limits->min)
    {
        limits->status = AppVadc_LimitsStatus_Min;
//        g_motor.control.hadEmergency = TRUE;
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
}


float32 AppVadc_updateAnalogInput(AppVadc_AnalogInput_1 *input)
{

	float32 value;
	uint32 rawValue;
	rawValue = IfxVadc_Adc_getResult(&input->adcChannel).B.RESULT;

	// Scale Input
	value = ((float32)input->gain * rawValue + input->offset);
	 /* Check limits */
	value = AppVadc_limits_float32_Execute(&input->limits, value);
	/* Store value */
	input->rawvalue = rawValue;
	input->value = value;
	return value;
}


float32 AppVadc_updateAnalogInput_DRC(AppVadc_AnalogInput_1 *input)
{
	float32 value;
	uint32 rawValue;
//	static float32 alpa = 0.2;

    rawValue = IfxVadc_Adc_getResult(&input->adcChannel).B.RESULT;

	/* Apply filter */
//	rawValue = LowPass_PT1_do(&g_CurrentLowPassPT1_filter, (float)rawValue);
//	FirstOrderRC_LPF(input->new_rawvalue,rawValue,alpa);

	// Scale Input
	value = -((float32)input->gain * rawValue + input->offset);
	 /* Check limits */
	value = AppVadc_limits_float32_Execute(&input->limits, value);

	/* Store value */

	input->rawvalue = rawValue;
	input->value = value;
	return value;
}

#define FACTOR_CURRETNW  (0.63)
void vadc_conversionEndGroup0(void)
{
	__enable();

//	AppVadc_updateAnalogInput(&g_appVadc_kernel.analogInputs[AppVadc_Ch_V_Vro]);

	AppVadc_updateAnalogInput_DRC(&g_appVadc_kernel.analogInputs[AppVadc_Ch_I_U]);
	AppVadc_updateAnalogInput_DRC(&g_appVadc_kernel.analogInputs[AppVadc_Ch_I_V]);
//    AppVadc_updateAnalogInput_DRC(&g_appVadc_kernel.analogInputs[AppVadc_Ch_I_W]);

//    get_PhaseCurrent(&g_motor);

    g_motor.currents.u = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_U].value;//-2
    g_motor.currents.v = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_V].value;//-2
//    g_motor.currents.w = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_W].value;
    g_motor.currents.w = -(g_motor.currents.u + g_motor.currents.v);

    vadc_SamplesToBuffer(&g_motor);

    TorqueControl_startMotor(&g_motor);

	if(IsCurrentSensorCalibrated(&g_motor))
	{
		TorqueControl_FocStep(&g_motor, &g_motor.currents, 0.0);
	}
	else
	{
	    AppMotor_AnalogCurrentInputs* analogIn=&g_motor.analogCurrentInputs;
        ZeroCurrentSensor(&g_motor,analogIn->currentA,analogIn->currentB,analogIn->currentB,analogIn->currentB);

	}

}


float32 currenttable[trace_memory];
float32 currenttable1[trace_memory];
float32 currenttable2[trace_memory];

sint16 angletable[trace_memory];
uint16 duty_cycle0[trace_memory];
//sint16 sensorposition;

#define samples 1 // 1 = 100us
#define K_TRIGGER_POS  (100)
#define   SEND_CURRENT_MSG_ACTUALVALUE    (1)
#define   SEND_CURRENT_MSG_RAWVALUE       (2)
#define   SENG_MSG                        (SEND_CURRENT_MSG_ACTUALVALUE)
void vadc_SamplesToBuffer(AppMotor_Motor* motor)
{
    static uint32 index1= 0, loop;
    static boolean trigger;

    sint16 sensorposition = TorqueControl_updateEncoderPosition();
//    sint16 sensorposition = TorqueControl_updateOpenLoopPosition();

     if(loop < samples)
     {
         loop++;
     }
     else
     {
         if (index1 == 0)
         {
             if (sensorposition < K_TRIGGER_POS &&
                     motor->analogCurrentInputs.currentTableFull == 0 )
             {
               trigger = 1;
             }
         }

         if (trigger)
         {
             if (index1<trace_memory)
             {

 #if( SENG_MSG==SEND_CURRENT_MSG_ACTUALVALUE)
                 currenttable[index1]  = motor->currents.u;
                 currenttable1[index1] = motor->currents.v;
                 currenttable2[index1] = motor->currents.w;
 #elif(SENG_MSG==SEND_CURRENT_MSG_RAWVALUE)
                 currenttable[index1]  =(float32) motor->analogCurrentInputs.currentA->rawvalue;
                 currenttable1[index1] =(float32) motor->analogCurrentInputs.currentB->rawvalue;
                 currenttable2[index1] =(float32) motor->analogCurrentInputs.currentC->rawvalue;
 #endif
                 angletable[index1] = sensorposition;
                 duty_cycle0[index1] = (uint16)motor->inverter.channels[0];
                 index1++;
             }
             else
             {
                 trigger = 0;
                 index1 = 0;
                 motor->analogCurrentInputs.currentTableFull = 1;
             }
         }

         loop = 0;
     }
}

void get_PhaseCurrent(AppMotor_Motor* motor)
{
    switch(motor->inverter.sector)
    {
        case 0:
            g_motor.currents.v = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_V].value;
            g_motor.currents.w = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_W].value;
            g_motor.currents.u = -(g_motor.currents.v + g_motor.currents.w);

            break;

        case 1:
            g_motor.currents.u = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_U].value;
            g_motor.currents.w = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_W].value;
            g_motor.currents.v = -(g_motor.currents.u + g_motor.currents.w);
            break;

        case 2:
            g_motor.currents.u = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_U].value;
            g_motor.currents.w = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_W].value;
            g_motor.currents.v = -(g_motor.currents.u + g_motor.currents.w);
            break;

        case 3:
            g_motor.currents.u = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_U].value;
            g_motor.currents.v = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_V].value;
            g_motor.currents.w = -(g_motor.currents.u + g_motor.currents.v);
            break;

        case 4:
            g_motor.currents.u = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_U].value;
            g_motor.currents.v = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_V].value;
            g_motor.currents.w = -(g_motor.currents.u + g_motor.currents.v);
            break;

        case 5:
            g_motor.currents.v = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_V].value;
            g_motor.currents.w = g_appVadc_kernel.analogInputs[AppVadc_Ch_I_W].value;
            g_motor.currents.u = -(g_motor.currents.v + g_motor.currents.w);
            break;
    }
}
