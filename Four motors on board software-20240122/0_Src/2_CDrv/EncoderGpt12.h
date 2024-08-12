

#ifndef _ZF_GPT12_H__
#define _ZF_GPT12_H__

#include "Cpu/Std/Ifx_Types.h"
#include "IfxStdIf.h"
#include "MotorMgtSwc.h"

#define  ENCODER_PINA         (IfxGpt120_T2INB_P33_7_IN)
#define  ENCODER_PINB         (IfxGpt120_T2EUDB_P33_6_IN)
#define  ENCODER_PINZ         (IfxGpt120_T4EUDB_P33_5_IN)

IFX_EXTERN sint16 Encoder_RawPosition;
IFX_EXTERN uint16 g_absMotSpeed;
IFX_EXTERN uint8 cycle_speed;
void EncoderInit(void);
sint16 EncoderUpdatePosition(void);

void EncoderReset(void);
void EncoderUpdateSpeed(void);
void  PreStartUp_UpdateSpeed(void) ;
enMotor_RotationDirState_fbk  RotDirectionFeedback(boolean pinA_Status, boolean pinB_Status);

#endif /* _ZF_GPT12_H__ */
