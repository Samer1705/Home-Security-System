/******************************************************************************
 *	Module: WATER SENSOR
 *	File Name: water_sensor.h
 *  Description: Water Sensor Driver Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_HAL_SENSORS_WATER_SENSOR_H_
#define SRC_HAL_SENSORS_WATER_SENSOR_H_

#include "../../common/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define WATER_PORTID 	PORTB_ID
#define WATER_PINID		PIN2_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void WATER_init();
uint8 WATER_read();

#endif /* SRC_HAL_SENSORS_WATER_SENSOR_H_ */
