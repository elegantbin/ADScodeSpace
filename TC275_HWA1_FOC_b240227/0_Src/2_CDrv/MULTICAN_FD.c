/********************************************************************************************************************
 * \file MULTICAN_FD.c
 * \
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *********************************************************************************************************************/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "MULTICAN_FD.h"
#include "MultiCan_DebugCanMsg.h"
#include "MultiCan_CanfdMsg.h"
#include "IfxCpu_Intrinsics.h"
#include "IfxGpt12_reg.h"
#include "AppTorqueControl.h"
#include "Configuration.h"
#include "ConfigurationISR.h"
#include "spi_encoder.h"
#include "stdlib.h"
#include "Ifx_cfg_FocControl.h"
#include "Tables.h"
/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/

multicanType                        g_multican;

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Macro to define Interrupt Service Routine.
 * This macro:
 * - defines linker section as .intvec_tc<vector number>_<interrupt priority>.
 * - defines compiler specific attribute for the interrupt functions.
 * - defines the Interrupt Service Routine as ISR function.
 *
 * IFX_INTERRUPT(isr, vectabNum, priority)
 *  - isr: Name of the ISR function.
 *  - vectabNum: Vector table number.
 *  - priority: Interrupt priority. Refer Usage of Interrupt Macro for more details.
 */
/* Interrupt Service Routine (ISR) called once the RX interrupt is generated.
 * Reads the received CAN message and in case of no errors, increments the counter to
 * indicate the number of successfully received CAN messages.
 */
IFX_INTERRUPT(canIsrRxHandler, 0, ISR_PRIORITY_CAN_RX);
IFX_INTERRUPT(DebugcanIsrRxHandler, 0, ISR_PRIORITY_CAN_debug_RX);

void DebugcanIsrRxHandler(void)
{
    DebugCanMsg_IsrRxHandler();
}

/* Interrupt Service Routine (ISR) called once the RX interrupt has been generated.
 * Compares the content of the received CAN message with the content of the transmitted CAN message
 * and in case of success, turns on the LED2 to indicate successful CAN message reception.
 */

void canIsrRxHandler(void)
{
    CanfdMsg_IsrRxHandler();
}

/* Function to initialize MULTICAN module, nodes and message objects related to this application use case */
void initMultican(void)
{
    uint8 currentCanMessageObject;
    /* ==========================================================================================
     * CAN module configuration and initialization:
     * ==========================================================================================
     *  - load the default CAN module configuration into the configuration structure
     *  - define the interrupt priority for both interrupt node pointers used in the example
     *  - initialize the CAN module with the modified configuration
     * ==========================================================================================
     */
    IfxMultican_Can_initModuleConfig(&g_multican.canConfig, &MODULE_CAN);

    g_multican.canConfig.nodePointer[RX_INTERRUPT_SRC_ID].priority = ISR_PRIORITY_CAN_RX;
    g_multican.canConfig.nodePointer[RX_debug_INTERRUPT_SRC_ID].priority = ISR_PRIORITY_CAN_debug_RX;

    IfxMultican_Can_initModule(&g_multican.can, &g_multican.canConfig);

    /* ==========================================================================================
     * Common CAN node configuration and initialization:
     * ==========================================================================================
     *  - load the default CAN node configuration into the configuration structure
     *
     *  - set CAN node in the "Loop back" mode (no external pins will be used)
     *  - enable usage of CAN Flexible Data rate (CAN FD) (NCRx.FDEN  = 1)
     *
     *  - set the nominal baud rate (used during arbitration phase) to 500kbits
     *  - set the nominal sample point to 80% of the total nominal bit time
     *  - set the nominal resynchronisation jump width to 20% of the total nominal bit time
     *  - set the fast baud rate (used during data phase) to 2Mbits
     *  - set the fast sample point to 70% of the total nominal bit time
     *  - set the fast resynchronisation jump width to 20% of the total nominal bit time
     *  - set the transceiver delay compensation offset to 0
     * ==========================================================================================
     */
    IfxMultican_Can_Node_initConfig(&g_multican.canNodeConfig, &g_multican.can);

    /* ==========================================================================================
     * CAN node 1 configuration and initialization:
     * ==========================================================================================
     *  - assign the node to CAN node 1
     *  - initialize the CAN node 1 with the modified configuration
     * ==========================================================================================
     */

    g_multican.canNodeConfig.nodeId = IfxMultican_NodeId_0;
    g_multican.canNodeConfig.rxPin  = &IfxMultican_RXD0A_P02_1_IN;
    g_multican.canNodeConfig.txPin  = &IfxMultican_TXD0_P02_0_OUT;
    g_multican.canNodeConfig.baudrate = 500000;
//    g_multican.canNodeConfig.lastErrorCodeInterrupt.enabled = FALSE ;
//    g_multican.canNodeConfig.alertInterrupt.enabled = FALSE ;

    IfxMultican_Can_Node_init(&g_multican.canNode1, &g_multican.canNodeConfig);

    /* ==========================================================================================
     * CAN node 0 configuration and initialization:
     * ==========================================================================================
     *  - assign the node to CAN node 0
     *  - initialize the CAN node 0 with the modified configuration
     * ==========================================================================================
     */
    g_multican.canNodeConfig.flexibleDataRate = TRUE;
    g_multican.canNodeConfig.fdConfig.nominalBaudrate = 1000000;//500000
    g_multican.canNodeConfig.fdConfig.nominalSamplePoint = 8000;
    g_multican.canNodeConfig.fdConfig.nominalSynchJumpWidth = 2000;
    g_multican.canNodeConfig.fdConfig.fastBaudrate = 2000000;//2000000
    g_multican.canNodeConfig.fdConfig.fastSamplePoint = 7000;
    g_multican.canNodeConfig.fdConfig.fastSynchJumpWidth = 2000;
    g_multican.canNodeConfig.fdConfig.loopDelayOffset = 0;
//    g_multican.canNodeConfig.lastErrorCodeInterrupt.enabled = FALSE ;
//    g_multican.canNodeConfig.errorWarningLevel = 0;

    g_multican.canNodeConfig.nodeId = IfxMultican_NodeId_2;
    g_multican.canNodeConfig.rxPin  = &IfxMultican_RXD2B_P02_3_IN;
    g_multican.canNodeConfig.txPin  = &IfxMultican_TXD2_P02_2_OUT;

    IfxMultican_Can_Node_init(&g_multican.canNode0, &g_multican.canNodeConfig);

    /* ================================================================================================================
     * Source standard message objects configuration and initialization:
     * ================================================================================================================
     *  - load the default CAN message object configuration into the configuration structure
     *
     *  - define the message object as a transmit message object (common setting for all source message objects)
     *  - define acceptance of the frame with only matching IDE (common setting for all source message objects)
     *
     *  - define the message object ID (each message object ID value should be unique)
     *  - define the CAN message ID used during arbitration phase
     *  - define the standard or extended frame to be used
     *  - define the message object that holds data bytes 8 to 35 (top message)
     *  - define the message object that holds data bytes 36 to 63 (bottom message)
     *
     *  - define the length of the transmitted data (related to MOFCRn.DLC, MOFCRn.FDF, MOFGPR.BOT, and MOFGPR.TOP bitfields)
     *  - define the usage of bit rate switching (related to MOFCRn.BRS bitfield)
     *
     *  - initialize the source standard CAN message object with the modified configuration
     * ----------------------------------------------------------------------------------------------------------------
     * These CAN message objects are assigned to CAN Node 0
     * ================================================================================================================
     */
    IfxMultican_Can_MsgObj_initConfig(&g_multican.canMsgObjConfig, &g_multican.canNode0);

    g_multican.canMsgObjConfig.frame = IfxMultican_Frame_transmit;
    g_multican.canMsgObjConfig.control.matchingId = TRUE;

    for(currentCanMessageObject = 0; currentCanMessageObject < NUMBER_OF_CAN_FD_CASES; currentCanMessageObject++)
    {
        g_multican.canMsgObjConfig.msgObjId = (IfxMultican_MsgObjId)currentCanMessageObject;
        g_multican.canMsgObjConfig.messageId = g_messageObjectConf[currentCanMessageObject].messageId;
        g_multican.canMsgObjConfig.control.extendedFrame = g_messageObjectConf[currentCanMessageObject].extendedFrame;
        g_multican.canMsgObjConfig.control.topMsgObjId = (2 * currentCanMessageObject) + SRC_EXTENDED_MO_OFFSET;
        g_multican.canMsgObjConfig.control.bottomMsgObjId = g_multican.canMsgObjConfig.control.topMsgObjId + 1;

        g_multican.canMsgObjConfig.control.messageLen = g_messageObjectConf[currentCanMessageObject].messageLen;
        g_multican.canMsgObjConfig.control.fastBitRate = g_messageObjectConf[currentCanMessageObject].fastBitRate;

        IfxMultican_Can_MsgObj_init(&g_multican.canSrcMsgObj[currentCanMessageObject], &g_multican.canMsgObjConfig);
    }


    /* ================================================================================================================
     * Destination standard message objects configuration and initialization:
     * ================================================================================================================
     *  - load the default CAN message object configuration into the configuration structure
     *
     *  - define the message object as a receive message object (common setting for all destination message objects)
     *  - define acceptance of the frame with only matching IDE (common setting for all destination message objects)
     *  - enable interrupt generation in case of CAN message reception (common setting for all destination message objects)
     *  - define interrupt node pointer to be used (all destination message objects share the SAME node)
     *
     *  - define the message object ID (each message object ID value should be unique)
     *  - define the CAN message ID used during arbitration phase (should match the source message objects ID)
     *  - define the standard or extended frame to be used
     *  - define the message object that holds data bytes 8 to 35 (top message)
     *  - define the message object that holds data bytes 36 to 63 (bottom message)
     *
     *  - define the length of the received data (related to MOFGPR.BOT and MOFGPR.TOP bitfields)
     *
     *  - initialize the source standard CAN message object with the modified configuration
     * ----------------------------------------------------------------------------------------------------------------
     * These CAN message objects are assigned to CAN Node 1
     * ================================================================================================================
     */
    IfxMultican_Can_MsgObj_initConfig(&g_multican.canMsgObjConfig, &g_multican.canNode0);

    g_multican.canMsgObjConfig.frame = IfxMultican_Frame_receive;
    g_multican.canMsgObjConfig.control.matchingId = TRUE;
    g_multican.canMsgObjConfig.rxInterrupt.enabled = TRUE;
    g_multican.canMsgObjConfig.rxInterrupt.srcId = RX_INTERRUPT_SRC_ID;
//    g_multican.canMsgObjConfig.acceptanceMask = 0x0UL;

    for(currentCanMessageObject = 0; currentCanMessageObject < NUMBER_OF_CAN_FD_CASES; currentCanMessageObject++)
    {
//        g_multican.canMsgObjConfig.msgObjId = (IfxMultican_MsgObjId)(currentCanMessageObject + DST_MO_OFFSET);
//        g_multican.canMsgObjConfig.messageId = g_messageObjectConf[currentCanMessageObject].messageId;
//        g_multican.canMsgObjConfig.control.extendedFrame = g_messageObjectConf[currentCanMessageObject].extendedFrame;
//        g_multican.canMsgObjConfig.control.topMsgObjId = (2 * currentCanMessageObject) + DST_EXTENDED_MO_OFFSET;
//        g_multican.canMsgObjConfig.control.bottomMsgObjId = g_multican.canMsgObjConfig.control.topMsgObjId + 1;
////        g_multican.canMsgObjConfig.acceptanceMask = 0x0UL;
//
//        g_multican.canMsgObjConfig.control.messageLen = g_messageObjectConf[currentCanMessageObject].messageLen;

        g_multican.canMsgObjConfig.msgObjId = (IfxMultican_MsgObjId)(currentCanMessageObject + DST_MO_OFFSET);
        g_multican.canMsgObjConfig.messageId =canDstMsgObj[currentCanMessageObject].messageId;
        g_multican.canMsgObjConfig.control.extendedFrame = canDstMsgObj[currentCanMessageObject].extendedFrame;
        g_multican.canMsgObjConfig.control.topMsgObjId = (2 * currentCanMessageObject) + DST_EXTENDED_MO_OFFSET;
        g_multican.canMsgObjConfig.control.bottomMsgObjId = g_multican.canMsgObjConfig.control.topMsgObjId + 1;

        g_multican.canMsgObjConfig.control.messageLen = canDstMsgObj[currentCanMessageObject].messageLen;
        g_multican.canMsgObjConfig.control.fastBitRate = canDstMsgObj[currentCanMessageObject].fastBitRate;

        IfxMultican_Can_MsgObj_init(&g_multican.canDstMsgObj[currentCanMessageObject], &g_multican.canMsgObjConfig);
    }



        /* ==========================================================================================
         * Source message object configuration and initialization:
         * ==========================================================================================
         *  - load default CAN message object configuration into configuration structure
         *
         *  - define the message object ID
         *  - define the CAN message ID used during arbitration phase
         *  - define the message object as a transmit message object
         *  - enable interrupt generation in case of CAN message transmission
         *  - define interrupt node pointer to be used
         *
         *  - initialize the source CAN message object with the modified configuration
         * ==========================================================================================
         */
        IfxMultican_Can_MsgObj_initConfig(&g_multican.canMsgObjConfig, &g_multican.canNode1);

        g_multican.canMsgObjConfig.msgObjId = 4;
        g_multican.canMsgObjConfig.messageId = 0x777;
        g_multican.canMsgObjConfig.control.matchingId               = FALSE;
        g_multican.canMsgObjConfig.frame = IfxMultican_Frame_transmit;
        g_multican.canMsgObjConfig.txInterrupt.enabled = FALSE;
        g_multican.canMsgObjConfig.control.extendedFrame = TRUE;

        g_multican.canMsgObjConfig.control.topMsgObjId              = 252;
        g_multican.canMsgObjConfig.control.bottomMsgObjId           = 253;
        g_multican.canMsgObjConfig.control.fastBitRate              = FALSE; /* fast bit rate enable/disable */
        g_multican.canMsgObjConfig.control.messageLen               = IfxMultican_DataLengthCode_8;
        IfxMultican_Can_MsgObj_init(&g_multican.canSrcMsgObjTx, &g_multican.canMsgObjConfig);

        /* ==========================================================================================
         * Rx message object configuration and initialization:
         * ==========================================================================================
         *  - load default CAN message object configuration into configuration structure
         *
         *  - define the message object ID (different than the ID used for source MO)
         *  - define the CAN message ID used during arbitration phase (same as ID used for source MO)
         *  - define the message object as a receive message object
         *  - enable interrupt generation in case of CAN message transmission
         *  - define interrupt node pointer to be used (different than the one used for source MO)
         *
         *  - initialize the destination CAN message object with the modified configuration
         * ==========================================================================================
         */
        IfxMultican_Can_MsgObj_initConfig(&g_multican.canMsgObjConfig, &g_multican.canNode1);

        g_multican.canMsgObjConfig.msgObjId = 5;
        g_multican.canMsgObjConfig.messageId = 0x888;
        g_multican.canMsgObjConfig.frame = IfxMultican_Frame_receive;
        g_multican.canMsgObjConfig.rxInterrupt.enabled = TRUE;
        g_multican.canMsgObjConfig.control.extendedFrame=TRUE;
        g_multican.canMsgObjConfig.rxInterrupt.srcId = IfxMultican_SrcId_2;

        g_multican.canMsgObjConfig.acceptanceMask = 0x0UL;

        IfxMultican_Can_MsgObj_init(&g_multican.canSrcMsgObjRx, &g_multican.canMsgObjConfig);

}


void Re_initMultican(void)
{
    if(debug_sendStatus != IfxMultican_Status_ok||canfd_sendStatus != IfxMultican_Status_ok ||NormalMsg_sendStatus !=IfxMultican_Status_ok)
    {
        initMultican();
    }
}

