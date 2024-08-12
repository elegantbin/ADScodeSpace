/*_COMMUTATION_POINT_H__*/

#ifndef _CFGOFFSET__COMMUTATIONPOINT_H_
#define _CFGOFFSET__COMMUTATIONPOINT_H_

#include "platform_types.h"
#include "GTM_ATOM_PWM_6Step.h"
#include  "MotorMgtSwc.h"
#include <DataFlash_ZeroOffest.h>

#define MOTOR_NUMBER_2023082901            (4801)
#define MOTOR_NUMBER_2023083106            (4806)
#define MOTOR_NUMBER_2023090107            (4807)
#define MOTOR_NUMBER_2023103120            (4820)
#define MOTOR_NUMBER_0000000000            (0000)

#define MDA_48VBLDC_MOTOR       (MOTOR_NUMBER_0000000000)

#if(MOTOR_NUMBER_2023082901 == MDA_48VBLDC_MOTOR)

#define POS_CTRL_STEP_OFFSET_CW                 (2)
#define POS_CTRL_STEP_OFFSET_CCW                (2)
#define K_ELE_ZERO_OFFSET_CW                    (11)
#define K_ELE_ZERO_OFFSET_CCW                   (11)

#elif(MOTOR_NUMBER_2023083106 == MDA_48VBLDC_MOTOR)

#define POS_CTRL_STEP_OFFSET_CW                 (5)            //1\2\3\4
#define POS_CTRL_STEP_OFFSET_CCW                (5)
#define K_ELE_ZERO_OFFSET_CW                    (0)            //8\6\4\2\1\0      @0
#define K_ELE_ZERO_OFFSET_CCW                   (16)          //26\28\22\18\20   @20

#elif(MOTOR_NUMBER_2023090107 == MDA_48VBLDC_MOTOR)
#define POS_CTRL_STEP_OFFSET_CW                 (4)    //2\5\4
#define POS_CTRL_STEP_OFFSET_CCW                (4)
#define K_ELE_ZERO_OFFSET_CW                    (2)    //8
#define K_ELE_ZERO_OFFSET_CCW                   (20)   //26

#elif(MOTOR_NUMBER_0000000000 == MDA_48VBLDC_MOTOR)
#define POS_CTRL_STEP_OFFSET_CW                 (Step_Offset_CW_Read)
#define POS_CTRL_STEP_OFFSET_CCW                (Step_Offset_CCW_Read)
#define K_ELE_ZERO_OFFSET_CW                    (Zero_Offset_CW_Read)
#define K_ELE_ZERO_OFFSET_CCW                   (Zero_Offset_CCW_Read)
#endif

#endif  /*_CFGOFFSET__COMMUTATIONPOINT_H_*/


