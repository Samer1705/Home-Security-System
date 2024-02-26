/******************************************************************************
 *	Module: MQ-9 SENSOR
 *	File Name: mq9_sensor.c
 *  Description: MQ-9 Sensor Driver Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "mq9_sensor.h"
#include "../../mcal/atmega32_gpio.h"

void MQ9_init()
{
	GPIO_setupPinDirection(MQ9_PORTID, MQ9_PINID, PIN_INPUT);
}
uint8 MQ9_read()
{
	return GPIO_readPin(MQ9_PORTID, MQ9_PINID);
}
