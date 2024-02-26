/******************************************************************************
 *	Module: Gas System
 *	File Name: gas_system.c
 *  Description: Gas System Module Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "gas_system.h"

#include "../../../hal/actuators/dc_motor.h"
#include "../../../hal/sensors/mq9_sensor.h"
#include "../../../mcal/atmega32_gpio.h"
#include "../../../mcal/atmega32_interrupt.h"
#include "../alarm_system/alarm_system.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
DCMotor g_fan = {PORTB_ID, PIN4_ID};			/* Gas System Fan */
uint8 g_threatFlag;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
void gasHandler()
{
	if(MQ9_read())
	{
		if(!(g_threatFlag & (1<<FIRE_THREAT)))DCMOTOR_on(&g_fan);
		else DCMOTOR_off(&g_fan);
		g_threatFlag |= (1<<GAS_THREAT);
	}
	else
	{
		DCMOTOR_off(&g_fan);
		g_threatFlag &= ~(1<<GAS_THREAT);
	}
}

void GAS_SYSTEM_Init()
{
	/* Initialize Gas System */
	MQ9_init();
	INTERRUPT_INT1_init(gasHandler, CHANGE);
	DCMOTOR_init(&g_fan);
}
