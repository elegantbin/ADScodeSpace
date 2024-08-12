/**
 * \file Cfg_PosIf_IncrEnc_Gpt12.c
 * \brief GPT12-based incremental encoder configuration data
 *
 * \license
 * You can use this file under the terms of the IFX License.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the IFX License for more details (IFX_License.txt).
 *
 * This file may be used, copied, and distributed, with or without modification, provided
 * that all copyright notices are retained; that all modifications to this file are
 * prominently noted in the modified file; and that this paragraph is not modified.
 *
 * \copyright Copyright (C) 2012 Infineon Technologies AG
 *
 * $Revision: 559 $
 * $Date: 2013-01-16 14:16:15 +0100 (Wed, 16 Jan 2013) $
 */

#include "Cfg_PosIf.h"
#include "ConfigurationIsr.h"
#include "Ifx_Cfg_FocControl.h"
#include "IfxGpt12_PinMap.h"
#include "Ifx_Types.h"
#define ENCODER_PULSE_PER_REVOLUTION (500)
/** Configuration for GPT12-based encoder interface
 * \ingroup configuration_pos_sensor */
CONST_CFG IfxGpt12_IncrEnc_Config cfg_PosIf_IncrEnc_Gpt12 =
{

	.base.offset			= CFG_ENCODER_OFFSET,
    .base.reversed          = TRUE,
    .base.periodPerRotation = 1,
    .base.resolution        = ENCODER_PULSE_PER_REVOLUTION*2, /* IfxGpt12_IncrEnc interface doubles the pulse count */
    .base.resolutionFactor  = IfxStdIf_Pos_ResolutionFactor_oneFold,
    .base.motorPolePairs	= CFG_M0_POLPAIR,

    .base.speedModeThreshold = 100.0/ 60 * 2 * IFX_PI,
    .base.updatePeriod       = 0.0001,
    .base.minSpeed           = 0.5 / 60 * 2 * IFX_PI,   // 0.5 rpm,
    .base.maxSpeed           = 10000 / 60 * 2 * IFX_PI, // 10000 rpm
    
    .pinA                     = &IfxGpt120_T2INB_P33_7_IN,//&IfxGpt120_T3EUDA_P02_7_IN, /**< \brief Encoder A signal. Should be connecting to T2 or T3 TxIN. See \ref IfxLld_Gpt12_pinmap "GPT12 pin map data" */
    .pinB                     = &IfxGpt120_T2EUDB_P33_6_IN,//&IfxGpt120_T3INA_P02_6_IN, /**< \brief Encoder B signal. Should be connecting to T2 or T3  TxEUD. See \ref IfxLld_Gpt12_pinmap "GPT12 pin map data" */
    .pinZ                     = &IfxGpt120_T4EUDB_P33_5_IN,//&IfxGpt120_T4INA_P02_8_IN, /**< \brief Encoder Z signal. Should be connecting to T4 TxIn for use with T3 and TxEUD (Ignore compiler type conflict warning) for use with T4.  See \ref IfxLld_Gpt12_pinmap "GPT12 pin map data" */
    .pinMode                  = IfxPort_InputMode_pullUp,//IfxPort_InputMode_noPullDevice,//


    .zeroIsrPriority           = INTERRUPT_ENCODER_GPT12_T4,
    .zeroIsrProvider           = IfxSrc_Tos_cpu0,
    .initPins                  = 1,
    .module                    = &MODULE_GPT120

};
