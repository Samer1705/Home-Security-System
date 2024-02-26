/******************************************************************************
 *	Module: BUZZER
 *	File Name: buzzer.c
 *  Description:Buzzer Driver Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "buzzer.h"

#include "../../mcal/atmega32_gpio.h"

void BUZZER_init(Buzzer* buzzer)
{
	GPIO_setupPinDirection(buzzer->portID, buzzer->pinID, PIN_OUTPUT);
}
void BUZZER_on(Buzzer* buzzer)
{
	GPIO_writePin(buzzer->portID, buzzer->pinID, LOGIC_HIGH);
}
void BUZZER_off(Buzzer* buzzer)
{
	GPIO_writePin(buzzer->portID, buzzer->pinID, LOGIC_LOW);
}
