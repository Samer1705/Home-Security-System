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

#define FIRE_TRIGGERED		0x41
#define FIRE_HANDLED		0x01
#define GAS_TRIGGERED		0x42
#define GAS_HANDLED			0x02
#define FLOOD_TRIGGERED		0x43
#define FLOOD_HANDLED		0x03
#define MOTION_TRIGGERED	0x44
#define MOTION_HANDLED		0x04
#define DOOR_OPENED			0x45
#define DOOR_CLOSED			0x05

#define PANIC_ON 			0x96
#define PANIC_OFF 			0x86
#define DISARM_ON			0x97
#define DISARM_OFF 			0x87
#define DOOR_OPEN			0xE8
#define DOOR_CLOSE			0x88

/*******************************************************************************
 *                                Function Prototypes                          *
 *******************************************************************************/

void Comm_Init();
void Comm_HandleSend(uint8 sData);

#endif /* SRC_APP_COMMUNICATION_H_ */
