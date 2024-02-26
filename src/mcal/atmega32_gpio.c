/******************************************************************************
 *	Module: ATMEGA32 GPIO
 *	File Name: atmega32_gpio.c
 *  Description: ATMEGA32 GPIO Driver Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "atmega32_gpio.h"

#include <avr/io.h>

#include "../common/common_macros.h"

/*
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
	if((pin_num < NUM_OF_PINS_PER_PORT) && (port_num < NUM_OF_PORTS))
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == PIN_OUTPUT) SET_BIT(DDRA,pin_num);
			else CLEAR_BIT(DDRA,pin_num);
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT) SET_BIT(DDRB,pin_num);
			else CLEAR_BIT(DDRB,pin_num);
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT) SET_BIT(DDRC,pin_num);
			else CLEAR_BIT(DDRC,pin_num);
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT) SET_BIT(DDRD,pin_num);
			else CLEAR_BIT(DDRD,pin_num);
			break;
		}
	}
}

/*
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	if((pin_num < NUM_OF_PINS_PER_PORT) && (port_num < NUM_OF_PORTS))
	{
		/* Set up the pin value as required */
		switch (port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_LOW) CLEAR_BIT(PORTA, pin_num);
			else if(value == LOGIC_HIGH) SET_BIT(PORTA, pin_num);
			break;
		case PORTB_ID:
			if(value == LOGIC_LOW) CLEAR_BIT(PORTB, pin_num);
			else if(value == LOGIC_HIGH) SET_BIT(PORTB, pin_num);
			break;
		case PORTC_ID:
			if(value == LOGIC_LOW) CLEAR_BIT(PORTC, pin_num);
			else if(value == LOGIC_HIGH) SET_BIT(PORTC, pin_num);
			break;
		case PORTD_ID:
			if(value == LOGIC_LOW) CLEAR_BIT(PORTD, pin_num);
			else if(value == LOGIC_HIGH) SET_BIT(PORTD, pin_num);
			break;
		}
	}
}

/*
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	if((pin_num < NUM_OF_PINS_PER_PORT) && (port_num < NUM_OF_PORTS))
	{
		/* Return the value of the desired pin as required */
		switch (port_num)
		{
		case PORTA_ID:
			return (BIT_IS_SET(PINA, pin_num)? LOGIC_HIGH : LOGIC_LOW);
			break;
		case PORTB_ID:
			return (BIT_IS_SET(PINB, pin_num)? LOGIC_HIGH : LOGIC_LOW);
			break;
		case PORTC_ID:
			return (BIT_IS_SET(PINC, pin_num)? LOGIC_HIGH : LOGIC_LOW);
			break;
		case PORTD_ID:
			return (BIT_IS_SET(PIND, pin_num)? LOGIC_HIGH : LOGIC_LOW);
			break;
		}
	}
	return LOGIC_LOW;
}

/*
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	if(port_num < NUM_OF_PORTS)
	{
		/* Setup the port direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

/*
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	if(port_num < NUM_OF_PORTS)
	{
		/* Setup the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

/*
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	if(port_num < NUM_OF_PORTS)
	{
		/* Return the value of the desired port as required */
		switch(port_num)
		{
		case PORTA_ID:
			return PINA;
			break;
		case PORTB_ID:
			return PINB;
			break;
		case PORTC_ID:
			return PINC;
			break;
		case PORTD_ID:
			return PIND;
			break;
		}
	}
	return LOGIC_LOW;
}
