/******************************************************************************
 *	Module: Communication Module
 *	File Name: communication.c
 *  Description: Communication Module Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "communication.h"

#include "../common/common_macros.h"
#include "../mcal/atmega32_timer1.h"
#include "../mcal/atmega32_uart.h"
#include "../mcal/atmega32_interrupt.h"
#include "subsystems/alarm_system/alarm_system.h"
#include "subsystems/motion_detection_system/motion_detection_system.h"
#include "subsystems/smart_door_lock_system/smart_door_lock_system.h"
#include "subsystems/gas_system/gas_system.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile uint8 g_transmitFlag = 0x00;
uint8 g_triggersFlag = 0x00, g_settingsFlag = 0x01;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

static void Comm_HandleSend()
{
	if (GET_BIT(g_triggersFlag,
			FIRE_TRIGGER) != GET_BIT(g_transmitFlag, FIRE_TRIGGER))
	{
		TOGGLE_BIT(g_transmitFlag, FIRE_TRIGGER);
		if (BIT_IS_SET(g_triggersFlag, FIRE_TRIGGER))
		{
			UART_sendByte(FIRE_TRIGGERED);
		}
		else
		{
			UART_sendByte(FIRE_HANDLED);
		}
	}
	else if (GET_BIT(g_triggersFlag,
			GAS_TRIGGER) != GET_BIT(g_transmitFlag, GAS_TRIGGER))
	{
		TOGGLE_BIT(g_transmitFlag, GAS_TRIGGER);
		if (BIT_IS_SET(g_triggersFlag, GAS_TRIGGER))
		{
			UART_sendByte(GAS_TRIGGERED);
		}
		else
		{
			UART_sendByte(GAS_HANDLED);
		}
	}
	else if (GET_BIT(g_triggersFlag,
			FLOOD_TRIGGER) != GET_BIT(g_transmitFlag, FLOOD_TRIGGER))
	{
		TOGGLE_BIT(g_transmitFlag, FLOOD_TRIGGER);
		if (BIT_IS_SET(g_triggersFlag, FLOOD_TRIGGER))
		{
			UART_sendByte(FLOOD_TRIGGERED);
		}
		else
		{
			UART_sendByte(FLOOD_HANDLED);
		}
	}
	else if (GET_BIT(g_triggersFlag,
			MOTION_TRIGGER) != GET_BIT(g_transmitFlag, MOTION_TRIGGER))
	{
		TOGGLE_BIT(g_transmitFlag, MOTION_TRIGGER);
		if (BIT_IS_SET(g_triggersFlag, MOTION_TRIGGER))
		{
			UART_sendByte(MOTION_TRIGGERED);
		}
		else
		{
			UART_sendByte(MOTION_HANDLED);
		}
	}
	else if (GET_BIT(g_triggersFlag,
			DOOR_TRIGGER) != GET_BIT(g_transmitFlag, DOOR_TRIGGER))
	{
		TOGGLE_BIT(g_transmitFlag, DOOR_TRIGGER);
		if (BIT_IS_SET(g_triggersFlag, DOOR_TRIGGER))
		{
			UART_sendByte(DOOR_TRIGGERED);
		}
		else
		{
			UART_sendByte(DOOR_HANDLED);
		}
	}
}

static void Comm_HandleReceive(uint8 rData)
{
	switch (rData)
	{
	case MOTION_ON:
		SET_BIT(g_settingsFlag, MOTION_ENABLE);
		break;
	case MOTION_OFF:
		CLEAR_BIT(g_settingsFlag, MOTION_ENABLE);
		break;
	case PANIC_ON:
		SET_BIT(g_settingsFlag, PANIC_MODE);
		break;
	case PANIC_OFF:
		CLEAR_BIT(g_settingsFlag, PANIC_MODE);
		break;
	case DISARM_ON:
//		INTERRUPT_disable();
//		SET_BIT(g_settingsFlag, DISARM_MODE);
//		setMode(NORMAL_LOCKED, 3);
		break;
	case DISARM_OFF:
		INTERRUPT_enable();
		CLEAR_BIT(g_settingsFlag, DISARM_MODE);
		break;
	case DOORLOCK_OFF:
		setMode(NORMAL_LOCKED, 3);
		break;
	case DOORLOCK_ON:
		setMode(NORMAL_LOCKED, 1);
		break;
	case FAN_ON:
		SET_BIT(g_settingsFlag, FAN);
		gasHandler();
		break;
	case FAN_OFF:
		CLEAR_BIT(g_settingsFlag, FAN);
		gasHandler();
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

