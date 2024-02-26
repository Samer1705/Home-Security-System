/******************************************************************************
 *	Module: DC MOTOR
 *	File Name: dc_motor.h
 *  Description: DC Motor Driver Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_HAL_ACTUATORS_DC_MOTOR_H_
#define SRC_HAL_ACTUATORS_DC_MOTOR_H_

#include "../../common/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef struct{
	uint8 portID;
	uint8 pinID;
}DCMotor;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void DCMOTOR_init(DCMotor* motor);
void DCMOTOR_on(DCMotor* motor);
void DCMOTOR_off(DCMotor* motor);


#endif /* SRC_HAL_ACTUATORS_DC_MOTOR_H_ */
