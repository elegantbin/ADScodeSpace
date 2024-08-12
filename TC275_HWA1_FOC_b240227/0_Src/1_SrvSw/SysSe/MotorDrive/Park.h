/**
 * @file Park.h
 * @brief Park transformation.
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
 *
 * $Revision: 72 $
 * $Date: 2009-09-14 17:58:55 +0200 (Mon, 14 Sep 2009) $
 *
 * @defgroup motor_control_park Park transformation
 *
 * This module implements the Park transformation.
 * @image html "ReferenceFrames.gif"
 *
 * @note: An assembler optimised version is used if the compiler and assembler 
 * switch CFG_OPTIMIZE is equal to 1. The files Park.fixpoint16.opt.asm and 
 * Park.float32.opt.asm must be included in the project.
 *
 * @ingroup motor_control
 *
 */

/** @ifnot no_page_src_PARK_H
 * @page page_src_PARK_H Park and reverse Park transformation
 *
 * @image html "Park.gif"
 *
 * The Park transformation is a vector rotation that converts from the stationary
 * reference frame \f$ (\alpha, \beta) \f$ to the rotating reference frame
 * \f$ (d, q) \f$ attached to the rotor flux using the following formula:
 *
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
 * The reverse Park transformation does the conversion back to the stationary
 * reference frame using the following formula:
 *
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
 *
 * @sourcecode @ref motor_control_park
 *
 * @prevnext{page_src_CLARKE_H,page_src_SPACE_VECTOR_MODULATION_H}
 * @endif
 */

#if !defined(PARK_H)
#define PARK_H
//------------------------------------------------------------------------------
#include "../Math/Arith.StdReal.h"
#include "MotorControl.h"
//------------------------------------------------------------------------------

CplxStdReal Park(CplxStdReal *mab, CplxStdReal *cosSin);
CplxStdReal Park_Reverse(CplxStdReal *mdq, CplxStdReal *cosSin);
#endif
