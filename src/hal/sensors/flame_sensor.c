/******************************************************************************
 *	Module: FLAME SENSOR
 *	File Name: flame_sensor.c
 *  Description: Flame Sensor Driver Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "flame_sensor.h"
#include "../../mcal/atmega32_gpio.h"

void FLAME_init()
{
	GPIO_setupPinDirection(FLAME_PORTID, FLAME_PINID, PIN_INPUT);
}
uint8 FLAME_read()
{
	return GPIO_readPin(FLAME_PORTID, FLAME_PINID);
}
