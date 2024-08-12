
#ifndef __ROLL_PITCH_PARAMETER_H
#define __ROLL_PITCH_PARAMETER_H
#include "OsTypedefs.h"

typedef struct Roll_Pitch_ParaSet
{
	float Kp;
	float Ki;
	uint16_t Referspeed ;
	uint16_t DutyOffsetPos [7];
	int16_t  DutyOffset[6];
	uint8_t  StartCurve[7];
	uint8_t  StartUpDuty;
	int16_t   ApPosOffset[8];
	boolean  EbrakEnable ;
	int16_t ApSumStartup;
	uint16_t ApStartupCout;
	uint16_t TiprunStartCout;
	uint16_t  EbrakDuty;


}Roll_Pitch_ParaSet_t;
void Roll_Pitch_Adjust(void);

extern Roll_Pitch_ParaSet_t gOpen_Roll_Pitch_ParaSet;
extern Roll_Pitch_ParaSet_t gClose_Roll_Pitch_ParaSet;

#endif /* 0_APPSW_COMPONENTS_MOTACT_ADJUSTCURVE_H_ */
