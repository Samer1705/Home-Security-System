/******************************************************************************
 *	Module: WATER SENSOR
 *	File Name: water_sensor.c
 *  Description: Water Sensor Driver Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "water_sensor.h"
#include "../../mcal/atmega32_gpio.h"

void WATER_init()
{
	GPIO_setupPinDirection(WATER_PORTID, WATER_PINID, PIN_INPUT);
}
uint8 WATER_read()
{
	return GPIO_readPin(WATER_PORTID, WATER_PINID);
}
