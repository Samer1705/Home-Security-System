/******************************************************************************
 *	Module: Water Flood System
 *	File Name: water_flood_system.c
 *  Description: Water Flood System Module Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "water_flood_system.h"

#include "../../../hal/actuators/dc_motor.h"
#include "../../../hal/sensors/water_sensor.h"
#include "../../../mcal/atmega32_gpio.h"
#include "../../../mcal/atmega32_interrupt.h"
#include "../alarm_system/alarm_system.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
DCMotor g_waterPump2 = {PORTD_ID, PIN5_ID};		/* Flood System Water Pump */

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
void floodHandler()
{
	if(WATER_read())
	{
		DCMOTOR_on(&g_waterPump2);
		g_threatFlag |= (1<<FLOOD_THREAT);
		INTERRUPT_INT2_init(floodHandler, FALLING);
	}
	else
	{
		DCMOTOR_off(&g_waterPump2);
		g_threatFlag &= ~(1<<FLOOD_THREAT);
		INTERRUPT_INT2_init(floodHandler, RISING);
	}
}

void WATER_FLOOD_SYSTEM_Init()
{
	/* Initialize Water Flood System */
	WATER_init();
	INTERRUPT_INT2_init(floodHandler, RISING);
	DCMOTOR_init(&g_waterPump2);
}
