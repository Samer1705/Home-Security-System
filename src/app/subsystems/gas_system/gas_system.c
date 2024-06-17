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
#include "../../communication.h"
#include "../../../common/common_macros.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
DCMotor g_fan =
{ PORTB_ID, PIN4_ID }; /* Gas System Fan */

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
void gasHandler()
{
	if (MQ9_read())
	{
		if (BIT_IS_CLEAR(g_triggersFlag, FIRE_TRIGGER))
			DCMOTOR_on(&g_fan);
		else
			DCMOTOR_off(&g_fan);
		SET_BIT(g_triggersFlag, GAS_TRIGGER);
	}
	else
	{
		if (BIT_IS_CLEAR(g_settingsFlag, FAN))
			DCMOTOR_off(&g_fan);
		else
			DCMOTOR_on(&g_fan);
		CLEAR_BIT(g_triggersFlag, GAS_TRIGGER);
	}
}

void GAS_SYSTEM_Init()
{
	/* Initialize Gas System */
	MQ9_init();
	INTERRUPT_INT1_init(gasHandler, CHANGE);
	DCMOTOR_init(&g_fan);
}
