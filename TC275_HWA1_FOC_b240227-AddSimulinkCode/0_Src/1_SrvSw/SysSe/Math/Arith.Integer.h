/**
 * \file Arith.Integer.h
 * \brief Integer arithmetic library
 *
 * Function naming:
 * __[m][add|sub][m][s]_r<result format>_i<Parameter 1 Format>[_i<...>[_i<Paramter n format>]]
 *     - <result format> : format of the result in the form xI. for example 32 bit value => 32I
 *     - <Parameter n Format> : format of the parameter in the form xI. for example 16 bit value => 16I
 *
 * \note The 16I value must be passed in the lower 16 bits of the data: Value[0..15] = data, Value[16..31] = ignored
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
 * \defgroup integer_arithmetics Integer arithmetics
 *
 * This module implements Integer arithmetics.
 * \ingroup mod_cpu_arithmetics
 *
 */

#ifndef MC_INTEGER_H
#define MC_INTEGER_H
//------------------------------------------------------------------------------
#include "Intrinsics.h"
#include "Ifx_Types.h"
//------------------------------------------------------------------------------
/** \brief Integer arithmetics: r = Value << Shift;
 * \ingroup integer_arithmetics
 */
IFX_INLINE sint32 __sha_r32I_i32I_i8I(sint32 Value, sint8 Shift)
{
    sint32 Result;

#if !(ARITH_FIX_POINT_OPTIMIZED)

    if (Shift >= 0)
    {
        Result = Value << Shift;
    }
    else
    {
        Result = Value / (1U << -Shift);
    }

#else
    __asm(
        "   sha\t%0, %1, %2  \n"       // Result = Value << Shift
        : "=d" (Result)
        : "d" (Value), "d" (Shift));
#endif
    return Result;
}


/** \brief Expand the sine bit
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-32, 31] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the sint32 format.
 *
 * \ingroup intrinsic
 */
IFX_INLINE sint32 ExpandSign_SInt32(sint32 value, sint32 shift)
{
    return (value << shift) >> shift;
}


IFX_INLINE FixPoint16 Div_Int16_Int16(sint16 a, sint16 b)
{
    return (FixPoint16)(SInt32_To_FixPoint32(a, 16) / SInt32_To_FixPoint32(b, 16));
}


//------------------------------------------------------------------------------
#endif
