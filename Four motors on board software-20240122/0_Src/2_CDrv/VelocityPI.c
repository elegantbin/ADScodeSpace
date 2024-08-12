
#include "EncoderGpt12.h"
#include "velocityPI.h"
#include "DataFlash_ZeroOffest.h"
#include "stdlib.h"

#define pos_VelocityControl    (01)
#define incre_VelocityControl  (02)
#define loc_VelocityControl    (03)
#define ControlWay             (03)

#define SPEED_ERROR_0        (20)
#define SPEED_ERROR_1        (4000)
#define SPEEDPID_FACTOR1      (1000.0)
#define SPEEDPID_FACTOR2      (100000.0)
#define PID_FUNCTION_PHASE1 ((error > 0 && error > SPEED_ERROR_0)||(error < 0 && error < -SPEED_ERROR_0))

#define PID_FUNCTION_PHASE2 ((error > 0 && error > SPEED_ERROR_1)||(error < 0 && error < -SPEED_ERROR_1))

IFX_EXTERN uint16 u8DrvDuty;
float32 delta_uk=0;
float32 uk=0;
float32 VelocityPIDControl(uint16 speed_ref,uint16 raw_speed)
{
#if(ControlWay == loc_VelocityControl)
   float kp = SpeedKP_Read/SPEEDPID_FACTOR1;          // 10
   float ki = SpeedKI_Read/SPEEDPID_FACTOR1;          // 0.125
   float kd = 0;          //1.8
   uint16 lower = 500;
   uint16 upper = 9000;
//   uint16 beta = 0;
//   uint16 maxerror_integral = 10000;
//   float32 uk ;
   static sint32  error,error_integral,last_error=0;

   error = speed_ref- raw_speed;
   uk = (kp*error) + (ki*error_integral)+(kd*(error-last_error));
   error_integral += error;

//   if(error_integral > maxerror_integral)
//   {
//       error_integral = maxerror_integral;
//   }
//   else if (error_integral < -maxerror_integral)
//   {
//       error_integral = -maxerror_integral;
//   }
   last_error = error;

   if (uk >= upper)
   {
       uk = upper;
   }
   else if (uk <= lower)
   {
       uk  = lower;
   }
   else
   {

   }
   return uk;

#elif(ControlWay==pos_VelocityControl)
   float kp_01 = 0.01;          //0.3,0.7,1.0,1.2
   float ki_01 = 0;             //0.018
   float kd_01 = 0;

   float kp_02 = 0.02;          //0.3,0.7,1.0,1.2
   float ki_02 = 0;             //0.018

   uint16 lower = 0;
   uint16 upper = 9000;
   uint16 fb_speed;
   static sint16  error,error_integral=0;
   fb_speed = raw_speed;
   error = speed_ref- fb_speed;

   if(PID_FUNCTION_PHASE2)
   {
       delta_uk = (kp_02 * error) + (ki_02*error_integral);
       error_integral += error;
   }
   else if(PID_FUNCTION_PHASE1)
   {
       delta_uk = (kp_01 * error) + (ki_01*error_integral);
      error_integral += error;
   }
   else
   {
       delta_uk =0;
       /* Speed Error is too small to adjust. */
   }

   uk=u8DrvDuty;
   uk+=delta_uk;

   if (uk >= upper)
   {
       uk        = upper;
   }
   else if (uk <= lower)
   {
       uk        = lower;
   }
   else
   {

   }

   return uk;

#elif(ControlWay == incre_VelocityControl)
   float kp = SpeedKP_Read/SPEEDPID_FACTOR1;          //0.016 SpeedKP_Read/SPEEDPID_FACTOR1
   float ki = SpeedKI_Read/SPEEDPID_FACTOR2;          //0.00008 SpeedKI_Read/SPEEDPID_FACTOR2
   float kd = 0;//SpeedKD_Read/SPEEDPID_FACTOR2
   uint16 lower = 0;
   uint16 upper = 9500;
//   uint32 maxerror_integral = SpeedKD_Read;
   float32 uk=0 ;
   static sint32  error,error_integral,last_error=0;//sint16

   uk=u8DrvDuty;
   error = speed_ref- raw_speed;
//   last_error = error;
//   error_integral += error;
  //   uk = (kp * error) + (ki*error_integral)+(kd*(error-last_error));

   if(error > 50 || error < -50 )
    {
       uk = (kp*error) + (ki* error_integral)+(kd*(error-last_error))+uk ;
       last_error = error;
       error_integral += error;
    }
    else
    {

    }

//     if(error_integral > maxerror_integral)
//     {
//         error_integral = maxerror_integral;
//     }
//     else if (error_integral < -maxerror_integral)
//     {
//         error_integral = -maxerror_integral;
//     }

     if (uk >= upper)
     {
         uk = upper;
     }
     else if (uk <= lower)
     {
         uk  = lower;
     }
     else
     {

     }
     return uk;
#endif
}


void Pic_param_init(void)
{
    velocity_Pic pic;
    pic.hitLimits = 0;
    pic.ik = 0;
    pic.kp = 0.1;
    pic.ki = 0.1;
    pic.lower = 10;
    pic.upper = 80;
    VelocityCtrl vc;
    vc.refLimit = 3500;
}

float32 Pic_VelocityControl(VelocityCtrl *vc, uint16 raw_speed)
{
    float32 result;
    if (vc->enabled != FALSE)
    {
        result = Pic_controlstep(&vc->pic, vc->speed_ref - raw_speed);
    }
    else
    {
        result = vc->pic.uk;
    }
    return result;
 }

float32 Pic_controlstep(velocity_Pic *pic, sint16 Input)
{
    float32 uk;
    uk      = (pic->kp * Input) + (pic->ki * pic->ik) + uk;

    pic->ik = Input;

    if (uk >= pic->upper)
    {
        pic->hitLimits = TRUE;
        pic->uk        = pic->upper;
    }
    else if (uk <= pic->lower)
    {
        pic->hitLimits = TRUE;
        pic->uk        = pic->lower;
    }
    else
    {
        pic->uk = uk;
    }

    return pic->uk;
}


