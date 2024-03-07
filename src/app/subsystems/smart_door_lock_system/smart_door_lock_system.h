/******************************************************************************
 *	Module: Smart Door Lock System
 *	File Name: smart_door_lock_system.h
 *  Description: Smart Door Lock System Module Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_APP_SUBSYSTEMS_SMART_DOOR_LOCK_SYSTEM_SMART_DOOR_LOCK_SYSTEM_H_
#define SRC_APP_SUBSYSTEMS_SMART_DOOR_LOCK_SYSTEM_SMART_DOOR_LOCK_SYSTEM_H_

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum{
	NORMAL, OLD, NEW
}PinMode;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void SMART_DOOR_LOCK_SYSTEM_Init();
void SMART_DOOR_LOCK_SYSTEM_Listener();

#endif /* SRC_APP_SUBSYSTEMS_SMART_DOOR_LOCK_SYSTEM_SMART_DOOR_LOCK_SYSTEM_H_ */
