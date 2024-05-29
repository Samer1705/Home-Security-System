/******************************************************************************
 *	Module: Smart Door Lock System
 *	File Name: smart_door_lock_system.c
 *  Description: Smart Door Lock System Module Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "smart_door_lock_system.h"

#include <util/delay.h>

#include "../../../hal/actuators/keypad.h"
#include "../../../hal/actuators/lcd.h"
#include "../../../hal/actuators/solenoid_lock.h"
#include "../../../mcal/atmega32_eeprom.h"
#include "../../../mcal/atmega32_gpio.h"
#include "../../../mcal/atmega32_timer2.h"
#include "../../communication.h"
#include "../../../common/common_macros.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
SolenoidLock g_lock =
{ PORTC_ID, PIN7_ID }; /* Door Lock */
uint16 g_lcdTimerCount = 0;
uint8 g_enteredPin[4], g_correctPin[4] =
{ 0, 0, 0, 0 }, g_pinCount = 0, g_lcdDelay = 0, g_doorOpened = 0;
PinMode g_mode = NORMAL_LOCKED;
boolean g_lcdDelayFlag = FALSE, g_isdoorLocked = TRUE;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

static void lockDoor()
{
	SOLENOID_on(&g_lock);
	SET_BIT(g_triggersFlag, DOOR_TRIGGER);
}

static void unlockDoor()
{
	SOLENOID_off(&g_lock);
	CLEAR_BIT(g_triggersFlag, DOOR_TRIGGER);
}

static void setLcdDelay(uint8 seconds)
{
	g_lcdDelay = seconds;
	g_lcdDelayFlag = TRUE;
	TIMER2_on();
}

void setMode(PinMode mode, uint8 quickMsg)
{
	g_mode = mode;
	LCD_clearScreen();
	switch (mode)
	{
	case NORMAL_LOCKED:
		switch (quickMsg)
		{
		case 1:
			LCD_displayString("Door Locked");
			lockDoor();
			setLcdDelay(2);
			break;
		case 2:
			LCD_displayString("Access Denied");
			setLcdDelay(2);
			break;
		case 3:
			LCD_displayString("Access Granted");
			g_mode = NORMAL_UNLOCKED;
			setLcdDelay(2);
			break;
		case 0:
		default:
			LCD_displayString("Enter Pin: ");
			break;
		}
		break;
	case NORMAL_UNLOCKED:
		unlockDoor();
		LCD_displayString("Door Unlocked");
		break;
	case CHANGE_OLD:
		switch (quickMsg)
		{
		case 1:
			LCD_displayString("Incorrect Pin");
			break;
		case 2:
			LCD_displayString("Correct Pin");
			g_mode = CHANGE_NEW;
			setLcdDelay(2);
			break;
		case 0:
		default:
			LCD_displayString("Enter Old Pin: ");
			break;
		}
		break;
	case CHANGE_NEW:
		if (quickMsg)
		{
			LCD_displayString("Pin Changed");
			if (SOLENOID_read(&g_lock) == 1)
			{
				g_mode = NORMAL_LOCKED;
			}
			else
			{
				g_mode = NORMAL_UNLOCKED;
			}
			setLcdDelay(2);
		}
		else
		{
			LCD_displayString("Enter New Pin: ");
		}
		break;
	default:
		break;
	}
	LCD_moveCursor(1, 0);
	g_pinCount = 0;
}

static void lcdDelayHandler()
{
	g_lcdTimerCount++;
	if (g_lcdTimerCount == g_lcdDelay * 30)
	{
		TIMER2_off();
		g_lcdDelayFlag = FALSE;
		g_lcdTimerCount = 0;
		setMode(g_mode, 0);
	}
}

static void setPin()
{
	uint8 i;
	EEPROM_write(0x000, 1);
	for (i = 0; i < 4; i++)
	{
		EEPROM_write(i + 1, g_enteredPin[i]);
		g_correctPin[i] = g_enteredPin[i];
	}
	g_pinCount = 0;
	setMode(CHANGE_NEW, 1);
}

static void getPin()
{
	uint8 pinChanged = EEPROM_read(0x000);
	if (pinChanged == 1)
	{
		uint8 i;
		for (i = 1; i <= 4; i++)
		{
			g_correctPin[i - 1] = EEPROM_read(i);
		}
	}
}

static void checkPin()
{
	uint8 i;
	boolean isValid = TRUE;
	for (i = 0; i < 4; i++)
	{
		if (g_enteredPin[i] != g_correctPin[i])
			isValid = FALSE;
	}
	LCD_clearScreen();
	if (isValid == TRUE)
	{
		if (g_mode == CHANGE_OLD)
		{
			setMode(CHANGE_OLD, 2);
		}
		else
		{
			setMode(NORMAL_LOCKED, 3);
		}
	}
	else
	{
		if (g_mode == CHANGE_OLD)
		{
			setMode(CHANGE_OLD, 1);
		}
		else
		{
			setMode(NORMAL_LOCKED, 2);
		}
	}
	setLcdDelay(2);
	g_pinCount = 0;
}

static void inputKey(uint8 key)
{
	if (key >= 0 && key <= 9 && g_mode != NORMAL_UNLOCKED)
	{
		//		LCD_displayCharacter('*');
		LCD_intgerToString(key);
		g_enteredPin[g_pinCount++] = key;
		if (g_pinCount == 4)
		{
			if (g_mode == CHANGE_NEW)
			{
				setPin();
			}
			else
			{
				checkPin();
			}
		}
	}
	else if (key == '#')
	{
		if (g_mode == NORMAL_LOCKED || g_mode == NORMAL_UNLOCKED)
		{
			setMode(CHANGE_OLD, 0);
		}
		else
		{
			if (SOLENOID_read(&g_lock) == 1)
			{
				setMode(NORMAL_LOCKED, 0);
			}
			else
			{
				setMode(NORMAL_UNLOCKED, 0);
			}
		}
	}
	else if (key == '*')
	{
		if (SOLENOID_read(&g_lock) == 0)
		{
			setMode(NORMAL_LOCKED, 1);
		}
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
	setMode(NORMAL_LOCKED, 0);

	/* Initialize Timer2 */
	TIMER2_init(TMR2_1024);
	TIMER2_setCallback(lcdDelayHandler);
	TIMER2_interruptEnable();
}

void SMART_DOOR_LOCK_SYSTEM_Listener()
{
	if (g_lcdDelayFlag == FALSE)
	{
		uint8 key = KEYPAD_getPressedKey();
		if (key != KEYPAD_NO_PRESS)
			inputKey(key);
	}
}
