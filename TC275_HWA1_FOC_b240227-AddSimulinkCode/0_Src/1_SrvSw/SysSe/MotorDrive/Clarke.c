/**
 * @file Clarke.c
 * @brief Clarke transformation.
 * @license
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
 * @copyright Copyright (C) 2009, 2008 Infineon Technologies AG
 *
 *
 * $Revision: 107 $
 * $Date: 2010-06-28 17:35:27 +0200 (Mon, 28 Jun 2010) $
 *
 */

//------------------------------------------------------------------------------
#include <Arith.StdReal.h>
#include <Clarke.h>

//------------------------------------------------------------------------------
#if !defined(CFG_OPTIMIZE) || (CFG_OPTIMIZE == 0)
/** @brief Clarke transformation.
 *
 * This function converts the current from the three phases system \f$ (a, b, c) \f$ to the two phases system \f$ (\alpha, \beta) \f$.
 * @image html "Clarke.gif"
 *
 * @param Currents Specifies the stator currents in the three phases system.
 *
 * @return Returns the stator current in two phases system :
 * \f$
 *  \begin{bmatrix}
 *  i_{s\alpha} \\
 *  i_{s\beta}
 *  \end{bmatrix}
 *  =
 *  \begin{bmatrix}
 *  i_a \\
 *  \frac{1}{\sqrt{3}}*(i_b-i_c)
 *  \end{bmatrix}
 * \f$.
 * @ingroup motor_control_clarke
 */
CplxStdReal Clarke(T3Phase *currents)
{
	CplxStdReal result;
    result.real = currents->u;
    result.imag = __mul_rSR_iSR_iSR(OneOverSqrt3_SR, __subs_rSR_iSR_iSR(currents->v, currents->w));
    return result;
}
#endif
