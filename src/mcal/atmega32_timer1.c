/******************************************************************************
 *
 * Module: ATMEGA32 TIMER1
 *
 * File Name: atmega32_timer1.c
 *
 * Description: ATMEGA32 Timer1 Driver Source File
 *
 * Author: Samer Sameh Lawindy
 *
 *******************************************************************************/

#include "atmega32_timer1.h"

#include <avr/interrupt.h>
#include <avr/io.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the addresses of the call back functions in the application */
static volatile void (*g_callBackPtrOVF1)(void) = NULL_PTR;
static volatile TIMER1_CLK g_clock;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtrOVF1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrOVF1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void TIMER1_init(TIMER1_CLK clk)
{
	TCCR1A = 0;
	TCCR1A |= (1 << FOC1A) | (1 << FOC1B);
	g_clock = clk;
	TCNT1 = 0;
}

void TIMER1_on()
{
	TCCR1B &= 0xF8;
	TCCR1B = (g_clock << CS10);
}

void TIMER1_off()
{
	TCCR1B &= 0xF8;
}

uint16 TIMER1_read()
{
	return TCNT1;
}

void TIMER1_write(uint16 time)
{
	TCNT1 = time;
}

void TIMER1_interruptEnable()
{
	TIMSK |= (1<<TOIE1);
}

void TIMER1_setCallback(void(*a_ptr)(void))
{
	g_callBackPtrOVF1 = a_ptr;
}

void TIMER1_interruptDisable()
{
	TIMSK &= ~(1<<TOIE1);
}
