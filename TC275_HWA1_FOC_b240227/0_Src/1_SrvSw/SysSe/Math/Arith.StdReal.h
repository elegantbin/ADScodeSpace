/**
 * \file Arith.StdReal.h
 * \brief StdReal arithmetic library
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
 * \copyright Copyright (C) 2011 - 2008 Infineon Technologies AG
 *
 *
 * $Revision: $1554.1
 * $Date: $2013-06-26 20:12:46 GMT
 *
 * \defgroup stdreal_type StdReal arithmetic
 * The StdReal arithmetic have been introduced to easy the switch between fix point 16 bit,
 * fix point 32 bit and floating point arithmetics. Note that scaling operation
 * like __shas_rSR_iSR_i8I leads to identity operation (result = input) for when
 * floating point is used, where as when fixpoint is used, this operation scales
 * the input to fit the data range.
 * \ingroup mod_cpu_arithmetics
 *
 */

#ifndef ARITH_STDREAL_H_
#define ARITH_STDREAL_H_

#include "Arith.FixPoint.h"
#include "Arith.Float.h"

#define PI                 (3.1415926535897932384626433832795)
#define TwoOverPi          (2.0 / PI)
#define OneOverSqrt3       (0.57735026918962576450914878050196)
#define Sqrt2              (1.4142135623730950488016887242097)

#if STD_REAL_TYPE == STD_REAL_FIX_POINT_16
#   define FLOAT32_TO_STD_REAL(value, shift) ((FixPoint16)Float32_To_FixPoint32(value, shift))
#   define STD_REAL_TO_FLOAT32(value, shift) (FixPoint32_To_Float32(value, shift))

#   define OneOverSqrt3_SR ((FixPoint16)(OneOverSqrt3))                             // Q1.15 format
#   define TwoOverPi_SR    ((FixPoint16)TwoOverPi)                                  // Q1.15 format

#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_32
#   define FLOAT32_TO_STD_REAL(value, shift) (Float32_To_FixPoint32(value, shift))
#   define STD_REAL_TO_FLOAT32(value, shift) (FixPoint32_To_Float32(value, shift))

#   define OneOverSqrt3_SR ((FixPoint32)(OneOverSqrt3))
#   define TwoOverPi_SR    ((FixPoint32)TwoOverPi)

#elif STD_REAL_TYPE == STD_REAL_FLOAT_32

#   define FLOAT32_TO_STD_REAL(value, shift) (value)
#   define STD_REAL_TO_FLOAT32(value, shift) (value)

#   define OneOverSqrt3_SR OneOverSqrt3
#   define TwoOverPi_SR    TwoOverPi
#endif

/** \brief StdReal arithmetics (saturated): r = a << b
 * \ingroup stdreal_type
 */
IFX_INLINE StdRealLong __scale_rLSR_iLSR_i8I(StdRealLong value, uint8 shift)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    (void)shift; /* ignore compiler warning */
    return value;
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __shas_r1Q31_i1Q31_i8I(value, shift);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = floor(a * b)
 * \ingroup stdreal_type
 */
IFX_INLINE sint16 __mul_r16I_iSR_i16I(StdReal a, sint16 b)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __mul_r16I_iF_i16I(a, b);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __mul_r16I_i1Q15_i16I(a, b);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a * b
 * \ingroup stdreal_type
 */
IFX_INLINE StdReal __mul_rSR_iSR_i16I(StdReal a, sint16 b)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __mul_rF_iF_i16I(a, b);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __mul_r1Q15_i1Q15_i16I(a, b);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a * b - c * d
 * \ingroup stdreal_type
 */
IFX_INLINE StdReal __msubms_rSR_iSR_iSR_iSR_iSR(StdReal a, StdReal b, StdReal c, StdReal d)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __msubms_rF_iF_iF_iF_iF(a, b, c, d);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __msubms_r1Q15_i1Q15_i1Q15_i1Q15_i1Q15(a, b, c, d);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a + b * c
 * \ingroup stdreal_type
 */
IFX_INLINE StdReal __madds_rSR_iSR_iSR_i16I(StdReal a, StdReal b, sint16 c)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __madds_rF_iF_iF_i16I(a, b, c);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __madds_r1Q15_i1Q15_i1Q15_i16I(a, b, c);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a * b
 * \ingroup stdreal_type
 */
IFX_INLINE StdReal __mul_rSR_iSR_iSR(StdReal a, StdReal b)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __mul_rF_iF_iF(a, b);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __mul_r1Q15_i1Q15_i1Q15(a, b);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a * 8
 * \ingroup stdreal_type
 */
IFX_INLINE StdRealLong __muls_8_rLSR_iLSR(StdRealLong a)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __muls_8_rF_iF(a);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __muls_8_r1Q31_i1Q31(a);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a * 128
 * \ingroup stdreal_type
 */
IFX_INLINE StdRealLong __muls_128_rLSR_iLSR(StdRealLong a)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __muls_128_rF_iF(a);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __muls_128_r1Q31_i1Q31(a);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a - b
 * \ingroup stdreal_type
 */
IFX_INLINE StdReal __subs_rSR_iSR_iSR(StdReal a, StdReal b)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __subs_rF_iF_iF(a, b);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __subs_r1Q15_i1Q15_i1Q15(a, b);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a * b + c * d
 * \ingroup stdreal_type
 */
IFX_INLINE StdReal __maddms_rSR_iSR_iSR_iSR_iSR(StdReal a, StdReal b, StdReal c, StdReal d)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __maddms_rF_iF_iF_iF_iF(a, b, c, d);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __maddms_r1Q15_i1Q15_i1Q15_i1Q15_i1Q15(a, b, c, d);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a * b + c * d
 * \ingroup stdreal_type
 */
IFX_INLINE StdRealLong __maddms_rLSR_iSR_iSR_iSR_iSR(StdReal a, StdReal b, StdReal c, StdReal d)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __maddms_rF_iF_iF_iF_iF(a, b, c, d);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __maddms_r1Q31_i1Q15_i1Q15_i1Q15_i1Q15(a, b, c, d);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a + b
 * \ingroup stdreal_type
 */
IFX_INLINE StdReal __adds_rSR_iSR_iSR(StdReal a, StdReal b)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __adds_rF_iF_iF(a, b);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __adds_r1Q15_i1Q15_i1Q15(a, b);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a + b
 * \ingroup stdreal_type
 */
IFX_INLINE StdRealLong __adds_rLSR_iLSR_iLSR(StdRealLong a, StdRealLong b)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __adds_rF_iF_iF(a, b);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __adds_r1Q31_i1Q31_i1Q31(a, b);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a * 2^b
 * \ingroup stdreal_type
 */
IFX_INLINE StdReal __shas_rSR_iSR_i8I(StdReal a, sint8 b)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __shas_rF_iF_i8I(a, b);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __shas_r1Q15_i1Q15_i8I(a, b);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = a * 2^b
 * \ingroup stdreal_type
 */
IFX_INLINE StdRealLong __shas_rLSR_iLSR_i8I(StdRealLong a, sint8 b)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __shas_rF_iF_i8I(a, b);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __shas_r1Q31_i1Q31_i8I(a, b);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = -a
 * \ingroup stdreal_type
 */
IFX_INLINE StdReal __negs_rSR_iSR(StdReal a)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __negs_rF_iF(a);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __negs_r1Q15_i1Q15(a);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = abs(a)
 * \ingroup stdreal_type
 */
IFX_INLINE StdReal __abss_rSR_iSR(StdReal a)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __abs_rF_iF(a);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __abss_r1Q15_i1Q15(a);
#else
#endif
}


/** \brief StdReal arithmetics (saturated): r = abs(a)
 * \ingroup stdreal_type
 */
IFX_INLINE StdRealLong __abss_rLSR_iLSR(StdRealLong a)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __abs_rF_iF(a);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __abss_r1Q31_i1Q31(a);
#else
#endif
}


/** \brief StdReal arithmetics: r = a / b
 * \ingroup stdreal_type
 */
IFX_INLINE StdRealLong __div_rLSR_iSR_i32I(StdReal a, sint32 b)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __div_rF_iF_i32I(a, b);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __div_r1Q31_i1Q31_i32I(a, b);
#else
#endif
}


/** \brief StdReal arithmetics: r = a / b
 * \ingroup stdreal_type
 */
IFX_INLINE StdRealLong __div_rLSR_iSR_iSR(StdReal a, StdReal b)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    return __div_rF_iF_iF(a, b);
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return __div_r16Q16_i1Q15_i1Q15(a, b);
#else
#endif
}


/** \brief StdReal arithmetics: r = floor(a);
 * \ingroup stdreal_type
 */
IFX_INLINE sint32 __floors_r32I_iLSR(StdRealLong value, uint8 shift)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    //return (Float32_To_SInt32(value*2)>>1) /* data range divided by 2 */
    (void)shift;                    /* ignore compiler warning */
    return (sint32)floorf(value);   /* Full data range */
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_16
    return FixPoint32_To_SInt32(value, shift);
#else
#endif
}


#endif /* ARITH_STDREAL_H_ */
