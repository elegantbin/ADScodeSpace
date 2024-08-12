/*
 * UartIf.c
 *
 *   Created on: 7.12.2023
 *      Author: Administrator
 */

#include <AdcIf.h>
#include <DoorSys.h>
#include "stdarg.h"
#include "stdio.h"
#include "string.h"

#include "UartIf.h"
#include "lpuart1.h"
#include "lpuart_driver.h"
#include "DualHall.h"
char USART1_TX_BUF[200];
void u1_printf(char* fmt,...);

void UartIf_Init(void)
{
	LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0);
	u1_printf("ϵͳ��ʼ����� \r\n");
	u1_printf("HallaCount:%d \r\n",hall_A.HallCount);
	u1_printf("HallbCount:%d \r\n",hall_B.HallCount);
	u1_printf("HallWidth:%d \r\n",hall_A.HallWidth);
	u1_printf("Current:%d \r\n",Current);
	u1_printf("Door_Pos:%d \r\n",g_door.u16Realtime_Pos);
	u1_printf("end2 \r\n");
	u1_printf("         \r\n");
	u1_printf("         \r\n");
}


void UartIf1_Send(void)
{
	u1_printf("HallaCount:%d \r\n",hall_A.HallCount);
	u1_printf("HallbCount:%d \r\n",hall_B.HallCount);
	u1_printf("HallWidth:%d \r\n",hall_A.HallWidth);
	u1_printf("Current:%d \r\n",Current);
	u1_printf("Door_Pos:%d \r\n",g_door.u16Realtime_Pos);
	u1_printf("end \r\n");
	u1_printf("         \r\n");
	u1_printf("         \r\n");
}

/*************************************************************************
  *FUNCTION NAME:			UART_Send
  *FUNCTION DESCRIPTION:		UART_Send
  *PAPRAMETER:		uint16_t Speed,motor_dir_t dir
  *RETURN VALUE:		void	VALUENAME:void
  *EDITOR:			ReaveGan
  *DATE:				2023.12.07
  *VERSION:			1.0
  *************************************************************************/

void u1_printf(char* fmt,...)
{
	uint32_t bytesRemaining;
   	va_list ap;
   	va_start(ap,fmt);
   	vsprintf((char*)USART1_TX_BUF,fmt,ap);
   	va_end(ap);

   	LPUART_DRV_SendData(INST_LPUART1, (uint8_t *)USART1_TX_BUF, (uint32_t)strlen(USART1_TX_BUF));

    while (LPUART_DRV_GetTransmitStatus(INST_LPUART1, &bytesRemaining)
               != STATUS_SUCCESS)  {}
}
