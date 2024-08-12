/**
 * @file MotorControl.h
 * @brief Motor control functions.
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
 * @defgroup motor_control Motor control
 *
 * This module implements motor control functions.
 * @image html "ControlLoop.gif"
 *
 * @ingroup library
 *
 * $Revision: 107 $
 * $Date: 2010-06-28 17:35:27 +0200 (Mon, 28 Jun 2010) $
 *
 */

#if !defined(MOTOR_CONTROL_H)
#define MOTOR_CONTROL_H
//------------------------------------------------------------------------------
#include "../Math/Arith.StdReal.h"
#include "IfxCpu_Intrinsics.h"
//------------------------------------------------------------------------------

/** @brief 3 phase variable definition.
 */
typedef struct
{
    StdReal u;                            /**< @brief Phase U variable */
    StdReal v;                            /**< @brief Phase V variable */
    StdReal w;                            /**< @brief Phase W variable */
}T3Phase;

#endif
