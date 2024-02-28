 /******************************************************************************
 *
 * Module: ATMEGA32 UART
 *
 * File Name: atmega32_uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Samer Sameh Lawindy
 *
 *******************************************************************************/

#ifndef SRC_MCAL_ATMEGA32_UART_H_
#define SRC_MCAL_ATMEGA32_UART_H_

#include "../common/std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(uint32 baud_rate);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #


#endif /* SRC_MCAL_ATMEGA32_UART_H_ */