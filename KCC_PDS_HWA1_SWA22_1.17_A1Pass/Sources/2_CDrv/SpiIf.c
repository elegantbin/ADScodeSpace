/*
 * SBC_SPI.c
 *
 *   Created on: 7.12.2023
 *      Author: Administrator
 */


#include <SpiIf.h>

void SpiIf_SbcInit(void)
{
	SPI_MasterInit(&SPI0spi1Instance,&SPI0spi1_MasterConfig0);
}

void SpiIf_sendSbc(void)
{
	/*To SBC*/
	uint16_t MTX = 0x55;
	uint16_t MRX = 0;
	SPI_MasterTransferBlocking(&SPI0spi1Instance,&MTX,&MRX,1,1000);
}


