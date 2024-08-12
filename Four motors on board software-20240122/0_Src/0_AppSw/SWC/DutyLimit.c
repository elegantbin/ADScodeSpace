
#include "dutylimit.h"
#include "MotorMgtSwc.h"

#define R_2PHASE_mOhm        (uint16)(60)
#define I_PHASE_MAX_AMPERE   (uint16)(160)

#define U_BUS_NORM_mV         (uint16)(48000)

#define RPM_MAX               (uint16)(4000)
#define DUTY_LIMIT_MAX        (9000)
#define K_VOLTAGE_PER1RPM   (uint16)((U_BUS_NORM_mV*0.9/RPM_MAX))

#define L_DI_DT_OFFSET_STARTUP     (700+2000)
#define L_DI_DT_OFFSET_RUNNING     (8000)

uint16 g_DutyLimitMax = DUTY_LIMIT_MAX;


uint16 DutyLmit_Max(uint16 u16RPM)
{
	uint32 u32DutyLimitRet=10000;
	uint32 Speed = u16RPM;
	
	u32DutyLimitRet = (R_2PHASE_mOhm * I_PHASE_MAX_AMPERE) + (K_VOLTAGE_PER1RPM * Speed);
					  
    u32DutyLimitRet = ((u32DutyLimitRet*10000)/U_BUS_NORM_mV);

    if(MOTOR_STATE_STARTUP == g_bldc.state)
    {
       u32DutyLimitRet += L_DI_DT_OFFSET_STARTUP;
    }
    else if (MOTOR_STATE_RUNNING == g_bldc.state)
    {

        u32DutyLimitRet += L_DI_DT_OFFSET_RUNNING;
    }

    if(u32DutyLimitRet > DUTY_LIMIT_MAX)
    {
      u32DutyLimitRet = DUTY_LIMIT_MAX;
    }
	
    g_DutyLimitMax = (uint16)u32DutyLimitRet;
	return (uint16)u32DutyLimitRet;	
}

