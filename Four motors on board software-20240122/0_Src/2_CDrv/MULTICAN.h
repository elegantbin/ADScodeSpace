/********************************************************************************************************************
 * \file MULTICAN.h
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

#ifndef MULTICAN_H_
#define MULTICAN_H_ 1

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxMultican_Can.h"
#include "IfxMultican.h"
#include "IfxPort.h"                                             /* For GPIO Port Pin Control                        */

#if(0)
/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define SRC_MESSAGE_OBJECT_TX_ID       (IfxMultican_MsgObjId)0     /* Source message object ID                          */
#define SRC_MESSAGE_OBJECT_RX_ID       (IfxMultican_MsgObjId)1     /* Destination message object ID                     */
#define DST_MESSAGE_OBJECT_TX_ID        (IfxMultican_MsgObjId)2
#define DST_MESSAGE_OBJECT_RX_ID         (IfxMultican_MsgObjId)3

#define CAN_MESSAGE_TXD_ID00        0x776                       /* Message ID that will be used in arbitration phase */
#define CAN_MESSAGE_TXD_ID01        0x777                       /* Message ID that will be used in arbitration phase */
#define CAN_MESSAGE_TXD_ID02        0x778
#define CAN_MESSAGE_TXD_ID03        0x779
#define CAN_MESSAGE_TXD_ID04        0x780

#define CAN_MESSAGE_RXD_ID01        0x888
#define CAN_MESSAGE_RXD_ID02        0x999
#define TX_INTERRUPT_SRC_ID         IfxMultican_SrcId_0         /* Transmit interrupt service request ID             */
#define RX_INTERRUPT_SRC_ID         IfxMultican_SrcId_1         /* Receive interrupt service request ID              */
#define INVALID_DATA_VALUE          (uint32)0xDEADBEEF          /* Used to invalidate RX message data content        */
#define INVALID_ID_VALUE            (uint32)0xFFFFFFFF          /* Used to invalidate RX message ID value            */

/*********************************************************************************************************************/
/*--------------------------------------------------Data Structures--------------------------------------------------*/
/*********************************************************************************************************************/
typedef struct
{
    IfxMultican_Can                 can;                   /* CAN module handle to HW module SFR set                 */
    IfxMultican_Can_Config          canConfig;             /* CAN module configuration structure                     */
    IfxMultican_Can_Node            canSrcNode;            /* CAN source node handle data structure                  */
    IfxMultican_Can_Node            canDstNode;            /* CAN destination node handle data structure             */
    IfxMultican_Can_NodeConfig      canNodeConfig;         /* CAN node configuration structure                       */
    IfxMultican_Can_MsgObj          canSrcMsgObjTx;          /* CAN source message object handle data structure        */
    IfxMultican_Can_MsgObj          canSrcMsgObjRx;          /* CAN source message object handle data structure        */
    IfxMultican_Can_MsgObj          canDstMsgObjTx;          /* CAN destination message object handle data structure   */
    IfxMultican_Can_MsgObj          canDstMsgObjRx;          /* CAN destination message object handle data structure   */

    IfxMultican_Can_MsgObjConfig    canMsgObjConfig;       /* CAN message object configuration structure             */
    IfxMultican_Message             txSrcMsg;                 /* Transmitted CAN message structure                      */
    IfxMultican_Message             txDstMsg;                 /* Transmitted CAN message structure                      */
    IfxMultican_Message             rxSrcMsg;                 /* Received CAN message structure                         */
    IfxMultican_Message             rxDstMsg;                 /* Received CAN message structure                         */
} AppMulticanType;

typedef union
{
    uint32  u32Data;
    uint8   u8Data[4];
}unU32ToU8;
/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/
void DebugcanIsrTxHandler(void);
void DebugcanIsrRxHandler(void);
void initMulticanDebug(void);
void transmitCanDebugMessage(void);

#endif /* MULTICAN_H_ */

#endif
