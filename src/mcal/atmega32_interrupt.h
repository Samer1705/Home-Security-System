 /******************************************************************************
 *
 * Module: ATMEGA32 INTERRUPTS
 *
 * File Name: atmega32_interrupt.h
 *
 * Description: ATMEGA32 Interrupt Driver Header File
 *
 * Author: Samer Sameh Lawindy
 *
 *******************************************************************************/

#ifndef SRC_MCAL_ATMEGA32_INTERRUPT_H_
#define SRC_MCAL_ATMEGA32_INTERRUPT_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

typedef enum{
	LOW_LEVEL, CHANGE, FALLING, RISING
}InterruptSense;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void INTERRUPT_enable();
void INTERRUPT_INT0_init(void(*a_ptr)(void), InterruptSense sense);
void INTERRUPT_INT1_init(void(*a_ptr)(void), InterruptSense sense);
void INTERRUPT_INT2_init(void(*a_ptr)(void), InterruptSense sense);
void INTERRUPT_disable();


#endif /* SRC_MCAL_ATMEGA32_INTERRUPT_H_ */
