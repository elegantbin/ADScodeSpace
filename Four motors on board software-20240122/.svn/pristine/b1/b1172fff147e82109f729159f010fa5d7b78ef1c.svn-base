/**
 * \file Convert.asm.h
 * \brief Number conversion functions in ASM
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
 * \defgroup mod_cpu_convert_asm Optimized implementation
 * \ingroup mod_cpu_convert
 */

#ifndef MC_CONVERT_ASM_H
#define MC_CONVERT_ASM_H

#include "StdReal.h"

/** \brief Convert sint32 to FixPoint32
 *
 * This function converts a value from a sint32 format to a FixPoint32 format,
 * taking in account the saturation.
 *
 * the result is saturated to a 32 bit value.
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-32, 31] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the FixPoint32 format
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert_asm
 */
IFX_INLINE FixPoint32 SInt32_To_FixPoint32(sint32 value, sint32 shift)
{
    FixPoint32 result;

    __asm(
        "   rsub\t%2, %2, #31   \n"     // shift = 31 - shift
        "   shas\t%0, %1, %2  \n"       // result = value << (31 - shift)
        : "=d" (result)
        : "d" (value), "d" (shift));
    return result;
}


/** \brief Convert FixPoint32 to sint32
 *
 * This function converts a value from a FixPoint32 format to a sint32 format,
 * taking in account the saturation.
 *
 * the result is saturated to a 32 bit value.
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-32, 31] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the sint32 format.
 *
 * \see FixPoint32_To_Float32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert_asm
 */
IFX_INLINE sint32 FixPoint32_To_SInt32(FixPoint32 value, sint32 shift)
{
    sint32 result;

    __asm(
        "   rsub\t%2, %2, #31   \n"
        "   rsub\t%2, %2, #0    \n"     // shift = shift - 31
        "   shas\t%0, %1, %2    \n"     // result = value << (shift - 31) = value >> (31 - shift)
        : "=d" (result)
        : "d" (value), "d" (shift));
    return result;
}


/** \brief Convert float32 to FixPoint32
 *
 * This function converts a value from a float32 format to a FixPoint32 format,
 * taking in account the saturation.
 *
 * the result is saturated to a 32 bit value.
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-256, 255] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the FixPoint32 format.
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert_asm
 */
IFX_INLINE FixPoint32 Float32_To_FixPoint32(float32 value, sint32 shift)
{
    FixPoint32 result;

    __asm(
        "   ftoq31\t%0, %1, %2  \n"
        : "=d" (result)
        : "d" (value), "d" (shift));
    return result;
}


/** \brief Convert FixPoint32 to float32
 *
 * This function converts a value from a FixPoint32 format to a float32 format.
 *
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-256, 255] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the float32 format.
 *
 * \see FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert_asm
 */
IFX_INLINE float32 FixPoint32_To_Float32(FixPoint32 value, sint32 shift)
{
    float32 result;

    __asm(
        "   q31tof\t%0, %1, %2  \n"
        : "=d" (result)
        : "d" (value), "d" (shift));
    return result;
}


/** \brief Convert float32 to sint32
 *
 * This function converts a value from a float32 format to a sint32 format,
 * the result is saturated to a 32 bit signed integer value.
 *
 * \param value value to be converted.
 *
 * \return Returns the converted value in the sint32 format.
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert_asm
 */
IFX_INLINE sint32 Float32_To_SInt32(float32 value)
{
    sint32 result;

    __asm(
        "   ftoi\t%0, %1  \n"
        : "=d" (result)
        : "d" (value));
    return result;
}


/** \brief Convert sint32 to float32
 *
 * This function converts a value from a sint32 format to a float32 format.
 *
 * \param value value to be converted.
 *
 * \return Returns the converted value in the float32 format.
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert_asm
 */
IFX_INLINE float32 SInt32_To_Float32(sint32 value)
{
    float32 result;

    __asm(
        "   itof\t%0, %1  \n"
        : "=d" (result)
        : "d" (value));
    return result;
}


/** \brief Convert float32 to uint32
 *
 * This function converts a value from a float32 format to a uint32 format,
 * the result is saturated to a 32 bit unsigned integer value.
 *
 * \param value value to be converted.
 *
 * \return Returns the converted value in the uint32 format.
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert_asm
 */
IFX_INLINE uint32 Float32_To_UInt32(float32 value)
{
    uint32 result;

    __asm(
        "   ftou\t%0, %1  \n"
        : "=d" (result)
        : "d" (value));
    return result;
}


/** \brief Convert uint32 to float32
 *
 * This function converts a value from a uint32 format to a float32 format.
 *
 * \param value value to be converted.
 *
 * \return Returns the converted value in the float32 format.
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32()
 * \ingroup mod_cpu_convert_asm
 */
IFX_INLINE float32 UInt32_To_Float32(uint32 value)
{
    float32 result;

    __asm(
        "   utof\t%0, %1  \n"
        : "=d" (result)
        : "d" (value));
    return result;
}


/** \brief Convert FixPoint32 to FixPoint32
 *
 * This function converts a value from a FixPoint32 format to a FixPoint32 format,
 * taking in account the saturation.
 *
 * the result is saturated to a 32 bit value.
 *
 * \param value value to be converted.
 * \param inputShift position of the fix point. Range = [-32, 31] => (Qx.y format where x = shift+1).
 * \param outputShift position of the fix point. Range = [-32, 31] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the sint32 format.
 *
 * \see FixPoint32_To_Float32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert_asm
 */
IFX_INLINE FixPoint32 FixPoint32_To_FixPoint32(FixPoint32 value, sint32 inputShift, sint32 outputShift)
{
    FixPoint32 result;

    __asm(
        "   shas\t%0, %1, %2    \n"
        : "=d" (result)
        : "d" (value), "d" (inputShift - outputShift));
    return result;
}


IFX_INLINE FixPoint16 Float32_To_FixPoint16(float32 value, sint32 shift)
{
    return Float32_To_FixPoint32(value, shift);
}


IFX_INLINE float32 FixPoint16_To_Float32(FixPoint16 value, sint32 shift)
{
    return FixPoint32_To_Float32((FixPoint32)value, shift);
}


#endif /* MC_CONVERT_ASM_H */
