/******************************************************************************
 *
 * Module: ATMEGA32 TIMER0
 *
 * File Name: atmega32_timer0.c
 *
 * Description: ATMEGA32 Timer0 Driver Source File
 *
 * Author: Samer Sameh Lawindy
 *
 *******************************************************************************/

#include "atmega32_timer0.h"

#include <avr/interrupt.h>
#include <avr/io.h>



/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the addresses of the call back functions in the application */
static volatile void (*g_callBackPtrOVF0)(void) = NULL_PTR;
static volatile TIMER0_CLK g_clock;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtrOVF0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrOVF0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void TIMER0_init(TIMER0_CLK clk)
{
	TCCR0 = 0;
	TCCR0 |= (1<<FOC0);
	g_clock = clk;
	TCNT0 = 0;
}

void TIMER0_on()
{
	TCCR0 &= 0xF8;
	TCCR0 |= (g_clock<<CS00);
}

void TIMER0_off()
{
	TCCR0 &= 0xF8;
}

uint8 TIMER0_read()
{
	return TCNT0;
}

void TIMER0_write(uint8 time)
{
	TCNT0 = time;
}

void TIMER0_interruptEnable()
{
	TIMSK |= (1<<TOIE0);
}

void TIMER0_setCallback(void(*a_ptr)(void))
{
	g_callBackPtrOVF0 = a_ptr;
}

void TIMER0_interruptDisable()
{
	TIMSK &= ~(1<<TOIE0);
}
