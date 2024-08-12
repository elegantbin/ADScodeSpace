/*
 * MotCurrent.c
 *
 *  Created on: 2023Äê12ÔÂ21ÈÕ
 *      Author: Administrator
 */

#include "Current.h"

#define ADC_VREFH  (5)
#define ADC_VREFL  (0)
#define CURRENT_CREST (400)
#define  GAIN (20)
uint16_t AdcMax = (uint16_t)(1<<12);

const float VIO = 0.005f;
const float RESISTOR = 0.005f;

MotorCurrent_t MotorCurrent;
MotorCurrent_t *g_MotorCurrent=&MotorCurrent;



uint16_t  MotorCurrent_Init_Adc_Value(void)
{

	MotorCurrent_t *g_MotorCurrent=&MotorCurrent;

	ADC_DRV_ConfigChan(INST_DRIVEMADCONV1, 0U, &DriveMadConv1_ChnConfig0);
	ADC_DRV_WaitConvDone(INST_DRIVEMADCONV1);
	ADC_DRV_GetChanResult(INST_DRIVEMADCONV1,0U,&(g_MotorCurrent->Adc_Init_Value));
	return g_MotorCurrent->Adc_Init_Value;

}


void MotorCurrent_Init(void)
{
	ADC_DRV_ConfigConverter(INST_DRIVEMADCONV1, &DriveMadConv1_ConvConfig0);
	ADC_DRV_AutoCalibration(INST_DRIVEMADCONV1);

	MotorCurrent_Init_Adc_Value();

}




uint16_t MotorCurrent_Adc_Value_Read(void)
{
	MotorCurrent_t *g_MotorCurrent=&MotorCurrent;


	ADC_DRV_ConfigChan(INST_DRIVEMADCONV1, 0U, &DriveMadConv1_ChnConfig0);
	ADC_DRV_WaitConvDone(INST_DRIVEMADCONV1);
	ADC_DRV_GetChanResult(INST_DRIVEMADCONV1,0U,&(g_MotorCurrent->Adc_Value));
	if(g_MotorCurrent->Adc_Value>CURRENT_CREST)
	{g_MotorCurrent->Adc_Value=0;}
	g_MotorCurrent->Adc_Modification_value = g_MotorCurrent->Adc_Value - g_MotorCurrent->Adc_Init_Value;

	return g_MotorCurrent->Adc_Modification_value;
}


uint16_t MotorCurrent_Adc_Average(int mean_value)
{
	MotorCurrent_Adc_Value_Read();

	MotorCurrent_t *g_MotorCurrent = &MotorCurrent;
    static uint8_t Cnt = 0;
    static uint32_t Sum = 0;
    static uint16_t Ave = 0;
    if(Cnt<mean_value)
    {

    	Sum += MotorCurrent_Adc_Value_Read();
    	Cnt++;
    }
    if(Cnt>=mean_value)
    {
    	Ave = Sum/mean_value;
    	g_MotorCurrent->Adc_Average = Ave;
    	Cnt = 0;
    	Sum = 0;
    }

    return Ave;

}

float  MotorCurrent_Get(void)
{
	MotorCurrent_t *g_MotorCurrent = &MotorCurrent;
	float Voltage = 0;
	Voltage = ((float)g_MotorCurrent->Adc_Average/AdcMax) *(ADC_VREFH-ADC_VREFL);
	g_MotorCurrent->Current = (Voltage-(GAIN*VIO))/(GAIN*RESISTOR);
	return  g_MotorCurrent->Current;

}



