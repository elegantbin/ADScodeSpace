/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PMSM_MTPA_Module.h
 *
 * Code generated for Simulink model 'PMSM_MTPA_Module'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Fri May 31 11:51:14 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PMSM_MTPA_Module_h_
#define RTW_HEADER_PMSM_MTPA_Module_h_

#ifndef PMSM_MTPA_Module_COMMON_INCLUDES_
#define PMSM_MTPA_Module_COMMON_INCLUDES_
#include "../../1_SrvSw/SysSe/MotorDrive/Current_Controller/rtwtypes.h"
#endif                                 /* PMSM_MTPA_Module_COMMON_INCLUDES_ */

#include "../../1_SrvSw/SysSe/MotorDrive/MTPA/PMSM_MTPA_Module_types.h"
#include <string.h>
#include "../../1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Merge[2];                     /* '<S7>/Merge' */
} B_PMSM_MTPA_Module_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Torque_ref;                   /* '<Root>/Torque_ref' */
  real_T speed_ref;                    /* '<Root>/speed_ref' */
} ExtU_PMSM_MTPA_Module_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Id_ref_out;                   /* '<Root>/Id_ref_out' */
  real_T Iq_ref_out;                   /* '<Root>/Iq_ref_out' */
} ExtY_PMSM_MTPA_Module_T;

/* Parameters (default storage) */
struct P_PMSM_MTPA_Module_T_ {
  struct_cH9I994dRwS2bXyepJDlH PU_System;/* Variable: PU_System
                                          * Referenced by: '<Root>/Iq_ref_saturation'
                                          */
  uint16_T CompareToConstant_const;   /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S29>/Constant'
                                       */
  uint16_T CompareToConstant1_const; /* Mask Parameter: CompareToConstant1_const
                                      * Referenced by: '<S30>/Constant'
                                      */
  real_T Constant_Value;               /* Expression: mtpablkSett.ipmsmfwterm5
                                        * Referenced by: '<S18>/Constant'
                                        */
  real_T fluxPMLd_Lq2_Value;           /* Expression: mtpablkSett.ipmsmfwterm6
                                        * Referenced by: '<S17>/fluxPMLd_Lq2'
                                        */
  real_T ld2_lq2_Value;              /* Expression: 1/mtpablkSett.ipmsmfwsalterm
                                      * Referenced by: '<S17>/ld2_lq2'
                                      */
  real_T fluxPM2_Lq2_Value;            /* Expression: mtpablkSett.ipmsmfwterm7
                                        * Referenced by: '<S17>/fluxPM2_Lq2'
                                        */
  real_T Gain_Gain;
         /* Expression: mtpablkSett.vsmax_scale_a*sqrt(mtpablkSett.ipmsmfwterm8)
          * Referenced by: '<S17>/Gain'
          */
  real_T Constant_Value_b;
         /* Expression: mtpablkSett.vsmax_scale_b*sqrt(mtpablkSett.ipmsmfwterm8)
          * Referenced by: '<S17>/Constant'
          */
  real_T u_Lq2_Value;                  /* Expression: 1
                                        * Referenced by: '<S17>/1_Lq2'
                                        */
  real_T Gain_Gain_a;                  /* Expression: mtpablkSett.ipmsmfwiqCorr1
                                        * Referenced by: '<S19>/Gain'
                                        */
  real_T Constant_Value_l;             /* Expression: 1
                                        * Referenced by: '<S19>/Constant'
                                        */
  real_T Gain1_Gain;                   /* Expression: mtpablkSett.ipmsmfwiqCorr1
                                        * Referenced by: '<S19>/Gain1'
                                        */
  real_T Constant1_Value;              /* Expression: 1
                                        * Referenced by: '<S19>/Constant1'
                                        */
  real_T Constant_Value_m;             /* Expression: 0
                                        * Referenced by: '<S35>/Constant'
                                        */
  real_T Gain_Gain_d;                  /* Expression: -1
                                        * Referenced by: '<S35>/Gain'
                                        */
  real_T Switch1_Threshold;            /* Expression: 0
                                        * Referenced by: '<S35>/Switch1'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S35>/Switch'
                                        */
  real_T Gain_Gain_j;                  /* Expression: -1
                                        * Referenced by: '<S33>/Gain'
                                        */
  real_T Constant_Value_e;             /* Expression: 1
                                        * Referenced by: '<S27>/Constant'
                                        */
  real_T ReplaceInport_satLim_Value;   /* Expression: 0
                                        * Referenced by: '<S20>/ReplaceInport_satLim'
                                        */
  real_T Constant3_Value;              /* Expression: Vmax
                                        * Referenced by: '<S25>/Constant3'
                                        */
  real_T zero_Gain;                    /* Expression: 0
                                        * Referenced by: '<S38>/zero'
                                        */
  real_T Constant_Value_g;             /* Expression: 0
                                        * Referenced by: '<S37>/Constant'
                                        */
  real_T term2_Value;                  /* Expression: sqrt(mtpablkSett.term2_fw)
                                        * Referenced by: '<S16>/term2'
                                        */
  real_T term3_Value; /* Expression: mtpablkSett.term3_fw*mtpablkSett.term3_gain
                       * Referenced by: '<S16>/term3'
                       */
  real_T Gain_Gain_o;                  /* Expression: mtpablkSett.term3_gain2_a
                                        * Referenced by: '<S16>/Gain'
                                        */
  real_T Constant1_Value_b;            /* Expression: mtpablkSett.term3_gain2_b
                                        * Referenced by: '<S16>/Constant1'
                                        */
  real_T u_Gain;                 /* Expression: sqrt(-mtpablkSett.term3_gain2_c)
                                  * Referenced by: '<S16>/ 1'
                                  */
  real_T _Gain;                        /* Expression: -1
                                        * Referenced by: '<S16>/ '
                                        */
  real_T term1_Value;                  /* Expression: mtpablkSett.term1_fw
                                        * Referenced by: '<S16>/term1'
                                        */
  real_T Constant_Value_ls;            /* Expression: 1
                                        * Referenced by: '<S22>/Constant'
                                        */
  real_T Gain_Gain_au;                 /* Expression: mtpablkSett.ipmsmfwiqCorr1
                                        * Referenced by: '<S22>/Gain'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S16>/Constant2'
                                        */
  real_T Gain1_Gain_i;                 /* Expression: mtpablkSett.ipmsmfwiqCorr1
                                        * Referenced by: '<S22>/Gain1'
                                        */
  real_T Constant1_Value_h;            /* Expression: 1
                                        * Referenced by: '<S22>/Constant1'
                                        */
  real_T Gain_Gain_dx;                 /* Expression: polePairs
                                        * Referenced by: '<S9>/Gain'
                                        */
  real_T Gain_Gain_k;                  /* Expression: mtpablkSett.V_base_PU
                                        * Referenced by: '<S12>/Gain'
                                        */
  real_T Vdc_lumped_Value;             /* Expression: double(V_dc)
                                        * Referenced by: '<S12>/Vdc_lumped'
                                        */
  real_T sign_Threshold;               /* Expression: 0
                                        * Referenced by: '<S5>/sign'
                                        */
  real_T Id_ref_nofw_Value;            /* Expression: 0
                                        * Referenced by: '<Root>/Id_ref_nofw'
                                        */
  real_T Gain_Gain_h;                  /* Expression: mtpablkSett.ipmsmT2i
                                        * Referenced by: '<S7>/Gain'
                                        */
  real_T Saturation_UpperSat;          /* Expression: mtpablkSett.I_max
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -mtpablkSett.I_max
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T term1_Value_n;                /* Expression: mtpablkSett.ipmsmmtpaterm1
                                        * Referenced by: '<S8>/term1'
                                        */
  real_T term3_Gain;                   /* Expression: mtpablkSett.ipmsmmtpaterm3
                                        * Referenced by: '<S8>/term3'
                                        */
  real_T term2_Value_e;          /* Expression: sqrt(mtpablkSett.ipmsmmtpaterm2)
                                  * Referenced by: '<S8>/term2'
                                  */
  real_T Saturation2_UpperSat;         /* Expression: 0
                                        * Referenced by: '<S13>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -mtpablkSett.I_max
                                        * Referenced by: '<S13>/Saturation2'
                                        */
  real_T Gain1_Gain_a;                 /* Expression: mtpablkSett.mech2elec
                                        * Referenced by: '<S7>/Gain1'
                                        */
  real_T Ld_Gain;                      /* Expression: mtpablkSett.Ld_term
                                        * Referenced by: '<S40>/Ld'
                                        */
  real_T FluxPM_Gain;                  /* Expression: mtpablkSett.FluxPM_term
                                        * Referenced by: '<S40>/FluxPM'
                                        */
  real_T Lq_Gain;                      /* Expression: mtpablkSett.Lq_term
                                        * Referenced by: '<S40>/Lq'
                                        */
  real_T Gain_Gain_f;                  /* Expression: mtpablkSett.vsmax_scale_a
                                        * Referenced by: '<S11>/Gain'
                                        */
  real_T Constant_Value_o;             /* Expression: mtpablkSett.vsmax_scale_b
                                        * Referenced by: '<S11>/Constant'
                                        */
  real_T Merge_InitialOutput;         /* Computed Parameter: Merge_InitialOutput
                                       * Referenced by: '<S7>/Merge'
                                       */
  real_T Enable_fwc_Value;             /* Expression: 1
                                        * Referenced by: '<Root>/Enable_fwc'
                                        */
  real_T Switch_Threshold_c;           /* Expression: 0
                                        * Referenced by: '<Root>/Switch'
                                        */
  uint16_T ReplaceInport_satMethod_Value;
                            /* Computed Parameter: ReplaceInport_satMethod_Value
                             * Referenced by: '<S20>/ReplaceInport_satMethod'
                             */
  uint16_T ChosenMethod_Value;         /* Computed Parameter: ChosenMethod_Value
                                        * Referenced by: '<S25>/ChosenMethod'
                                        */
  uint16_T enableInportSatMethod_Value;
                              /* Computed Parameter: enableInportSatMethod_Value
                               * Referenced by: '<S25>/enableInportSatMethod'
                               */
  uint16_T enableInportSatLim_Value;
                                 /* Computed Parameter: enableInportSatLim_Value
                                  * Referenced by: '<S25>/enableInportSatLim'
                                  */
  uint8_T Constant_Value_ll;           /* Computed Parameter: Constant_Value_ll
                                        * Referenced by: '<S12>/Constant'
                                        */
  uint8_T Switch_Threshold_f;          /* Computed Parameter: Switch_Threshold_f
                                        * Referenced by: '<S12>/Switch'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_PMSM_MTPA_Module_T {
  const char_T * volatile errorStatus;
  B_PMSM_MTPA_Module_T *blockIO;
};

/* Block parameters (default storage) */
extern P_PMSM_MTPA_Module_T PMSM_MTPA_Module_P;

/* Model entry point functions */
extern void PMSM_MTPA_Module_initialize(RT_MODEL_PMSM_MTPA_Module_T *const
  PMSM_MTPA_Module_M, ExtU_PMSM_MTPA_Module_T *PMSM_MTPA_Module_U,
  ExtY_PMSM_MTPA_Module_T *PMSM_MTPA_Module_Y);
extern void PMSM_MTPA_Module_step(RT_MODEL_PMSM_MTPA_Module_T *const
  PMSM_MTPA_Module_M, ExtU_PMSM_MTPA_Module_T *PMSM_MTPA_Module_U,
  ExtY_PMSM_MTPA_Module_T *PMSM_MTPA_Module_Y);
extern void PMSM_MTPA_Module_terminate(RT_MODEL_PMSM_MTPA_Module_T *const
  PMSM_MTPA_Module_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S13>/Data Type Duplicate' : Unused code path elimination
 * Block '<S27>/Data Type Duplicate' : Unused code path elimination
 * Block '<S34>/Data Type Duplicate' : Unused code path elimination
 * Block '<S34>/Data Type Propagation' : Unused code path elimination
 * Block '<S35>/Data Type Duplicate' : Unused code path elimination
 * Block '<S20>/Data Type Duplicate' : Unused code path elimination
 * Block '<S25>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S25>/Data Type Duplicate2' : Unused code path elimination
 * Block '<S26>/Sqrt' : Unused code path elimination
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
 * '<Root>' : 'PMSM_MTPA_Module'
 * '<S1>'   : 'PMSM_MTPA_Module/MTPA Control Reference'
 * '<S2>'   : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System'
 * '<S3>'   : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM'
 * '<S4>'   : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection'
 * '<S5>'   : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/Subsystem'
 * '<S6>'   : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators'
 * '<S7>'   : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate'
 * '<S8>'   : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/Circle_MTPA_intersection'
 * '<S9>'   : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition'
 * '<S10>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/MTPA condition'
 * '<S11>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/Subsystem1'
 * '<S12>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/Subsystem2'
 * '<S13>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/Circle_MTPA_intersection/Get_Iq_ref'
 * '<S14>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/If Action Subsystem'
 * '<S15>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/If Action Subsystem1'
 * '<S16>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed'
 * '<S17>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/If Action Subsystem1/fieldWeakening'
 * '<S18>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/If Action Subsystem1/fieldWeakening/torqueTangent'
 * '<S19>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/If Action Subsystem1/fieldWeakening/update iq1'
 * '<S20>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter'
 * '<S21>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/sqrt_controlled'
 * '<S22>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/update iq2'
 * '<S23>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D-Q Equivalence'
 * '<S24>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D//Q Axis Priority'
 * '<S25>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/Inport//Dialog Selection'
 * '<S26>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/Magnitude_calc'
 * '<S27>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D-Q Equivalence/Limiter'
 * '<S28>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D-Q Equivalence/Passthrough'
 * '<S29>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D//Q Axis Priority/Compare To Constant'
 * '<S30>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D//Q Axis Priority/Compare To Constant1'
 * '<S31>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D//Q Axis Priority/flipInputs'
 * '<S32>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D//Q Axis Priority/flipInputs1'
 * '<S33>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D//Q Axis Priority/limiter'
 * '<S34>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D//Q Axis Priority/limiter/limitRef1'
 * '<S35>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D//Q Axis Priority/limiter/limitRef2'
 * '<S36>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/DQ Limiter/D//Q Axis Priority/limiter/passThrough'
 * '<S37>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/sqrt_controlled/Compare To Zero'
 * '<S38>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/sqrt_controlled/If negative value'
 * '<S39>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/FW condition/max_iq_at_speed/sqrt_controlled/If positive value'
 * '<S40>'  : 'PMSM_MTPA_Module/MTPA Control Reference/Motor_System/Interior PMSM/MTPA_FW_iteratorSelection/no_iterators/fast_and_approximate/Subsystem1/find vs'
 */
#endif                                 /* RTW_HEADER_PMSM_MTPA_Module_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
