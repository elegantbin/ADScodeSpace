
//---------------------------------------------------------------------------
#include "App_VelocityControl.h"
#include "App_VelocityEval.h"
#include "GPT12_Encoder.h"
#include "Ifx_Cfg_FocControl.h"
#include "AppTorqueControl.h"
#include "Ifx_Cfg_VelocityControl.h"


/****************************************************************************************************************************************
 * Macro definition
 *****************************************************************************************************************************************/
#define K_PULSES_TO_RPM_FACTOR  (5.86/4*10) /* 1 mech circle =1024 puls, the factor is 5.86;  1 mech-circle = 4096,the factor is 5.86/4 */
#define K_VELOCITY_UPDATE_TICKS (20)    /*per tick=50us,  every 10ms update in 1ms Interrupt*/
/****************************************************************************************************************************************
 * Tips:
 *  1. If more than one circle in 10ms, the RPM should big than 1r/0.01s=100 r/s(6000 rpm)
 *  In fact the motor max speed is not more than 6000 rpm,
 *  So the counts value should limited in a circle.
 * 2.Acc.to 1 circle = 1024 count,there is 1 rpm  = 1024 counts/60s = 1024 counts/(60x100 (10ms)) = 1/(5.859375) ~= 1/5.86  counts/(10ms)
 *  That means if 1 count received in 10ms,then is equal to 1/(1/5.86) = 5.86 rpm
 *  (That is what the define the factor macro K_PULSES_TO_RPM_FACTOR is).
 *
 *****************************************************************************************************************************************/


/******************* GLOBAL VARIABLES ****************/


/*****************************************************/

static sint16 encoderUpdateSpeedPerTick(sint16 encoderPos);

uint16 absMotSpeed_raw;
sint16 encoderPos_old;

void AppVelocity_SpeedUpdate()    /* 10ms task*/
{
       static uint32 speedTicks=0;

       speedTicks++;

       if(speedTicks > K_VELOCITY_UPDATE_TICKS-1)
       {
           sint16 encoderRawPos=GPT12_EncoderUpdatePosition();

           g_motor.speed=(float)encoderUpdateSpeedPerTick(encoderRawPos);

           speedTicks = 0;
       }
}


static sint16 encoderUpdateSpeedPerTick(sint16 encoderPos)
{
    static sint16 DeltaPositons = 0;
    sint16  s16MotSpeed = 0;
    sint16 s16MechSpeedRaw;

    /* the motor direction from increEncorder*/
//    Ifx_GPT12 *gpt12=&MODULE_GPT120;
//    g_motor.rot_dir = gpt12->T2CON.B.T2RDIR;
    g_motor.rot_dir =  g_motor.control.direction;//K_ROT_DIR_CW;
    /*invalid speed calculate from iLLD*/
//    g_IncrEnc.update = (IfxGpt12_IncrEnc_Update) & IfxGpt12_IncrEnc_updateFromT2;
//    IfxGpt12_IncrEnc_update(&g_IncrEnc);
//    IfxGpt12_IncrEnc_updateFromT2(&g_IncrEnc);

    if(g_motor.rot_dir == K_ROT_DIR_CW)   /*CW,Position is positive value*/
    {
        if(encoderPos < 0)
        {
           encoderPos += K_TOTAL_COUNTS_PER_MECH_ROTATION;
        }

        if(encoderPos >= encoderPos_old)
        {
            DeltaPositons = encoderPos - encoderPos_old;
        }
        else if(encoderPos_old-encoderPos>3000)
        {
            DeltaPositons = K_TOTAL_COUNTS_PER_MECH_ROTATION - (encoderPos_old - encoderPos);
        }
    }
    else if(g_motor.rot_dir == K_ROT_DIR_CCW) /** CCW, Position is negative value**/
    {
        if(encoderPos > 0)
        {
            encoderPos -= K_TOTAL_COUNTS_PER_MECH_ROTATION;
        }

        if(encoderPos <= encoderPos_old)
        {
            DeltaPositons = encoderPos - encoderPos_old;
        }
        else if(encoderPos-encoderPos_old<-3000)
        {
            DeltaPositons =-(K_TOTAL_COUNTS_PER_MECH_ROTATION + (encoderPos_old - encoderPos));
        }

    }
    else
    {
        /* Do nothing because of unknown rotation direction */
    }

    s16MechSpeedRaw = (sint16)((float)DeltaPositons* K_PULSES_TO_RPM_FACTOR);

    encoderPos_old = encoderPos;

    if(s16MechSpeedRaw > 0)   /* calculate the absolute speed*/
    {
        absMotSpeed_raw = s16MechSpeedRaw;
    }
    else
    {
        absMotSpeed_raw =0x00 - (s16MechSpeedRaw);
    }

    {
        static uint16 speed_filter_array[10]={0};

        uint32 speed_sum = 0;

        speed_filter_array[0]=speed_filter_array[1];
        speed_filter_array[1]=speed_filter_array[2];
        speed_filter_array[2]=speed_filter_array[3];
        speed_filter_array[3]=speed_filter_array[4];
        speed_filter_array[4]=speed_filter_array[5];
        speed_filter_array[5]=speed_filter_array[6];
        speed_filter_array[6]=speed_filter_array[7];
        speed_filter_array[7]=speed_filter_array[8];
        speed_filter_array[8]=speed_filter_array[9];

        speed_filter_array[9]=absMotSpeed_raw;

        for(uint8 i=0;i<10;i++)
        {
            speed_sum+=speed_filter_array[i];
        }

        s16MotSpeed =(uint16)(speed_sum/10);

    }

    return s16MotSpeed;

}


uint16 Number_of_Fails = 0;
void AppMotor_EmergencyCheck(AppMotor_Motor* motor) /** 200ms Task**/
{
    if((motor->control.run == TRUE) & (g_velocityControl.ref > 0.0) & (motor->diag.focControlEnabled == TRUE)) // evaluate stall condition of the motor
    {
        if (motor->speed > min_speed)
        {
            Number_of_Fails = 0;
        }
        else
        {
            Number_of_Fails++;
            if(Number_of_Fails > fails) // stall condition or motor runs out of control
            {
                motor->control.stop = TRUE;
                motor->control.hadEmergency = TRUE;
            }
        }

        if (((motor->speed - g_velocityControl.ref) > delta_speed ) | (motor->speed > VELOCITY_CONTROL_MAX_RPM))//motor runs out of control
        {
            motor->control.stop = TRUE;
            motor->control.hadEmergency = TRUE;
        }

    }
}
