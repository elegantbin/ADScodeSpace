/**
 * @file pi.h
 * @brief Proportional integral controller.
 *
 * @license
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
 * @copyright Copyright (C) 2009, 2008 Infineon Technologies AG
 *
 *
 * $Revision: 82 $
 * $Date: 2009-11-04 15:22:26 +0100 (Wed, 04 Nov 2009) $
 *
 * @defgroup control_pi Proportional integral controller
 *
 * This module implements the Proportional integral controller, using the First Order Hold method.
 *  U(k+1)= A1 * I(k+1) + A0 * Ik + Uk
 *  Where:
 *  - A0 = Kp * (wpi * TSample/2 - 1)
 *  - A1 = Ki * (wpi * TSample/2 + 1)
 *  - wpi = Ki / Kp   (rad/s)
 *  - TSample is the sample time in seconds
 *
 * @note: An assembler optimised version is used if the compiler and assembler
 * switch CFG_OPTIMIZE is equal to 1. The files Pi.fixpoint16.opt.asm and
 * Pi.float32.opt.asm must be included in the project.
 *
 * @ingroup library
 */

#if !defined(PI_H)
#define PI_H
//------------------------------------------------------------------------------
#include "../Math/Arith.StdReal.h"
#include "IfxCpu_Intrinsics.h"
//------------------------------------------------------------------------------
/** @brief PI object definition.
 */
typedef struct
{
    StdReal  a0;                           /**< @brief A0 parameter */
    StdReal  a1;                           /**< @brief A1 parameter */
    StdReal  b0;                           /**< @brief A0 parameter */
    StdReal  b1;                           /**< @brief A1 parameter */
    StdRealLong  uk;                       /**< @brief high resolution PI output value */
    StdReal  ik;                           /**< @brief PI last error value */
    StdReal  sk;                           /**< @brief PI anti-saturation value */
    StdReal  c0;                           /**< @brief PI anti-saturation factor */
    StdReal  min;                          /**< @brief PI min limit */
    StdReal  max;                          /**< @brief PI max limit */
    StdReal  delta_uk;                     /**< @brief high resolution PI  delta output value */
#if !defined(CFG_OPTIMIZE) || (CFG_OPTIMIZE == 0)
    uint8 hitLimits;                        /**< @brief PI limit hit flag */
#endif
#if (STD_REAL_TYPE == STD_REAL_FIX_POINT_16) || (STD_REAL_TYPE == STD_REAL_FIX_POINT_32)
    sint8 shiftResult;                       /**< @brief Result shift for TStdReal fixpoint format only */
#endif
} TPic;

void Pic_Init(TPic * pic);
void CurrentPI_Init(TPic * Pic);
void Pic_Reset(TPic * pic);

void Pic_SetKpKi_StdReal(TPic * pic, float32 kp, float32 ki, float32 sampleTime, sint32 shiftCoef, sint8 shiftResult);
void Pic_GetKpKi_StdReal(TPic * pic, float32 *kp, float32 *ki, float32 sampleTime, sint32 shiftCoef);
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
void Pic_SetKpKi(TPic * pic, float32 kp, float32 ki, float32 sampleTime);
void Pic_GetKpKi(TPic * pic, float32 *kp, float32 *ki, float32 sampleTime);
#endif

void Pic_SetLimit(TPic * pic, StdReal min, StdReal max);
void Pic_GetLimit(TPic * pic, StdReal *min, StdReal *max);
StdReal Pic_Do(TPic * pic, StdReal input);
StdReal Current_PI(TPic * pic, StdReal input);
#if !defined(CFG_OPTIMIZE) || (CFG_OPTIMIZE == 0)
boolean Pic_IsLimitsHit(TPic * pic);
void Pic_ResetLimitsHit(TPic * pic);
#else
#define Pic_IsLimitsHit(pic) (FALSE)
#define Pic_ResetLimitsHit(pic) ((void)(0))
#endif

#endif

