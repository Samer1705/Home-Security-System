/******************************************************************************
 *	Module: LED
 *	File Name: led.h
 *  Description:LED Driver Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_HAL_ACTUATORS_LED_H_
#define SRC_HAL_ACTUATORS_LED_H_

#include "../../common/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef struct{
	uint8 portID;
	uint8 pinID;
}LED;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void LED_init(LED* led);
void LED_on(LED* led);
void LED_off(LED* led);

#endif /* SRC_HAL_ACTUATORS_LED_H_ */
