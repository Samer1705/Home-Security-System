/******************************************************************************
 *
 * Module: ATMEGA32 TIMER2
 *
 * File Name: atmega32_timer2.c
 *
 * Description: ATMEGA32 Timer2 Driver Source File
 *
 * Author: Samer Sameh Lawindy
 *
 *******************************************************************************/

#include "atmega32_timer2.h"

#include <avr/interrupt.h>
#include <avr/io.h>



/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the addresses of the call back functions in the application */
static volatile void (*g_callBackPtrOVF2)(void) = NULL_PTR;
static volatile TIMER2_CLK g_clock;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtrOVF2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrOVF2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void TIMER2_init(TIMER2_CLK clk)
{
	TCCR2 = 0;
	TCCR2 |= (1<<FOC2);
	g_clock = clk;
	TCNT2 = 0;
}

void TIMER2_on()
{
	TCCR2 &= 0xF8;
	TCCR2 |= (g_clock<<CS20);
}

void TIMER2_off()
{
	TCCR2 &= 0xF8;
}

uint8 TIMER2_read()
{
	return TCNT2;
}

void TIMER2_write(uint8 time)
{
	TCNT2 = time;
}

void TIMER2_interruptEnable()
{
	TIMSK |= (1<<TOIE2);
}

void TIMER2_setCallback(void(*a_ptr)(void))
{
	g_callBackPtrOVF2 = a_ptr;
}

void TIMER2_interruptDisable()
{
	TIMSK &= ~(1<<TOIE2);
}
