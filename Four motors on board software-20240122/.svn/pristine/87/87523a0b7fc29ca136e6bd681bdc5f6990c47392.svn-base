/**
 * \file AppPositionAquisition.c
 *
 *
 * \license
 * You can use this file under the terms of the IFX License.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * IFX License for more details (IFX_License.txt).
 *
 * This file may be used, copied, and distributed, with or without
 * modification, provided that all copyright notices are retained;
 * that all modifications to this file are prominently noted in the
 * modified file; and that this paragraph is not modified.
 *
 * \copyright Copyright (C) 2012 Infineon Technologies AG
 *
 */
//

#include "AppPositionAquisition.h"
#include "MotorDrive/Tables.h"
#include "Ifx_Cfg_FocControl.h"

#define CFG_SPEED_FILTER_CUT_OFF_FREQ       (50.0)                  /**< @brief Cut off frequency of the speed signal in Hz . */

void AppPositionAcquisition_init(PositionAcquisition *sensors, uint8 motorPolPairs)
{
	LowPass_PT1_Config config;
	config.K = 1.0;
	config.T =  (1.0/(2 * PI * CFG_SPEED_FILTER_CUT_OFF_FREQ));

	switch(sensors->mode)
		{
		case PositionAcquisition_Hall:
			//AppPositionHall_init(&sensors->hall);
		break;
		case PositionAcquisition_Encoder:
			PosIf_setupElAngleConst(&sensors->encoder,motorPolPairs);
			sensors->mode = PositionAcquisition_Encoder;
		break;
#if (Resolver == SensorMode)
		case PositionAcquisition_Resolver:
			// Alias of PosIf_updatePosition((PosIf*)&g_App.rdcDsadc);
			PosIf_setupElAngleConst(&sensors->rdcDsadc,motorPolPairs);
			sensors->mode = PositionAcquisition_Resolver;
			PosIf_setupSpeedConst_base(&sensors->rdcDsadc.angleTrk.base);
#endif
		break;
		default: break;
		}

	sensors->statusOk  = TRUE;

	LowPass_PT1_init(&sensors->speedFilter,&config, 1e-3);

}

sint32 AppPositionAcquisition_updatePosition(PositionAcquisition *sensors)
{
	sint32 position = 0;
	switch(sensors->mode)
	{
	case PositionAcquisition_Hall:
		//position = AppPositionHall_updatePosition(&sensors->hall);
	break;
	case PositionAcquisition_Encoder:
		PosIf_updatePosition((PosIf*)&sensors->encoder);
		position = PosIf_getElAngle((PosIf*)&sensors->encoder);
	break;
	case PositionAcquisition_Resolver:
		// Alias of PosIf_updatePosition((PosIf*)&g_App.rdcDsadc);
//		IfxDsadc_Rdc_updateStep2(&sensors->rdcDsadc);
//		position = PosIf_getElAngle((PosIf*)&sensors->rdcDsadc);
	break;
	default: break;
	}
	return(position);
}

float32 AppPositionAcquisition_updateSpeed(PositionAcquisition *sensors)
{
	float32 speed = 0.0;
	switch(sensors->mode)
	{
	case PositionAcquisition_Hall:
		//speed = AppPositionHall_updateSpeed(&sensors->hall);
	break;
	case PositionAcquisition_Encoder:
		speed = PosIf_updateSpeed((PosIf*)&sensors->encoder, TRUE);
	break;
	case PositionAcquisition_Resolver:
	//	speed = PosIf_updateSpeed((PosIf*)&sensors->rdcDsadc, TRUE);
	break;
	default: break;
	}
	speed = LowPass_PT1_do(&sensors->speedFilter, speed);
	return(speed);
}


