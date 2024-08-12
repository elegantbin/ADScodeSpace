#ifndef FuzzyPID_H
#define FuzzyPID_H

#include "Cpu/Std/Ifx_Types.h"
#include "IfxStdIf.h"

void Get_grad_membership(float erro, float erro_c);
float Quantization(float maximum, float minimum, float x);
float Inverse_quantization(float maximum, float minimum, float qvalues);
void GetSumGrad();
void GetOUT();
float FuzzyPIDcontroller(float e_max, float e_min, float ec_max, float ec_min, float kp_max, float kp_min, float erro, float erro_c, float ki_max, float ki_min,float kd_max, float kd_min,float erro_pre, float errp_ppre);
float membership(float x, float a, float b, float c);
float fuzzyInference(float error, float error_c);
float32 FuzzyPIDControl(uint16 speed_ref,uint16 raw_speed);

#endif
