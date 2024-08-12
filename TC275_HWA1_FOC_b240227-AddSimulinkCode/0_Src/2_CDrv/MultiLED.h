
#ifndef __MULTI_LED_H_
#define __MULTI_LED_H_
#include "Ifx_Types.h"
#include "IfxPort.h"
#include "IfxPort_reg.h"

#define PIN5                        5                           /* LED1 used in TX ISR is connected to this pin      */
#define PIN6                        6                           /* LED2 used in RX ISR is connected to this pin      */

typedef struct
{
    IfxPort_Pin_Config              led1;                  /* LED1 configuration structure                           */
    IfxPort_Pin_Config              led2;                  /* LED2 configuration structure                           */
} AppLedType;





void initLed(void);
void blinkLED1(void);
void blinkLED2(void);

void turnOnLed1(void);
void turnOnLed2(void);


void turnOffLed1(void);
void turnOffLed2(void);

#endif /*__MULTI_LED_H_*/
