/**
 * @file pi.c
 * @brief Proportional integral controller.
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
 * $Revision: 102 $
 * $Date: 2010-06-19 22:41:43 +0200 (Sat, 19 Jun 2010) $
 *
 */

//------------------------------------------------------------------------------
#include <Pi.h>

//------------------------------------------------------------------------------
/** @brief Initialize the PI controller.
 *
 * This function initializes the PI controller. It must be called before any call to other PI functions.
 *
 * @param Pic Specifies PI controller.
 *
 * @return none

 * @see Pic_SetKpKi(), Pic_SetKpKi_StdReal(), Pic_SetLimit()
 * @ingroup control_pi
 */
void Pic_Init(TPic * Pic)
{
    Pic->a0 = 0;
    Pic->a1 = 0;
    Pic->ik = 0;
    Pic->uk = 0;
    Pic->min = 0;
    Pic->max = 0;
#if !defined(CFG_OPTIMIZE) || (CFG_OPTIMIZE == 0)
    Pic->hitLimits = FALSE;
#endif
}

/** @brief Set the PI controller Kp and Ki parameter (for fixpoint calculation).
 *
 * This function sets the PI controller Kp and Ki parameter. The A0 and A1 coeficient
 * are converted to fix point values (Qx.y format where x = Shift+1) using the Shift parameter, taking in account the
 * saturation.
 *
 * @param Pic Specifies PI controller.
 * @param Kp Specifies the PI controller Kp value.
 * @param Ki Specifies the PI controller Ki value.
 * @param SampleTime Specifies PI controller sampling time in seconds.
 * @param ShiftCoef position of the fix point for the A0 and A1 parameters. Range = [-256, 255]. In case TStdReal type is float32, this parameter is ignored
 * @param ShiftResult Shift done on the result for fixpoint calculation. Range = [-32, 31]. In case TStdReal type is float32, this parameter is ignored
 *
 * @return none
 * @see Pic_GetKpKi(), Pic_GetKpKi_StdReal(), float32_To_FixPoint32()
 * @ingroup control_pi
 */
void Pic_SetKpKi_StdReal(TPic * pic, float32 kp, float32 ki, float32 sampleTime, sint32 shiftCoef, sint8 shiftResult)
{
    if ((kp < 0) || (kp > 0))
    {
        float32 k = (ki / kp) * (sampleTime / 2);
        pic->a0 = FLOAT32_TO_STD_REAL(kp * (k - 1), shiftCoef);  /* Kp.(Wpi.Tsample/2 - 1); Wpi = Ki/Kp  */
        pic->a1 = FLOAT32_TO_STD_REAL(kp * (k + 1), shiftCoef);  /* Kp.(Wpi.Tsample/2 + 1); Wpi = Ki/Kp  */
#if (STD_REAL_TYPE == STD_REAL_FIX_POINT_16) || (STD_REAL_TYPE == STD_REAL_FIX_POINT_32)
        pic->shiftResult = shiftResult;
#endif
    }
    else
    {
        pic->a0 = 0;
        pic->a1 = 0;
#if (STD_REAL_TYPE == STD_REAL_FIX_POINT_16) || (STD_REAL_TYPE == STD_REAL_FIX_POINT_32)
        pic->shiftResult = 0;
#endif
    }
}

/** @brief Return the PI controller Kp and Ki parameter.
 *
 * This function returns the PI controller Kp and Ki parameter. The A0 and A1 coeficient
 * are converted to floating point values using the Shift parameter  (Qx.y format where x = Shift+1).
 *
 * @param Pic Specifies PI controller.
 * @param Kp This parameter is filled in by the function with the PI controller Kp value.
 * @param Ki This parameter is filled in by the function with the PI controller Ki value.
 * @param SampleTime Specifies PI controller sampling time in seconds.
 * @param ShiftCoef position of the fix point. Range = [-256, 255]. In case TStdReal type is float32, this parameter is ignored
 *
 * @return none
 * @see Pic_SetKpKi(), Pic_SetKpKi_StdReal(), FixPoint32_To_float32()
 * @ingroup control_pi
 */
void Pic_GetKpKi_StdReal(TPic * pic, float32 *kp, float32 *ki, float32 sampleTime, sint32 shiftCoef)
{
    *ki = (STD_REAL_TO_FLOAT32(pic->a1, shiftCoef) + STD_REAL_TO_FLOAT32(pic->a0, shiftCoef)) / sampleTime;
    *kp = (STD_REAL_TO_FLOAT32(pic->a1, shiftCoef) - STD_REAL_TO_FLOAT32(pic->a0, shiftCoef)) / 2;
}

#if STD_REAL_TYPE == STD_REAL_FLOAT_32
/** @brief Set the PI controller Kp and Ki parameter (for TStdReal as float32 only).
 *
 * This function sets the PI controller Kp and Ki parameter.
 *
 * @param Pic Specifies PI controller.
 * @param Kp Specifies the PI controller Kp value.
 * @param Ki Specifies the PI controller Ki value.
 * @param SampleTime Specifies PI controller sampling time in seconds.
 *
 * @return none
 * @see Pic_GetKpKi(), Pic_GetKpKi_StdReal()
 * @ingroup control_pi
 */
void Pic_SetKpKi(TPic * pic, float32 kp, float32 ki, float32 sampleTime)
{
    Pic_SetKpKi_StdReal(pic, kp, ki, sampleTime, 0, 0);
}

/** @brief Return the PI controller Kp and Ki parameter (for TStdReal as float32 only).
 *
 * This function returns the PI controller Kp and Ki parameter.
 *
 * @param Pic Specifies PI controller.
 * @param Kp This parameter is filled in by the function with the PI controller Kp value.
 * @param Ki This parameter is filled in by the function with the PI controller Ki value.
 * @param SampleTime Specifies PI controller sampling time in seconds.
 *
 * @return none
 * @see Pic_SetKpKi(), Pic_SetKpKi_StdReal(), Pic_GetKpKi_StdReal()
 * @ingroup control_pi
 */
void Pic_GetKpKi(TPic * pic, float32 *kp, float32 *ki, float32 sampleTime)
{
    Pic_GetKpKi_StdReal(pic, kp, ki, sampleTime, 0);
}
#endif


/** @brief Set the PI controller limits.
 *
 * This function sets the PI controller limits.
 *
 * @param Pic Specifies PI controller.
 * @param Min Specifies the PI controller min value.
 * @param Max Specifies the PI controller max value.
 *
 * @return none
 * @see Pic_GetLimit()
 * @ingroup control_pi
 */
void Pic_SetLimit(TPic * pic, StdReal min,StdReal max)
{
    pic->min = min;
    pic->max = max;
#if !defined(CFG_OPTIMIZE) || (CFG_OPTIMIZE == 0)
    pic->hitLimits = FALSE;
#endif
}

/** @brief Return the PI controller limits.
 *
 * This function returns the PI controller limits.
 *
 * @param Pic Specifies PI controller.
 * @param Min This parameter is filled in by the function with the PI controller min value.
 * @param Max This parameter is filled in by the function with the PI controller max value.
 *
 * @return none
 * @ingroup control_pi
 */
void Pic_GetLimit(TPic * pic, StdReal *min, StdReal *max)
{
    *min = pic->min;
    *max = pic->max;
}


#if !defined(CFG_OPTIMIZE) || (CFG_OPTIMIZE == 0)
/** @brief Test if the PI controller limits have been hit.
 *
 * This function returns TRUE if the PI controller limits have been hit.
 *
 * @param Pic Specifies PI controller.
 *
 * @retval TRUE if the PI controller limits have been hit.
 * @retval FALSE if the PI controller limits have not been hit.
 * @see Pic_SetLimit()
 * @ingroup control_pi
 */
boolean Pic_IsLimitsHit(TPic * pic)
{
    return pic->hitLimits;
}
/** @brief Resets the PI controller limits hit flag.
 *
 * This function resets the PI controller limits hit flag.
 *
 * @param Pic Specifies PI controller.
 *
 * @return None.
 * @see Pic_IsLimitsHit()
 * @ingroup control_pi
 */
void Pic_ResetLimitsHit(TPic * pic)
{
    pic->hitLimits = FALSE;
}

#endif

#if !defined(CFG_OPTIMIZE) || (CFG_OPTIMIZE == 0)
/** @brief Update the PI controller with the new error value.
 *
 * This function updates the PI controller and return the new PI output according to the following formula:
 *  U(k+1)= A1 * I(k+1) + A0 * Ik + Uk
 *
 * In case Fix point calculation is used, the following formula is applyed (saturated shift)
 *  U(k+1)= ((A1 * I(k+1) + A0 * Ik) << ShiftResult) + Uk
 *
 * @param Pic Specifies PI controller.
 * @param Input Specifies the new input error value.
 *
 * @return Returns the new PI output value.
 * @ingroup control_pi
 */
StdReal Pic_Do(TPic * pic, StdReal input)
{
    StdRealLong uk;
//    Uk = A1 * Input + Uk + A0 * Pic->Ik;
#if (STD_REAL_TYPE == STD_REAL_FIX_POINT_16) || (STD_REAL_TYPE == STD_REAL_FIX_POINT_32)
    uk = __adds_rLSR_iLSR_iLSR(__scale_rLSR_iLSR_i8I(__maddms_rLSR_iSR_iSR_iSR_iSR(pic->a1, Input, pic->a0, pic->ik), pic->shiftResult), pic->uk);
#else
    uk = __adds_rLSR_iLSR_iLSR(__maddms_rLSR_iSR_iSR_iSR_iSR(pic->a1, input, pic->a0, pic->ik), pic->uk);
#endif

    pic->ik = input;

    if (uk >= pic->max)
    {
        pic->hitLimits = TRUE;
        pic->uk = pic->max;
    }
    else if (uk <= pic->min)
    {
        pic->hitLimits = TRUE;
        pic->uk = pic->min;
    }
    else
    {
        pic->uk = uk;
    }
    return (StdReal)pic->uk;
}
#endif

/** @brief Reset the PI controller.
 *
 * This function resets the PI controller by setting the Last error and integral part to 0.
 *
 * @param Pic Specifies PI controller.
 *
 * @return none
 * @ingroup control_pi
 */
void Pic_Reset(TPic * pic)
{
    pic->ik = 0;
    pic->uk = 0;
}
