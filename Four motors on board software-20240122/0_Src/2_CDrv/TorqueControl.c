#include "TorqueControl.h"
#include "ADC.h"
#include "MotorMgtSwc.h"
#include "CommutationControl.h"

uint8 MotorTorque;

//sint16 Current_to_Torque [10] = {41,35,30,23,19,14,10,5,2,0};
//uint8  Torque_to_Current [10] = {40,35,30,25,20,15,10,5,2,0};  /*Torque's Unit is 0.1N/m*/

sint16 Current_to_Torque [10] = {33,29,25,21,17,13,9,6,2,0};
uint8  Torque_to_Current [10] = {40,35,30,25,20,15,10,5,2,0};  /*Torque's Unit is 0.1N/m*/

void Torque_Calculate(void)
{
    if(g_bldc.CurrentV_BUS>=0)
    {
        for(uint8 k=0;k<10;k++)
       {
          if(g_bldc.CurrentV_BUS>=Current_to_Torque[k])
          {
             MotorTorque = Torque_to_Current[k];
             break;
          }
        }
    }
    else
    {
        MotorTorque = 0;
    }
}

uint8 REF_Torque;
uint16 REF_Current_By_Torque;
void Torque_To_Current(void)
{

   REF_Torque = g_bldc.RefTorque;
   if(REF_Torque>0)
   {
       for(uint8 k=1;k<10;k++)
       {
           if(REF_Torque>Torque_to_Current[k])
           {
               REF_Current_By_Torque = Current_to_Torque[k-1];
               break;
           }
       }
   }
   else
   {
       REF_Current_By_Torque = 0;
   }


}

void TorqueCalculation(void)
{
    if (g_bldc.CurrentV_BUS >= 2 && g_bldc.CurrentV_BUS < 5)
    {
        MotorTorque = 2;
    }
    else if (g_bldc.CurrentV_BUS >= 5 && g_bldc.CurrentV_BUS < 10)
    {
        MotorTorque = 5;
    }
    else if (g_bldc.CurrentV_BUS >= 10 && g_bldc.CurrentV_BUS < 14)
    {
        MotorTorque = 10;
    }
    else if (g_bldc.CurrentV_BUS >= 14 && g_bldc.CurrentV_BUS < 19)
    {
        MotorTorque = 15;
    }
    else if (g_bldc.CurrentV_BUS >= 19 && g_bldc.CurrentV_BUS < 23)
    {
        MotorTorque = 20;
    }
    else if (g_bldc.CurrentV_BUS >= 23 && g_bldc.CurrentV_BUS < 30)
    {
        MotorTorque = 25;
    }
    else if (g_bldc.CurrentV_BUS >= 30 && g_bldc.CurrentV_BUS < 35)
    {
        MotorTorque = 30;
    }
    else if (g_bldc.CurrentV_BUS >= 35 && g_bldc.CurrentV_BUS < 41)
    {
        MotorTorque = 35;
    }
    else
    {
        MotorTorque = 0xFF;
    }
}
