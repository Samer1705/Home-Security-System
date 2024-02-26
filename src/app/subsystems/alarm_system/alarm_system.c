/******************************************************************************
 *	Module: Alarm System
 *	File Name: alarm_system.c
 *  Description:Alarm System Module Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "../../../hal/actuators/buzzer.h"
#include "../../../hal/actuators/led.h"
#include "../../../mcal/atmega32_timer0.h"
#include "../../../mcal/atmega32_gpio.h"
#include "alarm_system.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
Buzzer 	g_alarmBuzzer = {PORTB_ID, PIN0_ID};		/* Alarm Buzzer */
LED		g_alarmLED = {PORTB_ID, PIN1_ID};		/* Alarm LED */
uint8 	g_alarmTimerCount = 0;
extern uint8 g_threatFlag = 0;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
static void alarmHandler()
{
	if(g_alarmTimerCount == 10)
	{
		LED_on(&g_alarmLED);
		BUZZER_on(&g_alarmBuzzer);
	}
	else if(g_alarmTimerCount == 20)
	{
		LED_off(&g_alarmLED);
		BUZZER_off(&g_alarmBuzzer);
		g_alarmTimerCount = 0;
	}
	g_alarmTimerCount++;
}
static void alarmOn()
{
	TIMER0_on();
}

static void alarmOff()
{
	TIMER0_off();
	LED_off(&g_alarmLED);
	BUZZER_off(&g_alarmBuzzer);
	g_alarmTimerCount = 0;
}

void ALARM_SYSTEM_Init()
{
	/* Initialize Timer0 */
	TIMER0_init(TMR0_1024);
	TIMER0_setCallback(alarmHandler);
	TIMER0_interruptEnable();

	/* Initialize Alarm System */
	BUZZER_init(&g_alarmBuzzer);
	LED_init(&g_alarmLED);
}

void ALARM_SYSTEM_Listener()
{
	if(g_threatFlag) alarmOn();
	else alarmOff();
}
