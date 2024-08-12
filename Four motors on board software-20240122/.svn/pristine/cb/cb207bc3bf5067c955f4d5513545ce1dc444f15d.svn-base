/**
 * \file LowPass_PT1.c
 * \brief Low pass filter: Type PT1.
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
 * $Revision: $1378.3
 * $Date: $2013-06-24 18:38:12 GMT
 *
 */

//------------------------------------------------------------------------------
#include <LowPass_PT1.h>
//------------------------------------------------------------------------------

/** \brief Set the low pass filter K and T parameters
 *
 * This function sets the low pass filter  K and T parameter and reset the filter output. The a and b coeficients
 * are converted to fix point values (Qx.y format where x = Shift+1) using the Shift parameter, taking in account the
 * saturation.
 *
 * \param filter Specifies PT1 filter.
 * \param config Specifies the PT1 filter configuration.
 * \param Ts Specifies the sampling period in seconds.
 *
 * \retval TRUE if initialization is successful
 * \retval FALSE if delay element coefficient is higher than 1, i.e. produce unstable filter.
 */
boolean LowPass_PT1_init(LowPass_PT1 *filter, const LowPass_PT1_Config *config, float32 Ts)
{
    filter->a   = FLOAT32_TO_STD_REAL((config->K * Ts) / (config->T+Ts), shiftCoef);
    filter->b   = FLOAT32_TO_STD_REAL(Ts / (config->T+Ts), shiftCoef);
    filter->out = 0;

    return (filter->b < FLOAT32_TO_STD_REAL(1.0, shiftCoef)) ? TRUE : FALSE;
}


/** \brief Execute the low pass filter
 * \param filter Specifies PT1 filter.
 * \param input Specifies the filter input.
 *
 * \return Returns the filter output
 */
StdReal LowPass_PT1_do(LowPass_PT1 *filter, StdReal input)
{
    filter->out = __adds_rSR_iSR_iSR(filter->out,
        __subs_rSR_iSR_iSR(__mul_rSR_iSR_iSR(filter->a, input),
            __mul_rSR_iSR_iSR(filter->b, filter->out)));

    return filter->out;
}
