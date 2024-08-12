/*
 * DoorSys_AntiPinch.c
 *
 *  Created on: 9.12.2023
 *      Author: Administrator
 */

#include <MotAct.h>
#include "DoorSys.h"
#include "DoorSys_AntiPinch.h"
#include "DualHall.h"
#include "DoorSys_velocity.h"
#include "DoorSys_ApAdapt.h"
#include "DoorSys_ApAdaptCurve.h"

static int8_t ApAdapt_DiffAverage(int16_t i16Sum);
static int8_t ApAdapt_DiffUpdate(int8_t i8AdaptVal, int8_t i8AdaptAverage);
static int8_t ApAdat_Save(const int8_t i8Adapt,int8_t * p_adapt,uint8_t index);

const uint16_t u16ApPosBase = 2100;
int8_t DoorSys_getDiffAdapt(uint16_t u16RtPos,int8_t i8Diff, int8_t* i8AdaptArray )
{
	static int16_t i16AdaptSum = 0;
	int8_t *p_i8ApAdaptCurve = i8AdaptArray;
	int8_t   i8Adapt = 0;
	uint8_t  u8Residual = 0;
	uint16_t Index = 0;


    if(u16RtPos > u16ApPosBase)
    {
    	Index   = u16RtPos - u16ApPosBase;
    	Index   >>= K_ADAPT_SHIFT_POS;
    }

    if(Index < AP_ADAPT_CURVE_LEN)
    {
        i8Adapt = p_i8ApAdaptCurve[Index];
    }
    else
    {
    	Index = 0;
    	i8Adapt = 0;
    }


	i16AdaptSum += i8Diff;
	u8Residual = ((uint16_t)(u16RtPos) & (uint16_t)(K_ADAPT_POS_MASK));/*  each 16 positions*/
	if (u8Residual <= 1)
	{
		int8_t i8AdaptUpdate;
		int8_t i8AdaptAverage = (int8_t)ApAdapt_DiffAverage(i16AdaptSum);

		i16AdaptSum = 0; /* reset sum value  */

		i8AdaptUpdate = ApAdapt_DiffUpdate(i8Adapt, i8AdaptAverage);

		ApAdat_Save(i8AdaptUpdate,p_i8ApAdaptCurve,Index);
	}
    return i8Adapt;
}

static int8_t ApAdapt_DiffAverage(int16_t i16Sum)
{
	int8_t i16RetAdaptAverage = 0;
	i16RetAdaptAverage = (i16Sum>>(K_ADAPT_SHIFT_POS)); /*div 8 for average value  */

	i16RetAdaptAverage =(i16RetAdaptAverage >= (int16_t)K_ADA_AP_MAX)? (int16_t)K_ADA_AP_MAX:i16RetAdaptAverage;
	i16RetAdaptAverage =(i16RetAdaptAverage <= (int16_t)(-K_ADA_AP_MAX))?(int16_t)(-K_ADA_AP_MAX):i16RetAdaptAverage;

	return (int8_t)i16RetAdaptAverage;
}


static int8_t ApAdapt_DiffUpdate(int8_t i8AdaptVal, int8_t i8AdaptAverage)
{
	int8_t i8AdaptAvr, i8RetUpateAdaptDiffVal;

	i8AdaptAvr = i8AdaptAverage;

	i8RetUpateAdaptDiffVal = i8AdaptVal;

	if (i8AdaptAvr > i8RetUpateAdaptDiffVal)
	{
		 i8RetUpateAdaptDiffVal += 5;
	}
	else
	{
		if (i8AdaptAvr < i8RetUpateAdaptDiffVal)
		{
			if (i8RetUpateAdaptDiffVal > 0)
			{
				i8RetUpateAdaptDiffVal -= 5;
			}
		}
	}

	i8RetUpateAdaptDiffVal = (i8RetUpateAdaptDiffVal >= (int8_t)K_ADA_AP_MAX)?(int8_t)K_ADA_AP_MAX:i8RetUpateAdaptDiffVal;
	i8RetUpateAdaptDiffVal = (i8RetUpateAdaptDiffVal <= (int8_t)(-K_ADA_AP_MAX))?(int8_t)(-K_ADA_AP_MAX):i8RetUpateAdaptDiffVal;

	return i8RetUpateAdaptDiffVal;
}


static int8_t ApAdat_Save(const int8_t i8Adapt,int8_t * p_adapt,uint8 index)
{
	int8_t i8Val = (int8_t)i8Adapt;

	p_adapt[index] = i8Val;

    return i8Val;
}

