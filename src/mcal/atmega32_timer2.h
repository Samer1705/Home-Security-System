 /******************************************************************************
 *
 * Module: ATMEGA32 TIMER2
 *
 * File Name: atmega32_timer2.h
 *
 * Description: ATMEGA32 Timer2 Driver Header File
 *
 * Author: Samer Sameh Lawindy
 *
 *******************************************************************************/

#ifndef SRC_MCAL_ATMEGA32_TIMER2_H_
#define SRC_MCAL_ATMEGA32_TIMER2_H_

#include "../common/std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	TMR2_OFF, TMR2_1, TMR2_8, TMR2_32, TMR2_64, TMR2_128, TMR2_256, TMR2_1024
}TIMER2_CLK;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void TIMER2_init(TIMER2_CLK clk);
void TIMER2_on();
void TIMER2_off();
uint8 TIMER2_read();
void TIMER2_write(uint8 time);
void TIMER2_interruptEnable();
void TIMER2_setCallback(void(*a_ptr)(void));
void TIMER2_interruptDisable();


#endif /* SRC_MCAL_ATMEGA32_TIMER2_H_ */
