/******************************************************************************
 *	Module: PIR SENSOR
 *	File Name: pir_sensor.c
 *  Description: PIR Sensor Driver Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "pir_sensor.h"
#include "../../mcal/atmega32_gpio.h"

void PIR_init()
{
	GPIO_setupPinDirection(PIR_PORTID, PIR_PINID, PIN_INPUT);
}
uint8 PIR_read()
{
	return GPIO_readPin(PIR_PORTID, PIR_PINID);
}
