/**
 * \file Arith.FixPoint.Tasking.h
 * \brief Fix-point arithmetics library (Tasking compiler)
 *
 * \license
 * You can use this file under the terms of the IFX License.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the IFX License for more details (IFX_License.txt).
 *
 * This file may be used, copied, and distributed, with or without modification, provided
 * that all copyright notices are retained; that all modifications to this file are
 * prominently noted in the modified file; and that this paragraph is not modified.
 *
 * \copyright Copyright (C) 2012 Infineon Technologies AG
 *
 * $Revision: $1554.1
 * $Date: $2013-06-26 20:12:46 GMT
 */

#ifndef ARITH_FIXPOINT_TASKING_H_
#define ARITH_FIXPOINT_TASKING_H_

#include "Convert.asm.h"
#include "StdReal.h"

//------------------------------------------------------------------------------
/** \brief Fix point arithmetics: r = a * b | Q1.15 = (Q1.15 * Q1.15) << 1
 *
 * Perform the operation a * b. The special case (0x8000)*(0x8000) is handled and result as (0x7FFF)
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a * b
 * \note There is no possibility of overflow as the result of 32bits * 32bits is always contained in 64bits which is tacken in accuont.
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint16 __mul_r1Q15_i1Q15_i1Q15(FixPoint16 a, FixPoint16 b)
{
    return a * b;
}


/** \brief Fix point arithmetics: r = floor(a * b) | I16 = (Q1.15 * Q16.0) >> 15
 *
 * Perform the operation a * b. The special case (0x8000)*(0x8000) is handled and result as (0x7FFF)
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter. b must be signed extended to 32 bits
 *
 * \return r = a * b
 * \note There is no possibility of overflow as the result of 32bits * 32bits is always contained in 64bits which is tacken in accuont.
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE sint16 __mul_r16I_i1Q15_i16I(FixPoint16 a, sint16 b)
{
    return (sint16)__mulfractlong(a, b);
}


/** \brief Fix point arithmetics (saturated): r = a + b | Q1.15 = Q1.15 + Q1.15
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a + b
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint16 __adds_r1Q15_i1Q15_i1Q15(FixPoint16 a, FixPoint16 b)
{
    return a + b;
}


/** \brief Fix point arithmetics (saturated): r = a + b | Q1.31 = Q1.31 + Q1.31
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a + b
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint32 __adds_r1Q31_i1Q31_i1Q31(FixPoint32 a, FixPoint32 b)
{
    return a + b;
}


/** \brief Fix point arithmetics (saturated): r = a - b | Q1.15 = Q1.15 - Q1.15
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a - b
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint16 __subs_r1Q15_i1Q15_i1Q15(FixPoint16 a, FixPoint16 b)
{
    return a - b;
}


/** \brief Fix point arithmetics (saturated): r = a * b + c * d | Q1.15 = ((Q1.15 * Q1.15) << 1) + ((Q1.15 * Q1.15) << 1)
 *
 * Perform the operation a * b + c * d. The special case (-1)*(-1) is handled and result as (+1). The result is saturated.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 * \param c Specifies the c parameter
 * \param d Specifies the d parameter
 *
 * \return r = a * b + c * d
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint16 __maddms_r1Q15_i1Q15_i1Q15_i1Q15_i1Q15(FixPoint16 a, FixPoint16 b, FixPoint16 c, FixPoint16 d)
{
    return (a * b) + (c * d);
}


/** \brief Fix point arithmetics (saturated): r = a * b + c * d | Q1.31 = ((Q1.15 * Q1.15) << 1) + ((Q1.15 * Q1.15) << 1)
 *
 * Perform the operation a * b + c * d. The special case (-1)*(-1) is handled and result as (+1). The result is saturated.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 * \param c Specifies the c parameter
 * \param d Specifies the d parameter
 *
 * \return r = a * b + c * d
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint32 __maddms_r1Q31_i1Q15_i1Q15_i1Q15_i1Q15(FixPoint16 a, FixPoint16 b, FixPoint16 c, FixPoint16 d)
{
    return (a * b) + (c * d);
}


/** \brief Fix point arithmetics (saturated): r = a * b - c * d | Q1.15 = ((Q1.15 * Q1.15) << 1) - ((Q1.15 * Q1.15) << 1)
 *
 * Perform the operation a * b - c * d. The special case (-1)*(-1) is handled and result as (+1). The result is saturated.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 * \param c Specifies the c parameter
 * \param d Specifies the d parameter
 *
 * \return r = a * b - c * d
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint16 __msubms_r1Q15_i1Q15_i1Q15_i1Q15_i1Q15(FixPoint16 a, FixPoint16 b, FixPoint16 c, FixPoint16 d)
{
    return (a * b) - (c * d);
}


/** \brief Fix point arithmetics (saturated): r = a + b * c | Q1.15 = Q1.15 + ((Q1.15 * Q1.15) << 1)
 *
 * Perform the operation a + b * c. The special case (-1)*(-1) is handled and result as (+1). The result is saturated.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 * \param c Specifies the c parameter
 *
 * \return r = a + b * c
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint16 __madds_r1Q15_i1Q15_i1Q15_i1Q15(FixPoint16 a, FixPoint16 b, FixPoint16 c)
{
    return a + (b * c);
}


/** \brief Fix point arithmetics (saturated): r = a + b * c | Q1.15 = Q1.15 + ((Q1.15 * Q16.0) << 16)
 *
 * Perform the operation a + b * c. The special case (-1)*(-1) is handled and result as (+1). The result is saturated.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 * \param c Specifies the c parameter
 *
 * \return r = a + b * c
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint16 __madds_r1Q15_i1Q15_i1Q15_i16I(FixPoint16 a, FixPoint16 b, sint16 c)
{
    FixPoint32 Result;                                          // Using a __sfract for the inline assembly result leads to the Result to be cleared by the compiler(Tasking 2.5r2).

    __asm(
        "   mul.q   %2, %2, %3L, #0                         \n" // %2 = b * c
        "   shas    %2, %2, #16                             \n"
        "   adds    %0, %2                                  \n" // %0 = a + b * c
        : "=d" (Result)
        : "0" (a), "d" (b), "d" (c));
    return (FixPoint16)Result;
}


/** \brief Fix point arithmetics (saturated): r = a * b | Q1.15 = ((Q1.15 * Q16.0) << 16)
 *
 * Perform the operation a * b. The special case (-1)*(-1) is handled and result as (+1).
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a * b
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint16 __mul_r1Q15_i1Q15_i16I(FixPoint16 a, sint16 b)
{
    FixPoint32 Result;                                          // Using a __sfract for the inline assembly result leads to the Result to be cleared by the compiler(Tasking 2.5r2).

    __asm(
        "   mul.q   %0,%0, %2L, #0                          \n" // %0 = %0 * b
        "   shas    %0, %0, #16                             \n"
        : "=d" (Result)
        : "0" (a), "d" (b));
    return (FixPoint16)Result;
}


/** \brief Fix point arithmetics (saturated): r = a * 8 | Q1.31 = Q1.31 * Q16.0
 *
 * Perform the operation a * 8.
 *
 * \param a Specifies the a parameter
 *
 * \return r = a * 8
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint32 __muls_8_r1Q31_i1Q31(FixPoint32 a)
{
    FixPoint32 Result;

    __asm(
        "   shas    %0, %0, #3                             \n"
        : "=d" (Result)
        : "0" (a));
    return Result;
}


/** \brief Fix point arithmetics (saturated): r = a * 128 | Q1.31 = Q1.31 * Q16.0
 *
 * Perform the operation a * 128.
 *
 * \param a Specifies the a parameter
 *
 * \return r = a * 128
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint32 __muls_128_r1Q31_i1Q31(FixPoint32 a)
{
    FixPoint32 Result;

    __asm(
        "   shas    %0, %0, #7                             \n"
        : "=d" (Result)
        : "0" (a));
    return Result;
}


/** \brief Fix point arithmetics (saturated): r = a - b * c | Q1.15 = Q1.15 - ((Q1.15 * Q1.15) << 1)
 *
 * Perform the operation a - b * c. The special case (-1)*(-1) is handled and result as (+1). The result is saturated.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 * \param c Specifies the c parameter
 *
 * \return r = a - b * c
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint16 __msubs_r1Q15_i1Q15_i1Q15_i1Q15(FixPoint16 a, FixPoint16 b, FixPoint16 c)
{
    return a - (b * c);
}


/** \brief Fix point arithmetics (saturated): r = a << b | Q1.15 = Q(1-b).(15-b)
 *
 * Perform the operation a << b. The result is saturated.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a << b
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint16 __shas_r1Q15_i1Q15_i8I(FixPoint16 a, sint8 b)
{
    return a << b;
}


/** \brief Fix point arithmetics (saturated): r = a << b | Q1.31 = Q(1-b).(31-b)
 *
 * Perform the operation a << b. The result is saturated.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a << b
 * \ingroup fixpoint_arithmetics
 */
IFX_INLINE FixPoint32 __shas_r1Q31_i1Q31_i8I(FixPoint32 a, sint8 b)
{
    return a << b;
}


IFX_INLINE sint16 Mul_Int16_FixPoint16(sint16 a, FixPoint16 b)
{
    return (sint16)FixPoint32_To_SInt32(SInt32_To_FixPoint32(a, 16) * b, 16);
}


IFX_EXTERN FixPoint16 __negs_r1Q15_i1Q15(FixPoint16 a);
IFX_EXTERN FixPoint16 __abss_r1Q15_i1Q15(FixPoint16 a);
IFX_EXTERN FixPoint32 __abss_r1Q31_i1Q31(FixPoint32 a);
IFX_EXTERN FixPoint32 __div_r1Q31_i1Q31_i32I(FixPoint32 a, sint32 b);
IFX_EXTERN FixPoint32 __div_r16Q16_i1Q15_i1Q15(FixPoint16 a, FixPoint16 b);

#endif /* ARIT_FIXPOINT_TASKING_H_ */
