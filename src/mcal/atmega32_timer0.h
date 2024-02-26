 /******************************************************************************
 *
 * Module: ATMEGA32 TIMER0
 *
 * File Name: atmega32_timer0.h
 *
 * Description: ATMEGA32 Timer0 Driver Header File
 *
 * Author: Samer Sameh Lawindy
 *
 *******************************************************************************/

#ifndef SRC_MCAL_ATMEGA32_TIMER0_H_
#define SRC_MCAL_ATMEGA32_TIMER0_H_

#include "../common/std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	TMR0_OFF, TMR0_1, TMR0_8, TMR0_64, TMR0_256, TMR0_1024, TMR0_EXTERNAL_FALLING, TMR0_EXTERNAL_RAISING
}TIMER0_CLK;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void TIMER0_init(TIMER0_CLK clk);
void TIMER0_on();
void TIMER0_off();
uint8 TIMER0_read();
void TIMER0_write(uint8 time);
void TIMER0_interruptEnable();
void TIMER0_setCallback(void(*a_ptr)(void));
void TIMER0_interruptDisable();



#endif /* SRC_MCAL_ATMEGA32_TIMER0_H_ */
