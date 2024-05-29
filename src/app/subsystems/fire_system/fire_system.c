/******************************************************************************
 *	Module: Fire System
 *	File Name: fire_system.c
 *  Description: Fire System Module Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "fire_system.h"

#include "../../../common/common_macros.h"
#include "../../../hal/actuators/dc_motor.h"
#include "../../../hal/sensors/flame_sensor.h"
#include "../../../mcal/atmega32_gpio.h"
#include "../../../mcal/atmega32_interrupt.h"
#include "../../communication.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
DCMotor g_waterPump1 =
{ PORTD_ID, PIN4_ID }; /* Fire System Water Pump */

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
static void fireHandler()
{
	if (FLAME_read())
	{
		DCMOTOR_on(&g_waterPump1);
		SET_BIT(g_triggersFlag, FIRE_TRIGGER);
	}
	else
	{
		DCMOTOR_off(&g_waterPump1);
		CLEAR_BIT(g_triggersFlag, FIRE_TRIGGER);
	}
	gasHandler();
}

void FIRE_SYSTEM_Init()
{
	/* Initialize Fire System */
	FLAME_init();
	INTERRUPT_INT0_init(fireHandler, CHANGE);
	DCMOTOR_init(&g_waterPump1);
}
