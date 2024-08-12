/**
 * @file tables.c
 * @brief Lookup tables.
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
 * $Revision: 162 $
 * $Date: 2011-04-04 15:43:24 +0200 (Mon, 04 Apr 2011) $
 *
 */
#include <Tables.h>
#include "Math.h"



StdReal sinCosVector[14];

#if CONST_LOOKUP_TABLES == 0
#if STD_REAL_TYPE == STD_REAL_FIX_POINT_16
LOOKUP_TABLE uint16 sinCosTable[COSSIN_TABLE_SIZE + (COSSIN_TABLE_SIZE / 4)];
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_32
LOOKUP_TABLE uint32 sinCosTable[COSSIN_TABLE_SIZE + (COSSIN_TABLE_SIZE / 4)];
#else
LOOKUP_TABLE StdReal sinCosTable[COSSIN_TABLE_SIZE + (COSSIN_TABLE_SIZE / 4)];
#endif
#endif

LOOKUP_TABLE StdReal* cosTable = &(sinCosTable[COSSIN_TABLE_SIZE / 4]);

/*
ArctanTableLow[0..512[  = atan(x) for x = [0, 4[, step = 8 / 512. Factor x=128
ArctanTableHigh[0..512[ = atan(x) for x = [0, 64[, step = 64 / 512. Factor x= 8
*/


#if STD_REAL_TYPE == STD_REAL_FLOAT_32
#define ARCTAN_LIMIT_LOW_SR         ((StdRealLong)ARCTAN_LIMIT_LOW)
#define ARCTAN_LIMIT_HIGH_SR        ((StdRealLong)ARCTAN_LIMIT_HIGH)
#else
#define ARCTAN_LIMIT_LOW_SR         ((StdRealLong)(FORMAT_INT_TO_FIXPOINT32(ARCTAN_LIMIT_LOW / 65536)))    // Format Q16.16
#define ARCTAN_LIMIT_HIGH_SR        ((StdRealLong)(FORMAT_INT_TO_FIXPOINT32(ARCTAN_LIMIT_HIGH / 65536)))    // Format Q16.16

#endif

#if CONST_LOOKUP_TABLES == 0
sint16 arctanTableLow[ARCTAN_TABLE_LOW_SIZE];
sint16 arctanTableHigh[ARCTAN_TABLE_HIGH_SIZE];
#endif

#ifndef OBJECT_NO_INIT
void LookUp_Init(void)
{
    sint32 k;

    for (k = 1; k <= 6; k++)
    {
        sinCosVector[((k-1)*2)]   = FLOAT32_TO_STD_REAL((sqrt(3)/PI)*sin(((k-1)*PI)/3), STD_REAL_SHIFT_Q1_y);
        sinCosVector[((k-1)*2)+1] = FLOAT32_TO_STD_REAL((sqrt(3)/PI)*cos(((k-1)*PI)/3), STD_REAL_SHIFT_Q1_y);
    }
    sinCosVector[12] = FLOAT32_TO_STD_REAL((sqrt(3)/PI)*sin(((1-1)*PI)/3), STD_REAL_SHIFT_Q1_y);
    sinCosVector[13] = FLOAT32_TO_STD_REAL((sqrt(3)/PI)*cos(((1-1)*PI)/3), STD_REAL_SHIFT_Q1_y);

    cosTable = (LOOKUP_TABLE StdReal*) &sinCosTable[COSSIN_TABLE_SIZE / 4];

#if CONST_LOOKUP_TABLES == 0
    for (k = 0; k < (COSSIN_TABLE_SIZE + (COSSIN_TABLE_SIZE / 4)); k++)
    {
        sinCosTable[k] = FLOAT32_TO_STD_REAL(sin((k * 2 * PI) / COSSIN_TABLE_SIZE), STD_REAL_SHIFT_Q1_y);
    }
    {
        float32 Step;
        Step = ARCTAN_LIMIT_LOW / ARCTAN_TABLE_LOW_SIZE;
        for (k = 0; k < ARCTAN_TABLE_LOW_SIZE; k++) 
        {
            arctanTableLow[k] = (sint16)(( (atan(k * Step) / (2.0 * PI)) * (2 * INDEX_PI)));
        }

        Step = ARCTAN_LIMIT_HIGH / ARCTAN_TABLE_HIGH_SIZE;
        for (k = 0; k < ARCTAN_TABLE_HIGH_SIZE; k++) 
        {
            arctanTableHigh[k] = (sint16)(( (atan(k * Step) / (2.0 * PI)) * (2 * INDEX_PI)));
        }

    }
#endif
}
#endif

// return atan(y/x) but also check the quadrant, result range is [0, 2.PI]
sint16 LookUp_Arctan(StdReal x, StdReal y)
{
    sint16 index;

    if ((x < 0) || (x > 0))
    {
        StdRealLong qdiv ;
        StdRealLong abs_div;
        qdiv = __div_rLSR_iSR_iSR(y, x); // Q16.16
        abs_div = __abss_rLSR_iLSR(qdiv);

        if(abs_div < ARCTAN_LIMIT_LOW_SR)
        {
            index = arctanTableLow[__floors_r32I_iLSR(__muls_128_rLSR_iLSR(abs_div), STD_REAL_SHIFT_Q16)];
        }
        else if(abs_div < ARCTAN_LIMIT_HIGH_SR)
        {
            index = arctanTableHigh[__floors_r32I_iLSR(__muls_8_rLSR_iLSR(abs_div), STD_REAL_SHIFT_Q16)];
        }
        else
        {
            index = INDEX_PI / 2;
        }

        if (qdiv < 0)
        {
            index = -index;
        }

        if (x < 0)
        {
            index += INDEX_PI;
        }
        else if (index < 0)
        {
            index += 2 * INDEX_PI;
        }
        else {}
    }
    else
    {
        if (y > 0)
        {
            index = INDEX_PI / 2;
        }
        else
        {
            index = (3 * INDEX_PI) / 2;
        }
    }
    return index;
}
