/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PMSM_CurrentControl_System.h
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

#ifndef RTW_HEADER_PMSM_CurrentControl_System_h_
#define RTW_HEADER_PMSM_CurrentControl_System_h_

#ifndef PMSM_CurrentControl_System_COMMON_INCLUDES_
#define PMSM_CurrentControl_System_COMMON_INCLUDES_
#include "../../1_SrvSw/SysSe/MotorDrive/Current_Controller/rtwtypes.h"
#endif                         /* PMSM_CurrentControl_System_COMMON_INCLUDES_ */

#include "../../1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System_types.h"
#include "../../1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_nonfinite.h"
#include "../../1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetNaN.h"
#include <string.h>
#include "../../1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real32_T UnitDelay_DSTATE;           /* '<Root>/Unit Delay' */
  real32_T Integrator_DSTATE;          /* '<S56>/Integrator' */
  real32_T UnitDelay_DSTATE_p;         /* '<S6>/Unit Delay' */
  real32_T Integrator_DSTATE_o;        /* '<S161>/Integrator' */
  real32_T UnitDelay_DSTATE_k;         /* '<S5>/Unit Delay' */
  real32_T Integrator_DSTATE_l;        /* '<S110>/Integrator' */
  real32_T UnitDelay_DSTATE_m;         /* '<S75>/Unit Delay' */
  int8_T Integrator_PrevResetState;    /* '<S56>/Integrator' */
  int8_T Integrator_PrevResetState_e;  /* '<S161>/Integrator' */
  int8_T Integrator_PrevResetState_g;  /* '<S110>/Integrator' */
  uint8_T Integrator_IC_LOADING;       /* '<S161>/Integrator' */
  uint8_T Integrator_IC_LOADING_m;     /* '<S110>/Integrator' */
} DW_PMSM_CurrentControl_System_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Id_ref_unsat;               /* '<Root>/Id_ref' */
  real32_T Iq_ref_unsat;               /* '<Root>/Iq_ref' */
  real32_T Id_fb;                      /* '<Root>/Id_fb' */
  real32_T Iq_fb;                      /* '<Root>/Iq_fb' */
  real32_T Wm_fb;                      /* '<Root>/Wm_fb' */
} ExtU_PMSM_CurrentControl_Syst_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T Vd_ref;                     /* '<Root>/Vd_ref' */
  real32_T Vq_ref;                     /* '<Root>/Vq_ref' */
} ExtY_PMSM_CurrentControl_Syst_T;

/* Parameters (default storage) */
struct P_PMSM_CurrentControl_System_T_ {
  real32_T DiscretePIControllerwithantiwin;
                              /* Mask Parameter: DiscretePIControllerwithantiwin
                               * Referenced by:
                               *   '<S63>/Saturation'
                               *   '<S49>/DeadZone'
                               */
  real32_T DiscretePIControllerwithantiw_h;
                              /* Mask Parameter: DiscretePIControllerwithantiw_h
                               * Referenced by:
                               *   '<S168>/Saturation'
                               *   '<S154>/DeadZone'
                               */
  real32_T DiscretePIControllerwithantiw_l;
                              /* Mask Parameter: DiscretePIControllerwithantiw_l
                               * Referenced by:
                               *   '<S117>/Saturation'
                               *   '<S103>/DeadZone'
                               */
  real32_T DiscretePIControllerwithantiw_f;
                              /* Mask Parameter: DiscretePIControllerwithantiw_f
                               * Referenced by:
                               *   '<S63>/Saturation'
                               *   '<S49>/DeadZone'
                               */
  real32_T DiscretePIControllerwithantiw_d;
                              /* Mask Parameter: DiscretePIControllerwithantiw_d
                               * Referenced by:
                               *   '<S168>/Saturation'
                               *   '<S154>/DeadZone'
                               */
  real32_T DiscretePIControllerwithanti_fy;
                              /* Mask Parameter: DiscretePIControllerwithanti_fy
                               * Referenced by:
                               *   '<S117>/Saturation'
                               *   '<S103>/DeadZone'
                               */
  uint16_T CompareToConstant_const;   /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S14>/Constant'
                                       */
  uint16_T CompareToConstant1_const; /* Mask Parameter: CompareToConstant1_const
                                      * Referenced by: '<S15>/Constant'
                                      */
  real_T Enable_Value;                 /* Expression: 1
                                        * Referenced by: '<S6>/Enable'
                                        */
  real_T EnCloseLoop_Value;            /* Expression: 1
                                        * Referenced by: '<S6>/EnCloseLoop'
                                        */
  real_T Enable_Value_p;               /* Expression: 1
                                        * Referenced by: '<S2>/Enable'
                                        */
  real_T EnCloseLoop_Value_n;          /* Expression: 1
                                        * Referenced by: '<S2>/EnCloseLoop'
                                        */
  real_T FW_Enable_Value;              /* Expression: 1
                                        * Referenced by: '<S2>/FW_Enable'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S2>/Switch'
                                        */
  real_T Enable_Value_l;               /* Expression: 1
                                        * Referenced by: '<S5>/Enable'
                                        */
  real_T EnCloseLoop_Value_h;          /* Expression: 1
                                        * Referenced by: '<S5>/EnCloseLoop'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S20>/Constant'
                                        */
  real32_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S20>/Gain'
                                        */
  real32_T Switch1_Threshold;          /* Computed Parameter: Switch1_Threshold
                                        * Referenced by: '<S20>/Switch1'
                                        */
  real32_T Switch_Threshold_h;         /* Computed Parameter: Switch_Threshold_h
                                        * Referenced by: '<S20>/Switch'
                                        */
  real32_T Gain_Gain_d;                /* Computed Parameter: Gain_Gain_d
                                        * Referenced by: '<S18>/Gain'
                                        */
  real32_T Constant_Value_p;           /* Computed Parameter: Constant_Value_p
                                        * Referenced by: '<S12>/Constant'
                                        */
  real32_T ReplaceInport_satLim_Value;
                               /* Computed Parameter: ReplaceInport_satLim_Value
                                * Referenced by: '<S1>/ReplaceInport_satLim'
                                */
  real32_T Constant3_Value;            /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S10>/Constant3'
                                        */
  real32_T Bypass_FWC_Value;           /* Computed Parameter: Bypass_FWC_Value
                                        * Referenced by: '<S2>/Bypass_FWC'
                                        */
  real32_T Vd_OpenLoop_Value;          /* Computed Parameter: Vd_OpenLoop_Value
                                        * Referenced by: '<S5>/Vd_OpenLoop'
                                        */
  real32_T Vq_OpenLoop_Value;          /* Computed Parameter: Vq_OpenLoop_Value
                                        * Referenced by: '<S6>/Vq_OpenLoop'
                                        */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S180>/Gain1'
                                        */
  real32_T Lq_lumped_Value;            /* Computed Parameter: Lq_lumped_Value
                                        * Referenced by: '<S180>/Lq_lumped'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S180>/Gain2'
                                        */
  real32_T FluxPM_lumped_Value;       /* Computed Parameter: FluxPM_lumped_Value
                                       * Referenced by: '<S180>/FluxPM_lumped'
                                       */
  real32_T Gain_Gain_g;                /* Computed Parameter: Gain_Gain_g
                                        * Referenced by: '<S180>/Gain'
                                        */
  real32_T Ld_lumped_Value;            /* Computed Parameter: Ld_lumped_Value
                                        * Referenced by: '<S180>/Ld_lumped'
                                        */
  real32_T Gain_Gain_f;                /* Computed Parameter: Gain_Gain_f
                                        * Referenced by: '<S179>/Gain'
                                        */
  real32_T vsat_mask_input_Value;   /* Computed Parameter: vsat_mask_input_Value
                                     * Referenced by: '<S179>/vsat_mask_input'
                                     */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S47>/Constant1'
                                        */
  real32_T Constant1_Value_c;          /* Computed Parameter: Constant1_Value_c
                                        * Referenced by: '<S101>/Constant1'
                                        */
  real32_T Constant1_Value_p;          /* Computed Parameter: Constant1_Value_p
                                        * Referenced by: '<S152>/Constant1'
                                        */
  real32_T Vmax_ref_Value;             /* Computed Parameter: Vmax_ref_Value
                                        * Referenced by: '<Root>/Vmax_ref'
                                        */
  real32_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<Root>/Unit Delay'
                                */
  real32_T Kp_fwc_Value;               /* Expression: PI_params.Kp_fwc
                                        * Referenced by: '<S2>/Kp_fwc'
                                        */
  real32_T Ki1_Value;                  /* Computed Parameter: Ki1_Value
                                        * Referenced by: '<S2>/Ki1'
                                        */
  real32_T Integrator_gainval;         /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S56>/Integrator'
                                        */
  real32_T Saturation_Id_ref_UpperSat;
                               /* Computed Parameter: Saturation_Id_ref_UpperSat
                                * Referenced by: '<S4>/Saturation_Id_ref'
                                */
  real32_T Saturation_Id_ref_LowerSat;
                               /* Computed Parameter: Saturation_Id_ref_LowerSat
                                * Referenced by: '<S4>/Saturation_Id_ref'
                                */
  real32_T Imax_Ibase_Squar_Value; /* Computed Parameter: Imax_Ibase_Squar_Value
                                    * Referenced by: '<S4>/Imax_Ibase_Squar'
                                    */
  real32_T Kp_iq_Value;                /* Expression: PI_params.Kp_i
                                        * Referenced by: '<S6>/Kp_iq'
                                        */
  real32_T UnitDelay_InitialCondition_k;
                             /* Computed Parameter: UnitDelay_InitialCondition_k
                              * Referenced by: '<S6>/Unit Delay'
                              */
  real32_T Integrator_gainval_e;     /* Computed Parameter: Integrator_gainval_e
                                      * Referenced by: '<S161>/Integrator'
                                      */
  real32_T wm_pu2si_mech2elec_Gain;
                                  /* Computed Parameter: wm_pu2si_mech2elec_Gain
                                   * Referenced by: '<S179>/wm_pu2si_mech2elec'
                                   */
  real32_T id_pu2si_Gain;              /* Computed Parameter: id_pu2si_Gain
                                        * Referenced by: '<S179>/id_pu2si'
                                        */
  real32_T VqFF_si2pu_Gain;            /* Computed Parameter: VqFF_si2pu_Gain
                                        * Referenced by: '<S179>/VqFF_si2pu'
                                        */
  real32_T Kp_id_Value;                /* Expression: PI_params.Kp_id
                                        * Referenced by: '<S5>/Kp_id'
                                        */
  real32_T UnitDelay_InitialCondition_e;
                             /* Computed Parameter: UnitDelay_InitialCondition_e
                              * Referenced by: '<S5>/Unit Delay'
                              */
  real32_T Integrator_gainval_n;     /* Computed Parameter: Integrator_gainval_n
                                      * Referenced by: '<S110>/Integrator'
                                      */
  real32_T iq_pu2si_Gain;              /* Computed Parameter: iq_pu2si_Gain
                                        * Referenced by: '<S179>/iq_pu2si'
                                        */
  real32_T NegSign_Gain;               /* Computed Parameter: NegSign_Gain
                                        * Referenced by: '<S179>/NegSign'
                                        */
  real32_T VdFF_si2pu_Gain;            /* Computed Parameter: VdFF_si2pu_Gain
                                        * Referenced by: '<S179>/VdFF_si2pu'
                                        */
  real32_T Filter_Constant_Value;   /* Computed Parameter: Filter_Constant_Value
                                     * Referenced by: '<S75>/Filter_Constant'
                                     */
  real32_T One_Value;                  /* Computed Parameter: One_Value
                                        * Referenced by: '<S75>/One'
                                        */
  real32_T UnitDelay_InitialCondition_o;
                             /* Computed Parameter: UnitDelay_InitialCondition_o
                              * Referenced by: '<S75>/Unit Delay'
                              */
  real32_T Clamping_zero_Value;       /* Computed Parameter: Clamping_zero_Value
                                       * Referenced by: '<S101>/Clamping_zero'
                                       */
  real32_T Ki_id_Value;                /* Computed Parameter: Ki_id_Value
                                        * Referenced by: '<S5>/Ki_id'
                                        */
  real32_T Clamping_zero_Value_k;   /* Computed Parameter: Clamping_zero_Value_k
                                     * Referenced by: '<S152>/Clamping_zero'
                                     */
  real32_T Ki_iq_Value;                /* Computed Parameter: Ki_iq_Value
                                        * Referenced by: '<S6>/Ki_iq'
                                        */
  real32_T Clamping_zero_Value_e;   /* Computed Parameter: Clamping_zero_Value_e
                                     * Referenced by: '<S47>/Clamping_zero'
                                     */
  real32_T Ki_fwc_Value;               /* Computed Parameter: Ki_fwc_Value
                                        * Referenced by: '<S2>/Ki_fwc'
                                        */
  uint16_T ReplaceInport_satMethod_Value;
                            /* Computed Parameter: ReplaceInport_satMethod_Value
                             * Referenced by: '<S1>/ReplaceInport_satMethod'
                             */
  uint16_T ChosenMethod_Value;         /* Computed Parameter: ChosenMethod_Value
                                        * Referenced by: '<S10>/ChosenMethod'
                                        */
  uint16_T enableInportSatMethod_Value;
                              /* Computed Parameter: enableInportSatMethod_Value
                               * Referenced by: '<S10>/enableInportSatMethod'
                               */
  uint16_T enableInportSatLim_Value;
                                 /* Computed Parameter: enableInportSatLim_Value
                                  * Referenced by: '<S10>/enableInportSatLim'
                                  */
  int8_T Constant_Value_k;             /* Computed Parameter: Constant_Value_k
                                        * Referenced by: '<S47>/Constant'
                                        */
  int8_T Constant2_Value;              /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S47>/Constant2'
                                        */
  int8_T Constant3_Value_n;            /* Computed Parameter: Constant3_Value_n
                                        * Referenced by: '<S47>/Constant3'
                                        */
  int8_T Constant4_Value;              /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S47>/Constant4'
                                        */
  int8_T Constant_Value_h;             /* Computed Parameter: Constant_Value_h
                                        * Referenced by: '<S101>/Constant'
                                        */
  int8_T Constant2_Value_h;            /* Computed Parameter: Constant2_Value_h
                                        * Referenced by: '<S101>/Constant2'
                                        */
  int8_T Constant3_Value_a;            /* Computed Parameter: Constant3_Value_a
                                        * Referenced by: '<S101>/Constant3'
                                        */
  int8_T Constant4_Value_h;            /* Computed Parameter: Constant4_Value_h
                                        * Referenced by: '<S101>/Constant4'
                                        */
  int8_T Constant_Value_c;             /* Computed Parameter: Constant_Value_c
                                        * Referenced by: '<S152>/Constant'
                                        */
  int8_T Constant2_Value_p;            /* Computed Parameter: Constant2_Value_p
                                        * Referenced by: '<S152>/Constant2'
                                        */
  int8_T Constant3_Value_n3;           /* Computed Parameter: Constant3_Value_n3
                                        * Referenced by: '<S152>/Constant3'
                                        */
  int8_T Constant4_Value_g;            /* Computed Parameter: Constant4_Value_g
                                        * Referenced by: '<S152>/Constant4'
                                        */
  uint8_T Constant_Value_g;            /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S179>/Constant'
                                        */
  uint8_T Switch_Threshold_p;          /* Computed Parameter: Switch_Threshold_p
                                        * Referenced by: '<S179>/Switch'
                                        */
  uint8_T Constant2_Value_j;           /* Computed Parameter: Constant2_Value_j
                                        * Referenced by: '<S180>/Constant2'
                                        */
  uint8_T Switch2_Threshold;           /* Computed Parameter: Switch2_Threshold
                                        * Referenced by: '<S180>/Switch2'
                                        */
  uint8_T Constant_Value_i;            /* Computed Parameter: Constant_Value_i
                                        * Referenced by: '<S180>/Constant'
                                        */
  uint8_T Switch_Threshold_g;          /* Computed Parameter: Switch_Threshold_g
                                        * Referenced by: '<S180>/Switch'
                                        */
  uint8_T Constant1_Value_i;           /* Computed Parameter: Constant1_Value_i
                                        * Referenced by: '<S180>/Constant1'
                                        */
  uint8_T Switch1_Threshold_c;        /* Computed Parameter: Switch1_Threshold_c
                                       * Referenced by: '<S180>/Switch1'
                                       */
};

/* Real-time Model Data Structure */
struct tag_RTM_PMSM_CurrentControl_S_T {
  const char_T * volatile errorStatus;
  DW_PMSM_CurrentControl_System_T *dwork;
};

/* Block parameters (default storage) */
extern P_PMSM_CurrentControl_System_T PMSM_CurrentControl_System_P;
extern RT_MODEL_PMSM_CurrentControl__T PMSM_CurrentControl_System_M_;
extern RT_MODEL_PMSM_CurrentControl__T *const PMSM_CurrentControl_System_MPtr;      /* Real-time model */
extern DW_PMSM_CurrentControl_System_T PMSM_CurrentControl_System_DW;/* Observable states */

extern ExtY_PMSM_CurrentControl_Syst_T PMSM_CurrentControl_System_Y;/* External outputs */
extern ExtU_PMSM_CurrentControl_Syst_T PMSM_CurrentControl_System_U;/* External inputs */
/* Model entry point functions */
extern void PMSM_CurrentControl_System_initialize
  (RT_MODEL_PMSM_CurrentControl__T *const PMSM_CurrentControl_System_M,
   ExtU_PMSM_CurrentControl_Syst_T *PMSM_CurrentControl_System_U,
   ExtY_PMSM_CurrentControl_Syst_T *PMSM_CurrentControl_System_Y);
extern void PMSM_CurrentControl_System_step(RT_MODEL_PMSM_CurrentControl__T *
  const PMSM_CurrentControl_System_M, ExtU_PMSM_CurrentControl_Syst_T
  *PMSM_CurrentControl_System_U, ExtY_PMSM_CurrentControl_Syst_T
  *PMSM_CurrentControl_System_Y);
extern void PMSM_CurrentControl_System_terminate(RT_MODEL_PMSM_CurrentControl__T
  *const PMSM_CurrentControl_System_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S19>/Data Type Duplicate' : Unused code path elimination
 * Block '<S19>/Data Type Propagation' : Unused code path elimination
 * Block '<S20>/Data Type Duplicate' : Unused code path elimination
 * Block '<S1>/Data Type Duplicate' : Unused code path elimination
 * Block '<S10>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S10>/Data Type Duplicate2' : Unused code path elimination
 * Block '<S75>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S179>/Data Type Duplicate' : Unused code path elimination
 * Block '<S181>/Data Type Duplicate' : Unused code path elimination
 * Block '<S182>/Data Type Duplicate' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PMSM_CurrentControl_System'
 * '<S1>'   : 'PMSM_CurrentControl_System/DQ Limiter'
 * '<S2>'   : 'PMSM_CurrentControl_System/FW_Controller'
 * '<S3>'   : 'PMSM_CurrentControl_System/IIR Filter'
 * '<S4>'   : 'PMSM_CurrentControl_System/Iq limiter'
 * '<S5>'   : 'PMSM_CurrentControl_System/PI_Controller_Id'
 * '<S6>'   : 'PMSM_CurrentControl_System/PI_Controller_Iq'
 * '<S7>'   : 'PMSM_CurrentControl_System/PMSM Feed Forward Control'
 * '<S8>'   : 'PMSM_CurrentControl_System/DQ Limiter/D-Q Equivalence'
 * '<S9>'   : 'PMSM_CurrentControl_System/DQ Limiter/D//Q Axis Priority'
 * '<S10>'  : 'PMSM_CurrentControl_System/DQ Limiter/Inport//Dialog Selection'
 * '<S11>'  : 'PMSM_CurrentControl_System/DQ Limiter/Magnitude_calc'
 * '<S12>'  : 'PMSM_CurrentControl_System/DQ Limiter/D-Q Equivalence/Limiter'
 * '<S13>'  : 'PMSM_CurrentControl_System/DQ Limiter/D-Q Equivalence/Passthrough'
 * '<S14>'  : 'PMSM_CurrentControl_System/DQ Limiter/D//Q Axis Priority/Compare To Constant'
 * '<S15>'  : 'PMSM_CurrentControl_System/DQ Limiter/D//Q Axis Priority/Compare To Constant1'
 * '<S16>'  : 'PMSM_CurrentControl_System/DQ Limiter/D//Q Axis Priority/flipInputs'
 * '<S17>'  : 'PMSM_CurrentControl_System/DQ Limiter/D//Q Axis Priority/flipInputs1'
 * '<S18>'  : 'PMSM_CurrentControl_System/DQ Limiter/D//Q Axis Priority/limiter'
 * '<S19>'  : 'PMSM_CurrentControl_System/DQ Limiter/D//Q Axis Priority/limiter/limitRef1'
 * '<S20>'  : 'PMSM_CurrentControl_System/DQ Limiter/D//Q Axis Priority/limiter/limitRef2'
 * '<S21>'  : 'PMSM_CurrentControl_System/DQ Limiter/D//Q Axis Priority/limiter/passThrough'
 * '<S22>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset'
 * '<S23>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Anti-windup'
 * '<S24>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/D Gain'
 * '<S25>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Filter'
 * '<S26>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Filter ICs'
 * '<S27>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/I Gain'
 * '<S28>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Ideal P Gain'
 * '<S29>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Ideal P Gain Fdbk'
 * '<S30>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Integrator'
 * '<S31>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Integrator ICs'
 * '<S32>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/N Copy'
 * '<S33>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/N Gain'
 * '<S34>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/P Copy'
 * '<S35>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Parallel P Gain'
 * '<S36>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Reset Signal'
 * '<S37>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Saturation'
 * '<S38>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Saturation Fdbk'
 * '<S39>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Sum'
 * '<S40>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Sum Fdbk'
 * '<S41>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Tracking Mode'
 * '<S42>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Tracking Mode Sum'
 * '<S43>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Tsamp - Integral'
 * '<S44>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Tsamp - Ngain'
 * '<S45>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/postSat Signal'
 * '<S46>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/preSat Signal'
 * '<S47>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel'
 * '<S48>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S49>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S50>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/D Gain/Disabled'
 * '<S51>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Filter/Disabled'
 * '<S52>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Filter ICs/Disabled'
 * '<S53>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/I Gain/External Parameters'
 * '<S54>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Ideal P Gain/Passthrough'
 * '<S55>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Ideal P Gain Fdbk/Disabled'
 * '<S56>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Integrator/Discrete'
 * '<S57>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Integrator ICs/External IC'
 * '<S58>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/N Copy/Disabled wSignal Specification'
 * '<S59>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/N Gain/Disabled'
 * '<S60>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/P Copy/Disabled'
 * '<S61>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Parallel P Gain/External Parameters'
 * '<S62>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Reset Signal/External Reset'
 * '<S63>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Saturation/Enabled'
 * '<S64>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Saturation Fdbk/Disabled'
 * '<S65>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Sum/Sum_PI'
 * '<S66>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Sum Fdbk/Disabled'
 * '<S67>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Tracking Mode/Disabled'
 * '<S68>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Tracking Mode Sum/Passthrough'
 * '<S69>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Tsamp - Integral/TsSignalSpecification'
 * '<S70>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/Tsamp - Ngain/Passthrough'
 * '<S71>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/postSat Signal/Forward_Path'
 * '<S72>'  : 'PMSM_CurrentControl_System/FW_Controller/Discrete PI Controller  with anti-windup & reset/preSat Signal/Forward_Path'
 * '<S73>'  : 'PMSM_CurrentControl_System/IIR Filter/IIR Filter'
 * '<S74>'  : 'PMSM_CurrentControl_System/IIR Filter/IIR Filter/Low-pass'
 * '<S75>'  : 'PMSM_CurrentControl_System/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S76>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset'
 * '<S77>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Anti-windup'
 * '<S78>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/D Gain'
 * '<S79>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Filter'
 * '<S80>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Filter ICs'
 * '<S81>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/I Gain'
 * '<S82>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Ideal P Gain'
 * '<S83>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Ideal P Gain Fdbk'
 * '<S84>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Integrator'
 * '<S85>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Integrator ICs'
 * '<S86>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/N Copy'
 * '<S87>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/N Gain'
 * '<S88>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/P Copy'
 * '<S89>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Parallel P Gain'
 * '<S90>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Reset Signal'
 * '<S91>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Saturation'
 * '<S92>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Saturation Fdbk'
 * '<S93>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Sum'
 * '<S94>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Sum Fdbk'
 * '<S95>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Tracking Mode'
 * '<S96>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Tracking Mode Sum'
 * '<S97>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Tsamp - Integral'
 * '<S98>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Tsamp - Ngain'
 * '<S99>'  : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/postSat Signal'
 * '<S100>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/preSat Signal'
 * '<S101>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel'
 * '<S102>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S103>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S104>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/D Gain/Disabled'
 * '<S105>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Filter/Disabled'
 * '<S106>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Filter ICs/Disabled'
 * '<S107>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/I Gain/External Parameters'
 * '<S108>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Ideal P Gain/Passthrough'
 * '<S109>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Ideal P Gain Fdbk/Disabled'
 * '<S110>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Integrator/Discrete'
 * '<S111>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Integrator ICs/External IC'
 * '<S112>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/N Copy/Disabled wSignal Specification'
 * '<S113>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/N Gain/Disabled'
 * '<S114>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/P Copy/Disabled'
 * '<S115>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Parallel P Gain/External Parameters'
 * '<S116>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Reset Signal/External Reset'
 * '<S117>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Saturation/Enabled'
 * '<S118>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Saturation Fdbk/Disabled'
 * '<S119>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Sum/Sum_PI'
 * '<S120>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Sum Fdbk/Disabled'
 * '<S121>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Tracking Mode/Disabled'
 * '<S122>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Tracking Mode Sum/Passthrough'
 * '<S123>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Tsamp - Integral/TsSignalSpecification'
 * '<S124>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/Tsamp - Ngain/Passthrough'
 * '<S125>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/postSat Signal/Forward_Path'
 * '<S126>' : 'PMSM_CurrentControl_System/PI_Controller_Id/Discrete PI Controller  with anti-windup & reset/preSat Signal/Forward_Path'
 * '<S127>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset'
 * '<S128>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Anti-windup'
 * '<S129>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/D Gain'
 * '<S130>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Filter'
 * '<S131>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Filter ICs'
 * '<S132>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/I Gain'
 * '<S133>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Ideal P Gain'
 * '<S134>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Ideal P Gain Fdbk'
 * '<S135>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Integrator'
 * '<S136>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Integrator ICs'
 * '<S137>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/N Copy'
 * '<S138>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/N Gain'
 * '<S139>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/P Copy'
 * '<S140>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Parallel P Gain'
 * '<S141>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Reset Signal'
 * '<S142>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Saturation'
 * '<S143>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Saturation Fdbk'
 * '<S144>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Sum'
 * '<S145>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Sum Fdbk'
 * '<S146>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Tracking Mode'
 * '<S147>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Tracking Mode Sum'
 * '<S148>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Tsamp - Integral'
 * '<S149>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Tsamp - Ngain'
 * '<S150>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/postSat Signal'
 * '<S151>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/preSat Signal'
 * '<S152>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel'
 * '<S153>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S154>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S155>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/D Gain/Disabled'
 * '<S156>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Filter/Disabled'
 * '<S157>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Filter ICs/Disabled'
 * '<S158>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/I Gain/External Parameters'
 * '<S159>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Ideal P Gain/Passthrough'
 * '<S160>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Ideal P Gain Fdbk/Disabled'
 * '<S161>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Integrator/Discrete'
 * '<S162>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Integrator ICs/External IC'
 * '<S163>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/N Copy/Disabled wSignal Specification'
 * '<S164>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/N Gain/Disabled'
 * '<S165>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/P Copy/Disabled'
 * '<S166>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Parallel P Gain/External Parameters'
 * '<S167>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Reset Signal/External Reset'
 * '<S168>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Saturation/Enabled'
 * '<S169>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Saturation Fdbk/Disabled'
 * '<S170>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Sum/Sum_PI'
 * '<S171>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Sum Fdbk/Disabled'
 * '<S172>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Tracking Mode/Disabled'
 * '<S173>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Tracking Mode Sum/Passthrough'
 * '<S174>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Tsamp - Integral/TsSignalSpecification'
 * '<S175>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/Tsamp - Ngain/Passthrough'
 * '<S176>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/postSat Signal/Forward_Path'
 * '<S177>' : 'PMSM_CurrentControl_System/PI_Controller_Iq/Discrete PI Controller  with anti-windup & reset/preSat Signal/Forward_Path'
 * '<S178>' : 'PMSM_CurrentControl_System/PMSM Feed Forward Control/FeedForward Control Selection'
 * '<S179>' : 'PMSM_CurrentControl_System/PMSM Feed Forward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort'
 * '<S180>' : 'PMSM_CurrentControl_System/PMSM Feed Forward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/LumpedParams_InpurPorts'
 * '<S181>' : 'PMSM_CurrentControl_System/PMSM Feed Forward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/Vd_sat'
 * '<S182>' : 'PMSM_CurrentControl_System/PMSM Feed Forward Control/FeedForward Control Selection/Linear FeedForward_LumpedParameter_InputPort/Vq_sat'
 */
#endif                            /* RTW_HEADER_PMSM_CurrentControl_System_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
