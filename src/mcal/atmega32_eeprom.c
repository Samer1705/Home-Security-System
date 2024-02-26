/******************************************************************************
 *	Module: ATMEGA32 EEPROM
 *	File Name: atmega32_eeprom.c
 *  Description: ATMEGA32 EEPROM Driver Source File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#include "atmega32_eeprom.h"

#include <avr/io.h>

void EEPROM_write(uint16 uiAddress, uint8 ucData)
{
	while(EECR & (1<<EEWE)); 				/* Wait for completion of previous write */

	/* Set up address and data registers */
	EEAR = uiAddress;
	EEDR = ucData;

	EECR |= (1<<EEMWE);						/* Write logical one to EEMWE */
	EECR |= (1<<EEWE);						/* Start eeprom write by setting EEWE */
}

uint8 EEPROM_read(uint16 uiAddress)
{
	while(EECR & (1<<EEWE));				/* Wait for completion of previous write */
	EEAR = uiAddress;						/* Set up address register */
	EECR |= (1<<EERE);						/* Start eeprom read by writing EERE */
	return EEDR;							/* Return data from data register */
}
