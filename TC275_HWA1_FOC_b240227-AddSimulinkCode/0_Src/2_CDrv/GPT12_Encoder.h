

#ifndef _ZF_GPT12_H__
#define _ZF_GPT12_H__

#include "Cpu/Std/Ifx_Types.h"
#include "IfxStdIf.h"
#include "IfxGpt12_reg.h"
#include "IfxGpt12_IncrEnc.h"

#define K_ENCODER_TOTAL_COUNTS_PER_MECH_CIRCLE        (4096)          /* Encoder counters a motor mechanical circle   */
#define K_ENCODER_TOTAL_COUNTS_PER_CYCLE_MAX  (K_ENCODER_TOTAL_COUNTS_PER_MECH_CIRCLE+50)
#define K_ENCODER_TOTAL_COUNTS_PER_CYCLE_MIN  (K_ENCODER_TOTAL_COUNTS_PER_MECH_CIRCLE-50)

#define  ENCODER_PINA         (IfxGpt120_T2INB_P33_7_IN)
#define  ENCODER_PINB         (IfxGpt120_T2EUDB_P33_6_IN)
#define  ENCODER_PINZ         (IfxGpt120_T4EUDB_P33_5_IN)

IFX_EXTERN sint16 g_Encoder_RawPosition;
IFX_EXTERN IfxGpt12_IncrEnc  g_IncrEnc;

void GPT12_EncoderInit(void);
sint16 GPT12_EncoderUpdatePosition(void);
void GPT12_EncoderReset(void);
sint16 EcoderPosition_EleAgle(void);

#endif /* _ZF_GPT12_H__ */
