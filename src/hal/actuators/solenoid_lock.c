/******************************************************************************
 *	Module: SOLENOID LOCK
 *	File Name: solenoid_lock.c
 *  Description: Solenoid Lock Driver Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "solenoid_lock.h"

#include "../../mcal/atmega32_gpio.h"

void SOLENOID_init(SolenoidLock* lock)
{
	GPIO_setupPinDirection(lock->portID, lock->pinID, PIN_OUTPUT);
}
void SOLENOID_on(SolenoidLock* lock)
{
	GPIO_writePin(lock->portID, lock->pinID, LOGIC_HIGH);
}
void SOLENOID_off(SolenoidLock* lock)
{
	GPIO_writePin(lock->portID, lock->pinID, LOGIC_LOW);
}
