/*
 * communication.c
 *
 *  Created on: Mar 12, 2024
 *      Author: samer
 */

#include "communication.h"

#include "../common/common_macros.h"
#include "../mcal/atmega32_timer1.h"
#include "../mcal/atmega32_uart.h"
#include "subsystems/alarm_system/alarm_system.h"
#include "subsystems/motion_detection_system/motion_detection_system.h"
#include "subsystems/smart_door_lock_system/smart_door_lock_system.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile uint8 g_transmitFlag = 0x00;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

static void Comm_HandleSend()
{
	if (GET_BIT(g_threatFlag, FIRE_THREAT) != GET_BIT(g_transmitFlag, FIRE_THREAT))
	{
		TOGGLE_BIT(g_transmitFlag, FIRE_THREAT);
		if (BIT_IS_SET(g_threatFlag, FIRE_THREAT))
		{
			UART_sendByte(FIRE_TRIGGERED);
		}
		else
		{
			UART_sendByte(FIRE_HANDLED);
		}
	}
	else if (GET_BIT(g_threatFlag, GAS_THREAT) != GET_BIT(g_transmitFlag, GAS_THREAT))
	{
		TOGGLE_BIT(g_transmitFlag, GAS_THREAT);
		if (BIT_IS_SET(g_threatFlag, GAS_THREAT))
		{
			UART_sendByte(GAS_TRIGGERED);
		}
		else
		{
			UART_sendByte(GAS_HANDLED);
		}
	}
	else if (GET_BIT(g_threatFlag, FLOOD_THREAT) != GET_BIT(g_transmitFlag, FLOOD_THREAT))
	{
		TOGGLE_BIT(g_transmitFlag, FLOOD_THREAT);
		if (BIT_IS_SET(g_threatFlag, FLOOD_THREAT))
		{
			UART_sendByte(FLOOD_TRIGGERED);
		}
		else
		{
			UART_sendByte(FLOOD_HANDLED);
		}
	}
	else if (GET_BIT(g_threatFlag, MOTION_THREAT) != GET_BIT(g_transmitFlag, MOTION_THREAT))
	{
		TOGGLE_BIT(g_transmitFlag, MOTION_THREAT);
		if (BIT_IS_SET(g_threatFlag, MOTION_THREAT))
		{
			UART_sendByte(MOTION_TRIGGERED);
		}
		else
		{
			UART_sendByte(MOTION_HANDLED);
		}
	}
}

static void Comm_HandleReceive(uint8 rData)
{
	switch (rData)
	{
	case MOTION_ON:
		g_motionEnable = TRUE;
		break;
	case MOTION_OFF:
		g_motionEnable = FALSE;
		break;
	case PANIC_ON:
		g_threatFlag |= (1 << PANIC_MODE);
		break;
	case PANIC_OFF:
		g_threatFlag &= ~(1 << PANIC_MODE);
		break;
	case DISARM_ON:
		break;
	case DISARM_OFF:
		break;
	case DOOR_OPEN:
		setMode(NORMAL_LOCKED, 3);
		break;
	case DOOR_CLOSE:
		setMode(NORMAL_LOCKED, 1);
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

static void TXHandler()
{
	Comm_HandleSend();
}

void Comm_Init()
{
	/* Configure & Initialize UART */
	UART_ConfigType uartConfig =
	{ UART_5BIT, PARITY_EVEN, UART_1_STOP_BIT, 115200 };
	UART_init(&uartConfig);
	UART_setCallBackRX(RXHandler);
	UART_interruptEnable(RX_INT);

	/* Configure & Initialize Timer1 */
	TIMER1_init(TMR1_256);
	TIMER1_setCallback(TXHandler);
	TIMER1_interruptEnable();
	TIMER1_on();
}

