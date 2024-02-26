/******************************************************************************
 *	Module: BUZZER
 *	File Name: buzzer.h
 *  Description:Buzzer Driver Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_HAL_ACTUATORS_BUZZER_H_
#define SRC_HAL_ACTUATORS_BUZZER_H_

#include "../../common/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef struct{
	uint8 portID;
	uint8 pinID;
}Buzzer;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void BUZZER_init(Buzzer* buzzer);
void BUZZER_on(Buzzer* buzzer);
void BUZZER_off(Buzzer* buzzer);

#endif /* SRC_HAL_ACTUATORS_BUZZER_H_ */
