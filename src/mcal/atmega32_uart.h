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

typedef enum{
	NO_INT, UDR_INT, TX_INT, TX_UDR_INT, RX_INT, RX_UDR_INT, RX_TX_INT, RX_TX_UDR_INT
}IntEn;

typedef enum{
	UART_5BIT,UART_6BIT,UART_7BIT,UART_8BIT,UART_9BIT=7
}UART_BitData;

typedef enum{
	PARITY_DISABLE,PARITY_ENABLE,PARITY_EVEN,PARITY_ODD
}UART_Parity;
typedef enum{
	UART_1_STOP_BIT,UART_2_STOP_BIT
}UART_StopBit;
typedef uint32 UART_BaudRate;
typedef struct{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;

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
void UART_init(const UART_ConfigType *config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void);

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

void UART_sendData(const uint8 *pData, uint32 uSize);

void UART_receiveData(uint8 *pData, uint32 uSize);

void UART_interruptEnable(IntEn intType);

void UART_setCallBackUDR(void(*a_ptr)(void));

void UART_setCallBackTX(void(*a_ptr)(void));

void UART_setCallBackRX(void(*a_ptr)(void));

#endif /* SRC_MCAL_ATMEGA32_UART_H_ */
