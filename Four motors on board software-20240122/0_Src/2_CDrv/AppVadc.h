/*
 * AppVadc.h
 *
 *  Created on: 04.07.2012
 *
 */

#ifndef APPVADC_H_
#define APPVADC_H_


#include "Vadc/Adc/IfxVadc_Adc.h"



//---------------------------------------------------------------------------
typedef enum
{
	AppVadc_LimitsStatus_Ok,
	AppVadc_LimitsStatus_Min,
	AppVadc_LimitsStatus_Max,
	AppVadc_LimitsStatus_OutOfRange
}AppVadc_LimitsStatus;


typedef void (*AppVadc_Limits_onOutOfRange)(void *object, AppVadc_LimitsStatus status, uint32 info);

typedef struct
{
    float32 min;
    float32 max;
    AppVadc_LimitsStatus status;
    AppVadc_Limits_onOutOfRange onOutOfRange;
    void* object;
    uint32 info;
} AppVadc_Limits_1_float32;

float32 AppVadc_Limits_float32_Execute(AppVadc_Limits_1_float32* limits, float32 in);

//---------------------------------------------------------------------------

typedef struct
{
	IfxVadc_RequestSource	requestSource;
	uint16					priority;				// for request source queued [range 1..8] 1 means first in the queue 8 last in queue
	boolean					refill;					// for request source queued refill in queue
	boolean					trigger;				// for request source queued seperate trigger for channel
}AppVadc_Conversion_cfg;

typedef struct
{
	IfxVadc_GroupId 			groupId;
	IfxVadc_Adc_ChannelConfig 	hwChannel;
	AppVadc_Conversion_cfg		coversionSetup;
	AppVadc_Limits_1_float32	limits;
	float32						gain;
	float32						offset;
}AppVadc_AnalogInput_cfg;


typedef struct
{
	IfxVadc_Adc_Channel		input;
	uint32 					rawvalue;
	AppVadc_Limits_1_float32   limits;
	float32					gain;
	float32					offset;
    float32               	value;
}AppVadc_AnalogInput_1;


void AppVadc_init(void);
float32 AppVadc_updateAnalogInput(AppVadc_AnalogInput_1 *input);
AppVadc_AnalogInput_1* AppVadc_getCurrentPhaseU_object(void);
AppVadc_AnalogInput_1* AppVadc_getCurrentPhaseV_object(void);
AppVadc_AnalogInput_1* AppVadc_getCurrentOffset_object(void);


IFX_INLINE void AppVadc_setOutOfRangefunction(AppVadc_AnalogInput_1 *input, AppVadc_Limits_onOutOfRange onOutOfRange, void *object)
{
	input->limits.onOutOfRange = onOutOfRange;
	input->limits.object = object;
}


#endif /* APPVADC_H_ */
