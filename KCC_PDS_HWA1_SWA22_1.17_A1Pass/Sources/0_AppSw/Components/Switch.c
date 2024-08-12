/*
 * DoorSys_Switch.c
 *
 *  Created on: 2023年12月12日
 *      Author: Administrator
 */
#include <Switch.h>
#include "DoorSys.h"

uint16_t SwitchValue;
#define SWITCH_AD_VALUE_LEVEL_LOW   (20)
#define SWITCH_AD_VALUE_LELVE_HIGH (100)

stSwich_t g_switch;
/*发送该指令打开SBC的HS3电源*/
static void Switch_Enable(void)
{

	uint16_t MTX = 0x0195;
	uint16_t MRX = 0;
	SPI_MasterTransferBlocking(&SPI0spi1Instance,&MTX,&MRX,1,1000);
	SPI_MasterTransferBlocking(&SPI0spi1Instance,&MTX,&MRX,1,1000);
}


static uint16_t  Switch_GetVal(void)
{
	ADC_DRV_ConfigChan(INST_DRIVEMADCONV1, 0U, &DriveMadConv1_ChnConfig1);
	ADC_DRV_WaitConvDone(INST_DRIVEMADCONV1);
	ADC_DRV_GetChanResult(INST_DRIVEMADCONV1,0U,&SwitchValue);
	return SwitchValue;
}


void Switch_Init(void)
{
	stSwich_t *p_switch = &g_switch;
	p_switch->adVal=0;
	p_switch->b_actived = 0;
	p_switch->cmd = SWITCH_CMD_NOCMD;
	p_switch->u16DebounceCount = 0;
	p_switch->cmdIndex = 0;
	Switch_Enable();

}

uint16_t Switch_Check(void)
{
	stSwich_t *p_switch = &g_switch;

	p_switch->adVal = Switch_GetVal();

	if(p_switch->adVal < SWITCH_AD_VALUE_LEVEL_LOW)
	{
		p_switch->u16DebounceCount++;
		if(p_switch->u16DebounceCount == K_SWTICH_DEBOUNCE_COUNT)
		{
			p_switch->b_actived = 1;
		}
		if(p_switch->u16DebounceCount > K_SWTICH_DEBOUNTCE_MAX)
		{
			p_switch->u16DebounceCount = K_SWTICH_DEBOUNTCE_MAX;

		}
	}
	else if(p_switch->adVal > SWITCH_AD_VALUE_LELVE_HIGH)
	{
		p_switch->u16DebounceCount=0;
		p_switch->b_actived = 0;

	}
	else
	{
		p_switch->u16DebounceCount=0;
		p_switch->b_actived = 0;
	}


	return 0;
}

static void Switch_GetCmd(void)
{
	stSwich_t *p_switch = &g_switch;
	DoorControl_t *door = &g_door;

	p_switch->cmd = SWITCH_CMD_NOCMD;
	if(p_switch->b_actived)
	{
		p_switch->b_actived=0;
		if(door->state == DOOR_STATE_OPENNING)
		{
			p_switch->cmd = SWITCH_CMD_STOP;
		}
		else if(door->state == DOOR_STATE_CLOSING)
		{
			p_switch->cmd = SWITCH_CMD_STOP;
		}
		else
		{
			switch (p_switch->cmdIndex)
			{
				 case 0:
				 {
					p_switch->cmd = SWITCH_CMD_CLOSE;
					p_switch->cmdIndex++;
					break;
				 }
				 case 1:
				 {
					p_switch->cmd = SWITCH_CMD_OPEN;
					p_switch->cmdIndex++;

					break;
				 }
				 case 2:
				 {
					p_switch->cmd = SWITCH_CMD_CLOSE;
					p_switch->cmdIndex++;
					break;
				 }
				 case 3:
				 {
					p_switch->cmd = SWITCH_CMD_OPEN;
					p_switch->cmdIndex = 0;

					break;
				 }
				 default:
				 {

					 p_switch->cmdIndex = 0;
					 break;
				 }
		   }
		}
	}
}

void Switch_CmdHandler(void)
{
	stSwich_t *p_switch = &g_switch;
	DoorControl_t *door = &g_door;

	Switch_GetCmd();

	switch (p_switch->cmd)
	{
		case SWITCH_CMD_OPEN:
		{
			door->DoorCmd = DOOR_CMD_OPEN;

			p_switch->cmd = SWITCH_CMD_NOCMD;
			break;
		}
		case SWITCH_CMD_CLOSE:
		{
			door->DoorCmd = DOOR_CMD_CLOSE;

			p_switch->cmd = SWITCH_CMD_NOCMD;
			break;
		}
		case SWITCH_CMD_STOP:
		{
			door->DoorCmd = DOOR_CMD_STOP;

			p_switch->cmd = SWITCH_CMD_NOCMD;
		}
			break;
		default:
		{

			p_switch->cmd = SWITCH_CMD_NOCMD;
			break;
		}
	}



}
