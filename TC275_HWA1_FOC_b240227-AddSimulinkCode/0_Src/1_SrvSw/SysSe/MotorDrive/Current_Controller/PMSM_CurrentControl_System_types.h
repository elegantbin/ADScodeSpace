/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PMSM_CurrentControl_System_types.h
 *
 * Code generated for Simulink model 'PMSM_CurrentControl_System'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Thu May 30 16:25:09 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PMSM_CurrentControl_System_types_h_
#define RTW_HEADER_PMSM_CurrentControl_System_types_h_
#include "../../1_SrvSw/SysSe/MotorDrive/Current_Controller/rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_struct_cH9I994dRwS2bXyepJDlH_
#define DEFINED_TYPEDEF_FOR_struct_cH9I994dRwS2bXyepJDlH_

typedef struct {
  real_T V_base;
  real_T I_base;
  real_T N_base;
  real_T T_base;
  real_T P_base;
  real_T Z_base;
} struct_cH9I994dRwS2bXyepJDlH;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_GxQtFxbh5yfTyZ3Qom6r4_
#define DEFINED_TYPEDEF_FOR_struct_GxQtFxbh5yfTyZ3Qom6r4_

typedef struct {
  real_T T1;
  real_T T2;
  real_T delay_IIR;
  real_T damping;
  real_T x;
  real_T sigma;
  real_T Ti_i;
  real_T Ti_id;
  real_T Kp_i;
  real_T Ki_i;
  real_T Kp_id;
  real_T Ki_id;
  real_T Ki_texas;
  real_T Ki_d_texas;
  real_T delta;
  real_T Ti_speed;
  real_T Kp_speed;
  real_T Ki_speed;
  real_T Ki_speed_texas;
  real_T gamma;
  real_T Kp_fwc;
  real_T Ki_fwc;
  real_T Ti_fwc;
  real_T delay_Currents;
  real_T delay_Position;
} struct_GxQtFxbh5yfTyZ3Qom6r4;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_9tIy2hpXIgA1EOi7WWu7i_
#define DEFINED_TYPEDEF_FOR_struct_9tIy2hpXIgA1EOi7WWu7i_

typedef struct {
  real_T nonLinear;
} struct_9tIy2hpXIgA1EOi7WWu7i;

#endif

/* Parameters (default storage) */
typedef struct P_PMSM_CurrentControl_System_T_ P_PMSM_CurrentControl_System_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_PMSM_CurrentControl_S_T RT_MODEL_PMSM_CurrentControl__T;

#endif                      /* RTW_HEADER_PMSM_CurrentControl_System_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
