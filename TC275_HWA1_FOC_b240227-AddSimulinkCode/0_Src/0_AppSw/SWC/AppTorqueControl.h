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
#include "MotorDrive/Current_Controller/PMSM_CurrentControl_System.h"

#include "IfxGtm_Tom_timer.h"
#include "IfxGtm_Tom_PwmHl.h"
#include "GTM_TOM_3_Phase_Inverter_PWM.h"
#include "Vadc_VIT.h"


typedef uint8 AppMotor_InverterFault;                /**< @brief Inverter status  */
#define INVERTER_NO_ERROR           (0x0)
#define INVERTER_FAULT_U            (0x1)
#define INVERTER_FAULT_V            (0x2)
#define INVERTER_FAULT_W            (0x4)


typedef uint32 TimerVal;        /**< \brief Used in timer values */


/** @brief Inverter object definition.
 */
typedef struct
{
    Pwm3PhaseOutput *pwm;        		/**< @brief PWM object */
	TimerVal			channels[3];
	TimerVal			adcTrigger[1];
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

    boolean direction;
    boolean calon;
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


/** @brief Diagnositcs information.
 */
typedef struct
{
    boolean swapped;                           /**< @brief if true and in @ref DIAG mode, the phases A and B are swapped (FALSE: ABC; TRUE: ACB)  */
    uint16 rotate;                           /**< @brief range[0,2] (for Swapped=FALSE => 0: ABC; 1: CAB, 2: BCA. for Swapped=TRUE => 0: ACB; 1: BAC, 2: CBA.)  */
    boolean focControlEnabled;                 /**< @brief Specifies if the F.O.C. is enabled or disabled */
    boolean FwcEnabled;                         /**< @brief Specifies if the FOC with field weakening control is enabled or disabled */
    boolean encoderEnabled;                    /**< @brief Specifies if the position sensor is enabled */
    boolean vectorFixedEnable;
    boolean SpeedCurrentLoopEnable;
    uint16 maxTurn;                          /**< @brief Specifies that the control should stop after the MaxTurn have been detected. In @ref DIAG mode only. */
    sint32 electricalAngleOffset;
    sint32 electricalAngleSensor;

    sint16 vectorFixedAngle;
    boolean sync_topzero;
    uint32  u32DiagCode;
}AppMotor_Diag;

/** @brief Open loop information.
 */
typedef struct
{
    float32 amplitude;                    /**< @brief Vector amplitude in open loop mode. Range=[0,1] */
    uint32 electricalAngleDelta;          /**< @brief Delta angle added. Format Q16.16 */
    uint32 electricalAngle;               /**< @brief Open loop electrical angle. */
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

typedef struct
{
    AppVadc_AnalogInput_1 *currentA;        /**< @brief Analog input Current phase A*/
    AppVadc_AnalogInput_1 *currentB;        /**< @brief Analog input Current phase B*/
    AppVadc_AnalogInput_1 *currentC;        /**< @brief Analog input Current phase C*/

    AppVadc_AnalogInput_1 *sensorOffset;       /**< @brief Analog input sensorOffset*/
    boolean currentTableFull;
}AppMotor_AnalogCurrentInputs;

typedef enum
{
    K_ROT_DIR_CW,
    K_ROT_DIR_CCW
}enMotorRotationDir;


/** @brief Motor object definition.
 */
typedef struct
{
	AppMotor_Inverter inverter;                     /**< @brief Inverter object */
	T3Phase	currents;
	AppMotor_Control control;                       /**< @brief Motor control parameters */

	AppMotor_AnalogCurrentInputs analogCurrentInputs;        /**< @brief analog Inputs Object*/
	AppMotor_Calibration calibration;               /**< @brief Calibration object */
	AppMotor_MotorParam motor_param;                      /**< @brief Motor parameters */
	AppMotor_Diag diag;                             /**< @brief Diagnostics object */

	AppMotor_OpenLoop openLoop;                     /**< @brief Open loop object */

	AppMotor_vfControl vfControl;					/**< @brief vf Control obkect used for sensorless FOC*/
	uint32 controlStep;

	TTime time[2];
	float32 speed;
    enMotorRotationDir rot_dir;

    uint8  test_count1;
    uint8  test_count2;
}AppMotor_Motor;

typedef union
{
   float actual;
   uint8 bytes_f[4];
}FloatBytes;

IFX_EXTERN FloatBytes g_floatbytes;
IFX_EXTERN AppMotor_Motor	g_motor;

IFX_EXTERN sint16  TorqueControl_updateOpenLoopPosition(void);
IFX_EXTERN void ZeroCurrentSensor(AppMotor_Motor *motor,AppVadc_AnalogInput_1 *currentU, AppVadc_AnalogInput_1 *currentV, AppVadc_AnalogInput_1 *currentW,AppVadc_AnalogInput_1 *offset);
IFX_EXTERN void AppTorqueControl_initControl(AppMotor_Motor* motor, uint32 pwmFrequency);
IFX_EXTERN void TorqueControl_FocStep(AppMotor_Motor* motor, T3Phase *currents, StdReal vdc);
IFX_EXTERN void  TorqueControl_startMotor(AppMotor_Motor* motor);
IFX_EXTERN void  TorqueControl_stopMotor(AppMotor_Motor* motor);


IFX_EXTERN sint16 TorqueControl_updateEncoderPosition(void);
IFX_EXTERN sint16 sensorposition;

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

IFX_INLINE Pwm3PhaseOutput* TorqueControl_get3ChannelPwm(void)
{
    return(&g_pwm3PhaseOutput);
}

IFX_INLINE TimerVal TorqueControl_getPeriod(Pwm3PhaseOutput *pwm)
{
    return(pwm->tmr.base.period);
}
/** @brief get the duty cycles of phases .
 *
 *	order 0 = U, 1 = V,2 = W
 * @ingroup app_analog_inputs
 */
IFX_INLINE void getPhaseDutyCycles(AppMotor_Motor *motor,float32 *ton)
{
	uint32 period = TorqueControl_getPeriod(motor->inverter.pwm);
	ton[0] = (float32)motor->inverter.channels[0]/period;
	ton[1] = (float32)motor->inverter.channels[1]/period;
	ton[2] = (float32)motor->inverter.channels[2]/period;
}
#endif /* APPTORQUECONTROL_H_ */
