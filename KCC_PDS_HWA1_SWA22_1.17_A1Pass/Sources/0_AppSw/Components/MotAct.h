/*
 * Drive_Motor.h
 *
 *  Created on: 2023Äê12ÔÂ1ÈÕ
 *      Author: Administrator
 */

#ifndef MOTORACTATOR_H_
#define MOTORACTATOR_H_

#include "Cpu.h"
#include <stdio.h>
#include <stdint.h>
#include "Ostypedefs.h"


#define MOTOR_WAKE()  	PINS_DRV_WritePin(PTD,3,1)
#define KL_30_ENABLE() 	PINS_DRV_WritePin(PTD,7,1)
#define MOTOR_SLEEP()   PINS_DRV_WritePin(PTD,3,0)
#define KL_30_DISABLE() PINS_DRV_WritePin(PTD,7,0)

#define PWM_DUTY_PERIOD (5000)
#define PWM_DUTY_PECENT (PWM_DUTY_PERIOD/100)
#define PWM_DUTY_MIN    ((2)*PWM_DUTY_PECENT)
#define PWM_DUTY_MAX    ((95)*PWM_DUTY_PECENT)

#define K_DEFAULT_MOTOR_DUTY   (PWM_DUTY_PERIOD-(40)*PWM_DUTY_PECENT)
#define K_DEFAULT_MOTOR_STOP_DUTY   (PWM_DUTY_PERIOD)

#define K_STARUP_DELAY_COUNT_MIN (100)
#define K_STARUP_DELAY_COUNT_OPEN (100)
#define K_STARUP_DELAY_COUNT_CLOSE (100)
#define K_STARUP_DELAY_COUNT_MAX (300)

#define K_MOT_SLOWDOWN_COUNT   (300)
#define K_MOT_SLOWDOWN_DELAY_COUNT  (0)
#define K_MOT_SLOWDOWN_DELTA        ((3))

#define K_MOT_STOP_COUNT_MAX (60000)
#define K_MOT_RUNNING_TIMEOUT (60000)



typedef enum
{

  MOTOR_DIR_UNKOWN,
  MOTOR_DIR_CW,
  MOTOR_DIR_CCW

}motor_dir_t;



typedef  enum enMotCmd
{
	MOTOR_CMD_NOCMD,
	MOTOR_CMD_STOP,
	MOTOR_CMD_START_CW,
	MOTOR_CMD_START_CCW

}MotCmd_t;

typedef  enum enMotState
{
	MOTOR_STATUE_STOP,
	MOTOR_STATUE_STARTUP,
	MOTOR_STATUE_RUNNING,
	MOTOR_STATUE_SLOWDOWN,
	MOTOR_STATUE_EMERGENCY

}MotStat_t;


typedef struct
{
	MotCmd_t    mot_cmd;
	MotStat_t	state;
	uint32_t    u32Speed;

	motor_dir_t dir_cmd;
	motor_dir_t dir_fbk;
	int16_t    duty;

	uint16_t    u16SLowdownCount;
	uint16_t    u16MotStopCount;
	uint16_t    u16MotRunningCount;
	uint16_t    u16StartupCount;

}MotorActator_Control;

extern MotorActator_Control g_motor;
extern int16_t g_i16DoorDutyPercent;

void MotorActator_Init(void);
void MotorActator_Start(motor_dir_t dir);
void MotorActator_Stop(void);
void MotorActator_StateMachine(void);
void MotorActator_SlowDown(void);
void MotorActator_UpdateDuty(int16_t i16Duty);
#endif /* MOTORACTATOR_H_ */
