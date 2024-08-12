/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PMSM_MTPA_Module_data.c
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

#include <MTPA/PMSM_MTPA_Module.h>

/* Block parameters (default storage) */
P_PMSM_MTPA_Module_T PMSM_MTPA_Module_P = {
  /* Variable: PU_System
   * Referenced by: '<Root>/Iq_ref_saturation'
   */
  {
    27.712812921102039,
    333.33333333333337,
    2622.0,
    33.079733725307527,
    13856.406460551021,
    0.083138438763306108
  },

  /* Mask Parameter: CompareToConstant_const
   * Referenced by: '<S29>/Constant'
   */
  1U,

  /* Mask Parameter: CompareToConstant1_const
   * Referenced by: '<S30>/Constant'
   */
  1U,

  /* Expression: mtpablkSett.ipmsmfwterm5
   * Referenced by: '<S18>/Constant'
   */
  -2.1573739386070105,

  /* Expression: mtpablkSett.ipmsmfwterm6
   * Referenced by: '<S17>/fluxPMLd_Lq2'
   */
  0.27010458464839054,

  /* Expression: 1/mtpablkSett.ipmsmfwsalterm
   * Referenced by: '<S17>/ld2_lq2'
   */
  0.72806890359144183,

  /* Expression: mtpablkSett.ipmsmfwterm7
   * Referenced by: '<S17>/fluxPM2_Lq2'
   */
  0.10020546996060049,

  /* Expression: mtpablkSett.vsmax_scale_a*sqrt(mtpablkSett.ipmsmfwterm8)
   * Referenced by: '<S17>/Gain'
   */
  0.050303914925035505,

  /* Expression: mtpablkSett.vsmax_scale_b*sqrt(mtpablkSett.ipmsmfwterm8)
   * Referenced by: '<S17>/Constant'
   */
  0.17816124929341395,

  /* Expression: 1
   * Referenced by: '<S17>/1_Lq2'
   */
  1.0,

  /* Expression: mtpablkSett.ipmsmfwiqCorr1
   * Referenced by: '<S19>/Gain'
   */
  -0.46352650419318941,

  /* Expression: 1
   * Referenced by: '<S19>/Constant'
   */
  1.0,

  /* Expression: mtpablkSett.ipmsmfwiqCorr1
   * Referenced by: '<S19>/Gain1'
   */
  -0.46352650419318941,

  /* Expression: 1
   * Referenced by: '<S19>/Constant1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S35>/Constant'
   */
  0.0,

  /* Expression: -1
   * Referenced by: '<S35>/Gain'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<S35>/Switch1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S35>/Switch'
   */
  0.0,

  /* Expression: -1
   * Referenced by: '<S33>/Gain'
   */
  -1.0,

  /* Expression: 1
   * Referenced by: '<S27>/Constant'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S20>/ReplaceInport_satLim'
   */
  0.0,

  /* Expression: Vmax
   * Referenced by: '<S25>/Constant3'
   */
  0.36,

  /* Expression: 0
   * Referenced by: '<S38>/zero'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S37>/Constant'
   */
  0.0,

  /* Expression: sqrt(mtpablkSett.term2_fw)
   * Referenced by: '<S16>/term2'
   */
  0.99328318171665342,

  /* Expression: mtpablkSett.term3_fw*mtpablkSett.term3_gain
   * Referenced by: '<S16>/term3'
   */
  -0.84508713051093409,

  /* Expression: mtpablkSett.term3_gain2_a
   * Referenced by: '<S16>/Gain'
   */
  0.57735026918962584,

  /* Expression: mtpablkSett.term3_gain2_b
   * Referenced by: '<S16>/Constant1'
   */
  2.0448,

  /* Expression: sqrt(-mtpablkSett.term3_gain2_c)
   * Referenced by: '<S16>/ 1'
   */
  0.033416654749365712,

  /* Expression: -1
   * Referenced by: '<S16>/ '
   */
  -1.0,

  /* Expression: mtpablkSett.term1_fw
   * Referenced by: '<S16>/term1'
   */
  0.99328318171665353,

  /* Expression: 1
   * Referenced by: '<S22>/Constant'
   */
  1.0,

  /* Expression: mtpablkSett.ipmsmfwiqCorr1
   * Referenced by: '<S22>/Gain'
   */
  -0.46352650419318941,

  /* Expression: 0
   * Referenced by: '<S16>/Constant2'
   */
  0.0,

  /* Expression: mtpablkSett.ipmsmfwiqCorr1
   * Referenced by: '<S22>/Gain1'
   */
  -0.46352650419318941,

  /* Expression: 1
   * Referenced by: '<S22>/Constant1'
   */
  1.0,

  /* Expression: polePairs
   * Referenced by: '<S9>/Gain'
   */
  5.0,

  /* Expression: mtpablkSett.V_base_PU
   * Referenced by: '<S12>/Gain'
   */
  13.856406460551019,

  /* Expression: double(V_dc)
   * Referenced by: '<S12>/Vdc_lumped'
   */
  48.0,

  /* Expression: 0
   * Referenced by: '<S5>/sign'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Id_ref_nofw'
   */
  0.0,

  /* Expression: mtpablkSett.ipmsmT2i
   * Referenced by: '<S7>/Gain'
   */
  1.0,

  /* Expression: mtpablkSett.I_max
   * Referenced by: '<S7>/Saturation'
   */
  0.36,

  /* Expression: -mtpablkSett.I_max
   * Referenced by: '<S7>/Saturation'
   */
  -0.36,

  /* Expression: mtpablkSett.ipmsmmtpaterm1
   * Referenced by: '<S8>/term1'
   */
  0.53934348465175264,

  /* Expression: mtpablkSett.ipmsmmtpaterm3
   * Referenced by: '<S8>/term3'
   */
  -0.5,

  /* Expression: sqrt(mtpablkSett.ipmsmmtpaterm2)
   * Referenced by: '<S8>/term2'
   */
  0.53934348465175264,

  /* Expression: 0
   * Referenced by: '<S13>/Saturation2'
   */
  0.0,

  /* Expression: -mtpablkSett.I_max
   * Referenced by: '<S13>/Saturation2'
   */
  -0.36,

  /* Expression: mtpablkSett.mech2elec
   * Referenced by: '<S7>/Gain1'
   */
  5.0,

  /* Expression: mtpablkSett.Ld_term
   * Referenced by: '<S40>/Ld'
   */
  0.706762037268565,

  /* Expression: mtpablkSett.FluxPM_term
   * Referenced by: '<S40>/FluxPM'
   */
  0.26219999999999993,

  /* Expression: mtpablkSett.Lq_term
   * Referenced by: '<S40>/Lq'
   */
  0.8282986866680192,

  /* Expression: mtpablkSett.vsmax_scale_a
   * Referenced by: '<S11>/Gain'
   */
  0.041666666666666671,

  /* Expression: mtpablkSett.vsmax_scale_b
   * Referenced by: '<S11>/Constant'
   */
  0.14757072880486832,

  /* Computed Parameter: Merge_InitialOutput
   * Referenced by: '<S7>/Merge'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Enable_fwc'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Switch'
   */
  0.0,

  /* Computed Parameter: ReplaceInport_satMethod_Value
   * Referenced by: '<S20>/ReplaceInport_satMethod'
   */
  0U,

  /* Computed Parameter: ChosenMethod_Value
   * Referenced by: '<S25>/ChosenMethod'
   */
  1U,

  /* Computed Parameter: enableInportSatMethod_Value
   * Referenced by: '<S25>/enableInportSatMethod'
   */
  0U,

  /* Computed Parameter: enableInportSatLim_Value
   * Referenced by: '<S25>/enableInportSatLim'
   */
  0U,

  /* Computed Parameter: Constant_Value_ll
   * Referenced by: '<S12>/Constant'
   */
  0U,

  /* Computed Parameter: Switch_Threshold_f
   * Referenced by: '<S12>/Switch'
   */
  0U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
