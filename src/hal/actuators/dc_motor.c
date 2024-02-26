/******************************************************************************
 *	Module: DC MOTOR
 *	File Name: dc_motor.c
 *  Description: DC Motor Driver Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "dc_motor.h"

#include "../../mcal/atmega32_gpio.h"

void DCMOTOR_init(DCMotor* motor)
{
	GPIO_setupPinDirection(motor->portID, motor->pinID, PIN_OUTPUT);
}
void DCMOTOR_on(DCMotor* motor)
{
	GPIO_writePin(motor->portID, motor->pinID, LOGIC_HIGH);
}
void DCMOTOR_off(DCMotor* motor)
{
	GPIO_writePin(motor->portID, motor->pinID, LOGIC_LOW);
}
