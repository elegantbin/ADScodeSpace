/*
 * Current.h
 *
 *  Created on: 2023Äê12ÔÂ21ÈÕ
 *      Author: Administrator
 */

#ifndef _1_BSW_COMPONENTS_CURRENT_H_
#define _1_BSW_COMPONENTS_CURRENT_H_


#include "Cpu.h"
typedef struct MotorCurrent
{
	float Current;
	uint16_t Adc_Current_Value;
	uint16_t Adc_Init_Value;
	uint16_t Adc_Value;
	uint16_t Adc_Modification_value;
	uint16_t Adc_Average;
}MotorCurrent_t;

void MotorCurrent_Init(void);

uint16_t  MotorCurrent_Init_Adc_Value(void);
uint16_t MotorCurrent_Adc_Value_Read(void);
uint16_t MotorCurrent_Adc_Average(int mean_value);
float  MotorCurrent_Get(void);



#endif /* _1_BSW_COMPONENTS_CURRENT_H_ */
