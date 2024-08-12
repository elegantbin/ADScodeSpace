
#include "LowPass_PT1.h"

#define K_SAMPLE_TIME_PERIOD                  (float32)(50e-6)                                        /*Specifies the sampling period in seconds.*/

LowPass_PT1 g_CurrentLowPassPT1_filter;

const LowPass_PT1_Config currentLowPassPT1_config=
{
      .K = (float32)(1),                                          /**  float32 K;               < \brief Gain (continuous domain) */
      .T = (float32)(1/1000),   //0.0001                          /**   float32 T;              < \brief Time constant in [sec] (continuous domain) */
      .shiftCoef = (sint8)(4)
};

void Vadc_LowPass_PT1_Init(void)
{
    LowPass_PT1_init(&g_CurrentLowPassPT1_filter, &currentLowPassPT1_config , K_SAMPLE_TIME_PERIOD);
}
