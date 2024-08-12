/********************************************************************************************************************
 * \file MULTICAN_DebugCanMsgFD.c
 *  *
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
#include "IfxCpu_Intrinsics.h"
#include "IfxGpt12_reg.h"
#include "AppTorqueControl.h"
#include "App_VelocityControl.h"
#include "Configuration.h"
#include "ConfigurationISR.h"
#include "spi_encoder.h"
#include "stdlib.h"
#include "Ifx_cfg_FocControl.h"
#include "Tables.h"
#include "MultiCan_DebugCanMsg.h"
#include "GPT12_Encoder.h"
#include "Vadc_VIT.h"
/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
FloatBytes   currenttableU[trace_memory];
FloatBytes   currenttableV[trace_memory];
FloatBytes   currenttableW[trace_memory];
FloatBytes   g_foc_Iq;
FloatBytes   g_foc_Id;
FloatBytes   g_foc_Vq;
FloatBytes   g_foc_Vd;
FloatBytes   g_foc_torque;
/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
IFX_EXTERN sint16  elePos_Offset;
#define      TORUQE_OR_CURRENT    (GIVE_CURRENT)
#define      GIVE_TORQUE          (1)
#define      GIVE_CURRENT         (2)
#define      REF_CURRENT_INCRE    (3)
void DebugCanMsg_IsrRxHandler(void)
{
    IfxMultican_Status readStatus;

    /* Read the received CAN message and store the status of the operation */

    readStatus = IfxMultican_Can_MsgObj_readMessage(&g_multican.canSrcMsgObjRx, &g_multican.rxSrcMsg);

    if( g_multican.rxSrcMsg.id  == CAN_MESSAGE_RXD_ID01)
    {
        uint8 motCANCmd=0;
        uint16 param01=10;
        uint16 param02=10;
        uint8  param03=0;

        static uint8 motCANCmd_Old=0;

        motCANCmd = (uint8)(g_multican.rxSrcMsg.data[0]&0x0F);
        param01 =   (uint16)(g_multican.rxSrcMsg.data[1]);
        param02 =   (uint16)(g_multican.rxSrcMsg.data[1]>>16);

        if(motCANCmd_Old != motCANCmd)
        {
            switch(motCANCmd)
            {
                case CAN_MOT_CMD_STOP:
                    g_motor.control.stop = 1;
                    g_motor.control.start = 0;

                    g_motor.diag.focControlEnabled = FALSE;
                    g_motor.diag.encoderEnabled= FALSE;
                    g_motor.diag.vectorFixedEnable = FALSE;
                    g_velocityControl.enabled = FALSE;
                    break;

                case CAN_MOT_CMD_OPENLOOP_START:
                    g_motor.control.stop = 0;
                    g_motor.control.start = 1;

                    g_motor.diag.focControlEnabled = FALSE;
                    g_motor.diag.encoderEnabled= TRUE;
                    g_motor.diag.vectorFixedEnable = FALSE;
                    g_velocityControl.enabled = FALSE;
                    break;

                case CAN_MOT_CMD_FOC_START:
                    g_motor.control.stop = 0;
                    g_motor.control.start = 1;

                    g_motor.diag.focControlEnabled = TRUE;
                    g_motor.diag.encoderEnabled= FALSE;
                    g_motor.diag.vectorFixedEnable = FALSE;
                    g_velocityControl.enabled = FALSE;
                    break;

                case CAN_MOT_CMD_FOC_DOUBLE_LOOP:
                    g_motor.control.stop = 0;
                    g_motor.control.start = 1;

                    g_motor.diag.focControlEnabled = TRUE;
                    g_motor.diag.encoderEnabled= FALSE;
                    g_motor.diag.vectorFixedEnable = FALSE;
                    g_velocityControl.enabled = TRUE;

                    break;

                case CAN_MOT_CMD_START_VECTORFIXED:

                    if(g_motor.control.run != TRUE)
                    {
                        g_motor.control.stop = 0;
                        g_motor.control.start = 1;

                        g_motor.diag.focControlEnabled = FALSE;
                        g_motor.diag.encoderEnabled= FALSE;
                        g_motor.diag.vectorFixedEnable = TRUE;
                        g_velocityControl.enabled = FALSE;

                        {
                            uint8 fixAngleIndex = (uint8)param01;

                          if(fixAngleIndex==1)
                          {
                             g_motor.diag.vectorFixedAngle = (COSSIN_TABLE_SIZE >> 2);
                          }
                          else if(fixAngleIndex==2)
                          {
                              g_motor.diag.vectorFixedAngle = (COSSIN_TABLE_SIZE >> 1);

                          }
                          else if(fixAngleIndex==3)
                          {

                              g_motor.diag.vectorFixedAngle = (COSSIN_TABLE_SIZE >> 2)+(COSSIN_TABLE_SIZE >> 1);
                          }
                          else
                          {
                              g_motor.diag.vectorFixedAngle = 0;

                          }
                        }
                    }

                    break;

                case CAN_MOT_CMD_ELEANGL_UPDATE:

                    if(g_motor.control.run != TRUE)
                    {
                            elePos_Offset = param01*4;
                    }

                    break;

                default:

                    break;
            }

            motCANCmd_Old = motCANCmd;
        }

        if(motCANCmd == CAN_MOT_CMD_OPENLOOP_START)
        {
            if(param01 > 90)
            {
                param01  = 90;
            }
            if(param02 > 90)
            {
                param02 = 90;
            }

              g_motor.control.foc.vdq_ref.imag = (float) 0.01*param01;
              g_motor.control.foc.vdq_ref.real = (float) -0.01*param02;
       }
        else if(motCANCmd == CAN_MOT_CMD_FOC_START)
        {

#if(TORUQE_OR_CURRENT == GIVE_CURRENT)

            g_motor.control.foc.Msg_ref.imag = param01*0.1;
            g_motor.control.foc.Msg_ref.real = -param02*0.1;

#elif(TORUQE_OR_CURRENT == REF_CURRENT_INCRE)
            g_motor.control.foc.incre_ref_max.imag = param01*0.1;

#elif(TORUQE_OR_CURRENT == GIVE_TORQUE)
            g_motor.control.foc.torque_ref = param01*0.1;
#endif
        }
        else if(motCANCmd == CAN_MOT_CMD_FOC_DOUBLE_LOOP)
        {
            g_velocityControl.ref_receive = param01;
        }

    }
}


#define TRANSMIT_TEST     0
#define TRANSMIT_DEBUG    1
#define TRANSMIT_MODE    (TRANSMIT_DEBUG)

IfxMultican_Status  debug_sendStatus = IfxMultican_Status_ok;

void DebugCanMsg_transmitCurrentMsg(void)
{
    /* Define the content of the data to be transmitted */
    static uint32 dataLow,dataHigh;
    static uint32 can_tx_id;
    static uint32 tx_seq =0;
    static uint32 Inum = 0;

#define CANFrame_2ByteVariable_In4Bytes(A,B)  (((uint32)A&0x0000FFFF)+(((uint32)(B)<<16)&0xFFFF0000))
#define CANFrame0_3Bytes(B0,B1,B2,B3) (((uint32)B0&0x000000FF)+(((uint32)(B1)<<8)&0x0000FF00)+(((uint32)(B2)<<16)&0x00FF0000)+(((uint32)(B3)<<24)&0xFF000000))
#define CANFrame4_7Bytes(B4,B5,B6,B7) (((uint32)B4&0x000000FF)+(((uint32)(B5)<<8)&0x0000FF00)+(((uint32)(B6)<<16)&0x00FF0000)+(((uint32)(B7)<<24)&0xFF000000))

    IFX_EXTERN float32 currenttable[trace_memory];
    IFX_EXTERN float32 currenttable1[trace_memory];
    IFX_EXTERN float32 currenttable2[trace_memory];
    IFX_EXTERN sint16 angletable[trace_memory];
    IFX_EXTERN uint16 duty_cycle0[trace_memory];
    IFX_EXTERN sint16 Encoder_SPIPosition;

    currenttableU[Inum].actual = currenttable[Inum];
    currenttableV[Inum].actual = currenttable1[Inum];
    currenttableW[Inum].actual = currenttable2[Inum];
   if(g_motor.analogCurrentInputs.currentTableFull == 1)
  {

    switch(tx_seq)
    {
           case 0x00:
           {

               dataLow  =  CANFrame0_3Bytes(currenttableU[Inum].bytes_f[0],currenttableU[Inum].bytes_f[1],
                       currenttableU[Inum].bytes_f[2],currenttableU[Inum].bytes_f[3]);
               dataHigh  =  CANFrame4_7Bytes(currenttableV[Inum].bytes_f[0],currenttableV[Inum].bytes_f[1],
                       currenttableV[Inum].bytes_f[2],currenttableV[Inum].bytes_f[3]);
               can_tx_id = CAN_MESSAGE_TXD_ID00;

               tx_seq++;

           }
           break;

           case 0x01:
           {
              dataLow  =  CANFrame0_3Bytes(currenttableW[Inum].bytes_f[0],currenttableW[Inum].bytes_f[1],
                      currenttableW[Inum].bytes_f[2],currenttableW[Inum].bytes_f[3]);
              dataHigh  =  CANFrame_2ByteVariable_In4Bytes(angletable[Inum],duty_cycle0[Inum]);

              can_tx_id = CAN_MESSAGE_TXD_ID01;

              Inum++;

              if(Inum > trace_memory)
              {
                  g_motor.analogCurrentInputs.currentTableFull = 0;
                  Inum = 0;
              }

              tx_seq=0;
           }
           break;


           default:
           {
              tx_seq = 0x00;
           }
           break;
       }


        /* Initialization of the TX message */
        IfxMultican_Message_init(&g_multican.txSrcMsg,
                                 can_tx_id,
                                 dataLow,
                                 dataHigh,
                                 IfxMultican_DataLengthCode_8);

        debug_sendStatus=IfxMultican_Can_MsgObj_sendMessage(&g_multican.canSrcMsgObjTx, &g_multican.txSrcMsg);

    }
}



IfxMultican_Status  NormalMsg_sendStatus = IfxMultican_Status_ok;

void DebugCanMsg_transimitNormalMsg(void)
{
    /* Define the content of the data to be transmitted */
    static uint32 dataLow,dataHigh;
    static uint32 can_tx_id;
    static uint32 tx_seq =0;

#define CANFrame_2ByteVariable_In4Bytes(A,B)  (((uint32)A&0x0000FFFF)+(((uint32)(B)<<16)&0xFFFF0000))
#define CANFrame0_3Bytes(B0,B1,B2,B3) (((uint32)B0&0x000000FF)+(((uint32)(B1)<<8)&0x0000FF00)+(((uint32)(B2)<<16)&0x00FF0000)+(((uint32)(B3)<<24)&0xFF000000))
#define CANFrame4_7Bytes(B4,B5,B6,B7) (((uint32)B4&0x000000FF)+(((uint32)(B5)<<8)&0x0000FF00)+(((uint32)(B6)<<16)&0x00FF0000)+(((uint32)(B7)<<24)&0xFF000000))

    IFX_EXTERN sint16 Encoder_SPIPosition;
    IFX_EXTERN sint16 g_Encoder_RawPosition;
    IFX_EXTERN sint16 ele_Angle;
    IFX_EXTERN uint8 g_direction;
    g_foc_Iq.actual = g_motor.control.foc.nfo_mdq.imag;
    g_foc_Id.actual = g_motor.control.foc.nfo_mdq.real;
    g_foc_Vq.actual = g_motor.control.foc.g_Vdq.imag;
    g_foc_Vd.actual = g_motor.control.foc.g_Vdq.real;
    g_foc_torque.actual = g_motor.control.foc.torque_actual;

    switch(tx_seq)
    {
           case 0x00:
           {
               dataLow  = CANFrame_2ByteVariable_In4Bytes(Encoder_SPIPosition,g_Encoder_RawPosition);
               dataHigh = CANFrame_2ByteVariable_In4Bytes(ele_Angle ,(uint16)g_motor.speed);// g_motor.speed,g_IncrEnc.speed
               can_tx_id = CAN_MESSAGE_TXD_ID02;//ID:0x778

               tx_seq=0x01;
           }
           break;

           case 0x01:
           {
               dataLow  = CANFrame0_3Bytes(g_foc_Iq.bytes_f[0],g_foc_Iq.bytes_f[1],g_foc_Iq.bytes_f[2],g_foc_Iq.bytes_f[3]);
               dataHigh = CANFrame4_7Bytes(g_foc_Id.bytes_f[0],g_foc_Id.bytes_f[1],g_foc_Id.bytes_f[2],g_foc_Id.bytes_f[3]);
               can_tx_id = CAN_MESSAGE_TXD_ID03;//ID:0x779

               tx_seq=0x02;
           }
           break;

           case 0x02://used for test data
           {
               dataLow  = CANFrame0_3Bytes((uint8)g_motor.control.foc.ref.imag,(uint8)g_motor.control.foc.ref.real,
                       (uint8)g_motor.rot_dir,g_motor.test_count1);
               dataHigh = CANFrame4_7Bytes(g_foc_torque.bytes_f[0],g_foc_torque.bytes_f[1],
                                           g_foc_torque.bytes_f[2],g_foc_torque.bytes_f[3]);
               can_tx_id = CAN_MESSAGE_TXD_ID04;//ID:0x780

               tx_seq=0x03;
           }
           break;

           case 0x03:
           {
               dataLow  = CANFrame0_3Bytes(g_foc_Vq.bytes_f[0],g_foc_Vq.bytes_f[1],g_foc_Vq.bytes_f[2],g_foc_Vq.bytes_f[3]);
               dataHigh = CANFrame4_7Bytes(g_foc_Vd.bytes_f[0],g_foc_Vd.bytes_f[1],g_foc_Vd.bytes_f[2],g_foc_Vd.bytes_f[3]);
               can_tx_id = CAN_MESSAGE_TXD_ID05;//ID:0x781

               tx_seq=0x00;
           }
           break;

           default:
           {
              tx_seq = 0x00;
           }
           break;
       }



       // if( IfxMultican_Status_notSentBusy != sendStatus)
        {
        /* Invalidation of the RX message */
       IfxMultican_Message_init(&g_multican.rxSrcMsg,
                                 CAN_MESSAGE_RXD_ID02,
                                 INVALID_DATA_VALUE,
                                 INVALID_DATA_VALUE,
                                 IfxMultican_DataLengthCode_8);

        /* Initialization of the TX message */
        IfxMultican_Message_init(&g_multican.txSrcMsg,
                                 can_tx_id,
                                 dataLow,
                                 dataHigh,
                                 IfxMultican_DataLengthCode_8);

        NormalMsg_sendStatus=IfxMultican_Can_MsgObj_sendMessage(&g_multican.canSrcMsgObjTx, &g_multican.txSrcMsg);
        }
}





