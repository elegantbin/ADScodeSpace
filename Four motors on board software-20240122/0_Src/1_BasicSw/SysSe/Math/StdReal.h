/**
 * \file StdReal.h
 * \brief Definition for StdReal types.
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
 * $Revision: $1554.1
 * $Date: $2013-06-26 20:12:46 GMT
 *
 */

#ifndef STDREAL_H
#define STDREAL_H

#include "Ifx_Types.h"
#include "IfxCpu_Intrinsics.h"

typedef sfract FixPoint16;
typedef fract  FixPoint32;

#define STD_REAL_FIX_POINT_16 (1)               /**< \brief define the standard real type as FixPoint16 */
#define STD_REAL_FIX_POINT_32 (2)               /**< \brief define the standard real type as FixPoint32 */
#define STD_REAL_FLOAT_32     (3)               /**< \brief define the standard real type as float32 (default) */

#ifndef STD_REAL_TYPE
/* The following switch is defined here as default value only. It must
 * be defined in the project options. in case it is not defined,
 * STD_REAL_FLOAT_32 is used as default */
#define STD_REAL_TYPE         (STD_REAL_FLOAT_32)   /**< \brief define the standard real. Range={STD_REAL_FLOAT_32, STD_REAL_FIX_POINT_32, STD_REAL_FIX_POINT_16} */
#endif

#if STD_REAL_TYPE == STD_REAL_FIX_POINT_16
#define STD_REAL_ZERO         (0)
typedef FixPoint16 StdReal;
typedef FixPoint32 StdRealLong;
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_32
#define STD_REAL_ZERO         (0)
typedef FixPoint32 StdReal;
typedef FixPoint32 StdRealLong;
#elif STD_REAL_TYPE == STD_REAL_FLOAT_32
#define STD_REAL_ZERO         (0.0)
/**
 * \brief standard real type definition. This type has been
 * introduced to easy the compilation of the application using
 * different type for the fix point and floating point calculation.
 * The following types can be selected: FixPoint16, FixPoint32 and float32
 *
 * Note that since Tricore supports 32-bit floating-point natively, the performance
 * improvement may be significant only when FixPoint16 is used.
 */
typedef float32 StdReal;

/**
 * \brief Long standard real type definition.
 * It is either FixPoint32 or float32 according to the selected type for StdReal
 */
typedef float32 StdRealLong;
#else
#error "Incorrect value for STD_REAL_TYPE."
#endif

#define STD_REAL_SHIFT_Qn9 (-9)         /**< \brief Fix point format: Range=[-2^(-9), 2^(-9)[; Q1.15 => Step=1/2^24.    Q1.31  => Step=1/2^40. */
#define STD_REAL_SHIFT_Qn8 (-8)         /**< \brief Fix point format: Range=[-2^(-8), 2^(-8)[; Q1.15 => Step=1/2^23.    Q1.31  => Step=1/2^39. */
#define STD_REAL_SHIFT_Qn7 (-7)         /**< \brief Fix point format: Range=[-2^(-7), 2^(-7)[; Q1.15 => Step=1/2^22.    Q1.31  => Step=1/2^38. */
#define STD_REAL_SHIFT_Qn6 (-6)         /**< \brief Fix point format: Range=[-2^(-6), 2^(-6)[; Q1.15 => Step=1/2^21.    Q1.31  => Step=1/2^37. */
#define STD_REAL_SHIFT_Qn5 (-5)         /**< \brief Fix point format: Range=[-2^(-5), 2^(-5)[; Q1.15 => Step=1/2^20.    Q1.31  => Step=1/2^36. */
#define STD_REAL_SHIFT_Qn4 (-4)         /**< \brief Fix point format: Range=[-2^(-4), 2^(-4)[; Q1.15 => Step=1/2^19.    Q1.31  => Step=1/2^35. */
#define STD_REAL_SHIFT_Qn3 (-3)         /**< \brief Fix point format: Range=[-2^(-3), 2^(-3)[; Q1.15 => Step=1/2^18.    Q1.31  => Step=1/2^34. */
#define STD_REAL_SHIFT_Qn2 (-2)         /**< \brief Fix point format: Range=[-2^(-2), 2^(-2)[; Q1.15 => Step=1/2^17.    Q1.31  => Step=1/2^33. */
#define STD_REAL_SHIFT_Qn1 (-1)         /**< \brief Fix point format: Range=[-2^(-1), 2^(-1)[; Q1.15 => Step=1/2^16.    Q1.31  => Step=1/2^32. */

#define STD_REAL_SHIFT_Q0  (0)          /**< \brief Fix point format: Range=[-2^0   , 2^0[;    Q0.15 => Step=1/2^15.    Q0.31  => Step=1/2^31. */
#define STD_REAL_SHIFT_Q1  (1)          /**< \brief Fix point format: Range=[-2^1   , 2^1[;    Q1.14 => Step=1/2^14.    Q1.30  => Step=1/2^30. */
#define STD_REAL_SHIFT_Q2  (2)          /**< \brief Fix point format: Range=[-2^2   , 2^2[;    Q2.13 => Step=1/2^13.    Q2.29  => Step=1/2^29. */
#define STD_REAL_SHIFT_Q3  (3)          /**< \brief Fix point format: Range=[-2^3   , 2^3[;    Q3.12 => Step=1/2^12.    Q3.28  => Step=1/2^28. */
#define STD_REAL_SHIFT_Q4  (4)          /**< \brief Fix point format: Range=[-2^4   , 2^4[;    Q4.11 => Step=1/2^11.    Q4.27  => Step=1/2^27. */
#define STD_REAL_SHIFT_Q5  (5)          /**< \brief Fix point format: Range=[-2^5   , 2^5[;    Q5.10 => Step=1/2^10.    Q5.26  => Step=1/2^26. */
#define STD_REAL_SHIFT_Q6  (6)          /**< \brief Fix point format: Range=[-2^6   , 2^6[;    Q6.9  => Step=1/2^9.     Q6.25  => Step=1/2^25. */
#define STD_REAL_SHIFT_Q7  (7)          /**< \brief Fix point format: Range=[-2^7   , 2^7[;    Q7.8  => Step=1/2^8.     Q7.24  => Step=1/2^24. */
#define STD_REAL_SHIFT_Q8  (8)          /**< \brief Fix point format: Range=[-2^8   , 2^8[;    Q8.7  => Step=1/2^7.     Q8.23  => Step=1/2^23. */
#define STD_REAL_SHIFT_Q9  (9)          /**< \brief Fix point format: Range=[-2^9   , 2^9[;    Q9.6  => Step=1/2^6.     Q9.22  => Step=1/2^22. */
#define STD_REAL_SHIFT_Q10 (10)         /**< \brief Fix point format: Range=[-2^10  , 2^10[;   Q10.5 => Step=1/2^5.     Q10.21 => Step=1/2^21. */
#define STD_REAL_SHIFT_Q11 (11)         /**< \brief Fix point format: Range=[-2^11  , 2^11[;   Q11.4 => Step=1/2^4.     Q11.20 => Step=1/2^20. */
#define STD_REAL_SHIFT_Q12 (12)         /**< \brief Fix point format: Range=[-2^12  , 2^12[;   Q12.3 => Step=1/2^3.     Q12.19 => Step=1/2^19. */
#define STD_REAL_SHIFT_Q13 (13)         /**< \brief Fix point format: Range=[-2^13  , 2^13[;   Q13.2 => Step=1/2^2.     Q13.18 => Step=1/2^18. */
#define STD_REAL_SHIFT_Q14 (14)         /**< \brief Fix point format: Range=[-2^14  , 2^14[;   Q14.1 => Step=1/2^1.     Q14.17 => Step=1/2^17. */
#define STD_REAL_SHIFT_Q15 (15)         /**< \brief Fix point format: Range=[-2^15  , 2^15[;   Q15.0 => Step=1.         Q15.16 => Step=1/2^16. */
#define STD_REAL_SHIFT_Q16 (16)         /**< \brief Fix point format: Range=[-2^15  , 2^15[;   Q15.0 => Step=1.         Q15.16 => Step=1/2^16. */
#define STD_REAL_SHIFT_Q31 (31)         /**< \brief Fix point format: Range=[-2^31  , 2^31[;   Q16.0 => N.A             Q32.0 => Step=1.       */

/** \brief Complex type definition (based on StdReal).
 */
typedef struct
{
    StdReal real;               /**< \brief Real part */
    StdReal imag;               /**< \brief Imaginary part */
} CplxStdReal;

#endif /* STDREAL_H */
