/*
 * communication.h
 *
 *  Created on: Mar 12, 2024
 *      Author: samer
 */

#ifndef SRC_APP_COMMUNICATION_H_
#define SRC_APP_COMMUNICATION_H_

#include "../common/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define FIRE_TRIGGERED 1
#define FIRE_HANDLED 2
#define GAS_TRIGGERED 3
#define GAS_HANDLED 4
#define FLOOD_TRIGGERED 5
#define FLOOD_HANDLED 6
#define MOTION_TRIGGERED 7
#define MOTION_HANDLED 8
#define DOOR_OPENED 9
#define DOOR_CLOSED 10

#define MOTION_ON 11
#define MOTION_OFF 12
#define PANIC_ON 13
#define PANIC_OFF 14
#define DISARM_ON 15
#define DISARM_OFF 16
#define DOOR_OPEN 17
#define DOOR_CLOSE 18

/*******************************************************************************
 *                                Function Prototypes                          *
 *******************************************************************************/

void Comm_Init();

#endif /* SRC_APP_COMMUNICATION_H_ */
