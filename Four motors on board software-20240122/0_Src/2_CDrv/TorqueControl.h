
#ifndef TORQUE_CONTROL_H_
#define TORQUE_CONTROL_H_

#include "Cpu/Std/Ifx_Types.h"
#include "IfxStdIf.h"

IFX_EXTERN uint16 REF_Current_By_Torque;

void Torque_Calculate(void);
void Torque_To_Current(void);


void TorqueCalculation(void);
#endif /* VELOCITY_PI_H_ */
