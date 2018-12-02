#ifndef _25LC256_H_
#define _25LC256_H_ 1

#include <avr/io.h>
#include "SPI.h"

//
// Requires EEPROM_SS_PORT and EEPROM_SS macros to be defined
//

// Selects/deselects EEPROM as slave
#define EEPROM_SLAVE_SELECT    (EEPROM_SS_PORT &= ~(1 << EEPROM_SS))
#define EEPROM_SLAVE_DESELECT  (EEPROM_SS_PORT |=  (1 << EEPROM_SS))

// Instruction Set (from data sheet)
#define EEPROM_READ   0b00000011  // Read memory
#define EEPROM_WRITE  0b00000010  // Write to memory

#define EEPROM_WRDI   0b00000100  // Write disable
#define EEPROM_WREN   0b00000110  // Write enable

#define EEPROM_RDSR   0b00000101  // Read status register
#define EEPROM_WRSR   0b00000001  // Write status register

// EEPROM Status Register Bits (from data sheet)
// Use these to parse status register
#define EEPROM_WRITE_IN_PROGRESS   0
#define EEPROM_WRITE_ENABLE_LATCH  1
#define EEPROM_BLOCK_PROTECT_0     2
#define EEPROM_BLOCK_PROTECT_1     3
#define EEPROM_BYTES_PER_PAGE  64
#define EEPROM_BYTES_MAX       0x7FFF


uint8_t  EEPROM_readStatus(void);               // Reads the EEPROM status register
void     EEPROM_writeEnable(void);              // Helper: Sets EEPROM write enable
void     EEPROM_sendAddress(uint16_t address);  // Splits 16-bit address into 2 bytes, sends both
uint8_t  EEPROM_readByte(uint16_t address);     // Reads a byte from a given memory location
void     EEPROM_writeByte(uint16_t address, uint8_t byte);   // Writes a byte to a given memory location
uint16_t EEPROM_readWord(uint16_t address);                  // Reads two bytes from a given memory location
void     EEPROM_writeWord(uint16_t address, uint16_t word);  // Writes two bytes to a given memory location
void     EEPROM_clearAll(void);                              // Sets every byte in memory to zero

#endif /* _25LC256_H_ */