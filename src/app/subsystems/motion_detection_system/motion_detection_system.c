/******************************************************************************
 *	Module: Motion Detection System
 *	File Name: motion_detection_system.c
 *  Description: Motion Detection System Module Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "motion_detection_system.h"

#include "../../../hal/sensors/pir_sensor.h"
#include "../../communication.h"
#include "../../../common/common_macros.h"

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
static void motionHandler()
{
	if (PIR_read())
	{
		SET_BIT(g_triggersFlag, MOTION_TRIGGER);
	}
	else
	{
		CLEAR_BIT(g_triggersFlag, MOTION_TRIGGER);
	}
}

void MOTION_DETECTION_SYSTEM_Init()
{
	/* Initialize Motion Detection System */
	PIR_init();
}

void MOTION_DETECTION_SYSTEM_Listener()
{
	if (BIT_IS_SET(g_settingsFlag, MOTION_ENABLE))
	{
		motionHandler();
	}
}
