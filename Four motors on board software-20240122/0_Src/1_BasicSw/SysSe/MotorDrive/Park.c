/**
 * @file Park.c
 * @brief Park transformation.
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
 * $Revision: 102 $
 * $Date: 2010-06-19 22:41:43 +0200 (Sat, 19 Jun 2010) $
 *
 */

//------------------------------------------------------------------------------
#include <Park.h>

//------------------------------------------------------------------------------
#if !defined(CFG_OPTIMIZE) || (CFG_OPTIMIZE == 0)
/** @brief Park transformation.
 *
 * This function converts the current from the stationary reference frame \f$ (\alpha, \beta) \f$
 * to the rotating reference frame \f$ (d, q) \f$ attached to the rotor flux.
 * @image html "Park.gif"
 *
 * @param mab Specifies the current in the stationary reference frame.
 * @param CosSin Specifies the cosinus and sinus coresponding to the angle \f$ \varphi \f$
 * between the phase U axis and the rotor flux axis.
 *
 * @return Returns the current in the rotating reference frame:
 * \f$
 *   \begin{bmatrix}
 *  i_{sd} \\
 *  i_{sq}
 *  \end{bmatrix}
 *  =
 *  \begin{bmatrix}
 *  \cos \varphi & \sin \varphi \\
 *  -\sin \varphi & \cos \varphi
 *  \end{bmatrix}
 *  *
 *  \begin{bmatrix}
 *  i_{s\alpha} \\
 *  i_{s\beta}
 *  \end{bmatrix}
 * \f$
 *
 * @ingroup motor_control_park
 */
CplxStdReal Park(CplxStdReal *mab, CplxStdReal *cosSin)
{
	CplxStdReal result;
	result.real = __maddms_rSR_iSR_iSR_iSR_iSR(mab->real, cosSin->real, mab->imag, cosSin->imag);
    result.imag = __msubms_rSR_iSR_iSR_iSR_iSR(mab->imag, cosSin->real, mab->real, cosSin->imag);
    return result;
}

/** @brief Reverse Park transformation.
 *
 * This function converts the current from the rotating reference frame \f$ (d, q) \f$
 * to the stationary reference frame \f$ (\alpha, \beta) \f$.
 * @image html "Park.gif"
 *
 * @param mdq Specifies the current in the rotating reference frame.
 * @param CosSin Specifies the cosinus and sinus coresponding to the angle \f$ \varphi \f$
 * between the phase U axis and the rotor flux axis.
 *
 * @return Returns the current in the stationary reference frame:
* \f$
 *  \begin{bmatrix}
 *  i_{s\alpha} \\
 *  i_{s\beta}
 *  \end{bmatrix}
 *  =
 *  \begin{bmatrix}
 *  \cos \varphi & -\sin \varphi \\
 *  \sin \varphi & \cos \varphi
 *  \end{bmatrix}
 *  *
 *  \begin{bmatrix}
 *  i_{sd} \\
 *  i_{sq}
 *  \end{bmatrix}
 * \f$
 * @ingroup motor_control_park
 */
CplxStdReal Park_Reverse(CplxStdReal *mdq, CplxStdReal *cosSin)
{
	CplxStdReal result;
    result.real = __msubms_rSR_iSR_iSR_iSR_iSR(mdq->real, cosSin->real, mdq->imag, cosSin->imag);
	result.imag = __maddms_rSR_iSR_iSR_iSR_iSR(mdq->real, cosSin->imag, mdq->imag, cosSin->real);
    return result;
}
#endif
