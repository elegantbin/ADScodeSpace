/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PMSM_CurrentControl_System.c
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
#include <Current_Controller/rt_nonfinite.h>
#include <Current_Controller/rtwtypes.h>
#include <math.h>
#include <string.h>
RT_MODEL_PMSM_CurrentControl__T PMSM_CurrentControl_System_M_;
RT_MODEL_PMSM_CurrentControl__T *const PMSM_CurrentControl_System_MPtr =
  &PMSM_CurrentControl_System_M_;      /* Real-time model */
DW_PMSM_CurrentControl_System_T PMSM_CurrentControl_System_DW;/* Observable states */

ExtY_PMSM_CurrentControl_Syst_T PMSM_CurrentControl_System_Y;/* External outputs */
ExtU_PMSM_CurrentControl_Syst_T PMSM_CurrentControl_System_U;/* External inputs */

/* Model step function */
void PMSM_CurrentControl_System_step(RT_MODEL_PMSM_CurrentControl__T *const
  PMSM_CurrentControl_System_M, ExtU_PMSM_CurrentControl_Syst_T
  *PMSM_CurrentControl_System_U, ExtY_PMSM_CurrentControl_Syst_T
  *PMSM_CurrentControl_System_Y)
{
  DW_PMSM_CurrentControl_System_T *PMSM_CurrentControl_System_DW =
    PMSM_CurrentControl_System_M->dwork;
  real32_T rtb_DeadZone;
  real32_T rtb_DeadZone_m;
  real32_T rtb_IProdOut;
  real32_T rtb_IProdOut_jc;
  real32_T rtb_Product;
  real32_T rtb_Sqrt;
  real32_T rtb_Switch2_h;
  real32_T rtb_VdFF_unsat;
  real32_T rtb_VqFF_unsat;
  real32_T rtb_we;
  uint16_T rtb_Switch1_c;
  int8_T tmp;
  int8_T tmp_0;
  boolean_T rtb_AND_n;
  boolean_T rtb_LogicalOperator;
  boolean_T rtb_LogicalOperator_b;
  boolean_T rtb_LogicalOperator_gv;

  /* Switch: '<S10>/Switch1' incorporates:
   *  Constant: '<S10>/ChosenMethod'
   *  Constant: '<S10>/enableInportSatMethod'
   *  Constant: '<S1>/ReplaceInport_satMethod'
   */
  if (PMSM_CurrentControl_System_P.enableInportSatMethod_Value != 0) {
    rtb_Switch1_c = PMSM_CurrentControl_System_P.ReplaceInport_satMethod_Value;
  } else {
    rtb_Switch1_c = PMSM_CurrentControl_System_P.ChosenMethod_Value;
  }

  /* End of Switch: '<S10>/Switch1' */

  /* Logic: '<S6>/AND' incorporates:
   *  Constant: '<S6>/EnCloseLoop'
   *  Constant: '<S6>/Enable'
   */
  rtb_AND_n = ((PMSM_CurrentControl_System_P.Enable_Value != 0.0) &&
               (PMSM_CurrentControl_System_P.EnCloseLoop_Value != 0.0));

  /* Sum: '<S2>/Sum' incorporates:
   *  Constant: '<Root>/Vmax_ref'
   *  UnitDelay: '<Root>/Unit Delay'
   */
  rtb_IProdOut = PMSM_CurrentControl_System_P.Vmax_ref_Value -
    PMSM_CurrentControl_System_DW->UnitDelay_DSTATE;

  /* Logic: '<S2>/Logical Operator' incorporates:
   *  Constant: '<S2>/EnCloseLoop'
   *  Constant: '<S2>/Enable'
   *  Logic: '<S2>/AND'
   */
  rtb_LogicalOperator = ((!(PMSM_CurrentControl_System_P.Enable_Value_p != 0.0))
    || (!(PMSM_CurrentControl_System_P.EnCloseLoop_Value_n != 0.0)));

  /* DiscreteIntegrator: '<S56>/Integrator' incorporates:
   *  Constant: '<S2>/Ki1'
   */
  if (rtb_LogicalOperator ||
      (PMSM_CurrentControl_System_DW->Integrator_PrevResetState != 0)) {
    PMSM_CurrentControl_System_DW->Integrator_DSTATE =
      PMSM_CurrentControl_System_P.Ki1_Value;
  }

  /* Sum: '<S65>/Sum' incorporates:
   *  Constant: '<S2>/Kp_fwc'
   *  DiscreteIntegrator: '<S56>/Integrator'
   *  Product: '<S61>/PProd Out'
   */
  rtb_DeadZone = rtb_IProdOut * PMSM_CurrentControl_System_P.Kp_fwc_Value +
    PMSM_CurrentControl_System_DW->Integrator_DSTATE;

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Bypass_FWC'
   *  Constant: '<S2>/FW_Enable'
   */
  if (PMSM_CurrentControl_System_P.FW_Enable_Value >
      PMSM_CurrentControl_System_P.Switch_Threshold) {
    /* Saturate: '<S63>/Saturation' */
    if (rtb_DeadZone >
        PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_f) {
      rtb_VdFF_unsat =
        PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_f;
    } else if (rtb_DeadZone <
               PMSM_CurrentControl_System_P.DiscretePIControllerwithantiwin) {
      rtb_VdFF_unsat =
        PMSM_CurrentControl_System_P.DiscretePIControllerwithantiwin;
    } else {
      rtb_VdFF_unsat = rtb_DeadZone;
    }

    /* End of Saturate: '<S63>/Saturation' */
  } else {
    rtb_VdFF_unsat = PMSM_CurrentControl_System_P.Bypass_FWC_Value;
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Switch: '<S2>/Switch'
   */
  rtb_IProdOut_jc = PMSM_CurrentControl_System_U->Id_ref_unsat + rtb_VdFF_unsat;

  /* Saturate: '<S4>/Saturation_Id_ref' */
  if (rtb_IProdOut_jc > PMSM_CurrentControl_System_P.Saturation_Id_ref_UpperSat)
  {
    rtb_IProdOut_jc = PMSM_CurrentControl_System_P.Saturation_Id_ref_UpperSat;
  } else if (rtb_IProdOut_jc <
             PMSM_CurrentControl_System_P.Saturation_Id_ref_LowerSat) {
    rtb_IProdOut_jc = PMSM_CurrentControl_System_P.Saturation_Id_ref_LowerSat;
  }

  /* End of Saturate: '<S4>/Saturation_Id_ref' */

  /* Sqrt: '<S4>/Sqrt' incorporates:
   *  Constant: '<S4>/Imax_Ibase_Squar'
   *  Product: '<S4>/Product1'
   *  Sum: '<S4>/Sum2'
   */
  rtb_Sqrt = sqrtf(PMSM_CurrentControl_System_P.Imax_Ibase_Squar_Value -
                   rtb_IProdOut_jc * rtb_IProdOut_jc);

  /* Switch: '<S4>/Switch' incorporates:
   *  Abs: '<S4>/Abs'
   *  Product: '<S4>/Product2'
   *  RelationalOperator: '<S4>/Less Than'
   *  Signum: '<S4>/Sign'
   */
  if (rtb_Sqrt < fabsf(PMSM_CurrentControl_System_U->Iq_ref_unsat)) {
    /* Signum: '<S4>/Sign' */
    if (rtIsNaNF(PMSM_CurrentControl_System_U->Iq_ref_unsat)) {
      rtb_VdFF_unsat = (rtNaNF);
    } else if (PMSM_CurrentControl_System_U->Iq_ref_unsat < 0.0F) {
      rtb_VdFF_unsat = -1.0F;
    } else {
      rtb_VdFF_unsat = (real32_T)(PMSM_CurrentControl_System_U->Iq_ref_unsat >
        0.0F);
    }

    rtb_Sqrt *= rtb_VdFF_unsat;
  } else {
    rtb_Sqrt = PMSM_CurrentControl_System_U->Iq_ref_unsat;
  }

  /* End of Switch: '<S4>/Switch' */

  /* Sum: '<S6>/Sum' */
  rtb_Sqrt -= PMSM_CurrentControl_System_U->Iq_fb;

  /* Logic: '<S6>/Logical Operator' */
  rtb_LogicalOperator_b = !rtb_AND_n;

  /* DiscreteIntegrator: '<S161>/Integrator' incorporates:
   *  UnitDelay: '<S6>/Unit Delay'
   */
  if (PMSM_CurrentControl_System_DW->Integrator_IC_LOADING != 0) {
    PMSM_CurrentControl_System_DW->Integrator_DSTATE_o =
      PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_p;
  }

  if (rtb_LogicalOperator_b ||
      (PMSM_CurrentControl_System_DW->Integrator_PrevResetState_e != 0)) {
    PMSM_CurrentControl_System_DW->Integrator_DSTATE_o =
      PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_p;
  }

  /* Sum: '<S170>/Sum' incorporates:
   *  Constant: '<S6>/Kp_iq'
   *  DiscreteIntegrator: '<S161>/Integrator'
   *  Product: '<S166>/PProd Out'
   */
  rtb_DeadZone_m = rtb_Sqrt * PMSM_CurrentControl_System_P.Kp_iq_Value +
    PMSM_CurrentControl_System_DW->Integrator_DSTATE_o;

  /* Switch: '<S6>/Switch' incorporates:
   *  Constant: '<S6>/Vq_OpenLoop'
   *  UnitDelay: '<S6>/Unit Delay'
   */
  if (rtb_AND_n) {
    /* Saturate: '<S168>/Saturation' */
    if (rtb_DeadZone_m >
        PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_d) {
      PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_p =
        PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_d;
    } else if (rtb_DeadZone_m <
               PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_h) {
      PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_p =
        PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_h;
    } else {
      PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_p = rtb_DeadZone_m;
    }

    /* End of Saturate: '<S168>/Saturation' */
  } else {
    PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_p =
      PMSM_CurrentControl_System_P.Vq_OpenLoop_Value;
  }

  /* End of Switch: '<S6>/Switch' */

  /* Switch: '<S179>/Switch' incorporates:
   *  Constant: '<S179>/Constant'
   *  Constant: '<S179>/vsat_mask_input'
   *  Gain: '<S179>/Gain'
   */
  if (PMSM_CurrentControl_System_P.Constant_Value_g >
      PMSM_CurrentControl_System_P.Switch_Threshold_p) {
    rtb_Switch2_h = PMSM_CurrentControl_System_P.Gain_Gain_f * 0.0F;
  } else {
    rtb_Switch2_h = PMSM_CurrentControl_System_P.vsat_mask_input_Value;
  }

  /* End of Switch: '<S179>/Switch' */

  /* Gain: '<S179>/wm_pu2si_mech2elec' */
  rtb_we = PMSM_CurrentControl_System_P.wm_pu2si_mech2elec_Gain *
    PMSM_CurrentControl_System_U->Wm_fb;

  /* Switch: '<S180>/Switch2' incorporates:
   *  Constant: '<S180>/Constant2'
   *  Constant: '<S180>/FluxPM_lumped'
   *  Gain: '<S180>/Gain2'
   */
  if (PMSM_CurrentControl_System_P.Constant2_Value_j >
      PMSM_CurrentControl_System_P.Switch2_Threshold) {
    rtb_VdFF_unsat = PMSM_CurrentControl_System_P.Gain2_Gain * 0.0F;
  } else {
    rtb_VdFF_unsat = PMSM_CurrentControl_System_P.FluxPM_lumped_Value;
  }

  /* Switch: '<S180>/Switch' incorporates:
   *  Constant: '<S180>/Constant'
   *  Constant: '<S180>/Ld_lumped'
   *  Gain: '<S180>/Gain'
   */
  if (PMSM_CurrentControl_System_P.Constant_Value_i >
      PMSM_CurrentControl_System_P.Switch_Threshold_g) {
    rtb_VqFF_unsat = PMSM_CurrentControl_System_P.Gain_Gain_g * 0.0F;
  } else {
    rtb_VqFF_unsat = PMSM_CurrentControl_System_P.Ld_lumped_Value;
  }

  /* Product: '<S179>/prod2' incorporates:
   *  Gain: '<S179>/id_pu2si'
   *  Product: '<S179>/prod3'
   *  Sum: '<S179>/add1'
   *  Switch: '<S180>/Switch'
   *  Switch: '<S180>/Switch2'
   */
  rtb_VqFF_unsat = (PMSM_CurrentControl_System_P.id_pu2si_Gain *
                    PMSM_CurrentControl_System_U->Id_fb * rtb_VqFF_unsat +
                    rtb_VdFF_unsat) * rtb_we;

  /* Switch: '<S182>/Switch2' incorporates:
   *  RelationalOperator: '<S182>/LowerRelop1'
   *  RelationalOperator: '<S182>/UpperRelop'
   *  Switch: '<S182>/Switch'
   *  UnaryMinus: '<S179>/Unary Minus'
   */
  if (rtb_VqFF_unsat > rtb_Switch2_h) {
    rtb_VqFF_unsat = rtb_Switch2_h;
  } else if (rtb_VqFF_unsat < -rtb_Switch2_h) {
    /* Switch: '<S182>/Switch' incorporates:
     *  UnaryMinus: '<S179>/Unary Minus'
     */
    rtb_VqFF_unsat = -rtb_Switch2_h;
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Gain: '<S179>/VqFF_si2pu'
   *  Switch: '<S182>/Switch2'
   *  UnitDelay: '<S6>/Unit Delay'
   */
  PMSM_CurrentControl_System_Y->Vq_ref =
    PMSM_CurrentControl_System_P.VqFF_si2pu_Gain * rtb_VqFF_unsat +
    PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_p;

  /* Logic: '<S5>/AND' incorporates:
   *  Constant: '<S5>/EnCloseLoop'
   *  Constant: '<S5>/Enable'
   */
  rtb_AND_n = ((PMSM_CurrentControl_System_P.Enable_Value_l != 0.0) &&
               (PMSM_CurrentControl_System_P.EnCloseLoop_Value_h != 0.0));

  /* Sum: '<S5>/Sum' */
  rtb_IProdOut_jc -= PMSM_CurrentControl_System_U->Id_fb;

  /* Logic: '<S5>/Logical Operator' */
  rtb_LogicalOperator_gv = !rtb_AND_n;

  /* DiscreteIntegrator: '<S110>/Integrator' incorporates:
   *  UnitDelay: '<S5>/Unit Delay'
   */
  if (PMSM_CurrentControl_System_DW->Integrator_IC_LOADING_m != 0) {
    PMSM_CurrentControl_System_DW->Integrator_DSTATE_l =
      PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_k;
  }

  if (rtb_LogicalOperator_gv ||
      (PMSM_CurrentControl_System_DW->Integrator_PrevResetState_g != 0)) {
    PMSM_CurrentControl_System_DW->Integrator_DSTATE_l =
      PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_k;
  }

  /* Sum: '<S119>/Sum' incorporates:
   *  Constant: '<S5>/Kp_id'
   *  DiscreteIntegrator: '<S110>/Integrator'
   *  Product: '<S115>/PProd Out'
   */
  rtb_VqFF_unsat = rtb_IProdOut_jc * PMSM_CurrentControl_System_P.Kp_id_Value +
    PMSM_CurrentControl_System_DW->Integrator_DSTATE_l;

  /* Switch: '<S5>/Switch' incorporates:
   *  Constant: '<S5>/Vd_OpenLoop'
   *  UnitDelay: '<S5>/Unit Delay'
   */
  if (rtb_AND_n) {
    /* Saturate: '<S117>/Saturation' */
    if (rtb_VqFF_unsat >
        PMSM_CurrentControl_System_P.DiscretePIControllerwithanti_fy) {
      PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_k =
        PMSM_CurrentControl_System_P.DiscretePIControllerwithanti_fy;
    } else if (rtb_VqFF_unsat <
               PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_l) {
      PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_k =
        PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_l;
    } else {
      PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_k = rtb_VqFF_unsat;
    }

    /* End of Saturate: '<S117>/Saturation' */
  } else {
    PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_k =
      PMSM_CurrentControl_System_P.Vd_OpenLoop_Value;
  }

  /* End of Switch: '<S5>/Switch' */

  /* Switch: '<S180>/Switch1' incorporates:
   *  Constant: '<S180>/Constant1'
   *  Constant: '<S180>/Lq_lumped'
   *  Gain: '<S180>/Gain1'
   */
  if (PMSM_CurrentControl_System_P.Constant1_Value_i >
      PMSM_CurrentControl_System_P.Switch1_Threshold_c) {
    rtb_VdFF_unsat = PMSM_CurrentControl_System_P.Gain1_Gain * 0.0F;
  } else {
    rtb_VdFF_unsat = PMSM_CurrentControl_System_P.Lq_lumped_Value;
  }

  /* Gain: '<S179>/NegSign' incorporates:
   *  Gain: '<S179>/iq_pu2si'
   *  Product: '<S179>/prod1'
   *  Switch: '<S180>/Switch1'
   */
  rtb_VdFF_unsat = PMSM_CurrentControl_System_P.iq_pu2si_Gain *
    PMSM_CurrentControl_System_U->Iq_fb * rtb_VdFF_unsat * rtb_we *
    PMSM_CurrentControl_System_P.NegSign_Gain;

  /* Switch: '<S181>/Switch2' incorporates:
   *  RelationalOperator: '<S181>/LowerRelop1'
   */
  if (!(rtb_VdFF_unsat > rtb_Switch2_h)) {
    /* Switch: '<S181>/Switch' incorporates:
     *  RelationalOperator: '<S181>/UpperRelop'
     *  UnaryMinus: '<S179>/Unary Minus'
     */
    if (rtb_VdFF_unsat < -rtb_Switch2_h) {
      rtb_Switch2_h = -rtb_Switch2_h;
    } else {
      rtb_Switch2_h = rtb_VdFF_unsat;
    }

    /* End of Switch: '<S181>/Switch' */
  }

  /* End of Switch: '<S181>/Switch2' */

  /* Sum: '<Root>/Sum' incorporates:
   *  Gain: '<S179>/VdFF_si2pu'
   *  UnitDelay: '<S5>/Unit Delay'
   */
  PMSM_CurrentControl_System_Y->Vd_ref =
    PMSM_CurrentControl_System_P.VdFF_si2pu_Gain * rtb_Switch2_h +
    PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_k;

  /* Switch: '<S10>/Switch' incorporates:
   *  Constant: '<S10>/Constant3'
   *  Constant: '<S10>/enableInportSatLim'
   *  Constant: '<S1>/ReplaceInport_satLim'
   */
  if (PMSM_CurrentControl_System_P.enableInportSatLim_Value != 0) {
    rtb_we = PMSM_CurrentControl_System_P.ReplaceInport_satLim_Value;
  } else {
    rtb_we = PMSM_CurrentControl_System_P.Constant3_Value;
  }

  /* End of Switch: '<S10>/Switch' */

  /* Product: '<S10>/Product' */
  rtb_Product = rtb_we * rtb_we;

  /* Sum: '<S11>/Sum1' incorporates:
   *  Product: '<S11>/Product'
   *  Product: '<S11>/Product1'
   */
  rtb_Switch2_h = PMSM_CurrentControl_System_Y->Vd_ref *
    PMSM_CurrentControl_System_Y->Vd_ref + PMSM_CurrentControl_System_Y->Vq_ref *
    PMSM_CurrentControl_System_Y->Vq_ref;

  /* If: '<S1>/If' incorporates:
   *  If: '<S8>/If'
   *  RelationalOperator: '<S8>/Relational Operator'
   */
  if ((rtb_Switch1_c == 1) || (rtb_Switch1_c == 2)) {
    /* Outputs for IfAction SubSystem: '<S1>/D//Q Axis Priority' incorporates:
     *  ActionPort: '<S9>/Action Port'
     */
    /* Switch: '<S9>/Switch' incorporates:
     *  Constant: '<S14>/Constant'
     *  RelationalOperator: '<S14>/Compare'
     */
    if (rtb_Switch1_c == PMSM_CurrentControl_System_P.CompareToConstant_const) {
      rtb_VdFF_unsat = PMSM_CurrentControl_System_Y->Vd_ref;

      /* Sum: '<Root>/Sum' */
      PMSM_CurrentControl_System_Y->Vd_ref =
        PMSM_CurrentControl_System_Y->Vq_ref;
    } else {
      rtb_VdFF_unsat = PMSM_CurrentControl_System_Y->Vq_ref;
    }

    /* End of Switch: '<S9>/Switch' */

    /* Switch: '<S19>/Switch2' incorporates:
     *  RelationalOperator: '<S19>/LowerRelop1'
     */
    if (rtb_VdFF_unsat > rtb_we) {
      rtb_VdFF_unsat = rtb_we;
    } else {
      /* Gain: '<S18>/Gain' */
      rtb_we *= PMSM_CurrentControl_System_P.Gain_Gain_d;

      /* Switch: '<S19>/Switch' incorporates:
       *  RelationalOperator: '<S19>/UpperRelop'
       */
      if (rtb_VdFF_unsat < rtb_we) {
        rtb_VdFF_unsat = rtb_we;
      }

      /* End of Switch: '<S19>/Switch' */
    }

    /* End of Switch: '<S19>/Switch2' */

    /* Sum: '<S18>/Sum' incorporates:
     *  Product: '<S18>/Product'
     */
    rtb_we = rtb_Product - rtb_VdFF_unsat * rtb_VdFF_unsat;

    /* If: '<S18>/If' incorporates:
     *  Product: '<S18>/Product2'
     *  RelationalOperator: '<S18>/Relational Operator'
     *  Switch: '<S20>/Switch'
     *  Switch: '<S20>/Switch1'
     */
    if (rtb_we >= PMSM_CurrentControl_System_Y->Vd_ref *
        PMSM_CurrentControl_System_Y->Vd_ref) {
      /* Outputs for IfAction SubSystem: '<S18>/passThrough' incorporates:
       *  ActionPort: '<S21>/Action Port'
       */
      /* Sum: '<Root>/Sum1' incorporates:
       *  SignalConversion generated from: '<S21>/ref2'
       */
      PMSM_CurrentControl_System_Y->Vq_ref =
        PMSM_CurrentControl_System_Y->Vd_ref;

      /* End of Outputs for SubSystem: '<S18>/passThrough' */

      /* Outputs for IfAction SubSystem: '<S18>/limitRef2' incorporates:
       *  ActionPort: '<S20>/Action Port'
       */
    } else if (PMSM_CurrentControl_System_Y->Vd_ref >=
               PMSM_CurrentControl_System_P.Switch_Threshold_h) {
      /* Switch: '<S20>/Switch1' incorporates:
       *  Constant: '<S20>/Constant'
       */
      if (!(rtb_we > PMSM_CurrentControl_System_P.Switch1_Threshold)) {
        rtb_we = PMSM_CurrentControl_System_P.Constant_Value;
      }

      /* Sum: '<Root>/Sum1' incorporates:
       *  Sqrt: '<S20>/Sqrt'
       *  Switch: '<S20>/Switch'
       *  Switch: '<S20>/Switch1'
       */
      PMSM_CurrentControl_System_Y->Vq_ref = sqrtf(rtb_we);
    } else {
      if (!(rtb_we > PMSM_CurrentControl_System_P.Switch1_Threshold)) {
        /* Switch: '<S20>/Switch1' incorporates:
         *  Constant: '<S20>/Constant'
         */
        rtb_we = PMSM_CurrentControl_System_P.Constant_Value;
      }

      /* Sum: '<Root>/Sum1' incorporates:
       *  Gain: '<S20>/Gain'
       *  Sqrt: '<S20>/Sqrt'
       *  Switch: '<S20>/Switch'
       *  Switch: '<S20>/Switch1'
       */
      PMSM_CurrentControl_System_Y->Vq_ref =
        PMSM_CurrentControl_System_P.Gain_Gain * sqrtf(rtb_we);

      /* End of Outputs for SubSystem: '<S18>/limitRef2' */
    }

    /* End of If: '<S18>/If' */

    /* Switch: '<S9>/Switch1' incorporates:
     *  Constant: '<S15>/Constant'
     *  RelationalOperator: '<S15>/Compare'
     */
    if (rtb_Switch1_c == PMSM_CurrentControl_System_P.CompareToConstant1_const)
    {
      /* Sum: '<Root>/Sum' incorporates:
       *  Outport: '<Root>/Vd_ref'
       */
      PMSM_CurrentControl_System_Y->Vd_ref = rtb_VdFF_unsat;
    } else {
      /* Sum: '<Root>/Sum' incorporates:
       *  Outport: '<Root>/Vd_ref'
       */
      PMSM_CurrentControl_System_Y->Vd_ref =
        PMSM_CurrentControl_System_Y->Vq_ref;

      /* Sum: '<Root>/Sum1' incorporates:
       *  Outport: '<Root>/Vq_ref'
       */
      PMSM_CurrentControl_System_Y->Vq_ref = rtb_VdFF_unsat;
    }

    /* End of Switch: '<S9>/Switch1' */
    /* End of Outputs for SubSystem: '<S1>/D//Q Axis Priority' */

    /* Outputs for IfAction SubSystem: '<S1>/D-Q Equivalence' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
  } else if (rtb_Switch2_h > rtb_Product) {
    /* Outputs for IfAction SubSystem: '<S8>/Limiter' incorporates:
     *  ActionPort: '<S12>/Action Port'
     */
    /* If: '<S8>/If' incorporates:
     *  Constant: '<S12>/Constant'
     *  Outport: '<Root>/Vd_ref'
     *  Outport: '<Root>/Vq_ref'
     *  Product: '<S12>/Product'
     *  Product: '<S12>/Product1'
     *  Product: '<S12>/Reciprocal'
     *  Sqrt: '<S12>/Square Root'
     *  Sum: '<Root>/Sum'
     *  Sum: '<Root>/Sum1'
     *  Switch: '<S12>/Switch'
     */
    rtb_VdFF_unsat = sqrtf(rtb_Switch2_h);
    if (!(rtb_VdFF_unsat != 0.0F)) {
      rtb_VdFF_unsat = PMSM_CurrentControl_System_P.Constant_Value_p;
    }

    rtb_VdFF_unsat = 1.0F / rtb_VdFF_unsat;
    PMSM_CurrentControl_System_Y->Vd_ref = PMSM_CurrentControl_System_Y->Vd_ref *
      rtb_we * rtb_VdFF_unsat;
    PMSM_CurrentControl_System_Y->Vq_ref = PMSM_CurrentControl_System_Y->Vq_ref *
      rtb_we * rtb_VdFF_unsat;

    /* End of Outputs for SubSystem: '<S8>/Limiter' */

    /* End of Outputs for SubSystem: '<S1>/D-Q Equivalence' */
  }

  /* End of If: '<S1>/If' */

  /* Sum: '<S75>/Add1' incorporates:
   *  Constant: '<S75>/Filter_Constant'
   *  Constant: '<S75>/One'
   *  Product: '<S75>/Product'
   *  Product: '<S75>/Product1'
   *  Sqrt: '<S11>/Sqrt'
   *  UnitDelay: '<S75>/Unit Delay'
   */
  PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_m = sqrtf(rtb_Switch2_h) *
    PMSM_CurrentControl_System_P.Filter_Constant_Value +
    PMSM_CurrentControl_System_P.One_Value *
    PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_m;

  /* DeadZone: '<S103>/DeadZone' */
  if (rtb_VqFF_unsat >
      PMSM_CurrentControl_System_P.DiscretePIControllerwithanti_fy) {
    rtb_VqFF_unsat -=
      PMSM_CurrentControl_System_P.DiscretePIControllerwithanti_fy;
  } else if (rtb_VqFF_unsat >=
             PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_l) {
    rtb_VqFF_unsat = 0.0F;
  } else {
    rtb_VqFF_unsat -=
      PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_l;
  }

  /* End of DeadZone: '<S103>/DeadZone' */

  /* Product: '<S107>/IProd Out' incorporates:
   *  Constant: '<S5>/Ki_id'
   */
  rtb_IProdOut_jc *= PMSM_CurrentControl_System_P.Ki_id_Value;

  /* DeadZone: '<S154>/DeadZone' */
  if (rtb_DeadZone_m >
      PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_d) {
    rtb_DeadZone_m -=
      PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_d;
  } else if (rtb_DeadZone_m >=
             PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_h) {
    rtb_DeadZone_m = 0.0F;
  } else {
    rtb_DeadZone_m -=
      PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_h;
  }

  /* End of DeadZone: '<S154>/DeadZone' */

  /* Product: '<S158>/IProd Out' incorporates:
   *  Constant: '<S6>/Ki_iq'
   */
  rtb_Sqrt *= PMSM_CurrentControl_System_P.Ki_iq_Value;

  /* DeadZone: '<S49>/DeadZone' */
  if (rtb_DeadZone >
      PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_f) {
    rtb_DeadZone -= PMSM_CurrentControl_System_P.DiscretePIControllerwithantiw_f;
  } else if (rtb_DeadZone >=
             PMSM_CurrentControl_System_P.DiscretePIControllerwithantiwin) {
    rtb_DeadZone = 0.0F;
  } else {
    rtb_DeadZone -= PMSM_CurrentControl_System_P.DiscretePIControllerwithantiwin;
  }

  /* End of DeadZone: '<S49>/DeadZone' */

  /* Product: '<S53>/IProd Out' incorporates:
   *  Constant: '<S2>/Ki_fwc'
   */
  rtb_IProdOut *= PMSM_CurrentControl_System_P.Ki_fwc_Value;

  /* Update for UnitDelay: '<Root>/Unit Delay' incorporates:
   *  UnitDelay: '<S75>/Unit Delay'
   */
  PMSM_CurrentControl_System_DW->UnitDelay_DSTATE =
    PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_m;

  /* Switch: '<S47>/Switch1' incorporates:
   *  Constant: '<S47>/Clamping_zero'
   *  Constant: '<S47>/Constant'
   *  Constant: '<S47>/Constant2'
   *  RelationalOperator: '<S47>/fix for DT propagation issue'
   */
  if (rtb_DeadZone > PMSM_CurrentControl_System_P.Clamping_zero_Value_e) {
    tmp = PMSM_CurrentControl_System_P.Constant_Value_k;
  } else {
    tmp = PMSM_CurrentControl_System_P.Constant2_Value;
  }

  /* Switch: '<S47>/Switch2' incorporates:
   *  Constant: '<S47>/Clamping_zero'
   *  Constant: '<S47>/Constant3'
   *  Constant: '<S47>/Constant4'
   *  RelationalOperator: '<S47>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > PMSM_CurrentControl_System_P.Clamping_zero_Value_e) {
    tmp_0 = PMSM_CurrentControl_System_P.Constant3_Value_n;
  } else {
    tmp_0 = PMSM_CurrentControl_System_P.Constant4_Value;
  }

  /* Switch: '<S47>/Switch' incorporates:
   *  Constant: '<S47>/Clamping_zero'
   *  Constant: '<S47>/Constant1'
   *  Logic: '<S47>/AND3'
   *  RelationalOperator: '<S47>/Equal1'
   *  RelationalOperator: '<S47>/Relational Operator'
   *  Switch: '<S47>/Switch1'
   *  Switch: '<S47>/Switch2'
   */
  if ((PMSM_CurrentControl_System_P.Clamping_zero_Value_e != rtb_DeadZone) &&
      (tmp == tmp_0)) {
    rtb_IProdOut = PMSM_CurrentControl_System_P.Constant1_Value;
  }

  /* Update for DiscreteIntegrator: '<S56>/Integrator' incorporates:
   *  Switch: '<S47>/Switch'
   */
  PMSM_CurrentControl_System_DW->Integrator_DSTATE +=
    PMSM_CurrentControl_System_P.Integrator_gainval * rtb_IProdOut;
  PMSM_CurrentControl_System_DW->Integrator_PrevResetState = (int8_T)
    rtb_LogicalOperator;

  /* Update for DiscreteIntegrator: '<S161>/Integrator' */
  PMSM_CurrentControl_System_DW->Integrator_IC_LOADING = 0U;

  /* Switch: '<S152>/Switch1' incorporates:
   *  Constant: '<S152>/Clamping_zero'
   *  Constant: '<S152>/Constant'
   *  Constant: '<S152>/Constant2'
   *  RelationalOperator: '<S152>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_m > PMSM_CurrentControl_System_P.Clamping_zero_Value_k) {
    tmp = PMSM_CurrentControl_System_P.Constant_Value_c;
  } else {
    tmp = PMSM_CurrentControl_System_P.Constant2_Value_p;
  }

  /* Switch: '<S152>/Switch2' incorporates:
   *  Constant: '<S152>/Clamping_zero'
   *  Constant: '<S152>/Constant3'
   *  Constant: '<S152>/Constant4'
   *  RelationalOperator: '<S152>/fix for DT propagation issue1'
   */
  if (rtb_Sqrt > PMSM_CurrentControl_System_P.Clamping_zero_Value_k) {
    tmp_0 = PMSM_CurrentControl_System_P.Constant3_Value_n3;
  } else {
    tmp_0 = PMSM_CurrentControl_System_P.Constant4_Value_g;
  }

  /* Switch: '<S152>/Switch' incorporates:
   *  Constant: '<S152>/Clamping_zero'
   *  Constant: '<S152>/Constant1'
   *  Logic: '<S152>/AND3'
   *  RelationalOperator: '<S152>/Equal1'
   *  RelationalOperator: '<S152>/Relational Operator'
   *  Switch: '<S152>/Switch1'
   *  Switch: '<S152>/Switch2'
   */
  if ((PMSM_CurrentControl_System_P.Clamping_zero_Value_k != rtb_DeadZone_m) &&
      (tmp == tmp_0)) {
    rtb_Sqrt = PMSM_CurrentControl_System_P.Constant1_Value_p;
  }

  /* Update for DiscreteIntegrator: '<S161>/Integrator' incorporates:
   *  Switch: '<S152>/Switch'
   */
  PMSM_CurrentControl_System_DW->Integrator_DSTATE_o +=
    PMSM_CurrentControl_System_P.Integrator_gainval_e * rtb_Sqrt;
  PMSM_CurrentControl_System_DW->Integrator_PrevResetState_e = (int8_T)
    rtb_LogicalOperator_b;

  /* Update for DiscreteIntegrator: '<S110>/Integrator' */
  PMSM_CurrentControl_System_DW->Integrator_IC_LOADING_m = 0U;

  /* Switch: '<S101>/Switch1' incorporates:
   *  Constant: '<S101>/Clamping_zero'
   *  Constant: '<S101>/Constant'
   *  Constant: '<S101>/Constant2'
   *  RelationalOperator: '<S101>/fix for DT propagation issue'
   */
  if (rtb_VqFF_unsat > PMSM_CurrentControl_System_P.Clamping_zero_Value) {
    tmp = PMSM_CurrentControl_System_P.Constant_Value_h;
  } else {
    tmp = PMSM_CurrentControl_System_P.Constant2_Value_h;
  }

  /* Switch: '<S101>/Switch2' incorporates:
   *  Constant: '<S101>/Clamping_zero'
   *  Constant: '<S101>/Constant3'
   *  Constant: '<S101>/Constant4'
   *  RelationalOperator: '<S101>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut_jc > PMSM_CurrentControl_System_P.Clamping_zero_Value) {
    tmp_0 = PMSM_CurrentControl_System_P.Constant3_Value_a;
  } else {
    tmp_0 = PMSM_CurrentControl_System_P.Constant4_Value_h;
  }

  /* Switch: '<S101>/Switch' incorporates:
   *  Constant: '<S101>/Clamping_zero'
   *  Constant: '<S101>/Constant1'
   *  Logic: '<S101>/AND3'
   *  RelationalOperator: '<S101>/Equal1'
   *  RelationalOperator: '<S101>/Relational Operator'
   *  Switch: '<S101>/Switch1'
   *  Switch: '<S101>/Switch2'
   */
  if ((PMSM_CurrentControl_System_P.Clamping_zero_Value != rtb_VqFF_unsat) &&
      (tmp == tmp_0)) {
    rtb_IProdOut_jc = PMSM_CurrentControl_System_P.Constant1_Value_c;
  }

  /* Update for DiscreteIntegrator: '<S110>/Integrator' incorporates:
   *  Switch: '<S101>/Switch'
   */
  PMSM_CurrentControl_System_DW->Integrator_DSTATE_l +=
    PMSM_CurrentControl_System_P.Integrator_gainval_n * rtb_IProdOut_jc;
  PMSM_CurrentControl_System_DW->Integrator_PrevResetState_g = (int8_T)
    rtb_LogicalOperator_gv;
}

/* Model initialize function */
void PMSM_CurrentControl_System_initialize(RT_MODEL_PMSM_CurrentControl__T *
  const PMSM_CurrentControl_System_M, ExtU_PMSM_CurrentControl_Syst_T
  *PMSM_CurrentControl_System_U, ExtY_PMSM_CurrentControl_Syst_T
  *PMSM_CurrentControl_System_Y)
{
  DW_PMSM_CurrentControl_System_T *PMSM_CurrentControl_System_DW =
    PMSM_CurrentControl_System_M->dwork;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* states (dwork) */
  (void) memset((void *)PMSM_CurrentControl_System_DW, 0,
                sizeof(DW_PMSM_CurrentControl_System_T));

  /* external inputs */
  (void)memset(PMSM_CurrentControl_System_U, 0, sizeof
               (ExtU_PMSM_CurrentControl_Syst_T));

  /* external outputs */
  (void)memset(PMSM_CurrentControl_System_Y, 0, sizeof
               (ExtY_PMSM_CurrentControl_Syst_T));

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay' */
  PMSM_CurrentControl_System_DW->UnitDelay_DSTATE =
    PMSM_CurrentControl_System_P.UnitDelay_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S56>/Integrator' incorporates:
   *  Constant: '<S2>/Ki1'
   */
  PMSM_CurrentControl_System_DW->Integrator_DSTATE =
    PMSM_CurrentControl_System_P.Ki1_Value;
  PMSM_CurrentControl_System_DW->Integrator_PrevResetState = 0;

  /* InitializeConditions for UnitDelay: '<S6>/Unit Delay' */
  PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_p =
    PMSM_CurrentControl_System_P.UnitDelay_InitialCondition_k;

  /* InitializeConditions for DiscreteIntegrator: '<S161>/Integrator' */
  PMSM_CurrentControl_System_DW->Integrator_PrevResetState_e = 0;
  PMSM_CurrentControl_System_DW->Integrator_IC_LOADING = 1U;

  /* InitializeConditions for UnitDelay: '<S5>/Unit Delay' */
  PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_k =
    PMSM_CurrentControl_System_P.UnitDelay_InitialCondition_e;

  /* InitializeConditions for DiscreteIntegrator: '<S110>/Integrator' */
  PMSM_CurrentControl_System_DW->Integrator_PrevResetState_g = 0;
  PMSM_CurrentControl_System_DW->Integrator_IC_LOADING_m = 1U;

  /* InitializeConditions for UnitDelay: '<S75>/Unit Delay' */
  PMSM_CurrentControl_System_DW->UnitDelay_DSTATE_m =
    PMSM_CurrentControl_System_P.UnitDelay_InitialCondition_o;
}

/* Model terminate function */
void PMSM_CurrentControl_System_terminate(RT_MODEL_PMSM_CurrentControl__T *const
  PMSM_CurrentControl_System_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(PMSM_CurrentControl_System_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
