/**
 * \file LowPass_PT1.h
 * \brief Low pass filter: Type PT1.
 * \ingroup mod_LowPass_PT1
 *
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
 * \copyright Copyright (C) 2009, 2008 Infineon Technologies AG
 *
 *
 * $Revision: $1368.3
 * $Date: $2013-06-24 18:38:13 GMT
 *
 * \defgroup mod_LowPass_PT1 Low-pass Filter: Type PT1
 * This module implements a PT1 low pass filter.
 *
 * Formula: \n
 * \f$ y_k = y_{k-1} + a * x_k - b * y_{k-1} \f$ \n
 * with \f$(T_d = \frac{T}{Ts})\f$, \f$(a = \frac{K}{T_d})\f$, \f$(b = \frac{1}{T_d})\f$
 *
 * \ingroup lib_math
 *
 */

#if !defined(LOW_PASS_PT1)
#define LOW_PASS_PT1
//------------------------------------------------------------------------------
#include "Arith.StdReal.h"
//------------------------------------------------------------------------------

/** \brief PT1 object definition.
 */
typedef struct
{
    StdReal a;              /**< \brief a=K/T parameter */
    StdReal b;              /**< \brief b=1/T parameter */
    StdReal out;            /**< \brief last output variable */
} LowPass_PT1;

/** \brief PT1 configuration */
typedef struct
{
    float32 K;              /**< \brief Gain (continuous domain) */
    float32 T;              /**< \brief Time constant in [sec] (continuous domain) */
    sint8   shiftCoef;      /**< \brief Shift coefficient.
                             *    Not required when (\ref STD_REAL_TYPE == \ref STD_REAL_FLOAT_32) */
} LowPass_PT1_Config;

//------------------------------------------------------------------------------

/** \addtogroup  mod_LowPass_PT1
 * \{ */
IFX_EXTERN boolean LowPass_PT1_init(LowPass_PT1 *filter, const LowPass_PT1_Config *config, float32 Ts);
IFX_INLINE void    LowPass_PT1_reset(LowPass_PT1 *filter);
IFX_EXTERN StdReal LowPass_PT1_do(LowPass_PT1 *filter, StdReal input);
/** \} */

//------------------------------------------------------------------------------

/** \brief Reset the internal filter variable
 * \param filter Specifies PT1 filter.
 */
IFX_INLINE void LowPass_PT1_reset(LowPass_PT1 *filter)
{
    filter->out = 0.0;
}


//------------------------------------------------------------------------------
#endif
