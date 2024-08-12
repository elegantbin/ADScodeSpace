/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PMSM_CurrentControl_System_data.c
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

#include <Current_Controller/PMSM_CurrentControl_System.h>

/* Block parameters (default storage) */
P_PMSM_CurrentControl_System_T PMSM_CurrentControl_System_P = {
  /* Mask Parameter: DiscretePIControllerwithantiwin
   * Referenced by:
   *   '<S63>/Saturation'
   *   '<S49>/DeadZone'
   */
  -0.36F,

  /* Mask Parameter: DiscretePIControllerwithantiw_h
   * Referenced by:
   *   '<S168>/Saturation'
   *   '<S154>/DeadZone'
   */
  -1.0F,

  /* Mask Parameter: DiscretePIControllerwithantiw_l
   * Referenced by:
   *   '<S117>/Saturation'
   *   '<S103>/DeadZone'
   */
  -1.0F,

  /* Mask Parameter: DiscretePIControllerwithantiw_f
   * Referenced by:
   *   '<S63>/Saturation'
   *   '<S49>/DeadZone'
   */
  0.0F,

  /* Mask Parameter: DiscretePIControllerwithantiw_d
   * Referenced by:
   *   '<S168>/Saturation'
   *   '<S154>/DeadZone'
   */
  1.0F,

  /* Mask Parameter: DiscretePIControllerwithanti_fy
   * Referenced by:
   *   '<S117>/Saturation'
   *   '<S103>/DeadZone'
   */
  1.0F,

  /* Mask Parameter: CompareToConstant_const
   * Referenced by: '<S14>/Constant'
   */
  1U,

  /* Mask Parameter: CompareToConstant1_const
   * Referenced by: '<S15>/Constant'
   */
  1U,

  /* Expression: 1
   * Referenced by: '<S6>/Enable'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S6>/EnCloseLoop'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S2>/Enable'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S2>/EnCloseLoop'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S2>/FW_Enable'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S2>/Switch'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S5>/Enable'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S5>/EnCloseLoop'
   */
  1.0,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S20>/Constant'
   */
  0.0F,

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S20>/Gain'
   */
  -1.0F,

  /* Computed Parameter: Switch1_Threshold
   * Referenced by: '<S20>/Switch1'
   */
  0.0F,

  /* Computed Parameter: Switch_Threshold_h
   * Referenced by: '<S20>/Switch'
   */
  0.0F,

  /* Computed Parameter: Gain_Gain_d
   * Referenced by: '<S18>/Gain'
   */
  -1.0F,

  /* Computed Parameter: Constant_Value_p
   * Referenced by: '<S12>/Constant'
   */
  1.0F,

  /* Computed Parameter: ReplaceInport_satLim_Value
   * Referenced by: '<S1>/ReplaceInport_satLim'
   */
  0.0F,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S10>/Constant3'
   */
  0.95F,

  /* Computed Parameter: Bypass_FWC_Value
   * Referenced by: '<S2>/Bypass_FWC'
   */
  0.0F,

  /* Computed Parameter: Vd_OpenLoop_Value
   * Referenced by: '<S5>/Vd_OpenLoop'
   */
  0.2F,

  /* Computed Parameter: Vq_OpenLoop_Value
   * Referenced by: '<S6>/Vq_OpenLoop'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<S180>/Gain1'
   */
  3302.62622F,

  /* Computed Parameter: Lq_lumped_Value
   * Referenced by: '<S180>/Lq_lumped'
   */
  0.414149344F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<S180>/Gain2'
   */
  9.90787888F,

  /* Computed Parameter: FluxPM_lumped_Value
   * Referenced by: '<S180>/FluxPM_lumped'
   */
  0.1311F,

  /* Computed Parameter: Gain_Gain_g
   * Referenced by: '<S180>/Gain'
   */
  3302.62622F,

  /* Computed Parameter: Ld_lumped_Value
   * Referenced by: '<S180>/Ld_lumped'
   */
  0.353381F,

  /* Computed Parameter: Gain_Gain_f
   * Referenced by: '<S179>/Gain'
   */
  1.0F,

  /* Computed Parameter: vsat_mask_input_Value
   * Referenced by: '<S179>/vsat_mask_input'
   */
  0.05F,

  /* Computed Parameter: Constant1_Value
   * Referenced by: '<S47>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant1_Value_c
   * Referenced by: '<S101>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant1_Value_p
   * Referenced by: '<S152>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Vmax_ref_Value
   * Referenced by: '<Root>/Vmax_ref'
   */
  0.95F,

  /* Computed Parameter: UnitDelay_InitialCondition
   * Referenced by: '<Root>/Unit Delay'
   */
  0.0F,

  /* Expression: PI_params.Kp_fwc
   * Referenced by: '<S2>/Kp_fwc'
   */
  0.225693569F,

  /* Computed Parameter: Ki1_Value
   * Referenced by: '<S2>/Ki1'
   */
  0.0F,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S56>/Integrator'
   */
  1.0F,

  /* Computed Parameter: Saturation_Id_ref_UpperSat
   * Referenced by: '<S4>/Saturation_Id_ref'
   */
  0.0F,

  /* Computed Parameter: Saturation_Id_ref_LowerSat
   * Referenced by: '<S4>/Saturation_Id_ref'
   */
  -0.36F,

  /* Computed Parameter: Imax_Ibase_Squar_Value
   * Referenced by: '<S4>/Imax_Ibase_Squar'
   */
  0.1296F,

  /* Expression: PI_params.Kp_i
   * Referenced by: '<S6>/Kp_iq'
   */
  15.0832758F,

  /* Computed Parameter: UnitDelay_InitialCondition_k
   * Referenced by: '<S6>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: Integrator_gainval_e
   * Referenced by: '<S161>/Integrator'
   */
  1.0F,

  /* Computed Parameter: wm_pu2si_mech2elec_Gain
   * Referenced by: '<S179>/wm_pu2si_mech2elec'
   */
  5.0F,

  /* Computed Parameter: id_pu2si_Gain
   * Referenced by: '<S179>/id_pu2si'
   */
  1.0F,

  /* Computed Parameter: VqFF_si2pu_Gain
   * Referenced by: '<S179>/VqFF_si2pu'
   */
  1.0F,

  /* Expression: PI_params.Kp_id
   * Referenced by: '<S5>/Kp_id'
   */
  12.8701F,

  /* Computed Parameter: UnitDelay_InitialCondition_e
   * Referenced by: '<S5>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: Integrator_gainval_n
   * Referenced by: '<S110>/Integrator'
   */
  1.0F,

  /* Computed Parameter: iq_pu2si_Gain
   * Referenced by: '<S179>/iq_pu2si'
   */
  1.0F,

  /* Computed Parameter: NegSign_Gain
   * Referenced by: '<S179>/NegSign'
   */
  -1.0F,

  /* Computed Parameter: VdFF_si2pu_Gain
   * Referenced by: '<S179>/VdFF_si2pu'
   */
  1.0F,

  /* Computed Parameter: Filter_Constant_Value
   * Referenced by: '<S75>/Filter_Constant'
   */
  0.01F,

  /* Computed Parameter: One_Value
   * Referenced by: '<S75>/One'
   */
  0.99F,

  /* Computed Parameter: UnitDelay_InitialCondition_o
   * Referenced by: '<S75>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: Clamping_zero_Value
   * Referenced by: '<S101>/Clamping_zero'
   */
  0.0F,

  /* Computed Parameter: Ki_id_Value
   * Referenced by: '<S5>/Ki_id'
   */
  0.108994909F,

  /* Computed Parameter: Clamping_zero_Value_k
   * Referenced by: '<S152>/Clamping_zero'
   */
  0.0F,

  /* Computed Parameter: Ki_iq_Value
   * Referenced by: '<S6>/Ki_iq'
   */
  0.108994909F,

  /* Computed Parameter: Clamping_zero_Value_e
   * Referenced by: '<S47>/Clamping_zero'
   */
  0.0F,

  /* Computed Parameter: Ki_fwc_Value
   * Referenced by: '<S2>/Ki_fwc'
   */
  0.00163090904F,

  /* Computed Parameter: ReplaceInport_satMethod_Value
   * Referenced by: '<S1>/ReplaceInport_satMethod'
   */
  0U,

  /* Computed Parameter: ChosenMethod_Value
   * Referenced by: '<S10>/ChosenMethod'
   */
  3U,

  /* Computed Parameter: enableInportSatMethod_Value
   * Referenced by: '<S10>/enableInportSatMethod'
   */
  0U,

  /* Computed Parameter: enableInportSatLim_Value
   * Referenced by: '<S10>/enableInportSatLim'
   */
  0U,

  /* Computed Parameter: Constant_Value_k
   * Referenced by: '<S47>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S47>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value_n
   * Referenced by: '<S47>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S47>/Constant4'
   */
  -1,

  /* Computed Parameter: Constant_Value_h
   * Referenced by: '<S101>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_h
   * Referenced by: '<S101>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value_a
   * Referenced by: '<S101>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value_h
   * Referenced by: '<S101>/Constant4'
   */
  -1,

  /* Computed Parameter: Constant_Value_c
   * Referenced by: '<S152>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_p
   * Referenced by: '<S152>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value_n3
   * Referenced by: '<S152>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value_g
   * Referenced by: '<S152>/Constant4'
   */
  -1,

  /* Computed Parameter: Constant_Value_g
   * Referenced by: '<S179>/Constant'
   */
  0U,

  /* Computed Parameter: Switch_Threshold_p
   * Referenced by: '<S179>/Switch'
   */
  0U,

  /* Computed Parameter: Constant2_Value_j
   * Referenced by: '<S180>/Constant2'
   */
  0U,

  /* Computed Parameter: Switch2_Threshold
   * Referenced by: '<S180>/Switch2'
   */
  0U,

  /* Computed Parameter: Constant_Value_i
   * Referenced by: '<S180>/Constant'
   */
  0U,

  /* Computed Parameter: Switch_Threshold_g
   * Referenced by: '<S180>/Switch'
   */
  0U,

  /* Computed Parameter: Constant1_Value_i
   * Referenced by: '<S180>/Constant1'
   */
  0U,

  /* Computed Parameter: Switch1_Threshold_c
   * Referenced by: '<S180>/Switch1'
   */
  0U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
