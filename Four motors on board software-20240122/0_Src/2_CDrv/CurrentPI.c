
#include"CurrentPI.h"
#include "DataFlash_ZeroOffest.h"
#include "MotorMgtSwc.h"

#define ControlWay   (2)
#define POS_PID      (1)
#define INCRE_PID    (2)
#define CURRENTPID_FACTOR           (1000.0)

IFX_EXTERN uint16 u8DrvDuty;
float32 CurrentPIDControl(float32 current_ref,float32 raw_current)
{
#if(ControlWay == POS_PID)
   float kp = CurrentKP_Read/CURRENTPID_FACTOR;          //0.3,0.7,1.0,1.2
   float ki = CurrentKI_Read/CURRENTPID_FACTOR;           //0.018
   uint16 lower = 300;
   uint16 upper = 9000;
   float32 uk ;
   static sint16  error,error_integral=0;

   error = current_ref- raw_current;
   uk = (kp * error) + (ki*error_integral);
   error_integral += error;

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
#elif(ControlWay == INCRE_PID)
     float kp = CurrentKP_Read/CURRENTPID_FACTOR;//1
     float ki = CurrentKI_Read/CURRENTPID_FACTOR;//0.02
     uint16 lower = 500;
     uint16 upper = 9000;
     static float32 uk = 0;
     static float32  error,last_error,error_integral=0;

     uk=u8DrvDuty;
     if(MOTOR_STATE_STOP==g_bldc.state)
     {
         uk = 0;
     }
     else
     {
         error = current_ref- raw_current;
//         if(error>1||error<-1)
         {
             uk = kp * error + (ki*error_integral)+uk;
             last_error = error;
             error_integral += error;
         }

         if (uk >= upper)
         {
             uk  = upper;
         }
         else if (uk <= lower)
         {
             uk  = lower;
         }
         else
         {

         }
     }

     return uk;
#endif
}



