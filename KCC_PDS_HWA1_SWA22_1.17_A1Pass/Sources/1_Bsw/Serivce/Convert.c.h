/**
 * \file Convert.c.h
 * \brief Number conversion functions in C
 *
 *
 *
 */

#ifndef MC_CONVERT_C_H
#define MC_CONVERT_C_H

#include <StdReal.h>

#define Convert__minX(X,Y)                     ( ((X) < (Y)) ? (X) : (Y) )
#define Convert__maxX(X,Y)                     ( ((X) > (Y)) ? (X) : (Y) )
#define Convert__saturateX(X,Min,Max)          ( Convert__minX(Convert__maxX(X, Min), Max) )
#define Convert__checkrangeX(X,Min,Max)        (((X) >= (Min)) && ((X) <= (Max)))
/** \} */

/** \defgroup  Lld_Cpu_Intrinsics_Ghs_singed_integer Signed integer operation
 * \ingroup  Lld_Cpu_Intrinsics_Ghs
 * \{
 */
#define Convert__saturate(X,Min,Max)           ( __min(__max(X, Min), Max) )
/** \} */

/** \defgroup Lld_Cpu_Intrinsics_Ghs_unsinged_integer Unsigned integer operation
 * \ingroup  Lld_Cpu_Intrinsics_Ghs
 * \{
 */
#define Convert__saturateu(X,Min,Max)           ( __minu(__maxu(X, Min), Max) )
/** \} */

/** \defgroup intrinsicsghs_float Floating point operation
 * \ingroup IfxLld_Cpu_Intrinsics_Ghs
 * \{
 */

#define Convert__sqrf(X)                       ((X) * (X))
#define Convert__sqrtf(X)                      sqrtf(X)
#define Convert__checkrange(X,Min,Max)         (((X) >= (Min)) && ((X) <= (Max)))

#define Convert__roundf(X)                     ((((X) - (sint32)(X)) > 0.5) ? (1 + (sint32)(X)) : ((sint32)(X)))
#define Convert__absf(X)                       ( ((X) < 0.0) ? -(X) : (X) )
#define Convert__minf(X,Y)                     ( ((X) < (Y)) ? (X) : (Y) )
#define Convert__maxf(X,Y)                     ( ((X) > (Y)) ? (X) : (Y) )
#define __saturatef(X,Min,Max)          ( Convert__minf(Convert__maxf(X, Min), Max) )
#define Convert__checkrangef(X,Min,Max)        (((X) >= (Min)) && ((X) <= (Max)))

#define Convert__abs_stdreal(X)                ( ((X) > 0.0) ? (X) : -(X) )
#define Convert__min_stdreal(X,Y)              ( ((X) < (Y)) ? (X) : (Y) )
#define Convert__max_stdreal(X,Y)              ( ((X) > (Y)) ? (X) : (Y) )
#define Convert__saturate_stdreal(X,Min,Max)   ( Convert__min_stdreal(Convert__max_stdreal(X, Min), Max) )

#define Convert__neqf(X,Y)                     ( ((X) > (Y)) ||  ((X) < (Y)) )     /**< X != Y */
#define Convert__leqf(X,Y)                     ( !((X) > (Y)) )     /**< X <= Y */
#define Convert__geqf(X,Y)                     ( !((X) < (Y)) )     /**< X >= Y */
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
 * \ingroup mod_cpu_convert
 */
inline FixPoint32 SInt32_To_FixPoint32(sint32 value, sint32 shift)
{
    sint32 result;

    if ((value & (0xFFFFFFFFUL << shift)) == 0)
    {
        result = value << (31 - shift);
    }
    else
    {
        result = (value < 0) ? -2147483647L : 2147483647L;
    }

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
 * \ingroup mod_cpu_convert
 */
inline sint32 FixPoint32_To_SInt32(FixPoint32 value, sint32 shift)
{
    sint32 result = (*((sint32 *)&value)) >> (31 - shift);

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
 * \ingroup mod_cpu_convert
 */
inline FixPoint32 Float32_To_FixPoint32(float32 value, sint32 shift)
{
    sint32 result;

    value = value * 2147483648.0F / (1U << shift);

    if (value < -2147483648.0F)
    {
        result = -2147483647L;
    }
    else if (value > 2147483647.0F)
    {
        result = 2147483647L;
    }
    else
    {
        result = (sint32)value;
    }

    return result;
}


/** \brief Convert float32 to FixPoint16
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
 * \ingroup mod_cpu_convert
 */
inline FixPoint16 Float32_To_FixPoint16(float32 value, sint32 shift)
{
    FixPoint16 result;

    value = value * 32768.0F / (1U << shift);

    if (value < -32768.0F)
    {
        result = -32768;
    }
    else if (value > 32767.0F)
    {
        result = 32767;
    }
    else
    {
        result = (FixPoint16)value;
    }

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
 * \ingroup mod_cpu_convert
 */
inline float32 FixPoint32_To_Float32(FixPoint32 value, sint32 shift)
{
    float32 result = (float32)value;

    result = result * (1U << shift) / 2147483648.0F;
    return result;
}


/** \brief Convert FixPoint16 to float32
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
 * \ingroup mod_cpu_convert
 */
inline float32 FixPoint16_To_Float32(FixPoint16 value, sint32 shift)
{
    float32 result = (float32)value;

    result = result * (1U << shift) / 32768.0F;
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
 * \ingroup mod_cpu_convert
 */
inline sint32 Float32_To_SInt32(float32 value)
{
    sint32 result;

    value  = __saturatef(value, -2147483648.0F, 2147483647.0F);
    result = (sint32)value;

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
 * \ingroup mod_cpu_convert
 */
inline float32 SInt32_To_Float32(sint32 value)
{
    return (float32)value;
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
 * \ingroup mod_cpu_convert
 */
inline uint32 Float32_To_UInt32(float32 value)
{
    uint32 result;

    value  = __saturatef(value, 0, 4294967295.0F);
    result = (uint32)value;

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
 * \ingroup mod_cpu_convert
 */
inline float32 UInt32_To_Float32(uint32 value)
{
    return (float32)value;
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
 * \ingroup mod_cpu_convert
 */
inline FixPoint32 FixPoint32_To_FixPoint32(FixPoint32 value, sint32 inputShift, sint32 outputShift)
{
    if (inputShift >= outputShift)
    {
        return value >> (inputShift - outputShift); /* FIXME: saturate to 32-bit */
    }
    else
    {
        return value << (outputShift - inputShift);
    }
}


#endif /* MC_CONVERT_C_H */
