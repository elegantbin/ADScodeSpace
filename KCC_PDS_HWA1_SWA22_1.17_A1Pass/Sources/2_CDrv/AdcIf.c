/*
 * AdIf.c
 *
 *   Created on: 7.12.2023
 *      Author: Administrator
 */

#include <AdcIf.h>
#define ADC_VREFH       3.3f
#define ADC_VREFL       0.0f

/*  ADC_Current*/
float Current;
uint16_t adcRawValue;
uint16_t adcMax = (uint16_t) (1 << 8);

/*************************************************************************
  *FUNCTION NAME:			BSW_Drive_Current_Init
  *FUNCTION DESCRIPTION:		Drive_Current_Init
  *PAPRAMETER:		void
  *RETURN VALUE:		void	VALUENAME:void
  *EDITOR:			ReaveGan
  *DATE:				2023.12.07
  *VERSION:			1.0
  *************************************************************************/
void AdcIf_Init(void)
{
	ADC_DRV_ConfigConverter(INST_DRIVEMADCONV1, &DriveMadConv1_ConvConfig0);
	ADC_DRV_ConfigConverter(INST_DRIVEMADCONV1, &ExSwtichConv1_ConvConfig1);
	ADC_DRV_AutoCalibration(INST_DRIVEMADCONV1);

}

/*************************************************************************
  *FUNCTION NAME:			BSW_Drive_Current_Read
  *FUNCTION DESCRIPTION:		BSW_Drive_Current_Read
  *PAPRAMETER:		void
  *RETURN VALUE:		float	VALUENAME:Current
  *EDITOR:			ReaveGan
  *DATE:				2023.12.07
  *VERSION:			1.0
  *************************************************************************/
float AdcIf_readCurrent(void)
{
	ADC_DRV_ConfigChan(INST_DRIVEMADCONV1, 0U, &DriveMadConv1_ChnConfig0);
	ADC_DRV_WaitConvDone(INST_DRIVEMADCONV1);
	ADC_DRV_GetChanResult(INST_DRIVEMADCONV1,0U,&adcRawValue);
    Current = ((float) adcRawValue / adcMax) * (ADC_VREFH - ADC_VREFL);

    return Current;
}
