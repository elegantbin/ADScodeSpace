/*
 * AppTorqueControl.c
 *
 *  Created on: 25.07.2012
 *
 */


#include "AppTorquecontrol.h"
#include "_Utilities\Ifx_assert.h"

#include "Ifx_Cfg_FocControl.h"

#include "SysSe/MotorDrive/Tables.h"

#include "Ifx_Cfg_FocControl.h"
#include "Ifx_Cfg_Vadc.h"

#include "Ifx_Cfg_FocControl.h"

#define samples 1 // 1 = 100�s

float32 currenttable[trace_memory];
float32 currenttable1[trace_memory];
float32 currenttable2[trace_memory];

sint16 angletable[trace_memory];

uint32 index1= 0, loop;
boolean trigger;

IFX_EXTERN AppMotor_Motor	g_motor;

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
    if (motor->control.run != FALSE)
    {
        // Calibrate the current sensors offset
        motor->calibration.count--;

        motor->calibration.offset +=  (sint32)offset->rawvalue;
        motor->calibration.currentA +=  (sint32)currentU->rawvalue;
        motor->calibration.currentB += (sint32)currentV->rawvalue;
        motor->calibration.currentC +=  (sint32)currentW->rawvalue;
        if (motor->calibration.count == 0)
        {
        	sint32 offsetU, offsetV, offsetW, lcl_offset;
        	sint32 tempdif0,tempdif1,tempdif2;

            // End of calibration
        	offsetU = motor->calibration.currentA / CFG_AN_I_CALIBRATION_COUNT;
        	offsetV = motor->calibration.currentB / CFG_AN_I_CALIBRATION_COUNT;
        	offsetW = motor->calibration.currentC / CFG_AN_I_CALIBRATION_COUNT;
        	lcl_offset = motor->calibration.offset / CFG_AN_I_CALIBRATION_COUNT;

            tempdif0 = lcl_offset - APPVADC_CFG_VMOTOR_OFFSET_NOM;
            if (tempdif0 < 0) tempdif0 *= (-1);
            tempdif1 = lcl_offset - offsetU;
            if (tempdif1 < 0) tempdif1 *= (-1);
            tempdif2 = lcl_offset - offsetV;
            if (tempdif2 < 0) tempdif2 *= (-1);

            if(tempdif0 > 150 || tempdif1 > 100 || tempdif2 > 100) // 120mV at 5V and 12bit
        	{
        		motor->calibration.count = CFG_AN_I_CALIBRATION_COUNT;
        	    motor->calibration.currentA = 0;
        	    motor->calibration.currentB = 0;
        	    motor->calibration.currentC = 0;
                motor->calibration.offset = 0;
        	    motor->control.hadEmergency = 1;
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

	Ifx_TimerValue period;
	// Setup Analog Channels
	motor->analogInputs.currentA = AppVadc_getCurrentPhaseU_object();
	motor->analogInputs.currentB = AppVadc_getCurrentPhaseV_object();
	motor->analogInputs.sensorOffset  = AppVadc_getCurrentOffset_object();

	//motor->inverter.pwm = AppPwmDriver_get3ChannelPwm();
	//period = AppPwmDriver_getPeriod(motor->inverter.pwm);
	period=2500;

	// Initialize PWM Channels
	motor->controlStep = 0;
    motor->inverter.channels[0] = period>>1;
    motor->inverter.channels[1] = period>>1;
    motor->inverter.channels[2] = period>>1;
    motor->inverter.adcTrigger[0] = period>>1;

	motor->motor.l = CFG_M0_INDUCTANCE;
	motor->motor.r = CFG_M0_RESISTANCE;
	motor->motor.polePair = CFG_M0_POLPAIR;
	motor->calibration.count = CFG_AN_I_CALIBRATION_COUNT;

#if (SensorMode == Encoder)
	motor->sensors.mode = PositionAcquisition_Encoder;
	AppPositionAcquisition_init(&motor->sensors,motor->motor.polePair);
#else
	motor->sensors.mode = PositionAcquisition_Resolver;
   // AppPositionAcquisition_init(&motor->sensors,motor->motor.polePair);
#endif

    // Init pi Controller for Iq and Id
    Foc_Init(&motor->control.foc);
    Foc_SetIdLimit(&motor->control.foc, CFG_M0_ID_LIMIT	);
    Foc_SetIqLimit(&motor->control.foc, CFG_M0_IQ_LIMIT	);

    Pic_SetKpKi_StdReal(&motor->control.foc.piId, CFG_M0_PI_ID_KP, CFG_M0_PI_ID_KI, 1.0/pwmFrequency, 0, 0);
    Pic_SetLimit(&motor->control.foc.piId,-CFG_M0_PI_ID_LIMIT_MAX,CFG_M0_PI_ID_LIMIT_MAX);

    Pic_SetKpKi_StdReal(&motor->control.foc.piIq, CFG_M0_PI_IQ_KP, CFG_M0_PI_IQ_KI, 1.0/pwmFrequency, 0, 0);
    Pic_SetLimit(&motor->control.foc.piIq,-CFG_M0_PI_IQ_LIMIT_MAX,CFG_M0_PI_IQ_LIMIT_MAX);

    motor->diag.sync_topzero = TRUE;

    motor->control.start = TRUE;

	motor->openLoop.electricalAngleDelta = 0;

	motor->control.foc.limitAmpl = eMotorBoardVoltageMax;

	motor->control.foc.limit.imag = eMotorBoardCurrentMax;
	motor->control.foc.limit.real = eMotorBoardCurrentMax;


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
	sint16 sensorposition = AppPositionAcquisition_updatePosition(&motor->sensors);


	if(loop < samples)
	{
		loop++;
	}
	else
	{

		if (index1 == 0)
		{
			if (motor->control.electricalAngle == 0)
			{
		  	  trigger = 1;
			}
		}

		if (trigger)
		{
			if (index1<trace_memory)
			{
				currenttable[index1] = motor->currents.u;
				currenttable1[index1] = motor->currents.v;
				currenttable2[index1] = motor->currents.w;
				angletable[index1] = motor->control.electricalAngle;
				index1++;
			}
			else
			{
				trigger = 0;
			}
		}
		loop = 0;
	}

	// check for System errors
	if (motor->control.run != FALSE)
    {
    	{
    	    Ifx_TimerValue channels[4];

    	    //Ifx_TimerValue period = AppPwmDriver_getPeriod(motor->inverter.pwm);
    	    Ifx_TimerValue period = 2500;

			if (motor->diag.focControlEnabled != FALSE)
			{
				motor->control.electricalAngle = sensorposition;
				/* Field oriented control is enabled */
				m = Foc_Do(&motor->control.foc, (motor->control.electricalAngle), &motor->currents); /// 6,3�s
				motor->control.foc.mab =  m;
			}
			else if (motor->diag.encoderEnabled != FALSE)
			{
				AppMotor_OpenLoop *openLoop = App_GetOpenLoop(motor);
				motor->control.electricalAngle = sensorposition;
				/* Encoder is enabled, no current control, vector amplitude is given directly, angle is 90�El */
				m = LookUp_CosinusSinus(motor->control.electricalAngle + (COSSIN_TABLE_SIZE >> 2));
				m.real = __mul_rSR_iSR_iSR(m.real,  openLoop->amplitude);
				m.imag = __mul_rSR_iSR_iSR(m.imag,  openLoop->amplitude);
				motor->control.foc.nfo_mab = m;
			}
			else
			{
				AppMotor_OpenLoop *openLoop = App_GetOpenLoop(motor);
				openLoop->electricalAngle += openLoop->electricalAngleDelta;
				motor->control.electricalAngle = (openLoop->electricalAngle >> 16) & (COSSIN_TABLE_SIZE - 1);
				/* Encoder is not enabled, no current control, vector amplitude and angle/speed are given directly */
				m = LookUp_CosinusSinus(motor->control.electricalAngle);
				m.real = __mul_rSR_iSR_iSR(m.real, openLoop->amplitude);
				m.imag = __mul_rSR_iSR_iSR(m.imag, openLoop->amplitude);
				motor->control.foc.nfo_mab = m;
			}

			/* Space vector PWM */
			motor->inverter.sector = SpaceVectorModulation(m, period, &channels[0]); // 2�s
			// Store PWM cycles
//			motor->inverter.channels[0] = channels[0];
			motor->inverter.channels[0] = 500;
			motor->inverter.channels[1] = channels[1];
			motor->inverter.channels[2] = channels[2];
			motor->inverter.adcTrigger[0] = (((period>>1) + motor->inverter.pwm->ch.base.deadtime) + 5);

			/* Update PWM duty cycle */
			/* Motor mode */
			//AppPwmDriver_update3ChannelPwm(motor->inverter.pwm, &motor->inverter.channels[0], motor->inverter.adcTrigger[0]);

    	}

    }
    else
    {
        Foc_Reset(&motor->control.foc);
        //Tle9180_deactivateEnable(&motor->inverter.driver);
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

		}else
		{
			//Tle9180_activateEnable(&motor->inverter.driver);
			motor->control.run = TRUE;
			motor->control.start = 0;
			motor->control.state = AppMotorControlState_foc;
		}
	}
	if(motor->control.stop == TRUE)
	{
		motor->control.run = FALSE;
		motor->control.stop = FALSE;
		motor->control.state = AppMotorControlState_idle;
	}

}

void  TorqueControl_stopMotor(AppMotor_Motor* motor)
{
		motor->control.stop = 1;
		motor->control.start = 0;
}



