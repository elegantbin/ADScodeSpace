#include "platform_types.h"
#include "CommutationPoint.h"
#include "MotorMgtSwc.h"
#include <EncoderGpt12.h>



stCommutationMap CommutateTable_CW[6]={
        {K_ROT_DIR_CW,EN_COMMUTATION_CW_POINT00,HIGH_W_PWM_LOW_U_ON},
        {K_ROT_DIR_CW,EN_COMMUTATION_CW_POINT01,HIGH_W_PWM_LOW_V_ON},
        {K_ROT_DIR_CW,EN_COMMUTATION_CW_POINT02,HIGH_U_PWM_LOW_V_ON},
        {K_ROT_DIR_CW,EN_COMMUTATION_CW_POINT03,HIGH_U_PWM_LOW_W_ON},
        {K_ROT_DIR_CW,EN_COMMUTATION_CW_POINT04,HIGH_V_PWM_LOW_W_ON},
        {K_ROT_DIR_CW,EN_COMMUTATION_CW_POINT05,HIGH_V_PWM_LOW_U_ON}

};

stCommutationMap CommutateTable_CCW[6]={
        {K_ROT_DIR_CCW,EN_COMMUTATION_CCW_POINT00,HIGH_W_PWM_LOW_V_ON},
        {K_ROT_DIR_CCW,EN_COMMUTATION_CCW_POINT01,HIGH_W_PWM_LOW_U_ON},
        {K_ROT_DIR_CCW,EN_COMMUTATION_CCW_POINT02,HIGH_V_PWM_LOW_U_ON},
        {K_ROT_DIR_CCW,EN_COMMUTATION_CCW_POINT03,HIGH_V_PWM_LOW_W_ON},
        {K_ROT_DIR_CCW,EN_COMMUTATION_CCW_POINT04,HIGH_U_PWM_LOW_W_ON},
        {K_ROT_DIR_CCW,EN_COMMUTATION_CCW_POINT05,HIGH_U_PWM_LOW_V_ON}
};


enComutateDriverIndex Commutation_getCommuPosIndex(enMotorRotationDir rotDirection)
{
    uint8 i=0;

    volatile sint16 position = EncoderUpdatePosition();  /* get the Mechanic Position */

    position %= K_TOTAL_COUNTS_PER_ELE_ROTATION;      /* get the electronic Position*/

    enComutateDriverIndex cmDrvIdx = COMMUTATION_UNKNOWN;
    if(rotDirection == K_ROT_DIR_CW)
    {
        if(position < 0)
        {
            position+=K_TOTAL_COUNTS_PER_ELE_ROTATION;    /* Transfer to Positive value*/
        }
        enCOMMUTE_POINT cmP = CommutationPoint_check(position,K_ROT_DIR_CW);

        for(i=0;i<6;i++)
        {
            if(CommutateTable_CW[i].cmPoint==cmP)
            {
                cmDrvIdx = CommutateTable_CW[i].cmStepIndex;
                break;
            }
        }
    }
    else if(rotDirection == K_ROT_DIR_CCW)  /* CCW neg-position,negative value */
    {
        if(position>0)
        {
            position-=K_TOTAL_COUNTS_PER_ELE_ROTATION;    /* Transfer to Negative value*/
        }
        enCOMMUTE_POINT cmP = CommutationPoint_check(position,K_ROT_DIR_CCW);

        for(i=0;i<6;i++)
        {
            if(CommutateTable_CCW[i].cmPoint==cmP)
            {
                cmDrvIdx = CommutateTable_CCW[i].cmStepIndex;
                break;

            }
        }
    }

    return cmDrvIdx;
}

enCOMMUTE_POINT CommutationPoint_check(sint16 encodeElePosition,enMotorRotationDir rotationDir)
{
    enCOMMUTE_POINT enComumuteStep=EN_COMMUTATION_UNKNOWN;

    if(rotationDir==K_ROT_DIR_CW)
       {

          if(encodeElePosition >= (sint16)K_COMMUTATION_CW_POINT_05)
          {
                enComumuteStep = EN_COMMUTATION_CW_POINT05;
          }
          else if(encodeElePosition >= (sint16)K_COMMUTATION_CW_POINT_04)
          {
                enComumuteStep = EN_COMMUTATION_CW_POINT04;
          }
          else if(encodeElePosition >= (sint16)K_COMMUTATION_CW_POINT_03)
          {
                enComumuteStep = EN_COMMUTATION_CW_POINT03;
          }
          else if(encodeElePosition >= (sint16)K_COMMUTATION_CW_POINT_02)
          {
                enComumuteStep = EN_COMMUTATION_CW_POINT02;
          }
          else if(encodeElePosition >= (sint16)K_COMMUTATION_CW_POINT_01)
          {
                enComumuteStep = EN_COMMUTATION_CW_POINT01;
          }
          else if(encodeElePosition >= (sint16)K_COMMUTATION_CW_POINT_00)
          {
                 enComumuteStep = EN_COMMUTATION_CW_POINT00;
          }
          else if(encodeElePosition >= 0)
          {
                enComumuteStep = EN_COMMUTATION_CW_POINT05;
          }
          else
          {
              /**UnReachable**/
              enComumuteStep=EN_COMMUTATION_UNKNOWN;
          }
    }
    else if(rotationDir==K_ROT_DIR_CCW)
    {
          if(encodeElePosition <= (sint16)K_COMMUTATION_CCW_POINT_05)
          {
                enComumuteStep = EN_COMMUTATION_CCW_POINT05;
          }
          else if(encodeElePosition <= (sint16)K_COMMUTATION_CCW_POINT_04)
          {
                enComumuteStep = EN_COMMUTATION_CCW_POINT04;
          }
          else if(encodeElePosition <= (sint16)K_COMMUTATION_CCW_POINT_03)
          {
                enComumuteStep = EN_COMMUTATION_CCW_POINT03;
          }
          else if(encodeElePosition <= (sint16)K_COMMUTATION_CCW_POINT_02)
          {
                enComumuteStep = EN_COMMUTATION_CCW_POINT02;
          }
          else if(encodeElePosition <= (sint16)K_COMMUTATION_CCW_POINT_01)
          {
                enComumuteStep = EN_COMMUTATION_CCW_POINT01;
          }
          else if(encodeElePosition <= (sint16)K_COMMUTATION_CCW_POINT_00)
          {
                 enComumuteStep = EN_COMMUTATION_CCW_POINT00;
          }
          else if(encodeElePosition <= 0)
          {
                enComumuteStep = EN_COMMUTATION_CCW_POINT05;
          }
          else
          {
              /**UnReachable**/
              enComumuteStep=EN_COMMUTATION_UNKNOWN;
          }

    }

    return enComumuteStep;
}

//enCOMMUTE_POINT CommutationPoint_check(sint16 encodeElePosition,enMotorRotationDir rotationDir)
//{
//    enCOMMUTE_POINT enComumuteStep=EN_COMMUTATION_UNKNOWN;
//
//    if(rotationDir==K_ROT_DIR_CW)
//       {
//
//          if(encodeElePosition >= commuPointCfg.CmtCW_P05)
//          {
//                enComumuteStep = EN_COMMUTATION_CW_POINT05;
//          }
//          else if(encodeElePosition >= commuPointCfg.CmtCW_P04)
//          {
//                enComumuteStep = EN_COMMUTATION_CW_POINT04;
//          }
//          else if(encodeElePosition >= commuPointCfg.CmtCW_P03)
//          {
//                enComumuteStep = EN_COMMUTATION_CW_POINT03;
//          }
//          else if(encodeElePosition >= commuPointCfg.CmtCW_P02)
//          {
//                enComumuteStep = EN_COMMUTATION_CW_POINT02;
//          }
//          else if(encodeElePosition >= commuPointCfg.CmtCW_P01)
//          {
//                enComumuteStep = EN_COMMUTATION_CW_POINT01;
//          }
//          else if(encodeElePosition >= commuPointCfg.CmtCW_P00)
//          {
//                 enComumuteStep = EN_COMMUTATION_CW_POINT00;
//          }
//          else if(encodeElePosition >= 0)
//          {
//                enComumuteStep = EN_COMMUTATION_CW_POINT05;
//          }
//          else
//          {
//              /**UnReachable**/
//              enComumuteStep=EN_COMMUTATION_UNKNOWN;
//          }
//    }
//    else if(rotationDir==K_ROT_DIR_CCW)
//    {
//          if(encodeElePosition <= commuPointCfg.CmtCCW_P05)
//          {
//                enComumuteStep = EN_COMMUTATION_CCW_POINT05;
//          }
//          else if(encodeElePosition <= commuPointCfg.CmtCCW_P04)
//          {
//                enComumuteStep = EN_COMMUTATION_CCW_POINT04;
//          }
//          else if(encodeElePosition <= commuPointCfg.CmtCCW_P03)
//          {
//                enComumuteStep = EN_COMMUTATION_CCW_POINT03;
//          }
//          else if(encodeElePosition <= commuPointCfg.CmtCCW_P02)
//          {
//                enComumuteStep = EN_COMMUTATION_CCW_POINT02;
//          }
//          else if(encodeElePosition <= commuPointCfg.CmtCCW_P01)
//          {
//                enComumuteStep = EN_COMMUTATION_CCW_POINT01;
//          }
//          else if(encodeElePosition <= commuPointCfg.CmtCCW_P00)
//          {
//                 enComumuteStep = EN_COMMUTATION_CCW_POINT00;
//          }
//          else if(encodeElePosition <= 0)
//          {
//                enComumuteStep = EN_COMMUTATION_CCW_POINT05;
//          }
//          else
//          {
//              /**UnReachable**/
//              enComumuteStep=EN_COMMUTATION_UNKNOWN;
//          }
//
//    }
//
//    return enComumuteStep;
//}
