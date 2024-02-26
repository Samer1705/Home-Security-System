/******************************************************************************
 *	Module: ATMEGA32 EEPROM
 *	File Name: atmega32_eeprom.h
 *  Description: ATMEGA32 EEPROM Driver Header File
 *  Author: Samer Sameh Lawindy
 *******************************************************************************/

#ifndef SRC_MCAL_ATMEGA32_EEPROM_H_
#define SRC_MCAL_ATMEGA32_EEPROM_H_

#include "../common/std_types.h"

void EEPROM_write(uint16 uiAddress, uint8 ucData);
uint8 EEPROM_read(uint16 uiAddress);

#endif /* SRC_MCAL_ATMEGA32_EEPROM_H_ */
