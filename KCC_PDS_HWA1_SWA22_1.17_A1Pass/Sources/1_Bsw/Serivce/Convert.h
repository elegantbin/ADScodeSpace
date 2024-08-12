/**
 * \file Convert.h
 * \brief Number conversion functions
 *
 *
 * $Revision: $1554.1
 * $Date: $2013-06-26 20:12:46 GMT
 *
 * \defgroup mod_cpu_convert Number conversion
 * This module implements number conversion function
 * \ingroup IfxLld_Cpu
 *
 */

#ifndef MC_CONVERT_H_
#define MC_CONVERT_H_

#include <StdReal.h>

#define FORMAT_INT_TO_FIXPOINT16(x) ((FixPoint16)(x))
#define FORMAT_INT_TO_FIXPOINT32(x) ((FixPoint32)(x))

#if !defined(WIN32) && (defined(__TASKING__) || defined(__GNUC__))
#define ARITH_FIX_POINT_OPTIMIZED (0)
#endif

#if !(ARITH_FIX_POINT_OPTIMIZED)
#include <Convert.c.h>
#else
#include "Convert.asm.h"
#endif /* MC_INTRINSICS_C */

/** \brief Convert StdReal to FixPoint32
 *
 * This function converts a value from a StdReal format to a FixPoint32 format.
 *
 * \param value value to be converted.
 * \param inputShift position of the fix point at param value. Range = [-256, 255] => (Qx.y format where x = shift+1).
 * \param outputShift position of the fix point at returned value. Range = [-256, 255] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the FixPoint32 format.
 *
 * \see Float32_To_FixPoint32(), FixPoint32_To_Float32()
 * \ingroup mod_cpu_convert
 */
inline FixPoint32 StdReal_To_FixPoint32(StdReal value, sint32 inputShift, sint32 outputShift)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    (void)inputShift; /* ignore compiler warning */
    return Float32_To_FixPoint32(value, outputShift);
#else
    return FixPoint32_To_FixPoint32(value, inputShift, outputShift);
#endif
}


/** \brief Convert StdReal to FixPoint32
 *
 * This function converts a value from a FixPoint32 format to a StdReal format.
 *
 * \param value value to be converted.
 * \param inputShift position of the fix point at param value. Range = [-256, 255] => (Qx.y format where x = shift+1).
 * \param outputShift position of the fix point at returned value. Range = [-256, 255] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the FixPoint32 format.
 *
 * \see Float32_To_FixPoint32(), FixPoint32_To_Float32()
 * \ingroup mod_cpu_convert
 */
inline StdReal FixPoint32_To_StdReal(FixPoint32 value, sint32 inputShift, sint32 outputShift)
{
#if STD_REAL_TYPE == STD_REAL_FLOAT_32
    (void)outputShift; /* ignore compiler warning */
    return FixPoint32_To_Float32(value, inputShift);
#else
    return FixPoint32_To_FixPoint32(value, inputShift, outputShift);
#endif
}


inline FixPoint16 StdReal_To_FixPoint16(StdReal value, sint32 inputShift, sint32 outputShift)
{
    return (FixPoint16)StdReal_To_FixPoint32(value, inputShift, outputShift);
}


inline StdReal FixPoint16_To_StdReal(FixPoint16 value, sint32 inputShift, sint32 outputShift)
{
    return FixPoint32_To_StdReal(value, inputShift, outputShift);
}


inline StdReal SInt16_To_StdReal(sint16 value, sint32 inputShift, sint32 outputShift)
{
    return FixPoint32_To_StdReal(SInt32_To_FixPoint32(value, STD_REAL_SHIFT_Q15), inputShift, outputShift);
}


inline StdReal SInt8_To_StdReal(sint8 value, sint32 inputShift, sint32 outputShift)
{
    return FixPoint32_To_StdReal(SInt32_To_FixPoint32(value, STD_REAL_SHIFT_Q15), inputShift, outputShift);
}


inline sint16 StdReal_To_SInt16(StdReal value, sint32 inputShift, sint32 outputShift)
{
    return (sint16)FixPoint32_To_SInt32(StdReal_To_FixPoint32(value, inputShift, outputShift), STD_REAL_SHIFT_Q15);
}


#endif /* CONVERT_H_ */
