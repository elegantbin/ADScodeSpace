/*
 * AppTorqueControl.c
 *
 *  Created on: 25.07.2012
 *  Revised on: 2023��12��01��
 *
 */


#include "AppTorquecontrol.h"
#include "_Utilities\Ifx_assert.h"

#include "Ifx_Cfg_FocControl.h"
#include "SysSe/MotorDrive/Tables.h"
#include "GPT12_Encoder.h"
#include "Torque_Calibration.h"
#include "App_VelocityControl.h"

//IFX_INLINE sint16  TorqueControl_updatePosition(void);
IFX_INLINE AppVadc_AnalogInput_1* TorqueControl_getCurrentPhaseU(void);
IFX_INLINE AppVadc_AnalogInput_1* TorqueControl_getCurrentPhaseV(void);
IFX_INLINE AppVadc_AnalogInput_1* TorqueControl_getCurrentPhaseW(void);
IFX_INLINE AppVadc_AnalogInput_1* TorqueControl_getCurrentOffset(void);
IFX_INLINE void TorqueControl_update3ChannelPwm(Pwm3PhaseOutput *pwm, TimerVal *tOn, TimerVal adcTon);


//IFX_INLINE sint16  TorqueControl_updateOpenLoopPosition(void);
//IFX_INLINE sint16 TorqueControl_updateEncoderPosition(void);

AppMotor_Motor	g_motor;

IFX_INLINE AppMotor_OpenLoop *App_GetOpenLoop(AppMotor_Motor* motor)
{
    // This function has been added because of a bug in the tasking compiler that generate load / store instructions with an offset bigger than 512
    return &motor->openLoop;
}


/** @brief Calibrate the current sensors offset.
 *
 * @return None.
 *
 * @ingroup app_analog_inputs
 */
void ZeroCurrentSensor(AppMotor_Motor *motor,AppVadc_AnalogInput_1 *currentU, AppVadc_AnalogInput_1 *currentV, AppVadc_AnalogInput_1 *currentW,AppVadc_AnalogInput_1 *offset)
{
// MAKE THE ROTOR IS NOT MOVING WHILE THE SENSOR IS CALIBRATING AND THAT THE INVERTER IS ON with m=0
    if (motor->control.run == FALSE && g_motor.speed == 0)
    {
        // Calibrate the current sensors offset
        motor->calibration.count--;

        motor->calibration.offset   +=  (sint32)offset->rawvalue;
        motor->calibration.currentA +=  (sint32)currentU->rawvalue;
        motor->calibration.currentB += (sint32)currentV->rawvalue;
        motor->calibration.currentC +=  (sint32)currentW->rawvalue;

        if (motor->calibration.count == 0)
        {
        	sint32 offsetU, offsetV, offsetW, lcl_offset;
        	sint32 tempdif0,tempdif1,tempdif2,tempdif3;

            // End of calibration
        	offsetU = motor->calibration.currentA / CFG_AN_I_CALIBRATION_COUNT;
        	offsetV = motor->calibration.currentB / CFG_AN_I_CALIBRATION_COUNT;
        	offsetW = motor->calibration.currentC / CFG_AN_I_CALIBRATION_COUNT;
        	lcl_offset = motor->calibration.offset / CFG_AN_I_CALIBRATION_COUNT;

            tempdif0 = lcl_offset - APPVADC_CFG_VMOTOR_OFFSET_NOM;
            if (tempdif0 < 0)
            {
                tempdif0 *= (-1);
            }
            tempdif1 = lcl_offset - offsetU;
            if (tempdif1 < 0)
            {
                tempdif1 *= (-1);
            }
            tempdif2 = lcl_offset - offsetV;
            if (tempdif2 < 0)
            {
                tempdif2 *= (-1);
            }
            tempdif3 = lcl_offset - offsetW;
            if (tempdif3 < 0)
            {
                tempdif3 *= (-1);
            }
            if(tempdif0 > 150 || tempdif1 > 100 || tempdif2 > 100||tempdif3 > 100) // 120mV at 5V and 12bit
        	{
        		motor->calibration.count = CFG_AN_I_CALIBRATION_COUNT;
        	    motor->calibration.currentA = 0;
        	    motor->calibration.currentB = 0;
        	    motor->calibration.currentC = 0;
                motor->calibration.offset = 0;
        	    motor->control.hadEmergency = TRUE;
        	}
			else
		    {
				currentU->offset = -currentU->gain * offsetU;
				currentV->offset = -currentV->gain * offsetV;
				currentW->offset = -currentW->gain * offsetW;
		    }
       }
    }
}



void AppTorqueControl_initControl(AppMotor_Motor* motor, uint32 pwmFrequency)
{
	LookUp_Init();

	// Setup Analog Channels
	motor->analogCurrentInputs.currentA      = TorqueControl_getCurrentPhaseU();
	motor->analogCurrentInputs.currentB      = TorqueControl_getCurrentPhaseV();
	motor->analogCurrentInputs.currentC      = TorqueControl_getCurrentPhaseW();
	motor->analogCurrentInputs.sensorOffset  = TorqueControl_getCurrentOffset();

    motor->analogCurrentInputs.currentTableFull = FALSE;

	motor->inverter.pwm                      = TorqueControl_get3ChannelPwm();

	{
	    TimerVal period;
        period = TorqueControl_getPeriod(motor->inverter.pwm);

        // Initialize PWM Channels
        motor->controlStep = 0;
        motor->inverter.channels[0] = period>>1;
        motor->inverter.channels[1] = period>>1;
        motor->inverter.channels[2] = period>>1;
        motor->inverter.adcTrigger[0] = period>>1;
	}

	motor->motor_param.l = CFG_M0_INDUCTANCE;
	motor->motor_param.r = CFG_M0_RESISTANCE;
	motor->motor_param.polePair = CFG_M0_POLPAIR;

	motor->calibration.count = CFG_AN_I_CALIBRATION_COUNT;

    // Init pi Controller for Iq and Id
    Foc_Init(&motor->control.foc);

//    Foc_SetIdLimit(&motor->control.foc, CFG_M0_ID_LIMIT	);
//    Foc_SetIqLimit(&motor->control.foc, CFG_M0_IQ_LIMIT	);

    Pic_SetKpKi_StdReal(&motor->control.foc.piId, CFG_M0_PI_ID_KP, CFG_M0_PI_ID_KI, 1.0/pwmFrequency, 0, 0);
    Pic_SetLimit(&motor->control.foc.piId,-CFG_M0_PI_ID_LIMIT_MAX,CFG_M0_PI_ID_LIMIT_MAX);

    Pic_SetKpKi_StdReal(&motor->control.foc.piIq, CFG_M0_PI_IQ_KP, CFG_M0_PI_IQ_KI, 1.0/pwmFrequency, 0, 0);
    Pic_SetLimit(&motor->control.foc.piIq,-CFG_M0_PI_IQ_LIMIT_MAX,CFG_M0_PI_IQ_LIMIT_MAX);

    /* Motor control setting */
    {
        motor->control.start = FALSE;
        motor->control.stop =  FALSE;
        motor->control.direction = K_MOT_DIR_CW;

        motor->control.hadEmergency = FALSE;
        motor->control.run = FALSE;
        motor->control.state = AppMotorControlState_foc;
    }

    /* Openloop parameters setting */
    {
        motor->openLoop.electricalAngleDelta = 1;
        motor->openLoop.electricalAngle = 0;
        motor->openLoop.amplitude = amplitude_openLoop;
    }

    {
     /* Zero pulse finder  */
        motor->diag.sync_topzero = FALSE;
        motor->diag.vectorFixedAngle = 0;

    /* Possible  Control Mode Setting:
     * ------------------------------------------------------------------------------------------------------------------
     * |          Control Mode            | * |          focControlEnabled         | * |        encoderEnabled          |      *
     * ------------------------------------------------------------------------------------------------------------------
     * |          FOC                     | * |          TRUE                      | * |        x                       |
     * ------------------------------------------------------------------------------------------------------------------
     * |          Encoder Pos OpenLoop    | * |          FALSE                     | * |        TRUE                    |
     * ------------------------------------------------------------------------------------------------------------------
     * |          PosSimulation OpenLoop  | * |          FALSE                     | * |        FALSE                   |
     * ------------------------------------------------------------------------------------------------------------------
     *
     * When selecting different coefficients, make sure to set the correct DIV_FACTOR.
     */
        motor->diag.focControlEnabled = FALSE;
        motor->diag.encoderEnabled = FALSE;
        motor->diag.vectorFixedEnable = FALSE;


    }

	motor->control.foc.limitAmpl = eMotorBoardVoltageMax;

	motor->control.foc.limit.imag = eMotorBoardCurrentMax;
	motor->control.foc.limit.real = eMotorBoardCurrentMax;

	motor->control.foc.ref.imag = 0;
    motor->control.foc.ref.real = 0;
}


/** @brief Execute motor control
 *
 * - Update the motor position and speed
 * - Start / Stop the motor
 * - Execute the FOC and open loop modes
 * - Compute the new PWM duty cycles (Space vector modulation)
 * - Update the PWM
 *
 * @return None.
 *
 * @see PositionAcquisition_Update(),
 * InverterIsFault(),
 * VelocityControl_Do(), Foc(), SpaceVectorModulation(), Pic_Reset(), Foc_Reset(),
 * DiagCurrents(), Diag(), DIAG
 *
 * @ingroup app_control
 */

void TorqueControl_FocStep(AppMotor_Motor* motor, T3Phase *currents, StdReal vdc)
{
	CplxStdReal m;
	// check for System errors
	/*The calculate time from sensor position to PWM time is about 11us*/
	if (motor->control.run != FALSE)
    {
    	{
			TimerVal channels[4];
			TimerVal period = TorqueControl_getPeriod(motor->inverter.pwm);

			if (motor->diag.focControlEnabled != FALSE)
			{
			    sint16 sensorposition=TorqueControl_updateEncoderPosition();

				motor->control.electricalAngle = sensorposition;
				if(motor->control.direction != K_MOT_DIR_CCW)
                {

                }
                else
                {
                    motor->control.electricalAngle +=(COSSIN_TABLE_SIZE >> 1);
                }

				/*When torque is inputed from upper computer , it's calibrated to Iq by the table*/
			    /*motor->control.foc.ref.imag = Torque_calibration(motor->control.foc.torque_ref);*/

			    if(g_velocityControl.enabled != TRUE)
			    {
			        Foc_Iq_incre(&motor->control.foc, motor->control.foc.Msg_ref.imag);
			        Foc_Id_incre(&motor->control.foc, motor->control.foc.Msg_ref.real);
			    }
			    else
			    {

			    }
                Foc_SetIq(&motor->control.foc, motor->control.foc.ref.imag);//set limit
                Foc_SetId(&motor->control.foc, motor->control.foc.ref.real);

				/* Field oriented control is enabled */
				m = Foc_Do(&motor->control.foc, (motor->control.electricalAngle), &motor->currents); /// 6,3us

				motor->control.foc.mab =  m;
			}
			else if(motor->diag.FwcEnabled != FALSE)
			{
                sint16 sensorposition=TorqueControl_updateEncoderPosition();

                motor->control.electricalAngle = sensorposition;
                if(motor->control.direction != K_MOT_DIR_CCW)
                {

                }
                else
                {
                    motor->control.electricalAngle +=(COSSIN_TABLE_SIZE >> 1);
                }

                /*When torque is inputed from upper computer , it's calibrated to Iq by the table*/
                /*motor->control.foc.ref.imag = Torque_calibration(motor->control.foc.torque_ref);*/

                if(g_velocityControl.enabled != TRUE)
                {
                    Foc_Iq_incre(&motor->control.foc, motor->control.foc.Msg_ref.imag);
                    Foc_Id_incre(&motor->control.foc, motor->control.foc.Msg_ref.real);
                }
                else
                {

                }
//                Foc_SetIq(&motor->control.foc, motor->control.foc.ref.imag);//set limit
//                Foc_SetId(&motor->control.foc, motor->control.foc.ref.real);
                PMSM_CurrentControl_System_U.Wm_fb = g_motor.speed;
                /* Field oriented control is enabled */
                m = Foc_Fw_Control(&motor->control.foc, (motor->control.electricalAngle), &motor->currents); /// 6,3us

                motor->control.foc.mab =  m;
			}
			else if (motor->diag.encoderEnabled != FALSE)
			{
				sint16 sensorposition=TorqueControl_updateEncoderPosition();
//                sint16 sensorposition = TorqueControl_updateOpenLoopPosition();
//				AppMotor_OpenLoop *openLoop = App_GetOpenLoop(motor);

				motor->control.electricalAngle = sensorposition;

				/* Encoder is enabled, no current control, vector amplitude is given directly, angle is 90�El */
				if(motor->control.direction!= K_MOT_DIR_CCW)
				{

				}
				else
				{
                    motor->control.electricalAngle +=(COSSIN_TABLE_SIZE >> 1);
				}

                motor->control.foc.ref.real = 0;
                motor->control.foc.ref.imag = 23;

				m = Foc_Openloop(&motor->control.foc, (motor->control.electricalAngle),motor->control.foc.vdq_ref);
				Foc_Do(&motor->control.foc, (motor->control.electricalAngle), &motor->currents);
				motor->control.foc.nfo_mab = m;
			}
			else if( motor->diag.vectorFixedEnable !=FALSE)
			{

                AppMotor_OpenLoop *openLoop = App_GetOpenLoop(motor);

                openLoop->amplitude = amplitude_openLoop;

                motor->control.electricalAngle = motor->diag.vectorFixedAngle;

                /* Encoder is enabled, no current control, vector amplitude is given directly, angle is 90�El */
                if(motor->control.direction!= K_MOT_DIR_CCW)
                {

                }
                else
                {
                    motor->control.electricalAngle +=(COSSIN_TABLE_SIZE >> 1);
                }

                m = LookUp_CosinusSinus(motor->control.electricalAngle);
                m.real = __mul_rSR_iSR_iSR(m.real,  openLoop->amplitude);
                m.imag = __mul_rSR_iSR_iSR(m.imag,  openLoop->amplitude);

                motor->control.foc.nfo_mab = m;

			}
			else
			{
		        sint16 sensorposition=TorqueControl_updateOpenLoopPosition();
				AppMotor_OpenLoop *openLoop = App_GetOpenLoop(motor);
				openLoop->electricalAngle  = sensorposition;
                motor->control.electricalAngle =(sint16) openLoop->electricalAngle;

                /* Encoder is not enabled, no current control, vector amplitude and angle/speed are given directly */
				if(motor->control.direction)
				{
				   m = LookUp_CosinusSinus(motor->control.electricalAngle + (COSSIN_TABLE_SIZE >> 1));
				}
				else
				{
				    m = LookUp_CosinusSinus(motor->control.electricalAngle);
				}

				m.real = __mul_rSR_iSR_iSR(m.real, openLoop->amplitude);
				m.imag = __mul_rSR_iSR_iSR(m.imag, openLoop->amplitude);
				motor->control.foc.nfo_mab = m;
			}

			/* Space vector PWM */
			motor->inverter.sector = SpaceVectorModulation(m, period, &channels[0]); // 2us

			// Store PWM cycles
			motor->inverter.channels[0] = channels[0];
			motor->inverter.channels[1] = channels[1];
			motor->inverter.channels[2] = channels[2];

            motor->inverter.adcTrigger[0] = 5;// ((motor->inverter.pwm->ch.base.deadtime)+10);

			/* Update PWM duty cycle */
			/* Motor mode */
			TorqueControl_update3ChannelPwm(motor->inverter.pwm, &motor->inverter.channels[0], motor->inverter.adcTrigger[0]);
    	}

    }
    else
    {
        Foc_Reset(&motor->control.foc);
        VelocityControl_Reset(&g_velocityControl);
    }
}


void  TorqueControl_startMotor(AppMotor_Motor* motor)
{
	if(motor->control.start == TRUE)
	{
		if(motor->control.hadEmergency != FALSE)
		{
			// Motor Error detected
			motor->control.stop = 1;
			motor->control.start = 0;

		}
		else
		{

			motor->control.run = TRUE;
			motor->control.start = 0;
			motor->control.state = AppMotorControlState_foc;

			/* enable the output of PWM pin*/
            IfxPort_setPinMode(&MODULE_P22, 0,  IfxPort_Mode_outputPushPullGeneral);//V
            IfxPort_setPinLow(&MODULE_P22, 0);
            IfxPort_setPinMode(&MODULE_P23, 3,  IfxPort_Mode_outputPushPullGeneral);//U
            IfxPort_setPinLow(&MODULE_P23, 3);
            IfxPort_setPinMode(&MODULE_P23, 0,  IfxPort_Mode_outputPushPullGeneral);//W
            IfxPort_setPinLow(&MODULE_P23, 0);
		}
	}
	if(motor->control.stop == TRUE)
	{
		motor->control.run = FALSE;
		motor->control.stop = FALSE;
		motor->control.state = AppMotorControlState_idle;

        /* disable the output of PWM pin*/
        IfxPort_setPinMode(&MODULE_P22, 0,  IfxPort_Mode_outputPushPullGeneral);//V
        IfxPort_setPinHigh(&MODULE_P22, 0);
        IfxPort_setPinMode(&MODULE_P23, 3,  IfxPort_Mode_outputPushPullGeneral);//U
        IfxPort_setPinHigh(&MODULE_P23, 3);
        IfxPort_setPinMode(&MODULE_P23, 0,  IfxPort_Mode_outputPushPullGeneral);//W
        IfxPort_setPinHigh(&MODULE_P23, 0);

	}

}

void  TorqueControl_stopMotor(AppMotor_Motor* motor)
{
		motor->control.stop = 1;
		motor->control.start = 0;
}

/********************** Interface *******************/
IFX_INLINE AppVadc_AnalogInput_1* TorqueControl_getCurrentPhaseU(void)
{
    return(AppVadc_getCurrentPhaseU_object());

}

IFX_INLINE AppVadc_AnalogInput_1* TorqueControl_getCurrentPhaseV(void)
{

    return(AppVadc_getCurrentPhaseV_object());
}



IFX_INLINE AppVadc_AnalogInput_1* TorqueControl_getCurrentPhaseW(void)
{

    return(AppVadc_getCurrentPhaseW_object());
}


IFX_INLINE AppVadc_AnalogInput_1* TorqueControl_getCurrentOffset(void)
{

    return(AppVadc_getCurrentOffset_object());
}


IFX_INLINE void TorqueControl_update3ChannelPwm(Pwm3PhaseOutput *pwm, TimerVal *tOn, TimerVal adcTon)
{

    GTM_Tom_update3ChannelPwm(pwm,tOn,adcTon);
}

sint16  TorqueControl_updateOpenLoopPosition(void)//240rpm
{
    static uint16 pos_simu = 0;
    static uint16 counter = 0;
    AppMotor_Motor* motor=&g_motor;

    if (g_motor.control.run != FALSE)
    {
        counter++;
        if (counter > 0)
        {
            pos_simu+=(sint16)motor->openLoop.electricalAngleDelta;
            counter = 0;
        }

        if(pos_simu > COSSIN_TABLE_SIZE)
        {
            pos_simu = 0;
        }
    }
    return (sint16)(pos_simu);
}

inline sint16 TorqueControl_updateEncoderPosition(void)
{

    return EcoderPosition_EleAgle();
}

