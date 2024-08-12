/**
 * @file Tables.h
 * @brief Lookup tables.
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
 * $Revision: 157 $
 * $Date: 2011-03-18 18:09:52 +0100 (Fri, 18 Mar 2011) $
 *
 */

#ifndef TABLES_H
#define TABLES_H
//---------------------------------------------------------------------------

//#include "Configuration.h"
#include "../Math/Arith.StdReal.h"
#include "../Math/StdReal.h"
#include "IfxCpu_Intrinsics.h"
//---------------------------------------------------------------------------


// ================================================================
//	define lookup table
//
//
//	OneOverSqrt3=1/sqrt(3)
//
//	SinCosVector
//	Look up table for Sqrt(3)/pi*SIN((k-1)*pi/3) and Sqrt(3)/pi*Cos((k-1)*pi/3)   k=0..6
//
//	SinTable
//  	Look up table for sin(k*pi*2/COSSIN_TABLE_SIZE)   k=0..COSSIN_TABLE_SIZE+COSSIN_TABLE_SIZE/4
//
//
// ================================================================

#ifndef CONST_LOOKUP_TABLES
#define CONST_LOOKUP_TABLES   (1)       /**< @brief Default lookup tables are generated and stored in RAM */
#endif

#if (CONST_LOOKUP_TABLES != 0)
#define LOOKUP_TABLE const
#else
#define LOOKUP_TABLE
#endif

extern StdReal sinCosVector[14];

/** @brief Resolution of cosinus and sinus lookup table in bits */
#define COSSIN_TABLE_RESOLUTION (10)

/** @brief Size of the cosinus & sinus lookup table */
#define COSSIN_TABLE_SIZE       (1<<COSSIN_TABLE_RESOLUTION)

extern LOOKUP_TABLE StdReal sinCosTable[COSSIN_TABLE_SIZE + (COSSIN_TABLE_SIZE / 4)];
extern LOOKUP_TABLE StdReal* cosTable;

#define INDEX_PI   (COSSIN_TABLE_SIZE / 2)

#ifndef OBJECT_NO_INIT
void LookUp_Init(void);
#endif

IFX_INLINE StdReal LookUp_Sinus(sint16 index)
{
    index &= COSSIN_TABLE_SIZE - 1;
    return sinCosTable[index];
}

IFX_INLINE StdReal LookUp_Cosinus(sint16 index)
{
    index &= (COSSIN_TABLE_SIZE - 1);
    return cosTable[index];
}

IFX_INLINE CplxStdReal LookUp_CosinusSinus(sint16 index)
{
    CplxStdReal result;
    index &= COSSIN_TABLE_SIZE - 1;
    result.imag = sinCosTable[index];
    result.real = cosTable[index];
    return result;
}


#define ARCTAN_TABLE_LOW_SIZE    (512)
#define ARCTAN_TABLE_HIGH_SIZE   (512)

#define ARCTAN_LIMIT_LOW         (4)
#define ARCTAN_LIMIT_HIGH        (64)


extern LOOKUP_TABLE sint16 arctanTableLow[ARCTAN_TABLE_LOW_SIZE];
extern LOOKUP_TABLE sint16 arctanTableHigh[ARCTAN_TABLE_HIGH_SIZE];
sint16 LookUp_Arctan(StdReal x, StdReal y);

//---------------------------------------------------------------------------
#endif
