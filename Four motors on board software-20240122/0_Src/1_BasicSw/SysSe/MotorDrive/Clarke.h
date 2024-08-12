/**
 * @file Clarke.h
 * @brief Clarke transformation.
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
 * $Revision: 107 $
 * $Date: 2010-06-28 17:35:27 +0200 (Mon, 28 Jun 2010) $
 *
 * @defgroup motor_control_clarke Clarke transformation
 *
 * This module implements the Clarke transformation.
 * @image html "ReferenceFrames.gif"
 * 
 * @note: An assembler optimised version is used if the compiler and assembler 
 * switch CFG_OPTIMIZE is equal to 1. The files Clarke.fixpoint16.opt.asm and 
 * Clarke.float32.opt.asm must be included in the project.
 *
 * @ingroup motor_control
 *
 */

/** @ifnot no_page_src_CLARKE_H
 * @page page_src_CLARKE_H Clarke transformation
 *
 * @image html "Clarke.gif"
 *
 * The Clarke transformation converts the vector coordinates from
 * the three phases system \f$ (a, b, c) \f$ to
 * the two phases system \f$ (\alpha, \beta) \f$ using the following formula:
 *
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
 *
 * @sourcecode @ref motor_control_clarke
 *
 * @prevnext{page_src_FOC_H,page_src_PARK_H}
 *
 * @endif
 */

#if !defined(CLARKE_H)
#define CLARKE_H
//------------------------------------------------------------------------------
#include "MotorControl.h"
//------------------------------------------------------------------------------

CplxStdReal Clarke(T3Phase *currents);
#endif
