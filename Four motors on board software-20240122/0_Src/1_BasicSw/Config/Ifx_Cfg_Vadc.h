/*
 * Ifx_Cfg_Vadc.h
 *
 *  Created on: 27.08.2013
 *
 */

#ifndef IFX_CFG_VADC_H_
#define IFX_CFG_VADC_H_

#include "AppVadc.h"


	typedef enum
		{
			AppVadc_Ch_I_U,
			AppVadc_Ch_V_Vro,
			AppVadc_Ch_I_V,
			AppVadc_ChannelCount
		}AppVadc_Channels;

IFX_EXTERN const IfxVadc_Adc_Config IfxVadc_adc_module_config;
IFX_EXTERN const IfxVadc_Adc_GroupConfig IfxVadc_adc_group_config[IFXVADC_NUM_ADC_GROUPS];
IFX_EXTERN const AppVadc_AnalogInput_cfg IfxVadc_cfg_adc_channel[AppVadc_ChannelCount];

#define 	APPVADC_CFG_VMOTOR_MIN	(2.3)
#define 	APPVADC_CFG_VMOTOR_MAX	(2.7)
#define 	APPVADC_CFG_VMOTOR_GAIN	0.00122070
#define 	APPVADC_CFG_VMOTOR_OFFSET	0.0
#define		APPVADC_CFG_VMOTOR_OFFSET_NOM  (2048)
#define		CFG_AN_I_CALIBRATION_COUNT 	(512)

#define 	APPVADC_CFG_IMOTOR_MIN	(-70.0)
#define 	APPVADC_CFG_IMOTOR_MAX	(70.0)

#define 	APPVADC_CFG_IMOTOR_GAIN	(-(5.0/(4096 * 32 * 0.01)))
#define 	APPVADC_CFG_IMOTOR_OFFSET	(2.5 / (32 * 0.01))


#endif /* IFX_CFG_VADC_H_ */
