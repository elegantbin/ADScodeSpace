/**
 * @file Foc.h
 * @brief Field Oriented Control.
 *
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
 * $Revision: 112 $
 * $Date: 2010-07-09 16:13:30 +0200 (Fri, 09 Jul 2010) $
 *
 * @defgroup motor_control_foc Field Oriented Control (FOC)
 *
 * This module implements the Field Oriented Control function.
 * @ingroup motor_control
 *
 */

/** @ifnot no_page_src_FOC_H
 * @page page_src_FOC_H Field Oriented Control
 *
 * The F.O.C. consist of controlling the stator currents in the rotor reference
 * frame which simplify considerably the complexity of the mathematical machine model.
 *
 * @par Definition of the stationary reference frames
 * The stationary reference frames are frames fixed to the stator. Two stationary
 * reference frames are use in the FOC:
 *  - the three phases stationary reference frame \f$ (a, b, c) \f$ which
 *    vector a is aligned with the stator phase U,
 *    vector b is aligned with the stator phase V,
 *    and vector c is aligned with the stator phase W.
 *  - the two phases stationary reference frame \f$ (\alpha, \beta) \f$ which
 *    vector \f$ \alpha \f$ is aligned with the stator phase U,
 *    and vector \f$ \beta \f$ is in quadrature with the \f$ \alpha \f$ vector.
 * @par Definition of the rotor reference frame
 * The rotor reference frame \f$ (d, q) \f$ is a frame fixed to the rotor flux,
 * which vector d is aligned with the rotor flux vector,
 * and vector q is in quadrature with the d vector. The \f$ (d, q) \f$ reference frame is
 * rotating at the same speed as the rotor flux at speed \f$ \omega_s \f$, where
 * \f$ \omega_s \f$ is the synchronous speed.
 * The d current id is named direct current and is responsible for the rotor
 * magnetisation, and the q current iq is the quadrature current and is responsible
 * for the mechanical torque. The relation between the mechanical speed and the rotor flux
 * speed is \f$ \omega = \omega_s + \omega_{slip} \f$. Note that in case of synchronous
 * motor, the slip speed \f$ \omega_{slip} \f$ is null, and therefore
 * \f$ \omega = \omega_s \f$
 *
 * @image html "ReferenceFrames.gif" "Reference frames"
 *
 *
 *
 *
 * @par FOC Description
 * The rotating stator current vector from the \f$ (a, b, c) \f$ reference frame
 * is transformed to a fix vector in the \f$ (d, q) \f$ frame by the
 * @subpage page_src_CLARKE_H "Clarke" and @subpage page_src_PARK_H "Park" transformations.
 * Then the current is controlled using PI controller in the \f$ (d, q) \f$ frame, the
 * results is transformed back to the \f$ (a, b, c) \f$ frame using the
 * @subpage page_src_SPACE_VECTOR_MODULATION_H "space vector modulation" to generate the PWM.
 *
 * @image html "FOC.gif" "Field Oriented Control"
 *
 * @par Timing information:
 * <TABLE cellspacing="0" cellpadding="0">
 *     <TR><TD>Function</TD>                <TD>Float C</TD>    <TD>Float asm optimized</TD>  <TD>Fixpoint 16 C</TD>  <TD>Fixpoint 16 optimized</TD></TR>
 *     <TR><TD>Clarke()</TD>                <TD> 23    </TD>    <TD> 13                </TD>  <TD> 44          </TD>  <TD> 12                  </TD></TR>
 *     <TR><TD>Park()</TD>                  <TD> 23    </TD>    <TD> 19                </TD>  <TD> 23          </TD>  <TD> 13                  </TD></TR>
 *     <TR><TD>Park_Reverse()</TD>          <TD> 23    </TD>    <TD> 19                </TD>  <TD> 23          </TD>  <TD> 12                  </TD></TR>
 *     <TR><TD>Pic_Do()</TD>                <TD> 26    </TD>    <TD> 21                </TD>  <TD> 23          </TD>  <TD> 17                  </TD></TR>
 *     <TR><TD>SpaceVectorModulation()</TD> <TD> 359   </TD>    <TD> 62                </TD>  <TD> 79          </TD>  <TD> 51                  </TD></TR>
 *     <TR><TD>Foc_Do()</TD>                <TD>       </TD>    <TD>                   </TD>  <TD>             </TD>  <TD>                     </TD></TR>
 * </TABLE>
 * @note Those timing have been measured using the system timer
 * @note Execution time in cycles( \@SystemFreqency = CpuFrequency / 2, execution in internal RAM for code and data, call included)
 *
 * @sourcecode @ref motor_control_foc
 *
 * @prevnext{@lnk_prev_page_src_FOC_H,page_src_CLARKE_H}
 *
 * @endif
 */


#if !defined(FOC_H)
#define FOC_H
//------------------------------------------------------------------------------
#include "../Math/Arith.StdReal.h"
#include "Clarke.h"
#include "IfxCpu_Intrinsics.h"
#include "Park.h"
#include "Pi.h"
#include "PMSM_CurrentControl_System.h" /*filed weakening  and current controller Model header file */
//------------------------------------------------------------------------------
/** @brief Foc object definition.
 */
typedef struct
{
	CplxStdReal        ref;             /**< @brief FOC reference currents in the dq frame */
    CplxStdReal        Msg_ref;             /**< @brief FOC reference currents in the dq frame */
    CplxStdReal        incre_ref_max;             /**< @brief FOC reference currents in the dq frame */
	CplxStdReal        vdq_ref;
	CplxStdReal        limit;           /**< @brief FOC reference current limits */
    StdReal            limitAmpl;       /**< @brief Iq and Id resultant limits */
    TPic               piId;            /**< @brief PI controller for the direct current */
    TPic               piIq;            /**< @brief PI controller for the quadrature current */

//#if (defined(DEBUG_FOC) && DEBUG_FOC) || (defined(FOC_FLUX_ESTIMATOR) && FOC_FLUX_ESTIMATOR)
    CplxStdReal        nfo_iab;         /**< @brief output of the reverse clarke transformation */
    CplxStdReal        nfo_mab;         /**< @brief output of the reverse park transformation */
//#endif

    CplxStdReal        mab;         /**< @brief output of the reverse park transformation */
    CplxStdReal        nfo_mdq;              /**< @brief output of the park transformation (debug information) */
    CplxStdReal        g_Idq;
    CplxStdReal        g_Vdq;
    float32            torque_ref;
    float32            torque_actual;
    float32            refspeed;
#if defined(DEBUG_FOC) && DEBUG_FOC
    T3Phase nfo_PhaseCurrents;      /**< @brief Stator currents in the abc frame (debug information) */
#endif
} TFoc;

extern ExtU_PMSM_CurrentControl_Syst_T PMSM_CurrentControl_System_U;
void Foc_Iq_incre(TFoc *foc, StdReal iq);
void Foc_Id_incre(TFoc *foc, StdReal id);

boolean Foc_Init(TFoc *foc);
void Foc_SetIq(TFoc *foc, StdReal iq);
StdReal Foc_GetIq(TFoc *foc);
void Foc_SetId(TFoc *foc, StdReal id);
StdReal Foc_GetId(TFoc *foc);
void Foc_SetIqLimit(TFoc *foc, StdReal limit);
StdReal Foc_GetIqLimit(TFoc *foc);
void Foc_SetIdLimit(TFoc *foc, StdReal limit);
StdReal Foc_GetIdLimit(TFoc *foc);
CplxStdReal Foc_Do(TFoc *foc, sint16 electricalAngle, T3Phase *currents);
CplxStdReal Foc_Openloop(TFoc *foc, sint16 electricalAngle, CplxStdReal Udq);
CplxStdReal Foc_Fw_Control(TFoc *foc, sint16 electricalAngle, T3Phase *currents);
void Foc_Reset(TFoc *foc);
IFX_INLINE StdReal Foc_GetIqActual(TFoc* foc) { return foc->nfo_mdq.imag; }
IFX_INLINE StdReal Foc_GetIdActual(TFoc* foc) { return foc->nfo_mdq.real; }
#endif
