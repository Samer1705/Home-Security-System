/*
 * communication.c
 *
 *  Created on: Mar 12, 2024
 *      Author: samer
 */

#include "communication.h"

#include "../common/std_types.h"
#include "../mcal/atmega32_uart.h"
#include "subsystems/alarm_system/alarm_system.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void Comm_HandleSend(uint8 sData)
{
	UART_sendByte(sData);
}

static void Comm_HandleReceive(uint8 rData)
{
	switch(rData)
	{
	case PANIC_ON:
		g_threatFlag |= (1<<PANIC_MODE);
		break;
	case PANIC_OFF:
		g_threatFlag &= ~(1<<PANIC_MODE);
		break;
	case DISARM_ON:
		break;
	case DISARM_OFF:
		break;
	case DOOR_OPEN:
		break;
	case DOOR_CLOSE:
		break;
	default:
		break;
	}
}

static void RXHandler()
{
	uint8 rData = UART_receiveByte();
	Comm_HandleReceive(rData);
}

void Comm_Init()
{
	/* Configure & Initialize UART */
	UART_ConfigType uartConfig = {
			UART_8BIT,
			PARITY_ENABLE,
			UART_1_STOP_BIT,
			9600
	};
	UART_init(&uartConfig);
	UART_interruptEnable(RX_INT);
	UART_setCallBackRX(RXHandler);
}




