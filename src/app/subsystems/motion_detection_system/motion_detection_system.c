/******************************************************************************
 *	Module: Motion Detection System
 *	File Name: motion_detection_system.c
 *  Description: Motion Detection System Module Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "motion_detection_system.h"

#include "../../../hal/sensors/pir_sensor.h"
#include "../../../test/performance_test.h"
#include "../alarm_system/alarm_system.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
boolean g_motionEnable = TRUE;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
static void motionHandler()
{
	if (PIR_read())
	{
		g_threatFlag |= (1 << MOTION_THREAT);
	}
	else
	{
		g_threatFlag &= ~(1 << MOTION_THREAT);
	}
}

void MOTION_DETECTION_SYSTEM_Init()
{
	/* Initialize Motion Detection System */
	PIR_init();
}

void MOTION_DETECTION_SYSTEM_Listener()
{
	if (g_motionEnable)
	{
		motionHandler();
	}
}
