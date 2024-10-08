/********************************************************************************************************************
 * \file MULTICAN_FD.h
 * \copyright Copyright (C) Infineon Technologies AG 2019
 *
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are solely in the form of
 * machine-executable object code generated by a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *********************************************************************************************************************/

#ifndef MULTICAN_CANFD_MSG_H_
#define MULTICAN_CANFD_MSG_H_ 1

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "Ifx_Types.h"
#include "IfxMultican_Can.h"
#include "IfxMultican.h"
#include "IfxPort.h"                                            /* For GPIO Port Pin Control                         */

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

#define MOTOR_FEEDBACK_FL_ID                0x18FF0C11          /* Left front motor */
#define MOTOR_FEEDBACK_FR_ID                0x18FF0C12          /* Right front motor */
#define MOTOR_FEEDBACK_RL_ID                0x18FF0C13          /* Left rear motor */
#define MOTOR_FEEDBACK_RR_ID                0x18FF0C14          /* Right rear motor */

#define MOTOR_COMMAND_FL_ID                 0x11FF0B11
#define MOTOR_COMMAND_FR_ID                 0x11FF0B12
#define MOTOR_COMMAND_RL_ID                 0x11FF0B13
#define MOTOR_COMMAND_RR_ID                 0x11FF0B14
//#define MOTORNUMBER                 (MotorTybe_Read)
//
//#if(MOTORNUMBER == 0x0)
//#define EXTENDED_MESSAGE_ID_1       0x18FF0C11                   /* Left front motor */
//#define MOTOR_RR_ID       0x11FF0B11
//
//#elif(MOTORNUMBER == 0x1)
//#define EXTENDED_MESSAGE_ID_1       0x18FF0C12                   /* Right front motor */
//#define MOTOR_RR_ID       0x11FF0B12
//
//#elif(MOTORNUMBER == 0x2)
//#define EXTENDED_MESSAGE_ID_1       0x18FF0C13                   /* Left rear motor */
//#define MOTOR_RR_ID       0x11FF0B13
//
//#elif(MOTORNUMBER == 0x3)
//#define EXTENDED_MESSAGE_ID_1       0x18FF0C14                   /* Right rear motor */
//#define MOTOR_RR_ID       0x11FF0B14
//#endif

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
extern const canMessageObjectConfigType    g_messageObjectConf[NUMBER_OF_CAN_FD_CASES];
extern const canMessageObjectConfigType canDstMsgObj[NUMBER_OF_CAN_FD_CASES];
extern IfxMultican_Status  canfd_sendStatus;

/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/
extern void CanfdMsg_IsrRxHandler(void);
extern void CanfdMsg_transmit(void);
#endif /* MULTICAN_FD_H_ */
