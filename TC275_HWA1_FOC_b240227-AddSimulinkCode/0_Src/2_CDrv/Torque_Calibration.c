/*
 * Torque_Calibration.c
 *
 *  Created on: 2024Äê1ÔÂ9ÈÕ
 *      Author: Brook.Wu
 */
#include  "AppTorquecontrol.h"
#include  "Torque_Calibration.h"

float32 Torque_table[25]  = {0,  0.5,   1.0,   1.5,   2.0,   2.5,  3.0,   3.5,   4.0,   4.5,    5.0,
                                 5.5,   6.0,   6.5,   7.0,   7.5,  8.0,   8.5,   9.0,   9.5,   10.0,
                                10.5,  11.0,  11.5,  12.0
                            };
float32 Current_table[25] = {0,  5.8,  11.0,  16.5,  22.0,  27.3,  32.7,  38.0,  43.5,  49.0,  54.8,
                                60.5,  66.4,  73.0,  79.5,  86.0,  93.0, 100.0, 105.0, 112.0, 120.0,
                               128.0, 137.0, 147.0, 157.0
                             };

float32 Torque_calibration(float32 torque_ref)
{
   static float32 Iq_ref = 0;

   if(torque_ref>=0 && torque_ref<=12)
   {
       for(uint8 i = 0; i<25;i++)
       {
           if(torque_ref <= Torque_table[i])
           {
               if(torque_ref < Torque_table[i])
               {
                   Iq_ref = Torque_table[i-1] + (torque_ref - Torque_table[i-1]) * (Current_table[i] - Current_table[i-1] / 0.5);
               }
               else
               {
                   Iq_ref = Current_table[i];
               }

               break;
           }
       }
   }
   else
   {
       Iq_ref = 0;
   }

   return Iq_ref;
}

void Actual_Torque_Calculation(void)
{
  static float32 Iq_actual;
  float32 torque_actual;

  Iq_actual = g_motor.control.foc.nfo_mdq.imag;

  if(Iq_actual>=0 && Iq_actual<=157)
  {
      for(uint8 i = 0; i<25; i++)
      {
          if(Iq_actual <= Current_table[i])
          {
             if(Iq_actual < Current_table[i])
             {
                 torque_actual = Torque_table[i-1] + (Iq_actual-Current_table[i-1])*0.5/(Current_table[i]-Current_table[i-1]);
             }
             else
             {
                 torque_actual =  Torque_table[i];
             }

             break;
          }
      }
  }
  else if(Iq_actual>157)
  {
      torque_actual = 12.0 + (Iq_actual-157.0)*0.05;
  }
  else
  {
      torque_actual = 0;
  }
  g_motor.control.foc.torque_actual = torque_actual;
}


void Current_Iq_Incr(void)
{
    static uint8 count_incre = 0;

    if (g_motor.control.run != FALSE)
    {
        count_incre++;
        if(count_incre>25)
        {
            g_motor.control.foc.ref.imag += 15;
            count_incre = 0;
        }
        if(g_motor.control.foc.ref.imag > g_motor.control.foc.incre_ref_max.imag)
        {
            g_motor.control.foc.ref.imag = g_motor.control.foc.incre_ref_max.imag;
        }
    }
    else
    {
        g_motor.control.foc.incre_ref_max.imag = 0;
    }

}
