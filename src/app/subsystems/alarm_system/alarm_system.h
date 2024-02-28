/******************************************************************************
 *	Module: Alarm System
 *	File Name: alarm_system.h
 *  Description:Alarm System Module Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_APP_SUBSYSTEMS_ALARM_SYSTEM_ALARM_SYSTEM_H_
#define SRC_APP_SUBSYSTEMS_ALARM_SYSTEM_ALARM_SYSTEM_H_

#include "../../../common/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Threat Flag Bits */
typedef enum{
	FIRE_THREAT, GAS_THREAT, FLOOD_THREAT, MOTION_THREAT, PANIC_MODE
}THREATS;

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
extern uint8 g_threatFlag;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void ALARM_SYSTEM_Init();
void ALARM_SYSTEM_Listener();


#endif /* SRC_APP_SUBSYSTEMS_ALARM_SYSTEM_ALARM_SYSTEM_H_ */
