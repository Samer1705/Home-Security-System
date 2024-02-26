/******************************************************************************
 *	Module: FLAME SENSOR
 *	File Name: flame_sensor.h
 *  Description: Flame Sensor Driver Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_HAL_SENSORS_FLAME_SENSOR_H_
#define SRC_HAL_SENSORS_FLAME_SENSOR_H_

#include "../../common/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define FLAME_PORTID 	PORTD_ID
#define FLAME_PINID		PIN2_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void FLAME_init();
uint8 FLAME_read();

#endif /* SRC_HAL_SENSORS_FLAME_SENSOR_H_ */
