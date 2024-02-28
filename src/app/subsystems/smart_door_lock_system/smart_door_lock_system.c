/******************************************************************************
 *	Module: Smart Door Lock System
 *	File Name: smart_door_lock_system.c
 *  Description: Smart Door Lock System Module Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "smart_door_lock_system.h"

#include <util/delay.h>

#include "../../../common/std_types.h"
#include "../../../hal/actuators/keypad.h"
#include "../../../hal/actuators/lcd.h"
#include "../../../hal/actuators/solenoid_lock.h"
#include "../../../mcal/atmega32_eeprom.h"
#include "../../../mcal/atmega32_gpio.h"
#include "../../../mcal/atmega32_timer2.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
SolenoidLock g_lock = {PORTC_ID, PIN7_ID};		/* Door Lock */
uint16 	g_lcdTimerCount = 0;
uint8 g_givenPin[4] = {0, 0, 0, 0},
		g_actualPin[4],
		g_pinCount = 0,
		g_lcdDelay = 0,
		g_lcdDelayFlag = 0;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
static void LCDDelay(uint8 seconds)
{
	g_lcdDelay = seconds;
	g_lcdDelayFlag = 1;
	TIMER2_on();
}
static void doorLockInit()
{
	LCD_clearScreen();
	LCD_displayString("Enter Pin:");
}
static void lcdDelayHandler()
{
	g_lcdTimerCount++;
	if(g_lcdTimerCount == g_lcdDelay*30)
	{
		TIMER2_off();
		g_lcdDelayFlag = 0;
		g_lcdTimerCount = 0;
		doorLockInit();
	}
}
static void pinCheck()
{
	uint8 i, isValid = 1;
	for(i = 0; i < 4; i++)
	{
		if(g_givenPin[i] != g_actualPin[i]) isValid = 0;
	}
	LCD_clearScreen();
	if(isValid)
	{
		LCD_displayString("ACCESS GRANTED");
		SOLENOID_off(&g_lock);
	}
	else
	{
		LCD_displayString("ACCESS DENIED");
	}
	LCDDelay(2);
	g_pinCount = 0;
}
static void inputKey(uint8 key)
{
	if(key >= 0 && key <= 9)
	{
		LCD_displayCharacter('*');
		g_givenPin[g_pinCount++] = key;
		if(g_pinCount == 4) pinCheck();
	}
	_delay_ms(300);
}
static void pinInit()
{
	uint8 i;
	if(EEPROM_read(0x000))
	{
		for(i = 1; i <= 4; i++)
		{
			g_actualPin[i] = EEPROM_read(i);
		}
	}
}
void SMART_DOOR_LOCK_SYSTEM_Init()
{
	/* Initialize Door Lock System */
	LCD_init();
	KEYPAD_init();
	SOLENOID_init(&g_lock);
	SOLENOID_on(&g_lock);
	pinInit();
	doorLockInit();

	/* Initialize Timer2 */
	TIMER2_init(TMR2_1024);
	TIMER2_setCallback(lcdDelayHandler);
	TIMER2_interruptEnable();
}

void SMART_DOOR_LOCK_SYSTEM_Listener()
{
	if(!g_lcdDelayFlag)
	{
		uint8 key = KEYPAD_getPressedKey();
		if(key != KEYPAD_NO_PRESS) inputKey(key);
	}
}
