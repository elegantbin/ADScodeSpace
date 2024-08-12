/**
 * \file PosIf.c
 * \brief Position sensor interface
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
 *
 * $Revision: $1346.3
 * $Date: $2013-06-24 18:38:09 GMT
 *
 */

#include "PosIf.h"
#include "AppTorqueControl.h"

IFX_EXTERN AppMotor_Motor   g_motor;
IfxStdIf_Pos  stdPosIf;

IFX_EXTERN CONST_CFG IfxGpt12_IncrEnc_Config  cfg_PosIf_IncrEnc_Gpt12;      /**< \brief Details in Cfg_PosIf_IncrEnc_Gpt12.c */

void      PosIf_setOffset_base(PosIf *handle, PosIf_Raw offset);
PosIf_Raw PosIf_resetOffset_base(PosIf *handle);
void      PosIf_setupElAngleConst_base(PosIf *handle, sint32 motorPolePairs);
StdReal   PosIf_updateSpeed_base(PosIf *handle, boolean update);
PosIf_Raw PosIf_updatePosition_base(PosIf *handle);

const PosIf_Calls g_PosIf_Functions = {
    &PosIf_resetOffset_base,
    &PosIf_setOffset_base,
    &PosIf_setupElAngleConst_base,
    &PosIf_setupSpeedConst_base,
    &PosIf_updatePosition_base,
    &PosIf_updateSpeed_base,
};

void initPosIf(void)
{
    /** - Incremental encoder with GPT12 */
    IfxGpt12_enableModule(&MODULE_GPT120);
    IfxGpt12_setGpt1BlockPrescaler(&MODULE_GPT120, IfxGpt12_Gpt1BlockPrescaler_8);
    IfxGpt12_setGpt2BlockPrescaler(&MODULE_GPT120, IfxGpt12_Gpt2BlockPrescaler_4);

    IfxGpt12_IncrEnc_Config config;
    IfxGpt12_IncrEnc_initConfig(&config, &MODULE_GPT120);

    IfxGpt12_IncrEnc_Config const *ptrUserCfg = &cfg_PosIf_IncrEnc_Gpt12;
    config.base.offset                    = ptrUserCfg->base.offset;
    config.base.reversed                  = ptrUserCfg->base.reversed;
    config.base.periodPerRotation         = ptrUserCfg->base.periodPerRotation ;
    config.base.resolution                = ptrUserCfg->base.resolution;
    config.base.updatePeriod              = ptrUserCfg->base.updatePeriod;

    config.base.minSpeed                  = ptrUserCfg->base.minSpeed;
    config.base.maxSpeed                  = ptrUserCfg->base.maxSpeed;

    config.zeroIsrPriority                = ptrUserCfg->zeroIsrPriority;
    config.zeroIsrProvider                = ptrUserCfg->zeroIsrProvider;

    config.pinA                           = ptrUserCfg->pinA;
    config.pinB                           = ptrUserCfg->pinB;
    config.pinZ                           = ptrUserCfg->pinZ;
    config.pinMode                        = ptrUserCfg->pinMode;

    config.base.speedFilterEnabled        = ptrUserCfg->base.speedFilterEnabled;

    config.base.speedFilerCutOffFrequency = ptrUserCfg->base.maxSpeed,

    config.base.resolutionFactor          = ptrUserCfg->base.resolutionFactor;
    config.base.updatePeriod              = ptrUserCfg->base.updatePeriod;
    config.initPins                       = ptrUserCfg->initPins;

    /** - Incremental encoder with GPT12 */
    IfxGpt12_IncrEnc_init(&g_motor.sensors.encoder, &config);
#if 1
    if (config.pinA->timer == 2)
    {
      Ifx_GPT12 *gpt12  = config.module;

     //IfxGpt12_T2_setCaptureInputMode(gpt12,IfxGpt12_CaptureTriggerMode_risingEdge);
     // IfxGpt12_T2_setCaptureTriggerEnable(gpt12, TRUE);

      /* T4 Configuration */
      IfxGpt12_T4_setMode(gpt12, IfxGpt12_Mode_capture);
      IfxGpt12_T4_setCaptureInputMode(gpt12, IfxGpt12_CaptureInputMode_risingEdgeTxIN);
      IfxGpt12_T4_enableClearTimerT2(gpt12, TRUE);
      IfxGpt12_T4_enableClearTimerT3(gpt12, FALSE);

      IfxGpt12_T4_setInterruptEnable(gpt12, config.zeroIsrPriority != 0);
      IfxGpt12_T4_setRemoteControl(gpt12, IfxGpt12_TimerRemoteControl_off);
      IfxGpt12_T4_run(gpt12, IfxGpt12_TimerRun_stop);

      if (config.zeroIsrPriority!=0)
      {
         /* setup interrupt */
         volatile Ifx_SRC_SRCR *src = IfxGpt12_T4_getSrc(gpt12);
         IfxSrc_init(src, config.zeroIsrProvider, config.zeroIsrPriority);
         IfxSrc_enable(src);
      }
      //IfxGpt12_T4_run(gpt12, IfxGpt12_TimerRun_start);



  }
#endif
    //IfxGpt12_IncrEnc_stdIfPosInit(&board->stdIf.encoder, &board->driver.encoder);
    IfxGpt12_IncrEnc_stdIfPosInit(&stdPosIf, &g_motor.sensors.encoder);
    //IfxGpt12_IncrEnc_setOffset(&board->driver.encoder, board->motorConfiguration->encoder.offset);
}

/** \brief Initialize the position sensor interface
 * \note This function shall not be called directly by user's application */
void PosIf_init(PosIf *handle, const PosIf_Config *config)
{
    handle->functions         = &g_PosIf_Functions;
    handle->offset            = config->offset;
    handle->periodPerRotation = config->periodPerRotation;
    handle->resolution        = config->resolution;
    handle->reversed          = config->reversed;
    handle->motorPolePairs	  = config->motorPolePairs;
    PosIf_reset(handle);
}


PosIf_Raw PosIf_resetOffset_base(PosIf *handle)
{
    PosIf_Raw offset;

    offset = (handle->offset - handle->position);
    PosIf_setOffset(handle, offset);

    return handle->offset;
}


void PosIf_setOffset_base(PosIf *handle, PosIf_Raw offset)
{
    handle->offset = offset;
}


void PosIf_setupSpeedConst_base(PosIf *handle)
{
    handle->speedConst = 1.0 / handle->periodPerRotation;
}


void PosIf_setupElAngleConst_base(PosIf *handle, sint32 motorPolePairs)
{
    handle->elAngleConst = (float32)motorPolePairs *
                           ((float32)POSIF_ANGLE_RANGE / (handle->periodPerRotation * handle->resolution));
}


StdReal PosIf_updateSpeed_base(PosIf *handle, boolean update)
{
    /* Should be overridden by implementor module */
    (void)handle;               /* ignore compiler warning */
    (void)update;               /* ignore compiler warning */
    return 0.0;
}


PosIf_Raw PosIf_updatePosition_base(PosIf *handle)
{
    /* Should be overridden by implementor module */
    (void)handle;               /* ignore compiler warning */
    return 0;
}
