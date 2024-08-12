/*
 * AppVadc.h
 *
 *  Created on: 04.07.2012
 *
 */

#ifndef APPVADC_H_
#define APPVADC_H_


#include "IfxVadc_Adc.h"
#include "Ifx_Cfg_Vadc.h"

//#define IFX_VADC_G_QBUR_QINR0_QBUR0_RF_OFF   (5)
//#define IFXVADC_QUEUE_REFILL (1 << IFX_VADC_G_QBUR_QINR0_QBUR0_RF_OFF)

/** \\brief  Offset for Ifx_VADC_G_QBUR_QINR0_QBUR0_Bits.EXTR */
#define IFX_VADC_G_QBUR_QINR0_QBUR0_EXTR_OFF (7)
#define IFXVADC_QUEUE_EXT_TRIGGER (1 << IFX_VADC_G_QBUR_QINR0_QBUR0_EXTR_OFF)
#define FirstOrderRC_LPF(Yn_1,Xn,a)  Yn_1 = (1-a)*Yn_1 + a*Xn;   /* low pass RC filtering Yn:out;Xn:in;a:factor */

#define DMM_DATA_REDUCTION          0x0     /* Value of DMM bit field to set Standard Data Reduction Mode           */
#define DMM_RESULT_FILTERING        0x1     /* Value of DMM bit field to set Result Filtering Mode                  */

float32 AppVadc_Limits_float32_Execute(AppVadc_Limits_1_float32* limits, float32 in);


typedef struct
{
	IfxVadc_Adc_Channel		adcChannel;
	uint32 					rawvalue;
	uint32                  new_rawvalue;
	AppVadc_Limits_1_float32   limits;
	float32					gain;
	float32					offset;
    float32               	value;

    uint8                   testcout_current;
}AppVadc_AnalogInput_1;

typedef struct
{
    AppVadc_AnalogInput_1 *currentA;        /**< @brief Analog input Current phase A*/
    AppVadc_AnalogInput_1 *currentB;        /**< @brief Analog input Current phase B*/
    AppVadc_AnalogInput_1 *currentC;        /**< @brief Analog input Current phase C*/
    AppVadc_AnalogInput_1 *vdc;            /**< @brief Analog input DC link voltage*/
}AppMotor_MotorAnalogInputs;

typedef struct
{
    IfxVadc_Adc       module;
    IfxVadc_Adc_Group group[IFXVADC_NUM_ADC_GROUPS];
    AppVadc_AnalogInput_1   analogInputs[AppVadc_ChannelCount];
}AppVadc_Kernel;

extern AppVadc_Kernel g_appVadc_kernel;       /**< @brief analog Inputs Object*/

void Vadc_VIT_init(void);

float32 AppVadc_updateAnalogInput(AppVadc_AnalogInput_1 *input);

IFX_INLINE AppVadc_AnalogInput_1* AppVadc_getCurrentPhaseU_object(void)
{
    return(&(g_appVadc_kernel.analogInputs[AppVadc_Ch_I_U]));

}
IFX_INLINE AppVadc_AnalogInput_1* AppVadc_getCurrentPhaseV_object(void)
{

    return(&(g_appVadc_kernel.analogInputs[AppVadc_Ch_I_V]));
}


IFX_INLINE AppVadc_AnalogInput_1* AppVadc_getCurrentPhaseW_object(void)
{

    return(&(g_appVadc_kernel.analogInputs[AppVadc_Ch_I_W]));
}


IFX_INLINE AppVadc_AnalogInput_1* AppVadc_getCurrentOffset_object(void)
{

    return(&(g_appVadc_kernel.analogInputs[AppVadc_Ch_V_Vro]));
}


IFX_INLINE void AppVadc_setOutOfRangefunction(AppVadc_AnalogInput_1 *input, AppVadc_Limits_onOutOfRange onOutOfRange, void *object)
{
	input->limits.onOutOfRange = onOutOfRange;
	input->limits.object = object;
}


#endif /* APPVADC_H_ */
