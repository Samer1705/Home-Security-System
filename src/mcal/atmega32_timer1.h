 /******************************************************************************
 *
 * Module: ATMEGA32 TIMER1
 *
 * File Name: atmega32_timer1.h
 *
 * Description: ATMEGA32 Timer1 Driver Header File
 *
 * Author: Samer Sameh Lawindy
 *
 *******************************************************************************/

#ifndef SRC_MCAL_ATMEGA32_TIMER1_H_
#define SRC_MCAL_ATMEGA32_TIMER1_H_

#include "../common/std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	TMR1_OFF, TMR1_1, TMR1_8, TMR1_64, TMR1_256, TMR1_1024, TMR1_EXTERNAL_FALLING, TMR1_EXTERNAL_RAISING
}TIMER1_CLK;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void TIMER1_init(TIMER1_CLK clk);
void TIMER1_on();
void TIMER1_off();
uint16 TIMER1_read();
void TIMER1_write(uint16 time);
void TIMER1_interruptEnable();
void TIMER1_setCallback(void(*a_ptr)(void));
void TIMER1_interruptDisable();

#endif /* SRC_MCAL_ATMEGA32_TIMER1_H_ */
