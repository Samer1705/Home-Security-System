/*
 ============================================================================
 Name        : main.c
 Author      : Samer Sameh Lawindy
 ============================================================================
 */

#include "../hal/actuators/led.h"
#include "../mcal/atmega32_gpio.h"
#include "../mcal/atmega32_interrupt.h"
#include "../mcal/atmega32_uart.h"
#include "subsystems/alarm_system/alarm_system.h"
#include "subsystems/fire_system/fire_system.h"
#include "subsystems/gas_system/gas_system.h"
#include "subsystems/motion_detection_system/motion_detection_system.h"
#include "subsystems/smart_door_lock_system/smart_door_lock_system.h"
#include "subsystems/water_flood_system/water_flood_system.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
LED	g_testLED = {PORTD_ID, PIN7_ID};		/* Testing LED */

/*******************************************************************************
 *                          Main Functions                              	   *
 *******************************************************************************/
int main(void)
{
	/* Configure & Initialize UART */
	UART_ConfigType uartConfig = {
		UART_9BIT,
		PARITY_ENABLE,
		UART_1_STOP_BIT,
		9600
	};
	UART_init(&uartConfig);

	/* Initialize Sub Systems */
	ALARM_SYSTEM_Init();
	FIRE_SYSTEM_Init();
	GAS_SYSTEM_Init();
	WATER_FLOOD_SYSTEM_Init();
	MOTION_DETECTION_SYSTEM_Init();
	SMART_DOOR_LOCK_SYSTEM_Init();

	/* Enable Global Interrupt */
	INTERRUPT_enable();

	/* Testing LED */
	LED_init(&g_testLED);

	while(1)
	{
		SMART_DOOR_LOCK_SYSTEM_Listener();
		MOTION_DETECTION_SYSTEM_Listener();
		ALARM_SYSTEM_Listener();
	}
}
