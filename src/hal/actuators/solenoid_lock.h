/******************************************************************************
 *	Module: SOLENOID LOCK
 *	File Name: solenoid_lock.h
 *  Description: Solenoid Lock Driver Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_HAL_ACTUATORS_SOLENOID_LOCK_H_
#define SRC_HAL_ACTUATORS_SOLENOID_LOCK_H_

#include "../../common/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef struct{
	uint8 portID;
	uint8 pinID;
}SolenoidLock;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void SOLENOID_init(SolenoidLock* lock);
void SOLENOID_on(SolenoidLock* lock);
void SOLENOID_off(SolenoidLock* lock);

#endif /* SRC_HAL_ACTUATORS_SOLENOID_LOCK_H_ */
