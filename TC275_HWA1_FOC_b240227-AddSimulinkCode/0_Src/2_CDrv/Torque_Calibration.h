/*
 * Torque_Calibration.h
 *
 *  Created on: 2024Äê1ÔÂ9ÈÕ
 *      Author: Brook.Wu
 */
#include "Cpu/Std/Ifx_Types.h"

#ifndef _SRC_2_CDRV_TORQUE_CALIBRATION_H_
#define _SRC_2_CDRV_TORQUE_CALIBRATION_H_

float32 Torque_calibration(float32 torque_ref);
void Actual_Torque_Calculation(void);
void Current_Iq_Incr(void);

#endif /* 0_SRC_2_CDRV_TORQUE_CALIBRATION_H_ */
