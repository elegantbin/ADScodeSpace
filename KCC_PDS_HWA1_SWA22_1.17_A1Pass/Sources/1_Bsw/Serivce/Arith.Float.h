/**
 * \file Arith.Float.h
 * \brief Floating point arithmetic library (for code compatibility with fix point arithmetics)
 *
 *
 *
 *
 * $Revision: $1554.1
 * $Date: $2013-06-26 20:12:46 GMT
 *
 * \defgroup floating_point_arithmetics Floating point arithmetics
 *
 * This module implements floating point arithmetics.
 *
 * Function naming:
 * __[m][add|sub][m][s]_r(result format)_i(Parameter 1 Format)[_i(...)[_i(Paramter n format)]]
 *     - (result format) : format of the result in the form xQy. for example Q1.15 => 1Q15
 *     - (Parameter n Format) : format of the parameter in the form xQy. for example Q1.15 => 1Q15
 *     - (Parameter n Format) : format of the parameter in the form xI. for example 16 bit value => 16I
 *
 * \note The 1Q15 value must be passed in the upper 16 bits of the data: Value[0..15] = ignored, Value[16..31] = data
 * \note The 16I value must be passed in the lower 16 bits of the data: Value[0..15] = data, Value[16..31] = ignored
 * \ingroup mod_cpu_arithmetics
 *
 */

#ifndef MC_FLOAT_H
#define MC_FLOAT_H
//------------------------------------------------------------------------------
#include <Convert.h>
#include <math.h>

//------------------------------------------------------------------------------
/** \brief Floating point arithmetics: r = a * b
 *
 * Perform the operation a * b.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a * b
 * \ingroup floating_point_arithmetics
 */
inline float32 __mul_rF_iF_iF(float32 a, float32 b)
{
    return a * b;
}


/** \brief Floating point arithmetics: r = floor(a * b)
 *
 * Perform the operation a * b.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter.
 *
 * \return r = a * b
 * \ingroup floating_point_arithmetics
 */
inline sint16 __mul_r16I_iF_i16I(float32 a, sint16 b)
{
    return (sint16)floorf(a * b);
}


/** \brief Floating point arithmetics: r = a + b
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a + b
 * \ingroup floating_point_arithmetics
 */
inline float32 __adds_rF_iF_iF(float32 a, float32 b)
{
    return a + b;
}


/** \brief Floating point arithmetics: r = a - b
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a - b
 * \ingroup floating_point_arithmetics
 */
inline float32 __subs_rF_iF_iF(float32 a, float32 b)
{
    return a - b;
}


/** \brief Floating point arithmetics: r = a * b + c * d
 *
 * Perform the operation a * b + c * d.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 * \param c Specifies the c parameter
 * \param d Specifies the d parameter
 *
 * \return r = a * b + c * d
 * \ingroup floating_point_arithmetics
 */
inline float32 __maddms_rF_iF_iF_iF_iF(float32 a, float32 b, float32 c, float32 d)
{
    return (a * b) + (c * d);
}


/** \brief Floating point arithmetics: r = a * b - c * d
 *
 * Perform the operation a * b - c * d.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 * \param c Specifies the c parameter
 * \param d Specifies the d parameter
 *
 * \return r = a * b - c * d
 * \ingroup floating_point_arithmetics
 */
inline float32 __msubms_rF_iF_iF_iF_iF(float32 a, float32 b, float32 c, float32 d)
{
    return (a * b) - (c * d);
}


/** \brief Floating point arithmetics: r = a + b * c
 *
 * Perform the operation a + b * c.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 * \param c Specifies the c parameter
 *
 * \return r = a + b * c
 * \ingroup floating_point_arithmetics
 */
inline float32 __madds_rF_iF_iF_iF(float32 a, float32 b, float32 c)
{
    return a + (b * c);
}


/** \brief Floating point arithmetics (saturated): r = a + b * c
 *
 * Perform the operation a + b * c.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 * \param c Specifies the c parameter
 *
 * \return r = a + b * c
 * \ingroup floating_point_arithmetics
 */
inline float32 __madds_rF_iF_iF_i16I(float32 a, float32 b, sint16 c)
{
    return a + (b * c);
}


/** \brief Floating point arithmetics: r = a * b
 *
 * Perform the operation a * b.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a * b
 * \ingroup floating_point_arithmetics
 */
inline float32 __mul_rF_iF_i16I(float32 a, sint16 b)
{
    return a * b;
}


/** \brief Floating point arithmetics: r = a * 8
 *
 * Perform the operation a * 8.
 *
 * \param a Specifies the a parameter
 *
 * \return r = a * 8
 * \ingroup floating_point_arithmetics
 */
inline float32 __muls_8_rF_iF(float32 a)
{
    return a * 8;
}


/** \brief Floating point arithmetics: r = a * 128
 *
 * Perform the operation a * 128.
 *
 * \param a Specifies the a parameter
 *
 * \return r = a * 128
 * \ingroup floating_point_arithmetics
 */
inline float32 __muls_128_rF_iF(float32 a)
{
    return a * 128;
}


/** \brief Floating point arithmetics: r = a - b * c
 *
 * Perform the operation a - b * c.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 * \param c Specifies the c parameter
 *
 * \return r = a - b * c
 * \ingroup floating_point_arithmetics
 */
inline float32 __msubs_rF_iF_iF_iF(float32 a, float32 b, float32 c)
{
    return a - (b * c);
}


/** \brief Floating point arithmetics: r = a * 2^b
 *
 * Perform the operation a * 2^b.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter
 *
 * \return r = a * 2^b
 * \ingroup floating_point_arithmetics
 */
inline float32 __shas_rF_iF_i8I(float32 a, sint8 b)
{
    return (b > 0) ? (a * (2U << b)) : (a / (2U << b));
}


/** \brief Floating point arithmetics: r = -a
 *
 * Perform the operation -a.
 *
 * \param a Specifies the a parameter
 *
 * \return r = -a
 * \ingroup floating_point_arithmetics
 */
inline float32 __negs_rF_iF(float32 a)
{
    return -a;
}


/** \brief Floating point arithmetics: r = abs(a)
 *
 * Perform the operation abs(a).
 *
 * \param a Specifies the a parameter
 *
 * \return r = abs(a)
 * \ingroup floating_point_arithmetics
 */
inline float32 __abs_rF_iF(float32 a)
{
    return (a > 0) ? a : -a;
}


/** \brief Floating point arithmetics: r = a / b
 *
 * Perform the operation a / b.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter.
 *
 * \return r = a / b
 * \ingroup floating_point_arithmetics
 */
inline float32 __div_rF_iF_i32I(float32 a, sint32 b)
{
    return a / b;
}


/** \brief Floating point arithmetics: r = a / b
 *
 * Perform the operation a / b.
 *
 * \param a Specifies the a parameter
 * \param b Specifies the b parameter.
 *
 * \return r = a / b
 * \ingroup floating_point_arithmetics
 */
inline float32 __div_rF_iF_iF(float32 a, float32 b)
{
    return a / b;
}


//------------------------------------------------------------------------------
#endif
