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

#define FIRE_TRIGGERED 0x01
#define FIRE_HANDLED 0x02
#define GAS_TRIGGERED 0x03
#define GAS_HANDLED 0x04
#define FLOOD_TRIGGERED 0x05
#define FLOOD_HANDLED 0x06
#define MOTION_TRIGGERED 0x07
#define MOTION_HANDLED 0x08
#define DOOR_TRIGGERED 0x09
#define DOOR_HANDLED 0x0A

#define MOTION_ON 0x0B
#define MOTION_OFF 0x0C
#define PANIC_ON 0x0D
#define PANIC_OFF 0x0E
#define DISARM_ON 0x0F
#define DISARM_OFF 0x10
#define DOORLOCK_ON 0x11
#define DOORLOCK_OFF 0x12
#define FAN_ON 0x13
#define FAN_OFF 0x14

/* Threat Flag Bits */
typedef enum{
	FIRE_TRIGGER, GAS_TRIGGER, FLOOD_TRIGGER, MOTION_TRIGGER, DOOR_TRIGGER
}TRIGGERS;

typedef enum{
	MOTION_ENABLE, PANIC_MODE, DISARM_MODE, FAN
}SETTINGS;

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
extern uint8 g_triggersFlag, g_settingsFlag;

/*******************************************************************************
 *                                Function Prototypes                          *
 *******************************************************************************/

void Comm_Init();

#endif /* SRC_APP_COMMUNICATION_H_ */
