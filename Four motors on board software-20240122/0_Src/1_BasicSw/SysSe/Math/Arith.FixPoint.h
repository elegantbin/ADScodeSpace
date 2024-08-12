/**
 * \file Arith.FixPoint.h
 * \brief Fix-point arithmetics library
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
 * \copyright Copyright (C) 2011 - 2008 Infineon Technologies AG
 *
 *
 * $Revision: $1084.1
 * $Date: $2013-06-26 20:12:46 GMT
 *
 * \defgroup fixpoint_arithmetics Fix-point arithmetics
 *
 * This module implements Fix-point arithmetics.
 *
 * Function naming:
 * __[m][add|sub][m][s]_r(result format)_i(Parameter 1 Format)[_i(...)[_i(Paramter n format)]]
 *     - (result format) : format of the result in the form xQy. for example Q1.15 => 1Q15
 *     - (Parameter n Format) : format of the parameter in the form xQy. for example Q1.15 => 1Q15
 *     - (Parameter n Format) : format of the parameter in the form xI. for example 16 bit value => 16I
 *
 * \note The 1Q15 value must be passed in the upper 16 bits of the data: Value[0..15] = ignored, Value[16..31] = data
 * \note The 16I value must be passed in the lower 16 bits of the data: Value[0..15] = data, Value[16..31] = must contain the extended sign bit
 * \ingroup mod_cpu_arithmetics
 *
 */

#ifndef MC_FIXPOINT_H
#define MC_FIXPOINT_H
//------------------------------------------------------------------------------
#include "Convert.h"

#ifdef __GNUC__
#include "Arith.FixPoint.Gnu.h"
#endif
#ifdef __TASKING__
#include "Arith.FixPoint.Tasking.h"
#endif

//------------------------------------------------------------------------------
#endif
