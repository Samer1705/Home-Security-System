/******************************************************************************
 *	Module: LED
 *	File Name: led.c
 *  Description:LED Driver Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "led.h"

#include "../../mcal/atmega32_gpio.h"

void LED_init(LED* led)
{
	GPIO_setupPinDirection(led->portID, led->pinID, PIN_OUTPUT);
}
void LED_on(LED* led)
{
	GPIO_writePin(led->portID, led->pinID, LOGIC_HIGH);
}
void LED_off(LED* led)
{
	GPIO_writePin(led->portID, led->pinID, LOGIC_LOW);
}
