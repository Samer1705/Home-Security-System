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
uint8 g_enteredPin[4],
		g_correctPin[4] = {0, 0, 0, 0},
		g_pinCount = 0,
		g_lcdDelay = 0,
		g_lcdDelayFlag = 0;
PinMode g_mode = NORMAL;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

static void setLCD()
{
	g_pinCount = 0;
	LCD_clearScreen();
	switch(g_mode)
	{
	case OLD:
		LCD_displayString("Enter Old Pin:");
		break;
	case NEW:
		LCD_displayString("Enter New Pin:");
		break;
	case NORMAL:
	default:
		LCD_displayString("Enter Pin:");
		break;
	}
	LCD_moveCursor(1, 0);
}

static void setLcdDelay(uint8 seconds)
{
	g_lcdDelay = seconds;
	g_lcdDelayFlag = 1;
	TIMER2_on();
}

static void lcdDelayHandler()
{
	g_lcdTimerCount++;
	if(g_lcdTimerCount == g_lcdDelay*30)
	{
		TIMER2_off();
		g_lcdDelayFlag = 0;
		g_lcdTimerCount = 0;
		setLCD();
	}
}

static void setPin()
{
	uint8 i;
	EEPROM_write(0x000, 1);
	for(i = 0; i < 4; i++)
	{
		EEPROM_write(i+1, g_enteredPin[i]);
		g_correctPin[i] = g_enteredPin[i];
	}
	g_pinCount = 0;
	g_mode = NORMAL;
	setLCD();
}

static void getPin()
{
	uint8 pinChanged = EEPROM_read(0x000);
	if(pinChanged == 1)
	{
		uint8 i;
		for(i = 1; i <= 4; i++)
		{
			g_correctPin[i-1] = EEPROM_read(i);
		}
	}
}

static void checkPin()
{
	uint8 i, isValid = 1;
	for(i = 0; i < 4; i++)
	{
		if(g_enteredPin[i] != g_correctPin[i]) isValid = 0;
	}
	LCD_clearScreen();
	if(isValid)
	{
		if(g_mode == OLD)
		{
			g_mode = NEW;
			setLCD();
		}
		else
		{
			LCD_displayString("ACCESS GRANTED");
			SOLENOID_off(&g_lock);
		}
	}
	else
	{
		if(g_mode == OLD)
		{
			LCD_displayString("INCORRECT PIN");
		}
		else
		{
			LCD_displayString("ACCESS DENIED");
		}
	}
	setLcdDelay(2);
	g_pinCount = 0;
}

static void inputKey(uint8 key)
{
	if(key >= 0 && key <= 9)
	{
		//		LCD_displayCharacter('*');
		LCD_intgerToString(key);
		g_enteredPin[g_pinCount++] = key;
		if(g_pinCount == 4)
		{
			switch (g_mode)
			{
			case NEW:
				setPin();
				break;
			default:
				checkPin();
				break;
			}
		}
	}
	else if(key == '#')
	{
		switch(g_mode)
		{
		case NORMAL:
			g_mode = OLD;
			setLCD();
			break;
		default:
			g_mode = NORMAL;
			setLCD();
			break;
		}
	}
	else if (key == '*')
	{
		LCD_clearScreen();
		LCD_displayString("DOOR LOCKED");
		SOLENOID_on(&g_lock);
		g_mode = NORMAL;
		setLcdDelay(2);
	}
	_delay_ms(300);
}

void SMART_DOOR_LOCK_SYSTEM_Init()
{
	/* Initialize Door Lock System */
	LCD_init();
	KEYPAD_init();
	SOLENOID_init(&g_lock);
	SOLENOID_on(&g_lock);
	getPin();
	setLCD();

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
