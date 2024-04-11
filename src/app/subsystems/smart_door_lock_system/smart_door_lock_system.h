/******************************************************************************
 *	Module: Smart Door Lock System
 *	File Name: smart_door_lock_system.h
 *  Description: Smart Door Lock System Module Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_APP_SUBSYSTEMS_SMART_DOOR_LOCK_SYSTEM_SMART_DOOR_LOCK_SYSTEM_H_
#define SRC_APP_SUBSYSTEMS_SMART_DOOR_LOCK_SYSTEM_SMART_DOOR_LOCK_SYSTEM_H_

#include "../../../common/std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum{
	NORMAL_LOCKED, NORMAL_UNLOCKED, CHANGE_OLD, CHANGE_NEW
}PinMode;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void setMode(PinMode mode, uint8 quickMsg);
void SMART_DOOR_LOCK_SYSTEM_Init();
void SMART_DOOR_LOCK_SYSTEM_Listener();


#endif /* SRC_APP_SUBSYSTEMS_SMART_DOOR_LOCK_SYSTEM_SMART_DOOR_LOCK_SYSTEM_H_ */
