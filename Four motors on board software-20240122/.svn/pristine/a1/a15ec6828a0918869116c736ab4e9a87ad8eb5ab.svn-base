/*
 * AppTorqueControl.h
 *
 *  Created on: 25.07.2012
 *
 */

#ifndef APPTORQUECONTROL_H_
#define APPTORQUECONTROL_H_

#include "Cpu/Std/IfxCpu_Intrinsics.h"


#include "MotorDrive/Foc.h"
#include "MotorDrive/SpaceVectorModulation.h"

#include "IfxGtm_Tom_Timer.h"
#include "IfxGtm_Tom_PwmHl.h"
#include "AppVadc.h"
#include "AppPositionAquisition.h"




typedef uint8 AppMotor_InverterFault;                /**< @brief Inverter status  */
#define INVERTER_NO_ERROR           (0x0)
#define INVERTER_FAULT_U            (0x1)
#define INVERTER_FAULT_V            (0x2)
#define INVERTER_FAULT_W            (0x4)

typedef struct
{
    IfxGtm_Tom_Timer tmr;
    IfxGtm_Tom_PwmHl ch;
}AppPwmDriver_3ChPwm;

/** @brief Inverter object definition.
 */
typedef struct
{
	AppPwmDriver_3ChPwm *pwm;        		/**< @brief PWM object */
	Ifx_TimerValue			channels[3];
	Ifx_TimerValue			adcTrigger[1];
	uint8				sector;
	AppMotor_InverterFault faultStatus;     /**< @brief Current fault status from inverter */
}AppMotor_Inverter;


typedef enum
{
	AppMotorControlState_idle = 0,
	AppMotorControlState_vf,
	AppMotorControlState_foc
}AppMotorControlState;
/** @brief Calibration data.
 */
typedef struct
{
    sint32 currentA;                      /**< @brief Current phase A raw sum */
    sint32 currentB;                      /**< @brief Current phase B raw sum */
    sint32 currentC;                      /**< @brief Current phase C raw sum */
    sint32 offset;						  /**< @brief Offset if BridgeDriver has a seperate Offset output like: TLE9180;*/
    sint32 count;                            /**< @brief Calibration index */
}AppMotor_Calibration;

/** @brief Motor control parameters.
 */
typedef struct
{
    volatile boolean run;                      /**< @brief Run flag (read only): TRUE the motor is running. FALSE, the motor is stopped. */
    boolean start;                             /**< @brief If set to TRUE the motor is started */
    boolean stop;                              /**< @brief If set to TRUE, the motor is stopped */
    boolean hadEmergency;                      /**< @brief Emergency flag. FALSE: No emergency occured. TRUE: An emergency event occured. */
    boolean demo;
    boolean demorun;
    boolean demostop;
    boolean calon;                             /* Calibration ON */
    AppMotorControlState	state;					   /**< @brief control state */
    sint16 electricalAngle;                    /**< @brief Actual electrical angle position Q16.16 */
    TFoc foc;                                  /**< @brief Field Oriented Control object */
}AppMotor_Control;

/** @brief Motor parameters.
 */
typedef struct
{
    uint8 polePair;                       /**< @brief Motor pole pair count */
    float32 r;                             /**< @brief Motor phase resistance in Ohm */
    float32 l;                             /**< @brief Motor Phase inductance in H Q0.15*/
}AppMotor_MotorParam;
/** @brief Motor Analog input list.
 */

typedef struct
{
	AppVadc_AnalogInput_1 *currentA;        /**< @brief Analog input Current phase A*/
	AppVadc_AnalogInput_1 *currentB;        /**< @brief Analog input Current phase B*/
	AppVadc_AnalogInput_1 *currentC;        /**< @brief Analog input Current phase C*/
	AppVadc_AnalogInput_1 *sensorOffset;       /**< @brief Analog input sensorOffset*/
	AppVadc_AnalogInput_1 *vdc;            /**< @brief Analog input DC link voltage*/
}AppMotor_MotorAnalogInputs;

/** @brief Diagnositcs information.
 */
typedef struct
{
    boolean swapped;                           /**< @brief if true and in @ref DIAG mode, the phases A and B are swapped (FALSE: ABC; TRUE: ACB)  */
    uint16 rotate;                           /**< @brief range[0,2] (for Swapped=FALSE => 0: ABC; 1: CAB, 2: BCA. for Swapped=TRUE => 0: ACB; 1: BAC, 2: CBA.)  */
    boolean focControlEnabled;                 /**< @brief Specifies if the F.O.C. is enabled or disabled */
    boolean encoderEnabled;                    /**< @brief Specifies if the position sensor is enabled */
    uint16 maxTurn;                          /**< @brief Specifies that the control should stop after the MaxTurn have been detected. In @ref DIAG mode only. */
    sint32 electricalAngleOffset;
    sint32 electricalAngleSensor;
    boolean sync_topzero;
}AppMotor_Diag;

/** @brief Open loop information.
 */
typedef struct
{
    float32 amplitude;                     /**< @brief Vector amplitude in open loop mode. Range=[0,1] */
    uint32 electricalAngleDelta;          /**< @brief Delta angle added. Format Q16.16 */
    uint32 electricalAngle;                  /**< @brief Open loop electrical angle. */
}AppMotor_OpenLoop;

typedef struct
{
	uint32 counter;
	uint32 slewAngle;// = 50;
	sint32 slewAngleLimit;
	float32 slewVoltage;// = 0.00022;
	float32 ukLimit;
	float32 speedThreshold;
	boolean changeState;
}AppMotor_vfControl;



/** @brief Motor object definition.
 */
typedef struct
{
	AppMotor_Inverter inverter;                     /**< @brief Inverter object */
	PositionAcquisition sensors;					/**< @brief Position sensors*/

	T3Phase	currents;
	StdReal dcCurrent;

	AppMotor_Control control;                       /**< @brief Motor control parameters */
	AppMotor_MotorAnalogInputs analogInputs;		/**< @brief analog Inputs Object*/
	AppMotor_Calibration calibration;               /**< @brief Calibration object */
	AppMotor_MotorParam motor;                      /**< @brief Motor parameters */
	AppMotor_Diag diag;                             /**< @brief Diagnostics object */
	AppMotor_OpenLoop openLoop;                     /**< @brief Open loop object */

	AppMotor_vfControl vfControl;					/**< @brief vf Control obkect used for sensorless FOC*/

	uint32 controlStep;
	TTime time[2];
	float32 speed;
}AppMotor_Motor;


IFX_EXTERN AppMotor_Motor	g_motor;


IFX_EXTERN void ZeroCurrentSensor(AppMotor_Motor *motor,AppVadc_AnalogInput_1 *currentU, AppVadc_AnalogInput_1 *currentV, AppVadc_AnalogInput_1 *currentW,AppVadc_AnalogInput_1 *offset);
IFX_EXTERN void AppTorqueControl_initControl(AppMotor_Motor* motor, uint32 pwmFrequency);
IFX_EXTERN void TorqueControl_FocStep(AppMotor_Motor* motor, T3Phase *currents, StdReal vdc);
IFX_EXTERN boolean TorqueControl_updateCurrent(AppMotor_Motor* motor, float32 current, boolean step);
IFX_EXTERN void  TorqueControl_startMotor(AppMotor_Motor* motor);
IFX_EXTERN void TorqueControl_stateMachine(AppMotor_Motor* motor, sint32 counter);
IFX_EXTERN void  TorqueControl_stopMotor(AppMotor_Motor* motor);



/** @brief Check if the current sensor offsets have been calibrated.
 *
 * @retval TRUE Returns TRUE if the current sensors have been calibrated.
 * @retval FALSE Returns FALSE if the current sensors have not been calibrated.
 *
 * @ingroup app_analog_inputs
 */
IFX_INLINE boolean IsCurrentSensorCalibrated(AppMotor_Motor *motor)
{
    return (motor->calibration.count == 0) ? TRUE : FALSE;
}

/** @brief get the duty cycles of phases .
 *
 *	order 0 = U, 1 = V,2 = W
 * @ingroup app_analog_inputs
 */
IFX_INLINE void getPhaseDutyCycles(AppMotor_Motor *motor,float32 *ton)
{
	//uint32 period = AppPwmDriver_getPeriod(motor->inverter.pwm);
    uint32 period =  2500;
	ton[0] = (float32)motor->inverter.channels[0]/period;
	ton[1] = (float32)motor->inverter.channels[1]/period;
	ton[2] = (float32)motor->inverter.channels[2]/period;
}


#endif /* APPTORQUECONTROL_H_ */
