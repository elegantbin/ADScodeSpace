/**
 * \file Arith.FixPoint.Tasking.c
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

#ifdef __TASKING__

#include <Arith.FixPoint.Tasking.h>

/** \brief Fix point arithmetics (saturated): r = -a | Q1.15 = Q1.15
 *
 * Perform the operation -a. The result is saturated.
 *
 * \param a Specifies the a parameter
 *
 * \return r = -a
 * \ingroup fixpoint_arithmetics
 */
FixPoint16 __negs_r1Q15_i1Q15(FixPoint16 a)
{
#if 0
// This implementation generates incorrect code when using Tasking 2.5r1. 0xFFFF-a is returned instead
    return -a;
#else
    FixPoint32 Result;
    __asm(
        "   rsubs   %0, %1, #0                      \n"     // %0 = -%1
        : "=d" (Result)
        : "d" (a));
    return (FixPoint16)Result;
#endif
}


/** \brief Fix point arithmetics (saturated): r = abs(a) | Q1.15 = Q1.15
 *
 * Perform the operation abs(a). The result is saturated.
 *
 * \param a Specifies the a parameter
 *
 * \return r = abs(a)
 * \ingroup fixpoint_arithmetics
 */
FixPoint16 __abss_r1Q15_i1Q15(FixPoint16 a)
{
    FixPoint32 Result;

    __asm(
        "   abss.h  %0, %1                      \n"
        : "=d" (Result)
        : "d" (a));
    return (FixPoint16)Result;
}


/** \brief Fix point arithmetics (saturated): r = abs(a) | Q1.31 = Q1.31
 *
 * Perform the operation abs(a). The result is saturated.
 *
 * \param a Specifies the a parameter
 *
 * \return r = abs(a)
 * \ingroup fixpoint_arithmetics
 */
FixPoint32 __abss_r1Q31_i1Q31(FixPoint32 a)
{
    FixPoint32 Result;

    __asm(
        "   abss    %0, %1                      \n"
        : "=d" (Result)
        : "d" (a));
    return Result;
}


/** \brief Fix point arithmetics: r = a / b | Q1.31 = Q1.15 / Q16.0
 *
 * Perform the operation a / b.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter.
 *
 * \return r = a / b
 * \ingroup fixpoint_arithmetics
 */
FixPoint32 __div_r1Q31_i1Q31_i32I(FixPoint32 a, sint32 b)
{
    FixPoint32 Result;

    __asm(
        "   dvinit  e2, %1, %2                      \n"
        "   dvstep  e2, e2, %2                      \n"
        "   dvstep  e2, e2, %2                      \n"
        "   dvstep  e2, e2, %2                      \n"
        "   dvstep  e2, e2, %2                      \n"
        "   dvadj   e2, e2, %2                      \n"
        "   mov     %0, d2                          \n"
        : "=d" (Result)
        : "d" (a), "d" (b) : "d2", "d3");
    return Result;
}


/** \brief Fix point arithmetics: r = a / b | Q16.16 = Q1.15 / Q1.15
 *
 * Perform the operation a / b.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter.
 *
 * \return r = a / b
 * \ingroup fixpoint_arithmetics
 */
FixPoint32 __div_r16Q16_i1Q15_i1Q15(FixPoint16 a, FixPoint16 b)
{
    FixPoint32 Result;

    // Qa.b / qc.d = q(32-(b-d)).(b-d)
    __asm(
        "   shas    %2, %2, #-16                    \n"     // Q17.15
        "   dvinit  e2, %1, %2                      \n"
        "   dvstep  e2, e2, %2                      \n"
        "   dvstep  e2, e2, %2                      \n"
        "   dvstep  e2, e2, %2                      \n"
        "   dvstep  e2, e2, %2                      \n"
        "   dvadj   e2, e2, %2                      \n"
        "   mov     %0, d2                          \n"     // Q16.16
        : "=d" (Result)
        : "d" (a), "d" (b) : "d2", "d3");
    return Result;
}


#endif
