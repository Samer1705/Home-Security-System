/******************************************************************************
 *	Module: PIR SENSOR
 *	File Name: pir_sensor.h
 *  Description: PIR Sensor Driver Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_HAL_SENSORS_PIR_SENSOR_H_
#define SRC_HAL_SENSORS_PIR_SENSOR_H_

#include "../../common/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PIR_PORTID 	PORTB_ID
#define PIR_PINID	PIN3_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void PIR_init();
uint8 PIR_read();



#endif /* SRC_HAL_SENSORS_PIR_SENSOR_H_ */
