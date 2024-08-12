/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PMSM_MTPA_Module.c
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

#include <Current_Controller/rtwtypes.h>
#include <math.h>
#include <MTPA/PMSM_MTPA_Module.h>
#include <string.h>

/* Model step function */
void PMSM_MTPA_Module_step(RT_MODEL_PMSM_MTPA_Module_T *const PMSM_MTPA_Module_M,
  ExtU_PMSM_MTPA_Module_T *PMSM_MTPA_Module_U, ExtY_PMSM_MTPA_Module_T
  *PMSM_MTPA_Module_Y)
{
  B_PMSM_MTPA_Module_T *PMSM_MTPA_Module_B = PMSM_MTPA_Module_M->blockIO;
  real_T rtb_Abs;
  real_T rtb_Gain;
  real_T rtb_Imag;
  real_T rtb_Saturation2;
  real_T rtb_Sqrt;
  real_T rtb_Sqrt_o;
  real_T rtb_Sum1_c;
  real_T rtb_Sum1_g;
  real_T rtb_Switch;
  uint16_T rtb_Switch1_l;

  /* Gain: '<S7>/Gain' incorporates:
   *  Abs: '<S3>/Abs'
   */
  rtb_Gain = PMSM_MTPA_Module_P.Gain_Gain_h * fabs
    (PMSM_MTPA_Module_U->Torque_ref);

  /* Saturate: '<S7>/Saturation' */
  if (rtb_Gain > PMSM_MTPA_Module_P.Saturation_UpperSat) {
    rtb_Imag = PMSM_MTPA_Module_P.Saturation_UpperSat;
  } else if (rtb_Gain < PMSM_MTPA_Module_P.Saturation_LowerSat) {
    rtb_Imag = PMSM_MTPA_Module_P.Saturation_LowerSat;
  } else {
    rtb_Imag = rtb_Gain;
  }

  /* End of Saturate: '<S7>/Saturation' */

  /* Outputs for IfAction SubSystem: '<S7>/FW condition' incorporates:
   *  ActionPort: '<S9>/Action Port'
   */
  /* If: '<S7>/If' incorporates:
   *  Product: '<S26>/Product1'
   *  Product: '<S8>/Square'
   */
  rtb_Sum1_g = rtb_Imag * rtb_Imag;

  /* End of Outputs for SubSystem: '<S7>/FW condition' */

  /* Sum: '<S8>/Sum2' incorporates:
   *  Abs: '<S8>/Abs'
   *  Constant: '<S8>/term1'
   *  Constant: '<S8>/term2'
   *  Gain: '<S8>/term3'
   *  Product: '<S8>/Square'
   *  Product: '<S8>/Square1'
   *  Sqrt: '<S8>/Sqrt'
   *  Sum: '<S8>/Sum3'
   */
  rtb_Saturation2 = PMSM_MTPA_Module_P.term1_Value_n - sqrt(fabs
    (PMSM_MTPA_Module_P.term3_Gain * rtb_Sum1_g -
     PMSM_MTPA_Module_P.term2_Value_e * PMSM_MTPA_Module_P.term2_Value_e));

  /* Saturate: '<S13>/Saturation2' */
  if (rtb_Saturation2 > PMSM_MTPA_Module_P.Saturation2_UpperSat) {
    rtb_Saturation2 = PMSM_MTPA_Module_P.Saturation2_UpperSat;
  } else if (rtb_Saturation2 < PMSM_MTPA_Module_P.Saturation2_LowerSat) {
    rtb_Saturation2 = PMSM_MTPA_Module_P.Saturation2_LowerSat;
  }

  /* End of Saturate: '<S13>/Saturation2' */

  /* Abs: '<S1>/Abs' */
  rtb_Abs = fabs(PMSM_MTPA_Module_U->speed_ref);

  /* Sqrt: '<S13>/Sqrt' incorporates:
   *  Abs: '<S13>/Abs'
   *  Product: '<S13>/Product1'
   *  Product: '<S8>/Square'
   *  Sum: '<S13>/Sum2'
   */
  rtb_Sqrt = sqrt(fabs(rtb_Sum1_g - rtb_Saturation2 * rtb_Saturation2));

  /* Switch: '<S12>/Switch' incorporates:
   *  Constant: '<S12>/Constant'
   *  Constant: '<S12>/Vdc_lumped'
   *  Gain: '<S12>/Gain'
   */
  if (PMSM_MTPA_Module_P.Constant_Value_ll >
      PMSM_MTPA_Module_P.Switch_Threshold_f) {
    rtb_Switch = PMSM_MTPA_Module_P.Gain_Gain_k * 0.0;
  } else {
    rtb_Switch = PMSM_MTPA_Module_P.Vdc_lumped_Value;
  }

  /* End of Switch: '<S12>/Switch' */

  /* Gain: '<S7>/Gain1' */
  rtb_Sqrt_o = PMSM_MTPA_Module_P.Gain1_Gain_a * rtb_Abs;

  /* Sum: '<S40>/Sum1' incorporates:
   *  Gain: '<S40>/FluxPM'
   *  Gain: '<S40>/Ld'
   *  Product: '<S40>/Product1'
   */
  rtb_Sum1_c = rtb_Saturation2 * rtb_Sqrt_o * PMSM_MTPA_Module_P.Ld_Gain +
    PMSM_MTPA_Module_P.FluxPM_Gain * rtb_Sqrt_o;

  /* Gain: '<S40>/Lq' incorporates:
   *  Product: '<S40>/Product'
   */
  rtb_Sqrt_o = rtb_Sqrt_o * rtb_Sqrt * PMSM_MTPA_Module_P.Lq_Gain;

  /* Sum: '<S40>/Sum3' incorporates:
   *  Product: '<S40>/Product2'
   *  Product: '<S40>/Product3'
   */
  rtb_Sqrt_o = rtb_Sum1_c * rtb_Sum1_c + rtb_Sqrt_o * rtb_Sqrt_o;

  /* If: '<S7>/If' incorporates:
   *  Constant: '<S11>/Constant'
   *  Constant: '<S25>/enableInportSatMethod'
   *  Gain: '<S11>/Gain'
   *  RelationalOperator: '<S11>/GreaterThan'
   *  Sqrt: '<S40>/Sqrt'
   *  Sum: '<S11>/Subtract'
   *  Switch: '<S25>/Switch1'
   */
  if (!(sqrt(rtb_Sqrt_o) >= PMSM_MTPA_Module_P.Gain_Gain_f * rtb_Switch -
        PMSM_MTPA_Module_P.Constant_Value_o)) {
    /* Outputs for IfAction SubSystem: '<S7>/MTPA condition' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    /* SignalConversion generated from: '<S10>/id' incorporates:
     *  Merge: '<S7>/Merge'
     */
    PMSM_MTPA_Module_B->Merge[0] = rtb_Saturation2;

    /* SignalConversion generated from: '<S10>/iq' incorporates:
     *  Merge: '<S7>/Merge'
     */
    PMSM_MTPA_Module_B->Merge[1] = rtb_Sqrt;

    /* End of Outputs for SubSystem: '<S7>/MTPA condition' */
  } else {
    /* Outputs for IfAction SubSystem: '<S7>/FW condition' incorporates:
     *  ActionPort: '<S9>/Action Port'
     */
    if (PMSM_MTPA_Module_P.enableInportSatMethod_Value != 0) {
      /* Switch: '<S25>/Switch1' incorporates:
       *  Constant: '<S20>/ReplaceInport_satMethod'
       */
      rtb_Switch1_l = PMSM_MTPA_Module_P.ReplaceInport_satMethod_Value;
    } else {
      /* Switch: '<S25>/Switch1' incorporates:
       *  Constant: '<S25>/ChosenMethod'
       */
      rtb_Switch1_l = PMSM_MTPA_Module_P.ChosenMethod_Value;
    }

    /* Gain: '<S16>/ 1' incorporates:
     *  Constant: '<S16>/Constant1'
     *  Gain: '<S16>/Gain'
     *  Math: '<S16>/Math Function'
     *  Product: '<S16>/Square1'
     *  Sum: '<S16>/Subtract1'
     *
     * About '<S16>/Math Function':
     *  Operator: reciprocal
     */
    rtb_Saturation2 = (PMSM_MTPA_Module_P.Gain_Gain_o * rtb_Switch -
                       PMSM_MTPA_Module_P.Constant1_Value_b) * (1.0 / rtb_Abs) *
      PMSM_MTPA_Module_P.u_Gain;

    /* Sum: '<S16>/Sum3' incorporates:
     *  Constant: '<S16>/term2'
     *  Constant: '<S16>/term3'
     *  Gain: '<S16>/ '
     *  Product: '<S16>/Square'
     *  Product: '<S16>/Square2'
     *  Sum: '<S16>/Sum1'
     */
    rtb_Saturation2 = PMSM_MTPA_Module_P.term2_Value *
      PMSM_MTPA_Module_P.term2_Value - (PMSM_MTPA_Module_P.term3_Value -
      rtb_Saturation2 * rtb_Saturation2 * PMSM_MTPA_Module_P._Gain);

    /* If: '<S21>/If' incorporates:
     *  Constant: '<S16>/term1'
     *  Constant: '<S37>/Constant'
     *  Gain: '<S38>/zero'
     *  RelationalOperator: '<S37>/Compare'
     *  Sqrt: '<S39>/Sqrt'
     *  Sum: '<S16>/Sum2'
     */
    if (rtb_Saturation2 < PMSM_MTPA_Module_P.Constant_Value_g) {
      /* Outputs for IfAction SubSystem: '<S21>/If negative value' incorporates:
       *  ActionPort: '<S38>/Action Port'
       */
      rtb_Saturation2 *= PMSM_MTPA_Module_P.zero_Gain;

      /* End of Outputs for SubSystem: '<S21>/If negative value' */
    } else {
      /* Outputs for IfAction SubSystem: '<S21>/If positive value' incorporates:
       *  ActionPort: '<S39>/Action Port'
       */
      rtb_Saturation2 = sqrt(rtb_Saturation2);

      /* End of Outputs for SubSystem: '<S21>/If positive value' */
    }

    rtb_Saturation2 = PMSM_MTPA_Module_P.term1_Value - rtb_Saturation2;

    /* End of If: '<S21>/If' */

    /* Switch: '<S25>/Switch' incorporates:
     *  Constant: '<S20>/ReplaceInport_satLim'
     *  Constant: '<S25>/Constant3'
     *  Constant: '<S25>/enableInportSatLim'
     */
    if (PMSM_MTPA_Module_P.enableInportSatLim_Value != 0) {
      rtb_Sqrt = PMSM_MTPA_Module_P.ReplaceInport_satLim_Value;
    } else {
      rtb_Sqrt = PMSM_MTPA_Module_P.Constant3_Value;
    }

    /* End of Switch: '<S25>/Switch' */

    /* Product: '<S25>/Product' */
    rtb_Sqrt_o = rtb_Sqrt * rtb_Sqrt;

    /* Sum: '<S26>/Sum1' incorporates:
     *  Product: '<S26>/Product'
     */
    rtb_Sum1_g += rtb_Saturation2 * rtb_Saturation2;

    /* If: '<S20>/If' incorporates:
     *  If: '<S23>/If'
     *  RelationalOperator: '<S23>/Relational Operator'
     */
    if ((rtb_Switch1_l == 1) || (rtb_Switch1_l == 2)) {
      /* Outputs for IfAction SubSystem: '<S20>/D//Q Axis Priority' incorporates:
       *  ActionPort: '<S24>/Action Port'
       */
      /* Switch: '<S24>/Switch' incorporates:
       *  Constant: '<S29>/Constant'
       *  RelationalOperator: '<S29>/Compare'
       */
      if (rtb_Switch1_l == PMSM_MTPA_Module_P.CompareToConstant_const) {
        rtb_Sum1_g = rtb_Saturation2;
        rtb_Saturation2 = rtb_Imag;
      } else {
        rtb_Sum1_g = rtb_Imag;
      }

      /* End of Switch: '<S24>/Switch' */

      /* Switch: '<S34>/Switch2' incorporates:
       *  RelationalOperator: '<S34>/LowerRelop1'
       */
      if (rtb_Sum1_g > rtb_Sqrt) {
        rtb_Sum1_g = rtb_Sqrt;
      } else {
        /* Gain: '<S33>/Gain' */
        rtb_Imag = PMSM_MTPA_Module_P.Gain_Gain_j * rtb_Sqrt;

        /* Switch: '<S34>/Switch' incorporates:
         *  RelationalOperator: '<S34>/UpperRelop'
         */
        if (rtb_Sum1_g < rtb_Imag) {
          rtb_Sum1_g = rtb_Imag;
        }

        /* End of Switch: '<S34>/Switch' */
      }

      /* End of Switch: '<S34>/Switch2' */

      /* Sum: '<S33>/Sum' incorporates:
       *  Product: '<S33>/Product'
       */
      rtb_Imag = rtb_Sqrt_o - rtb_Sum1_g * rtb_Sum1_g;

      /* If: '<S33>/If' incorporates:
       *  Product: '<S33>/Product2'
       *  RelationalOperator: '<S33>/Relational Operator'
       */
      if (!(rtb_Imag >= rtb_Saturation2 * rtb_Saturation2)) {
        /* Outputs for IfAction SubSystem: '<S33>/limitRef2' incorporates:
         *  ActionPort: '<S35>/Action Port'
         */
        /* Switch: '<S35>/Switch' incorporates:
         *  Gain: '<S35>/Gain'
         *  Sqrt: '<S35>/Sqrt'
         *  Switch: '<S35>/Switch1'
         */
        if (rtb_Saturation2 >= PMSM_MTPA_Module_P.Switch_Threshold) {
          /* Switch: '<S35>/Switch1' incorporates:
           *  Constant: '<S35>/Constant'
           */
          if (!(rtb_Imag > PMSM_MTPA_Module_P.Switch1_Threshold)) {
            rtb_Imag = PMSM_MTPA_Module_P.Constant_Value_m;
          }

          rtb_Saturation2 = sqrt(rtb_Imag);
        } else {
          if (!(rtb_Imag > PMSM_MTPA_Module_P.Switch1_Threshold)) {
            /* Switch: '<S35>/Switch1' incorporates:
             *  Constant: '<S35>/Constant'
             */
            rtb_Imag = PMSM_MTPA_Module_P.Constant_Value_m;
          }

          rtb_Saturation2 = PMSM_MTPA_Module_P.Gain_Gain_d * sqrt(rtb_Imag);
        }

        /* End of Switch: '<S35>/Switch' */
        /* End of Outputs for SubSystem: '<S33>/limitRef2' */
      }

      /* End of If: '<S33>/If' */

      /* Switch: '<S24>/Switch1' incorporates:
       *  Constant: '<S30>/Constant'
       *  RelationalOperator: '<S30>/Compare'
       */
      if (rtb_Switch1_l == PMSM_MTPA_Module_P.CompareToConstant1_const) {
        PMSM_MTPA_Module_B->Merge[0] = rtb_Sum1_g;
        PMSM_MTPA_Module_B->Merge[1] = rtb_Saturation2;
      } else {
        PMSM_MTPA_Module_B->Merge[0] = rtb_Saturation2;
        PMSM_MTPA_Module_B->Merge[1] = rtb_Sum1_g;
      }

      /* End of Switch: '<S24>/Switch1' */
      /* End of Outputs for SubSystem: '<S20>/D//Q Axis Priority' */

      /* Outputs for IfAction SubSystem: '<S20>/D-Q Equivalence' incorporates:
       *  ActionPort: '<S23>/Action Port'
       */
    } else if (rtb_Sum1_g > rtb_Sqrt_o) {
      /* Outputs for IfAction SubSystem: '<S23>/Limiter' incorporates:
       *  ActionPort: '<S27>/Action Port'
       */
      /* If: '<S23>/If' incorporates:
       *  Constant: '<S27>/Constant'
       *  Product: '<S27>/Product'
       *  Product: '<S27>/Product1'
       *  Product: '<S27>/Reciprocal'
       *  Sqrt: '<S27>/Square Root'
       *  Switch: '<S27>/Switch'
       */
      rtb_Sum1_g = sqrt(rtb_Sum1_g);
      if (!(rtb_Sum1_g != 0.0)) {
        rtb_Sum1_g = PMSM_MTPA_Module_P.Constant_Value_e;
      }

      rtb_Sum1_g = 1.0 / rtb_Sum1_g;
      PMSM_MTPA_Module_B->Merge[0] = rtb_Saturation2 * rtb_Sqrt * rtb_Sum1_g;
      PMSM_MTPA_Module_B->Merge[1] = rtb_Imag * rtb_Sqrt * rtb_Sum1_g;

      /* End of Outputs for SubSystem: '<S23>/Limiter' */
    } else {
      /* Outputs for IfAction SubSystem: '<S23>/Passthrough' incorporates:
       *  ActionPort: '<S28>/Action Port'
       */
      /* If: '<S23>/If' incorporates:
       *  SignalConversion generated from: '<S28>/dqRef'
       */
      PMSM_MTPA_Module_B->Merge[0] = rtb_Saturation2;
      PMSM_MTPA_Module_B->Merge[1] = rtb_Imag;

      /* End of Outputs for SubSystem: '<S23>/Passthrough' */

      /* End of Outputs for SubSystem: '<S20>/D-Q Equivalence' */
    }

    /* End of If: '<S20>/If' */

    /* Product: '<S22>/Divide' incorporates:
     *  Constant: '<S16>/Constant2'
     *  Constant: '<S22>/Constant'
     *  Constant: '<S22>/Constant1'
     *  Gain: '<S22>/Gain'
     *  Gain: '<S22>/Gain1'
     *  Sum: '<S22>/Add'
     *  Sum: '<S22>/Add1'
     */
    rtb_Gain = 1.0 / (PMSM_MTPA_Module_P.Gain_Gain_au *
                      PMSM_MTPA_Module_B->Merge[0] +
                      PMSM_MTPA_Module_P.Constant_Value_ls) * rtb_Gain *
      (PMSM_MTPA_Module_P.Gain1_Gain_i * PMSM_MTPA_Module_P.Constant2_Value +
       PMSM_MTPA_Module_P.Constant1_Value_h);

    /* If: '<S9>/If' incorporates:
     *  RelationalOperator: '<S9>/GreaterThan'
     */
    if (!(rtb_Gain > PMSM_MTPA_Module_B->Merge[1])) {
      /* Outputs for IfAction SubSystem: '<S9>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S15>/Action Port'
       */
      /* UnaryMinus: '<S18>/Unary Minus' incorporates:
       *  Constant: '<S18>/Constant'
       *  Product: '<S18>/Divide'
       *  Sum: '<S18>/Sum1'
       */
      rtb_Imag = -(rtb_Gain / (PMSM_MTPA_Module_B->Merge[0] +
        PMSM_MTPA_Module_P.Constant_Value));

      /* Sum: '<S18>/constant output' incorporates:
       *  Product: '<S18>/Product'
       */
      rtb_Sum1_g = rtb_Gain - rtb_Imag * PMSM_MTPA_Module_B->Merge[0];

      /* Sum: '<S17>/B' incorporates:
       *  Constant: '<S17>/fluxPMLd_Lq2'
       *  Product: '<S17>/mc'
       */
      rtb_Saturation2 = rtb_Imag * rtb_Sum1_g +
        PMSM_MTPA_Module_P.fluxPMLd_Lq2_Value;

      /* Sum: '<S17>/A' incorporates:
       *  Constant: '<S17>/ld2_lq2'
       *  Product: '<S17>/m2'
       */
      rtb_Imag = rtb_Imag * rtb_Imag + PMSM_MTPA_Module_P.ld2_lq2_Value;

      /* Product: '<S17>/c2' */
      rtb_Sqrt = rtb_Sum1_g * rtb_Sum1_g;

      /* Product: '<S17>/Divide' incorporates:
       *  Constant: '<S17>/Constant'
       *  Gain: '<S17>/Gain'
       *  Gain: '<S9>/Gain'
       *  Sum: '<S17>/Subtract'
       */
      rtb_Sum1_g = (PMSM_MTPA_Module_P.Gain_Gain * rtb_Switch -
                    PMSM_MTPA_Module_P.Constant_Value_b) /
        (PMSM_MTPA_Module_P.Gain_Gain_dx * rtb_Abs);

      /* Product: '<S17>/Divide1' incorporates:
       *  Abs: '<S17>/Abs'
       *  Constant: '<S17>/1_Lq2'
       *  Constant: '<S17>/fluxPM2_Lq2'
       *  Product: '<S17>/AC'
       *  Product: '<S17>/B2'
       *  Product: '<S17>/Product'
       *  Product: '<S17>/Product1'
       *  Sqrt: '<S17>/Sqrt'
       *  Sum: '<S17>/C'
       *  Sum: '<S17>/Subtract4'
       *  Sum: '<S17>/Subtract5'
       */
      rtb_Imag = (sqrt(fabs(rtb_Saturation2 * rtb_Saturation2 - ((rtb_Sqrt +
        PMSM_MTPA_Module_P.fluxPM2_Lq2_Value) - rtb_Sum1_g * rtb_Sum1_g *
        PMSM_MTPA_Module_P.u_Lq2_Value) * rtb_Imag)) - rtb_Saturation2) /
        rtb_Imag;

      /* Gain: '<S19>/Gain1' */
      rtb_Saturation2 = PMSM_MTPA_Module_B->Merge[0];

      /* Merge: '<S7>/Merge' incorporates:
       *  Constant: '<S19>/Constant'
       *  Constant: '<S19>/Constant1'
       *  Gain: '<S19>/Gain'
       *  Gain: '<S19>/Gain1'
       *  Product: '<S19>/Divide'
       *  SignalConversion generated from: '<S15>/Out1'
       *  Sum: '<S19>/Add'
       *  Sum: '<S19>/Add1'
       */
      PMSM_MTPA_Module_B->Merge[0] = rtb_Imag;
      PMSM_MTPA_Module_B->Merge[1] = 1.0 / (PMSM_MTPA_Module_P.Gain_Gain_a *
        rtb_Imag + PMSM_MTPA_Module_P.Constant_Value_l) * rtb_Gain *
        (PMSM_MTPA_Module_P.Gain1_Gain * rtb_Saturation2 +
         PMSM_MTPA_Module_P.Constant1_Value);

      /* End of Outputs for SubSystem: '<S9>/If Action Subsystem1' */
    }

    /* End of If: '<S9>/If' */
    /* End of Outputs for SubSystem: '<S7>/FW condition' */
  }

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Enable_fwc'
   */
  if (PMSM_MTPA_Module_P.Enable_fwc_Value >
      PMSM_MTPA_Module_P.Switch_Threshold_c) {
    /* Outport: '<Root>/Id_ref_out' */
    PMSM_MTPA_Module_Y->Id_ref_out = PMSM_MTPA_Module_B->Merge[0];

    /* Switch: '<S5>/sign' */
    if (PMSM_MTPA_Module_U->Torque_ref > PMSM_MTPA_Module_P.sign_Threshold) {
      /* Saturate: '<Root>/Iq_ref_saturation' incorporates:
       *  Outport: '<Root>/Iq_ref_out'
       */
      PMSM_MTPA_Module_Y->Iq_ref_out = PMSM_MTPA_Module_B->Merge[1];
    } else {
      /* Saturate: '<Root>/Iq_ref_saturation' incorporates:
       *  Outport: '<Root>/Iq_ref_out'
       *  UnaryMinus: '<S5>/Unary Minus'
       */
      PMSM_MTPA_Module_Y->Iq_ref_out = -PMSM_MTPA_Module_B->Merge[1];
    }

    /* End of Switch: '<S5>/sign' */
  } else {
    /* Outport: '<Root>/Id_ref_out' incorporates:
     *  Constant: '<Root>/Id_ref_nofw'
     */
    PMSM_MTPA_Module_Y->Id_ref_out = PMSM_MTPA_Module_P.Id_ref_nofw_Value;

    /* Saturate: '<Root>/Iq_ref_saturation' */
    PMSM_MTPA_Module_Y->Iq_ref_out = -120.0 /
      PMSM_MTPA_Module_P.PU_System.I_base;
    rtb_Abs = 120.0 / PMSM_MTPA_Module_P.PU_System.I_base;
    if (PMSM_MTPA_Module_U->Torque_ref > rtb_Abs) {
      /* Outport: '<Root>/Iq_ref_out' */
      PMSM_MTPA_Module_Y->Iq_ref_out = rtb_Abs;
    } else if (!(PMSM_MTPA_Module_U->Torque_ref < PMSM_MTPA_Module_Y->Iq_ref_out))
    {
      /* Outport: '<Root>/Iq_ref_out' */
      PMSM_MTPA_Module_Y->Iq_ref_out = PMSM_MTPA_Module_U->Torque_ref;
    }
  }

  /* End of Switch: '<Root>/Switch' */
}

/* Model initialize function */
void PMSM_MTPA_Module_initialize(RT_MODEL_PMSM_MTPA_Module_T *const
  PMSM_MTPA_Module_M, ExtU_PMSM_MTPA_Module_T *PMSM_MTPA_Module_U,
  ExtY_PMSM_MTPA_Module_T *PMSM_MTPA_Module_Y)
{
  B_PMSM_MTPA_Module_T *PMSM_MTPA_Module_B = PMSM_MTPA_Module_M->blockIO;

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) PMSM_MTPA_Module_B), 0,
                sizeof(B_PMSM_MTPA_Module_T));

  /* external inputs */
  (void)memset(PMSM_MTPA_Module_U, 0, sizeof(ExtU_PMSM_MTPA_Module_T));

  /* external outputs */
  (void)memset(PMSM_MTPA_Module_Y, 0, sizeof(ExtY_PMSM_MTPA_Module_T));

  /* SystemInitialize for Merge: '<S7>/Merge' */
  PMSM_MTPA_Module_B->Merge[0] = PMSM_MTPA_Module_P.Merge_InitialOutput;
  PMSM_MTPA_Module_B->Merge[1] = PMSM_MTPA_Module_P.Merge_InitialOutput;
}

/* Model terminate function */
void PMSM_MTPA_Module_terminate(RT_MODEL_PMSM_MTPA_Module_T *const
  PMSM_MTPA_Module_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(PMSM_MTPA_Module_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
