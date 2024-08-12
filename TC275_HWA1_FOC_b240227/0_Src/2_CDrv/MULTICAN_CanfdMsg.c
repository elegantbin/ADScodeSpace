/********************************************************************************************************************
 * \file MULTICAN_FD.c
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
volatile uint8                      g_isrRxCount = 0; /* Declared as volatile in order not to be removed by compiler */
canCommunicationStatusType          g_status = CanCommunicationStatus_Success;
uint8 g_currentCanFdUseCase;

const uint8                         g_dlcLookUpTable[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64 };
const canMessageObjectConfigType    g_messageObjectConf[NUMBER_OF_CAN_FD_CASES] =
                                    {
                                        { MOTOR_COMMAND_FL_ID , TRUE,  IfxMultican_DataLengthCode_64,  FALSE  },
                                        { MOTOR_COMMAND_FR_ID , TRUE,  IfxMultican_DataLengthCode_64,  FALSE  },
                                        { MOTOR_COMMAND_RL_ID , TRUE,  IfxMultican_DataLengthCode_64,  FALSE  },
                                        { MOTOR_COMMAND_RR_ID , TRUE,  IfxMultican_DataLengthCode_64,  FALSE  }

                                    };//transmit
const canMessageObjectConfigType canDstMsgObj[NUMBER_OF_CAN_FD_CASES]=
                                    {
                                        { MOTOR_FEEDBACK_FL_ID, TRUE,  IfxMultican_DataLengthCode_64,  FALSE },
                                        { MOTOR_FEEDBACK_FR_ID, TRUE,  IfxMultican_DataLengthCode_64,  FALSE },
                                        { MOTOR_FEEDBACK_RL_ID, TRUE,  IfxMultican_DataLengthCode_64,  FALSE },
                                        { MOTOR_FEEDBACK_RR_ID, TRUE,  IfxMultican_DataLengthCode_64,  FALSE }
                                    };//receive
void CanfdMsg_IsrRxHandler(void)
{
//    g_isrRxCount = MotorTybe_Read ;
    g_currentCanFdUseCase = 0;
    IfxMultican_Status readStatus_canfd;
    readStatus_canfd = IfxMultican_MsgObj_readLongFrame(g_multican.canDstMsgObj[g_isrRxCount].node->mcan,
                                                             g_multican.canDstMsgObj[g_isrRxCount].msgObjId,
                                                             &g_multican.rxMsg,
                                                             (uint32*)&g_multican.rxData);

//          g_bldc.RefPosition = (g_multican.rxData[21]<<8)|g_multican.rxData[20];
//          g_bldc.Refspeed    = (g_multican.rxData[25]<<8)|g_multican.rxData[24];
//          g_bldc.RefTorque   = g_multican.rxData[26];
//          g_bldc.cmd=(enMotorCmd)((g_multican.rxData[30])&0x0F);
//          g_bldc.loop_cmd    = ((g_multican.rxData[31])&0x0F);


    /* If no new data has been received, report an error */
    if(!( readStatus_canfd & IfxMultican_Status_newData ))
    {
//        while(1)
                {
                }
    }

    /* If new data has been received but with one message lost, report an error */
    if(readStatus_canfd == IfxMultican_Status_newDataButOneLost)
    {
//        while(1)
                {
                }
    }

    /* If there was no error, increment the counter to indicate the number of successfully received CAN messages */
    if (g_status == CanCommunicationStatus_Success)
    {
//        while(1)
                {
                }
    }


}


IfxMultican_Status  canfd_sendStatus = IfxMultican_Status_ok;
void CanfdMsg_transmit(void)
{
    g_currentCanFdUseCase = 0;
//    Current_Vphase.actual =  g_bldc.CurrentV_BUS;

//    IFX_EXTERN uint32 count_A,count_Z;
//    IFX_EXTERN sint16 cycleTotalCount;

    if(g_messageObjectConf[g_currentCanFdUseCase].messageLen > IfxMultican_DataLengthCode_8)
    {

        IfxMultican_Message_longFrameInit(&g_multican.txMsg,
                                          g_messageObjectConf[g_currentCanFdUseCase].messageId,
                                          g_messageObjectConf[g_currentCanFdUseCase].messageLen,
                                          g_messageObjectConf[g_currentCanFdUseCase].fastBitRate);


//        if(Encoder_RawPosition > 0)
//         {
//            g_multican.txData[0] = 1;
//         }
//         else if(Encoder_RawPosition < 0)
//         {
//             g_multican.txData[0] = 2;
//         }
//         if(g_absMotSpeed == 0)
//         {
//             g_multican.txData[0] = 0;
//         }
//
//        g_multican.txData[1] = Current_Vphase.bytes_f[0];
//        g_multican.txData[2] = Current_Vphase.bytes_f[1];
//        g_multican.txData[3] = Current_Vphase.bytes_f[2];
//        g_multican.txData[4] = Current_Vphase.bytes_f[3];
//
//        g_multican.txData[5]= g_bldc.Voltage_BUS;
//        g_multican.txData[6]= 0;
//        g_multican.txData[7]= 0;
//        g_multican.txData[8]= 0;
//
//        g_multican.txData[9]= ((Actual_Angle_Position)>>0)&0XFF;
//        g_multican.txData[10]=((Actual_Angle_Position)>>8)&0XFF;
//
//        g_multican.txData[11]= g_DriverBoardTemp;
//
//        g_multican.txData[12]= (g_absMotSpeed)&0XFF;
//        g_multican.txData[13]= (g_absMotSpeed>>8)&0XFF;
//
//        g_multican.txData[14]= MotorTorque;
//
//        g_multican.txData[18]= (uint16)g_bldc.u32DiagCode;
//
//        if(g_bldc.state == MOTOR_STATE_STOP)
//        {
//            if(g_bldc.loop_cmd == 0||g_bldc.loop_cmd == 1||g_bldc.loop_cmd == 2)
//            {
//                g_multican.txData[19] = 0;
//            }
//        }
//        else
//        {
//            g_multican.txData[19] = 1;
//        }


        canfd_sendStatus = IfxMultican_Can_MsgObj_sendLongFrame(&g_multican.canSrcMsgObj[g_currentCanFdUseCase],
                                                            &g_multican.txMsg,
                                                            (uint32*)&g_multican.txData);
    }
    else
    {
        /* Initialization of the TX message (standard frame) */

        IfxMultican_Message_init(&g_multican.txMsg,
                                 g_messageObjectConf[g_currentCanFdUseCase].messageId,
                                 INVALID_DATA_VALUE,
                                 INVALID_DATA_VALUE,
                                 g_messageObjectConf[g_currentCanFdUseCase].messageLen);
        /* Send the CAN message with the previously defined TX message content */
        canfd_sendStatus =  IfxMultican_Can_MsgObj_sendMessage(&g_multican.canSrcMsgObj[g_currentCanFdUseCase], &g_multican.txMsg);
    }

}
