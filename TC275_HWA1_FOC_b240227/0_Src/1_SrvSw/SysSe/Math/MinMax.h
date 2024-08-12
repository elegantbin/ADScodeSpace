/**
 * \file MinMax.h
 * \brief Minimum-maximum latch function
 * \ingroup mod_MinMax
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
 * \copyright Copyright (C) 2011 Infineon Technologies AG
 *
 *
 * $Revision: $1368.3
 * $Date: $2013-06-24 18:38:14 GMT
 *
 * \defgroup mod_MinMax Minimum-maximum Latch
 * \ingroup lib_math
 *
 */
#ifndef MINMAX_H_
#define MINMAX_H_

#include "Arith.StdReal.h"

/** \brief MinMax object definition */
typedef struct sMinMax
{
    sint32 lower;   /**< \brief lower (minimum) value */
    sint32 upper;   /**< \brief upper (maximum) value */
} MinMax;

/** \addtogroup mod_MinMax
 * \{ */

/** \brief Initialise the MinMax object
* \param mm Pointer to MinMax object */
IFX_INLINE void MinMax_init(MinMax *mm)
{
    mm->lower = 2147483647;
    mm->upper = -2147483647;
}


/** \brief Update the MinMax object
 * \param mm Pointer to MinMax object
 * \param value New value to compare with the upper and lower */
IFX_INLINE void MinMax_update(MinMax *mm, sint32 value)
{
    mm->lower = __min(mm->lower, value);
    mm->upper = __max(mm->upper, value);
}


/** \} */

#endif /* MINMAX_H_ */
