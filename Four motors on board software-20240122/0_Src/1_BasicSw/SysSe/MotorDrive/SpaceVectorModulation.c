/**
 * @file SpaceVectorModulation.c
 * @brief Space vector modulation.
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

//------------------------------------------------------------------------------

#include <Arith.StdReal.h>
#include <SpaceVectorModulation.h>
#include <Tables.h>
//------------------------------------------------------------------------------
#if !defined(CFG_OPTIMIZE) || (CFG_OPTIMIZE == 0)
/** @brief Space vector modulation.
 *
 * This function returns the "on time" in ticks corresponding to the input vector m for the 3 output channels.
 * The produced voltage is \f$ V = 2 . m . \frac{V_{dc}}{\pi} \f$
 *
 * @param m Specifies the modulation index as a vector. The limit between the continuous and discontinuous mode is defined as follow:
 *  - Continuous mode: \f$ 0 \le \left | m \right | \le 0.906 \f$
 *  - Saturation mode: \f$ 0.906 \ll  \left | m \right | \f$
 * @param Period Specifies the PWM period value in ticks.
 * @param Channels This parameter is filled in by the function with the corresponding "on time" for the 3 output channels. The unit is ticks.
 *
 * @return none
 * @ingroup motor_control_svpwm
 */

#if(1)
uint8 SpaceVectorModulation(CplxStdReal m, Ifx_TimerValue period, Ifx_TimerValue *  tOn)
{
    uint8 sector;
    StdReal x;
    Ifx_TimerValue tk, tk1;
    Ifx_TimerValue ts, tm, tb;
    Ifx_TimerValue halfPeriod;

    // determination of the sector
    x = __mul_rSR_iSR_iSR(m.imag, (float32)OneOverSqrt3_SR);
    if (m.imag > 0)
    {   // m.imag>0
        if (m.real > 0)
        {   // Quadrant 1
            if (x < m.real) {sector=0;} else    {sector=1;}
        }
        else
        {   // Quadrant 2
            if (x < __negs_rSR_iSR(m.real)) {sector=2;} else    {sector=1;}
        }
    }
    else
    {   // m.imag<0
        if (m.real < 0)
        {   // Quadrant 3
            if (x < m.real) {sector=4;} else    {sector=3;}
        }
        else
        {   // Quadrant 4
            if (x < __negs_rSR_iSR(m.real)) {sector=4;} else    {sector=5;}
        }
    }
    // Sector range is the Sector number minus 1 (from 0 to 5)
    // Calcul of Tk and Tk+1, k is the sector number
    // Tk=      sin(k)*m.Re     -   Cos(k)*m.Im
    // Tk+1=    Cos(k-1)*m.Im   -   Sin(k-1)*m.Re
    tk  = __mul_r16I_iSR_i16I(__msubms_rSR_iSR_iSR_iSR_iSR(sinCosVector[((sector + 1)*2)+0], m.real, sinCosVector[((sector + 1)*2)+1], m.imag), (sint16)period);
    tk1 = __mul_r16I_iSR_i16I(__msubms_rSR_iSR_iSR_iSR_iSR(sinCosVector[((sector    )*2)+1], m.imag, sinCosVector[((sector    )*2)+0], m.real), (sint16)period);

    if ((sector & 0x1) != 0)
    {
    	Ifx_TimerValue temp;
        temp = tk;
        tk = tk1;
        tk1 = temp;
    }

    halfPeriod = period >> 1;
//    ts = __saturate((halfPeriod  - tk) - tk1, 0, period);
//    tm = __saturate((halfPeriod  - tk) + tk1, 0, period);
//    tb = __saturate((halfPeriod  + tk) + tk1, 0, period);
    ts = __saturate((halfPeriod  - tk) - tk1, 0, period);
    tm = __saturate((halfPeriod  - tk) + tk1, 0, period);
    tb = __saturate((halfPeriod  + tk) + tk1, 0, period);

    switch (sector)
    {
        case 0:
        	tOn[0] = tb;
        	tOn[1] = tm;
        	tOn[2] = ts;
            break;
        case 1:
        	tOn[0] = tm;
        	tOn[1] = tb;
        	tOn[2] = ts;
            break;
        case 2:
        	tOn[0] = ts;
        	tOn[1] = tb;
        	tOn[2] = tm;
            break;
        case 3:
        	tOn[0] = ts;
        	tOn[1] = tm;
        	tOn[2] = tb;
            break;
        case 4:
        	tOn[0] = tm;
        	tOn[1] = ts;
        	tOn[2] = tb;
            break;
        case 5:
        	tOn[0] = tb;
        	tOn[1] = ts;
        	tOn[2] = tm;
            break;
        default:
            break;
    }


    return(sector);
}
#else
uint8 SpaceVectorModulation(CplxStdReal m, Ifx_TimerValue period, Ifx_TimerValue *  tOn,Ifx_TimerValue *  tshift)
{
    uint8 sector;
    StdReal x;
    Ifx_TimerValue tk, tk1,shift = 0;
    Ifx_TimerValue ts, tm, tb;
    Ifx_TimerValue halfPeriod;

    // determination of the sector
    x = __mul_rSR_iSR_iSR(m.imag, (float32)OneOverSqrt3_SR);
    if (m.imag > 0)
    {   // m.imag>0
        if (m.real > 0)
        {   // Quadrant 1
            if (x < m.real) {sector=0;} else    {sector=1;}
        }
        else
        {   // Quadrant 2
            if (x < __negs_rSR_iSR(m.real)) {sector=2;} else    {sector=1;}
        }
    }
    else
    {   // m.imag<0
        if (m.real < 0)
        {   // Quadrant 3
            if (x < m.real) {sector=4;} else    {sector=3;}
        }
        else
        {   // Quadrant 4
            if (x < __negs_rSR_iSR(m.real)) {sector=4;} else    {sector=5;}
        }
    }
    // Sector range is the Sector number minus 1 (from 0 to 5)
    // Calcul of Tk and Tk+1, k is the sector number
    // Tk=      sin(k)*m.Re     -   Cos(k)*m.Im
    // Tk+1=    Cos(k-1)*m.Im   -   Sin(k-1)*m.Re
    tk  = __mul_r16I_iSR_i16I(__msubms_rSR_iSR_iSR_iSR_iSR(sinCosVector[((sector + 1)*2)+0], m.real, sinCosVector[((sector + 1)*2)+1], m.imag), (sint16)period);
    tk1 = __mul_r16I_iSR_i16I(__msubms_rSR_iSR_iSR_iSR_iSR(sinCosVector[((sector    )*2)+1], m.imag, sinCosVector[((sector    )*2)+0], m.real), (sint16)period);

    if ((sector & 0x1) != 0)
    {
    	Ifx_TimerValue temp;
        temp = tk;
        tk = tk1;
        tk1 = temp;
    }
    if(tk < 10)
    {
    	if(tk1 > 10)
    	{
    		shift = (10 - tk);
    	}else
    	{
    		shift = 0;
    	}
    }
    if(tk1<10)
    {
		if(tk > 10)
		{
			shift = (10 - tk1);
		}else
		{
			shift = 0;
		}
	}
//    tk = __maxf(tk,10);
//   tk1 = __maxf(tk1,10);

    halfPeriod = period >> 1;
    ts = __saturate((halfPeriod  - tk) - tk1, 0, period);
    tm = __saturate((halfPeriod  - tk) + tk1, 0, period);
    tb = __saturate((halfPeriod  + tk) + tk1, 0, period);

    switch (sector)
    {
        case 0:
        	tOn[0] = tb;
        	tOn[1] = tm;
        	tOn[2] = ts;
        	tshift[0] = 0;
        	tshift[1] = shift;
        	tshift[2] = 0;
            break;
        case 1:
        	tOn[0] = tm;
        	tOn[1] = tb;
        	tOn[2] = ts;
        	tshift[0] = shift;
			tshift[1] = 0;
			tshift[2] = 0;
            break;
        case 2:
        	tOn[0] = ts;
        	tOn[1] = tb;
        	tOn[2] = tm;
        	tshift[0] = 0;
			tshift[1] = 0;
			tshift[2] = shift;
            break;
        case 3:
        	tOn[0] = ts;
        	tOn[1] = tm;
        	tOn[2] = tb;
        	tshift[0] = 0;
        	tshift[1] = shift;
        	tshift[2] = 0;
            break;
        case 4:
        	tOn[0] = tm;
        	tOn[1] = ts;
        	tOn[2] = tb;
        	tshift[0] = shift;
			tshift[1] = 0;
			tshift[2] = 0;
            break;
        case 5:
        	tOn[0] = tb;
        	tOn[1] = ts;
        	tOn[2] = tm;
        	tshift[0] = 0;
			tshift[1] = 0;
			tshift[2] = shift;
            break;
        default:
            break;
    }
   	tOn[3] = tb;

    return(sector);
}
#endif

#endif
/** @brief Return the reference voltage.
 *
 * The reference voltage is \f$ V_{ref} = 2 . m . \frac{V_{dc}}{\pi} \f$
 *
 * @param m Specifies the modulation index as a vector.
 * @param Vdc Specifies the DC link voltage. The unit is arbitrary, the same unit will be returned by the function
 *
 * @return return the reference voltage. The unit is the same as the Vdc parameter
 * @ingroup motor_control_svpwm
 */
CplxStdReal SpaceVectorModulation_GetVoltages(CplxStdReal m, StdReal vdc)
{
    CplxStdReal vRef;
    StdReal factor = __mul_rSR_iSR_iSR(vdc, (float32)TwoOverPi_SR);
    vRef.real = __mul_rSR_iSR_iSR(m.real, factor);
    vRef.imag = __mul_rSR_iSR_iSR(m.imag, factor);
    return vRef;
}
