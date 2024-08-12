

#include "MultiLED.h"
AppLedType        g_led;                                    /* Global LED configuration and control structure        */

void initLed(void)
{
    /* ======================================================================
     * Configuration of the pins connected to the LEDs:
     * ======================================================================
     *  - define the GPIO port
     *  - define the GPIO pin that is the connected to the LED
     *  - define the general GPIO pin usage (no alternate function used)
     *  - define the pad driver strength
     * ======================================================================
     */
    g_led.led1.port      = &MODULE_P00;
    g_led.led1.pinIndex  = PIN5;
    g_led.led1.mode      = IfxPort_OutputIdx_general;
    g_led.led1.padDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1;


    g_led.led2.port      = &MODULE_P00;
    g_led.led2.pinIndex  = PIN6;
    g_led.led2.mode      = IfxPort_OutputIdx_general;
    g_led.led2.padDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1;

    /* Initialize the pins connected to LEDs to level "HIGH"; will keep the LEDs turned off as default state */
    IfxPort_setPinHigh(g_led.led1.port, g_led.led1.pinIndex);
    IfxPort_setPinHigh(g_led.led2.port, g_led.led2.pinIndex);

    /* Set the pin input/output mode for both pins connected to the LEDs */
    IfxPort_setPinModeOutput(g_led.led1.port, g_led.led1.pinIndex, IfxPort_OutputMode_pushPull, g_led.led1.mode);
    IfxPort_setPinModeOutput(g_led.led2.port, g_led.led2.pinIndex, IfxPort_OutputMode_pushPull, g_led.led2.mode);

    /* Set the pad driver mode for both pins connected to the LEDs */
    IfxPort_setPinPadDriver(g_led.led1.port, g_led.led1.pinIndex, g_led.led1.padDriver);
    IfxPort_setPinPadDriver(g_led.led2.port, g_led.led2.pinIndex, g_led.led2.padDriver);
}



void blinkLED1(void)
{
    IfxPort_togglePin(g_led.led1.port, g_led.led1.pinIndex);
}

void blinkLED2(void)
{
     IfxPort_togglePin(g_led.led2.port, g_led.led2.pinIndex);
}


void turnOnLed1(void)
{
    IfxPort_setPinHigh(g_led.led1.port, g_led.led1.pinIndex);
}

void turnOnLed2(void)
{
    IfxPort_setPinHigh(g_led.led2.port, g_led.led2.pinIndex);
}

void turnOffLed1(void)
{
    IfxPort_setPinLow(g_led.led1.port, g_led.led1.pinIndex);
}

void turnOffLed2(void)
{
    IfxPort_setPinLow(g_led.led2.port, g_led.led2.pinIndex);
}
