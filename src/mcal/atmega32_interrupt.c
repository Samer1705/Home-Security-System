 /******************************************************************************
 *
 * Module: ATMEGA32 INTERRUPTS
 *
 * File Name: atmega32_interrupt.c
 *
 * Description: ATMEGA32 Interrupt Driver Source File
 *
 * Author: Samer Sameh Lawindy
 *
 *******************************************************************************/

#include "atmega32_interrupt.h"

#include <avr/common.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "../common/std_types.h"
#include "atmega32_gpio.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the addresses of the call back functions in the application */
static volatile void (*g_callBackPtrInt0)(void) = NULL_PTR;
static volatile void (*g_callBackPtrInt1)(void) = NULL_PTR;
static volatile void (*g_callBackPtrInt2)(void) = NULL_PTR;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/
ISR(INT0_vect)
{
	if(g_callBackPtrInt0 != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtrInt0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}

ISR(INT1_vect)
{
	if(g_callBackPtrInt1 != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtrInt1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}

ISR(INT2_vect)
{
	if(g_callBackPtrInt2 != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtrInt2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void INTERRUPT_enable()
{
	SREG |= (1<<7);					/* Enable Global Interrupts */
}
void INTERRUPT_INT0_init(void(*a_ptr)(void), InterruptSense sense)
{
	GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT);
	GICR |= (1<<INT0);
	MCUCR &= 0xFC;
	MCUCR |= (sense<<ISC00);
	g_callBackPtrInt0 = a_ptr;
}
void INTERRUPT_INT1_init(void(*a_ptr)(void), InterruptSense sense)
{
	GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_INPUT);
	GICR |= (1<<INT1);
	MCUCR &= 0xF3;
	MCUCR |= (sense<<ISC10);
	g_callBackPtrInt1 = a_ptr;
}
void INTERRUPT_INT2_init(void(*a_ptr)(void), InterruptSense sense)
{
	GPIO_setupPinDirection(PORTB_ID, PIN2_ID, PIN_INPUT);
	GICR |= (1<<INT2);
	sense &= ~(1<<1);
	MCUCSR =(MCUCSR & ~(1<<ISC2))|(sense<<ISC2);
	g_callBackPtrInt2 = a_ptr;
}
void INTERRUPT_disable()
{
	SREG &= ~(1<<7);					/* Disable Global Interrupts */
}
