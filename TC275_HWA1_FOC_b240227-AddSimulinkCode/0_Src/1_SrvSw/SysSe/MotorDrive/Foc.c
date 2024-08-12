/**
 * @file Foc.c
 * @brief Field Oriented Control.
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
 * $Revision: 133 $
 * $Date: 2010-09-29 16:03:53 +0200 (Wed, 29 Sep 2010) $
 *
 */

//------------------------------------------------------------------------------
#include <Foc.h>
#include <Tables.h>
#include "Vadc_LowPassPT1.h"
#include "AverageFiltering.h"
//------------------------------------------------------------------------------

IFX_INLINE void Foc_InitComplex(CplxStdReal* compl)
{
    compl->imag = 0.0;
    compl->real = 0.0;
}


IFX_INLINE CplxStdReal Foc_LimitVqVd(TPic* Pic_d,TPic* Pic_q, CplxStdReal mdq,StdReal Limit )
{
    /* Note 0.9 is the maximum for where Vref in the lies in the circle (continuous) */
	StdReal ModIndex = sqrt((mdq.imag * mdq.imag) + (mdq.real * mdq.real));
    ModIndex = (Limit / ModIndex );
    if(ModIndex < 1)
    {
    	mdq.imag *= ModIndex;
    	mdq.real *= ModIndex;
    	// Correct PI-Output with new calculated values for anti wind up reason
    	Pic_d->uk = mdq.real;
    	Pic_q->uk = mdq.imag;
    }
    return mdq;
}

/** @brief Initialize the Foc object.
 *
 * This function initializes the Foc object:
 *    - PiId and PiIq parameters are set to default values as done by Pic_Init()
 *    - The Id and Iq references and limits are set to 0
 *
 * @param Foc Specifies the field oriented control object.
 *
 * @return none
 * @note The Kp, Ki and limits of the PI controllers must be set separately.
 * @see Pic_Init(), Pic_SetKpKi(), Pic_SetKpKi_StdReal(), Pic_SetLimit(), Foc_SetIdLimit(), Foc_SetIqLimit(), Foc_SetId(), Foc_SetIq().
 * @ingroup motor_control_foc
 */
boolean Foc_Init(TFoc *foc)
{
    Foc_InitComplex(&foc->ref);
    Foc_InitComplex(&foc->limit);
    Pic_Init(&foc->piId);
    Pic_Init(&foc->piIq);
    CurrentPI_Init(&foc->piId);
    CurrentPI_Init(&foc->piIq);

    return TRUE;
}


IFX_INLINE void Foc_SetPiLimit(TPic* pic, StdReal orthoRef)
{
    /* Note 0.9 is the maximum for where Vref in the lies in the circle (continuous) */
    StdReal limit = 0;//sqrt_f((0.9 * 0.9) - (orthoRef * orthoRef));
    Pic_SetLimit(pic, -limit, limit);
}


/** @brief Field Oriented Control function.
 *
 * This function performs field oriented control calculations, and returns the output of the reverse parke transformation.
 *
 * @param Foc Specifies the field oriented control object.
 * @param ElectricalAngle Specifies motor electrical angle between 0 an 2*PI where 2*PI corresponds to COSSIN_TABLE_SIZE.
 * @param Currents Specifies the 3 phases currents in the (a, b, c) frame. which are the input for the Clarke transformation.
 *
 * @return mab
 * @see Clarke(), Park(), Park_Reverse(), Pic().
 * @ingroup motor_control_foc
 */

StdReal FOC_Limit = 0.85; // pi/(2* sqrt(3)) + 2*DT/Periode
#define FACTOR_VAVB  (0.8)

CplxStdReal mdq_ctrl  = {0.05,0.05};
CplxStdReal Foc_Do(TFoc *foc, sint16 electricalAngle, T3Phase *currents)
{
	CplxStdReal cosSin;
	CplxStdReal mdq, mab;

    /* Clarke Park transformation */
    mab = Clarke(currents);

    cosSin = LookUp_CosinusSinus(electricalAngle);

    mdq = Park(&mab, &cosSin);

    foc->nfo_mdq = mdq;
    /* Pure PI controller only with symmetrical Limitation of Vq and Vd*/

    /* Pi controller */
    /*input mdq is the actual current, Output mdq is in (-0.85,0.85)*/

    mdq.imag = Current_PI(&foc->piIq, __subs_rSR_iSR_iSR(foc->ref.imag, mdq.imag));
    mdq.real = Current_PI(&foc->piId, __subs_rSR_iSR_iSR(foc->ref.real, mdq.real));

    /* Limitation of Vq and Vd with anti wind up*/
    mdq = Foc_LimitVqVd(&foc->piId,&foc->piIq, mdq, foc->limitAmpl);
    foc->g_Vdq = mdq;

    /* Reverse Park transformation */
    mab = Park_Reverse(&mdq, &cosSin);

    foc->nfo_mab = mab;

    return mab;
}

CplxStdReal Foc_Openloop(TFoc *foc, sint16 electricalAngle, CplxStdReal Udq)
{
    CplxStdReal cosSin;
    CplxStdReal mdq, mab;

    cosSin = LookUp_CosinusSinus(electricalAngle);

    mdq.imag = Udq.imag;
    mdq.real = Udq.real;

    /*  symmetrical Limitation of Vq and Vd*/
    mdq = Foc_LimitVqVd(&foc->piId,&foc->piIq, mdq, foc->limitAmpl);

    /* Reverse Park transformation */
    mab = Park_Reverse(&mdq, &cosSin);

    foc->nfo_mab = mab;

    return mab;
}

/* Field Oriented Control function with field weakening control*/
CplxStdReal Foc_Fw_Control(TFoc *foc, sint16 electricalAngle, T3Phase *currents)
{
    CplxStdReal cosSin;
    CplxStdReal mdq, mab;

    /* Clarke Park transformation */
    mab = Clarke(currents);

    cosSin = LookUp_CosinusSinus(electricalAngle);

    mdq = Park(&mab, &cosSin);

    foc->nfo_mdq = mdq;
    /* Pure PI controller only with symmetrical Limitation of Vq and Vd*/

    /* Pi controller */
    /*input mdq is the actual current, Output mdq is in (-0.85,0.85)*/
//
//    mdq.imag = Current_PI(&foc->piIq, __subs_rSR_iSR_iSR(foc->ref.imag, mdq.imag));
//    mdq.real = Current_PI(&foc->piId, __subs_rSR_iSR_iSR(foc->ref.real, mdq.real));

    PMSM_CurrentControl_System_U.Id_fb = mdq.real;
    PMSM_CurrentControl_System_U.Iq_fb = mdq.imag;
    PMSM_CurrentControl_System_U.Id_ref_unsat = foc->ref.real;
    PMSM_CurrentControl_System_U.Iq_ref_unsat = foc->ref.imag;

    /* Step the model */
    PMSM_CurrentControl_System_step(PMSM_CurrentControl_System_MPtr, &PMSM_CurrentControl_System_U, &PMSM_CurrentControl_System_Y);

    /* Limitation of Vq and Vd with anti wind up*/
//    mdq = Foc_LimitVqVd(&foc->piId,&foc->piIq, mdq, foc->limitAmpl);
    mdq.imag = PMSM_CurrentControl_System_Y.Vq_ref;
    mdq.real = PMSM_CurrentControl_System_Y.Vd_ref;

    /* Reverse Park transformation */
    mab = Park_Reverse(&mdq, &cosSin);

    foc->nfo_mab = mab;

    return mab;
}
/** @brief Set the Iq current reference.
 *
 * This function sets the Iq current reference. The Iq reference value is checked against the Iq Limit.
 *
 * @param Foc Specifies the field oriented control object.
 * @param Iq Specifies Iq current reference.
 *
 * @return none
 * @see Foc_GetIq(), Foc_GetIqLimit(), Foc_SetIqLimit().
 * @ingroup motor_control_foc
 */

void Foc_Iq_incre(TFoc *foc, StdReal iq)
{
    if((iq - foc->ref.imag)>0.5)
    {
        foc->ref.imag += 0.5;
    }
    else if((foc->ref.imag - iq)>0.5)
    {
        foc->ref.imag -= 0.5;
    }
    else
    {
        foc->ref.imag =  iq;
    }
}

void Foc_SetIq(TFoc *foc, StdReal iq)
{
    foc->ref.imag = __saturate_stdreal(iq, -foc->limit.imag, foc->limit.imag);
}

/** @brief Return the Iq current reference.
 *
 * This function returns the Iq current reference.
 *
 * @param Foc Specifies the field oriented control object.
 *
 * @return Returns the Iq current reference
 * @see Foc_SetIq().
 * @ingroup motor_control_foc
 */
StdReal Foc_GetIq(TFoc *foc)
{
    return foc->ref.imag;
}

/** @brief Set the Id current reference.
 *
 * This function sets the Id current reference. The Id reference value is checked against the Id Limit.
 *
 * @param Foc Specifies the field oriented control object.
 * @param Id Specifies Id current reference.
 *
 * @return none
 * @see Foc_GetId(), Foc_GetIdLimit(), Foc_SetIdLimit().
 * @ingroup motor_control_foc
 */

void Foc_Id_incre(TFoc *foc, StdReal id)
{
    if((id-foc->ref.real)>0.5)
    {
        foc->ref.real += 0.5;
    }
    else if((foc->ref.real-id)>0.5)
    {
        foc->ref.real -= 0.5;
    }
    else
    {
        foc->ref.real = id;
    }
}

void Foc_SetId(TFoc *foc, StdReal id)
{

    foc->ref.real = __saturate_stdreal(id, -foc->limit.real, foc->limit.real);
}

/** @brief Return the Id current reference.
 *
 * This function returns the Id current reference.
 *
 * @param Foc Specifies the field oriented control object.
 *
 * @return Returns the Id current reference
 * @see Foc_SetId().
 * @ingroup motor_control_foc
 */
StdReal Foc_GetId(TFoc *foc)
{
    return foc->ref.real;
}

/** @brief Set the Iq current limit.
 *
 * This function sets the Iq current limit.
 *
 * @param Foc Specifies the field oriented control object.
 * @param Limit Specifies Iq current limit.
 *
 * @return none
 * @see Foc_GetIqLimit().
 * @ingroup motor_control_foc
 */
void Foc_SetIqLimit(TFoc *foc, StdReal limit)
{
    foc->limit.imag = limit;
}

/** @brief Return the Iq current limit.
 *
 * This function returns the Iq current limit.
 *
 * @param Foc Specifies the field oriented control object.
 *
 * @return Returns the Iq current limit
 * @see Foc_SetIqLimit().
 * @ingroup motor_control_foc
 */
StdReal Foc_GetIqLimit(TFoc *foc)
{
    return foc->limit.imag;
}

/** @brief Set the Id current limit.
 *
 * This function sets the Id current limit.
 *
 * @param Foc Specifies the field oriented control object.
 * @param Limit Specifies Id current limit.
 *
 * @return none
 * @see Foc_GetIdLimit().
 * @ingroup motor_control_foc
 */
void Foc_SetIdLimit(TFoc *foc, StdReal limit)
{
    foc->limit.real = limit;
}

/** @brief Return the Id current limit.
 *
 * This function returns the Id current limit.
 *
 * @param Foc Specifies the field oriented control object.
 *
 * @return Returns the Id current limit
 * @see Foc_SetIdLimit().
 * @ingroup motor_control_foc
 */
StdReal Foc_GetIdLimit(TFoc *foc)
{
    return foc->limit.real;
}

/** @brief Set the Modulation Index limit.
 *
 * This function sets the limit of Modulation Index.
 *
 * @param Foc Specifies the field oriented control object.
 * @param Limit Specifies Modulation Index limit.
 *
 * @return none
 * @see Foc_GetModIndexLimit().
 * @ingroup motor_control_foc
 */
void Foc_SetModIndexLimit(TFoc *foc, StdReal limit)
{
    foc->limitAmpl = limit;
}

/** @brief Return the Modulation Index limit.
 *
 * This function returns the limit of Modulation Index.
 *
 * @param Foc Specifies the field oriented control object.
 *
 * @return Returns the Modulation Index limit
 * @see Foc_SetModIndexLimit().
 * @ingroup motor_control_foc
 */
StdReal Foc_GetModIndexLimit(TFoc *foc)
{
    return foc->limitAmpl;
}

/** @brief Reset the FOC PI controllers.
 *
 * The PiId and PiIq parameters are set to default values by Pic_Reset()
 *
 * @param Foc Specifies the field oriented control object.
 *
 * @return None.
 * @ingroup motor_control_foc
 */
void Foc_Reset(TFoc *foc)
{
    Pic_Reset(&foc->piId);
    Pic_Reset(&foc->piIq);

   foc->ref.imag = 0;
   foc->ref.real = 0;

   foc->Msg_ref.imag = 0;
   foc->Msg_ref.real = 0;

   foc->incre_ref_max.imag = 0;
   foc->incre_ref_max.real = 0;

   foc->torque_ref = 0;

   foc->vdq_ref.imag = 0;
   foc->vdq_ref.real = 0;

   foc->nfo_mdq.imag = 0;
   foc->nfo_mdq.real = 0;

   foc->g_Vdq.imag   = 0;
   foc->g_Vdq.real   = 0;
}
