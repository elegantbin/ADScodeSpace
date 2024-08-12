/*
 * MotorSWC.h
 *
 *  Created on: 18.07.2023
 *
 */

#ifndef _MOTOR_SWC_H__
#define _MOTOR_SWC_H__
#include "Platform_Types.h"
#include "Compilers.h"


#define MOTOR_DIAG_CODE_OVER_TEMPERATURE      (0x00000001)
#define MOTOR_DIAG_CODE_STARTUP_FAIL          (0x00000002)
#define MOTOR_DIAG_CODE_STALL_FAIL            (0x00000004)
#define MOTOR_DIAG_CODE_CURRENT_FAIL          (0x00000008)
#define MOTOR_DIAG_CODE_VLOTAGE_FAIL          (0x00000010)
#define MOTOR_DIAG_CODE_UPDATAPOSITION_FAIL   (0x00000020)
#define MOTOR_DIAG_CODE_REALPOSITION_FAIL     (0x00000040)
#define MOTOR_DIAG_CODE_VELOCITY_MAX_FAIL     (0x00000080)

#define  K_VOLTAGE_LIMIT_MAX         (58)
#define  K_VOLTAGE_LIMIT_MIN         (38)

#define  K_CURRENT_LIMIT_MAX         (230)

typedef enum
{
  MOTOR_STATE_STOP,
  MOTOR_STATE_STARTUP,
  MOTOR_STATE_RUNNING,
  MOTOR_STATE_FAIL,
  MOTOR_STATE_HOLDING_POSITION

}enMotorState;

typedef enum
{
    K_ROT_DIR_FBK_STOP,
    K_ROT_DIR_FBK_CW,
    K_ROT_DIR_FBK_CCW

}enMotor_RotationDirState_fbk;

typedef enum
{
    K_ROT_DIR_UNKNOWN,
    K_ROT_DIR_CW,
    K_ROT_DIR_CCW

}enMotorRotationDir;


typedef enum
{
  MOTOR_CMD_STOP,
  MOTOR_CMD_START_CCW,
  MOTOR_CMD_START_CW,

  MOTOR_CMD_REINIT     = 0x08
}enMotorCmd;


typedef enum
{
  LOOP_CMD_SPEED=1,
  LOOP_CMD_CURRENT,
  LOOP_CMD_POSITION,
  LOOP_CMD_DOUBLE_SPPED_CURRENT


}MotorLoopCmd;

typedef enum
{
  LOOP_MODE_SPEED=1,
  LOOP_MODE_CURRENT,
  LOOP_MODE_POSITION,
  LOOP_MODE_DOUBLE_SPPED_CURRENT

}MotorLoopMode;

typedef struct
{
    enMotorState state;
    enMotorRotationDir rot_dir;
    enMotor_RotationDirState_fbk   rot_dir_fbk;
    uint32  u32DiagCode;
    uint16   testcount;
    uint16   second_speed;

    enMotorCmd cmd;
    MotorLoopCmd  loop_cmd;
    MotorLoopMode loop_mode;
    uint16     Refspeed;
    uint16     RefCurrent;
    uint8      RefTorque;
    uint16     RefPosition;
    sint16     RPM_s16MechSpeed;
    float32      CurrentU_BUS;
    float32      CurrentV_BUS;
    float32      CurrentW_BUS;
    uint8       Voltage_BUS;
}Bldc_Motor;

typedef struct
{
    uint8  Step_offset_CW;
    uint8  Step_offset_CCW;
    uint8  Zero_offset_CW;
    uint8  Zero_offset_CCW;
    uint8  Offset_Write_Enable;

    uint8  MotorType;
    uint8  Type_Write_Enable;

    uint16  Speed_KI;
    uint16  Speed_KP;
    uint16  Speed_KD;
    uint8   Speed_KPI_Write_Enabel;

    uint16  Current_KI;
    uint16  Current_KP;
    uint16  Current_KD;
    uint8   Current_KPI_Write_Enabel;
}Bldc_Calibration;

typedef union
{
   float actual;
   uint8 bytes_f[4];
}FloatBytes;

IFX_EXTERN Bldc_Motor g_bldc;
IFX_EXTERN FloatBytes g_floatbytes;
IFX_EXTERN Bldc_Calibration g_calibration;

void MotorControl_init(void);

void MotorDemoControl_Runnable(void);
void MotorCalibration_Runnable(void);

void MotorStallCheck_Runnable(void);

void MotorVelocityControl_Runnable(void);
void Over_Temperature_Detect(void);

void MotorRPM_Check(void);
void Motor_VlotageBus_Check(void);
void MotorPhaseCurrent_Check(void);
void RealPos_ValidCheck(void);

#endif /* _MOTOR_SWC_H__ */
