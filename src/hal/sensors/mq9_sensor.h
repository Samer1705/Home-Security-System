/******************************************************************************
 *	Module: MQ-9 SENSOR
 *	File Name: mq9_sensor.h
 *  Description: MQ-9 Sensor Driver Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_HAL_SENSORS_MQ9_SENSOR_H_
#define SRC_HAL_SENSORS_MQ9_SENSOR_H_

#include "../../common/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MQ9_PORTID 	PORTD_ID
#define MQ9_PINID	PIN3_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void MQ9_init();
uint8 MQ9_read();


#endif /* SRC_HAL_SENSORS_MQ9_SENSOR_H_ */
