/*
 * MotorSwc.c
 *
 *  Created on: 18.07.2023
 *
 */

#include "AppTorqueControl.h"

#include "Ifx_cfg_VelocityControl.h"
#include "App_VelocityControl.h"
#include "MotorMgtSwc.h"
#include "GTM_ATOM_PWM_6Step.h"
#include "ADC.h"
#include "AppIsr.h"
#include <EncoderGpt12.h>
#include <TempDetect.h>


AppMotor_Motor   g_motor;
VelocityControl g_velocityControl;


Bldc_Motor g_bldc = {
       .state = MOTOR_STATE_STOP,
       .rot_dir = K_ROT_DIR_UNKNOWN,
       .cmd = MOTOR_CMD_STOP,
       .RPM_s16MechSpeed = 0,
       .u32DiagCode = 0
};

sint16 New_Encoder_Offset;
uint16 Call_Loop = 0;
uint16 Number_of_Fails;

volatile uint8 b_RealCountsValidCheck =0;

float32 velocity;

void MotorControl_init(void)
{
    // Init Velocity control
    VelocityControl_Init(&g_velocityControl);
    VelocityControl_SetKpKi(&g_velocityControl, VELOCITY_CONTROL_KP, VELOCITY_CONTROL_KI, VELOCITY_CONTROL_PERIOD,0, 0);
    VelocityControl_SetLimit(&g_velocityControl, VELOCITY_CONTROL_MIN, VELOCITY_CONTROL_MAX);
    VelocityControl_SetMaxSpeed(&g_velocityControl, VELOCITY_CONTROL_MAX_RPM);
    VelocityControl_SetRefSpeed(&g_velocityControl, VELOCITY_CONTROL_REF);
}


void MotorDemoControl_Runnable(void)
{
#if 0
//    if(g_motor.control.demo == 1)
    {
        g_motor.control.start = 1;
        g_motor.control.demorun = 1;
        velocity = VelocityControl_GetRefSpeed(&g_velocityControl);
        velocity = velocity + 50.0;
        VelocityControl_SetRefSpeed(&g_velocityControl, velocity);


        if(velocity > (VELOCITY_CONTROL_MAX_RPM - 3500))
        {

            g_motor.control.demorun = 0;
            g_motor.control.demo = 0;
            g_motor.control.demostop = 1;

        }
    }

//    if(g_motor.control.demostop == 1)
//    {
//            velocity = VelocityControl_GetRefSpeed(&g_velocityControl);
//            velocity = velocity - 50.0;
//            VelocityControl_SetRefSpeed(&g_velocityControl, velocity);
//
//        if(velocity <= 0)
//        {
//            g_motor.control.start = 0;
//            g_motor.control.demostop = 0;
//            g_motor.control.run = 0;
//            velocity = 0;
//            VelocityControl_SetRefSpeed(&g_velocityControl, velocity);
//        }
//    }
#endif
}

void MotorVelocityControl_Runnable(void)
{
      g_velocityControl.speed = Rad_s_To_Rpm(AppPositionAcquisition_updateSpeed(&g_motor.sensors));
      // Control Speed if enabled
      if(VelocityControl_IsEnabled(&g_velocityControl))
      {   // set reference Speed

          float32 uk=VelocityControl_Do(&g_velocityControl, g_velocityControl.speed);

          Foc_SetIq(&g_motor.control.foc,uk * Foc_GetIqLimit(&g_motor.control.foc));

      }
}

void MotorCalibration_Runnable(void)
{

#if (SensorMode == Encoder)

    if((g_motor.control.calon == TRUE) & (g_motor.diag.sync_topzero == FALSE)) //Calibration
    {
        Call_Loop++;

        if(Call_Loop == 1)
        {
            g_motor.diag.focControlEnabled  = FALSE;
            g_motor.diag.encoderEnabled = FALSE;
            g_motor.sensors.encoder.offset = 0;
            g_motor.openLoop.amplitude = 0;
            g_motor.openLoop.electricalAngleDelta = 0;
            g_motor.openLoop.electricalAngle = 0;
            g_motor.openLoop.amplitude = 0.05;
            g_motor.control.start = 1;
        }

        if(Call_Loop == 2)
        {
            g_motor.openLoop.amplitude = 0.1;
        }
        if(Call_Loop == 5)
        {
            g_motor.openLoop.amplitude = 0.15;
        }
        if(Call_Loop == 10)
        {
            //IFX_INLINE void PosIf_setOffset_base(PosIf *handle, PosIf_Raw offset);
            g_motor.sensors.encoder.offset =  - g_motor.sensors.encoder.rawPosition;
            g_motor.control.calon = FALSE;
            g_motor.openLoop.amplitude = 0.0;
            g_motor.control.stop = TRUE;
            g_motor.diag.focControlEnabled  = TRUE;
            g_motor.diag.encoderEnabled = TRUE;
            Call_Loop=0;
        }
    }
#endif

}



void MotorStallCheck_Runnable(void)
{
/*
    if((g_motor.control.run == TRUE) & (g_velocityControl.ref > 0.0) & (g_motor.diag.focControlEnabled == TRUE)) // evaluate stall condition of the motor
    {
        if (g_velocityControl.speed > min_speed)
        {
            Number_of_Fails = 0;
        }
        else
        {
            Number_of_Fails++;
            if(Number_of_Fails > fails) // stall condition or motor runs out of control
            {
                g_motor.control.stop = TRUE;
                g_motor.control.hadEmergency = TRUE;
                g_motor.control.demorun = 0;
            }
        }

        if (((g_velocityControl.speed - g_velocityControl.ref) > delta_speed ) | (g_velocityControl.speed > VELOCITY_CONTROL_MAX_RPM))//motor runs out of control
        {
            g_motor.control.stop = TRUE;
            g_motor.control.hadEmergency = TRUE;
            g_motor.control.demorun = 0;
        }

    }
*/
}



void MotorRPM_Check(void)
{
   boolean b_MotorFailCheck =FALSE;

  if(g_bldc.state == MOTOR_STATE_RUNNING)  // evaluate stall condition of the motor
  {
      sint16 absMechSpeed = g_bldc.RPM_s16MechSpeed;

      if(absMechSpeed < 0)
      {
        absMechSpeed = -(absMechSpeed);
      }

      if (absMechSpeed > min_speed)
      {
          Number_of_Fails = 0;
      }
      else
      {
          Number_of_Fails++;
          if(Number_of_Fails > fails) // stall condition or motor runs out of control
          {
              g_bldc.u32DiagCode |= MOTOR_DIAG_CODE_STALL_FAIL;
              b_MotorFailCheck = TRUE;

          }
      }


      if(absMechSpeed > VELOCITY_CONTROL_MAX_RPM)//motor runs out of control
      {

          b_MotorFailCheck = TRUE;

          g_bldc.u32DiagCode |= MOTOR_DIAG_CODE_VELOCITY_MAX_FAIL;
      }
      else
      {

      }

      if(b_MotorFailCheck)
      {
          g_bldc.state = MOTOR_STATE_FAIL;

          CommutationDriver_Stop();
      }
  }
}


void Motor_VlotageBus_Check(void)
{

    if((g_bldc.Voltage_BUS>K_VOLTAGE_LIMIT_MAX)||(g_bldc.Voltage_BUS<K_VOLTAGE_LIMIT_MIN))
         {
                 g_bldc.u32DiagCode |= MOTOR_DIAG_CODE_VLOTAGE_FAIL;
                 CommutationDriver_Stop();
         }
         else
         {
           }
}

void MotorPhaseCurrent_Check(void)
{
#define CURRENT_CHECK_DELAY   (0)
      uint8 b_MotorCurrentFailCheck = 0;

//     static uint16 current_checkdelay = 0;
     static uint8 b_CurrenCheckEnable = 1;
#if(CURRENT_CHECK_DELAY)
     if(MOTOR_STATE_RUNNING == g_bldc.state)
     {
         if(!b_CurrenCheckEnable)
         {
            current_checkdelay++;
            if (current_checkdelay >2000)
            {
                b_CurrenCheckEnable =1;
                current_checkdelay = 0;
            }
         }

     }
     else
     {
         current_checkdelay =0;
         b_CurrenCheckEnable =0;
     }
#endif

  if(b_CurrenCheckEnable)
  {
      if( g_bldc.CurrentU_BUS>=K_CURRENT_LIMIT_MAX||g_bldc.CurrentV_BUS>=K_CURRENT_LIMIT_MAX
              ||g_bldc.CurrentW_BUS>=K_CURRENT_LIMIT_MAX)
      {
          b_MotorCurrentFailCheck = TRUE;
          g_bldc.u32DiagCode |= MOTOR_DIAG_CODE_CURRENT_FAIL;
      }
      else
      {

      }


      if(b_MotorCurrentFailCheck)
      {
              g_bldc.state = MOTOR_STATE_FAIL;

              CommutationDriver_Stop();
      }
  }
}


#define K_REAL_POS_MAX  (3072)
void RealPos_ValidCheck(void)
{
    static uint32 absEncoder_RawPosition_Old = 0xFFFFFFF;
    uint32 absEncoder_RawPosition=0;
    b_RealCountsValidCheck = FALSE;

    if((MOTOR_STATE_RUNNING == g_bldc.state)||
            (MOTOR_STATE_STARTUP == g_bldc.state ))
    {
        if(Encoder_RawPosition > 0)
       {
           absEncoder_RawPosition = Encoder_RawPosition;
       }
       else
       {
           absEncoder_RawPosition = -Encoder_RawPosition;
       }

       if((absEncoder_RawPosition > K_REAL_POS_MAX)||
               ((absEncoder_RawPosition == absEncoder_RawPosition_Old)))
       {
           b_RealCountsValidCheck = TRUE;

           g_bldc.state = MOTOR_STATE_FAIL;
           CommutationDriver_Stop();

           g_bldc.u32DiagCode |= MOTOR_DIAG_CODE_REALPOSITION_FAIL;
       }

       absEncoder_RawPosition_Old = absEncoder_RawPosition;
    }
}

void Over_Temperature_Detect(void)
{
    if(g_DriverBoardTemp > 65)
    {
        g_bldc.u32DiagCode |= MOTOR_DIAG_CODE_OVER_TEMPERATURE;
        CommutationDriver_Stop();
        g_bldc.state = MOTOR_STATE_FAIL;
    }
}
