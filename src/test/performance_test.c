 /******************************************************************************
 *
 * Module: Performance Test
 *
 * File Name: performance_test.c
 *
 * Description: Performance Test Source File
 *
 * Author: Samer Sameh Lawindy
 *
 *******************************************************************************/

#include "../mcal/atmega32_timer1.h"
#include "../hal/actuators/lcd.h"

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void PERFORMANCE_Init()
{
	LCD_init();
	TIMER1_init(TMR1_1);
}
void PERFORMANCE_Start()
{
	TIMER1_on();
}
void PERFORMANCE_Stop()
{
	TIMER1_off();
}
void PERFORMANCE_Measure()
{
	uint16 timer =  TIMER1_read();
	float32 performance = timer / 1.6;
	LCD_clearScreen();
	LCD_floatToString(performance);
	TIMER1_write(0);
}
