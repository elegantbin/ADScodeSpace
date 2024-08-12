/*
 * Ifx_Cfg_Vadc.h
 *
 *  Created on: 27.08.2013
 *
 */

#ifndef IFX_CFG_VADC_H_
#define IFX_CFG_VADC_H_
#include "IfxVadc_adc.h"
#include "Ifx_Cfg_Vadc.h"
#include "IfxVadc_cfg.h"

typedef enum
{
    AppVadc_Ch_I_U,
    AppVadc_Ch_V_Vro,
    AppVadc_Ch_I_V,
    AppVadc_Ch_I_W,
    AppVadc_ChannelCount
}AppVadc_Channels;

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

typedef struct
{
    IfxVadc_RequestSource   requestSource;
    uint16                  priority;               // for request source queued [range 1..8] 1 means first in the queue 8 last in queue
    boolean                 refill;                 // for request source queued refill in queue
    boolean                 trigger;                // for request source queued seperate trigger for channel
}AppVadc_Conversion_cfg;

typedef struct
{
    IfxVadc_GroupId             groupId;
    IfxVadc_Adc_ChannelConfig   hwChannel;
    AppVadc_Conversion_cfg      coversionSetup;
    AppVadc_Limits_1_float32    limits;
    float32                     gain;
    float32                     offset;
}AppVadc_AnalogInput_cfg;

IFX_EXTERN IfxVadc_Adc_Config IfxVadc_adc_module_config;
IFX_EXTERN IfxVadc_Adc_GroupConfig IfxVadc_adc_group_config[IFXVADC_NUM_ADC_GROUPS];
IFX_EXTERN AppVadc_AnalogInput_cfg IfxVadc_cfg_adc_channel[AppVadc_ChannelCount];

#define 	APPVADC_CFG_VMOTOR_MIN	(38)
#define 	APPVADC_CFG_VMOTOR_MAX	(58)
#define 	APPVADC_CFG_VMOTOR_GAIN	0.00122070
#define 	APPVADC_CFG_VMOTOR_OFFSET	0.0
#define		APPVADC_CFG_VMOTOR_OFFSET_NOM  (2048)
#define		CFG_AN_I_CALIBRATION_COUNT 	(512)

#define 	APPVADC_CFG_IMOTOR_MIN	(-180.0)
#define 	APPVADC_CFG_IMOTOR_MAX	(180.0)

#define VADC_MAX            4096            /* Maximum value (conversion results are expressed in 12-bit format)    */
#define VADC_MIN            0               /* Minimum value of a conversion result                                 */
#define VAREF_VOLTAGE       5.0             /* Maximum voltage measurable by the VADC                               */
#define VOLT_CONVERSION     VAREF_VOLTAGE / VADC_MAX  /* Conversion factor from ADC value to voltage (V)            */
#define VOLT_GAIN           30.0         //(30.0)     /*Current or Voltage amplification*/
#define RESISTANCE_VALUE    4000            /*The reciprocal of the sampled resistance value @1/R*/

#define     AD_VALUE_OFFSET             (2064)
#define     APPVADC_CFG_IMOTOR_GAIN_U     (VOLT_CONVERSION*RESISTANCE_VALUE/VOLT_GAIN)//motor6 is 1 ,motor 16 is 0.914   // 0.8742
#define     APPVADC_CFG_IMOTOR_GAIN_V     (VOLT_CONVERSION*RESISTANCE_VALUE/VOLT_GAIN*0.78)//motor6 is 0.78 OR 0.65,motor 16 is 0.943//0.78
#define     APPVADC_CFG_IMOTOR_GAIN_W     (VOLT_CONVERSION*RESISTANCE_VALUE/VOLT_GAIN)

#define     APPVADC_CFG_IMOTOR_OFFSET_U   (-AD_VALUE_OFFSET*VOLT_CONVERSION*RESISTANCE_VALUE/VOLT_GAIN)  //-335.93664
#define     APPVADC_CFG_IMOTOR_OFFSET_V   (-AD_VALUE_OFFSET*VOLT_CONVERSION*RESISTANCE_VALUE/VOLT_GAIN)
#define     APPVADC_CFG_IMOTOR_OFFSET_W   (-AD_VALUE_OFFSET*VOLT_CONVERSION*RESISTANCE_VALUE/VOLT_GAIN)
#endif /* IFX_CFG_VADC_H_ */
