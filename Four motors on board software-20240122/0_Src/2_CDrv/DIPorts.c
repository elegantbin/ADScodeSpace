

#include <EncoderGpt12.h>
#include "DIPorts.h"
#include "IfxGpt12_PinMap.h"

boolean portState_A=FALSE;
boolean portState_B=FALSE;
boolean portState_Z=FALSE;

boolean portState_Aold=FALSE;
boolean portState_Bold=FALSE;
boolean portState_Zold=FALSE;

#define OFFSET_ZERO_A   (0x1000)
#define OFFSET_ZERO_B   (0x1000)
uint32 count_A=OFFSET_ZERO_A;
uint32 count_B=OFFSET_ZERO_B;
uint32 count_Z=0;


void PortABZ_StateCheck(void)
{
    portState_A=IfxPort_getPinState(ENCODER_PINA.pin.port,ENCODER_PINA.pin.pinIndex);
    portState_B=IfxPort_getPinState(ENCODER_PINB.pin.port,ENCODER_PINB.pin.pinIndex);
    portState_Z=IfxPort_getPinState(ENCODER_PINZ.pin.port,ENCODER_PINZ.pin.pinIndex);

    if(portState_Aold!=portState_A)
    {
        if(portState_A==0)
        {
            if(portState_B)
            {
               count_A++;
            }
            else
            {
                (count_A>0)?(count_A--):0;
            }
        }
    }

    if(portState_Bold!=portState_B)
    {
        if(portState_B==0)
        {
            count_B++;
        }
    }

    if(portState_Zold!=portState_Z)
   {
       if(portState_Z)
       {
           count_Z++;

           count_B=OFFSET_ZERO_B;
           count_A=OFFSET_ZERO_A;

       }
   }

    portState_Aold=portState_A;
    portState_Bold=portState_B;
    portState_Zold=portState_Z;

}
