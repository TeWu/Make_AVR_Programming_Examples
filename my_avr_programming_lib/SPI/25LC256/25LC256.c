#include "25LC256.h"


uint8_t EEPROM_readStatus(void) {
  EEPROM_SLAVE_SELECT;
  SPI_tradeByte(EEPROM_RDSR);
  SPI_tradeByte(0);  // Clock out eight bits
  EEPROM_SLAVE_DESELECT;
  return SPDR;       // Return received byte
}

void EEPROM_writeEnable(void) {
  EEPROM_SLAVE_SELECT;
  SPI_tradeByte(EEPROM_WREN);
  EEPROM_SLAVE_DESELECT;
}

void EEPROM_sendAddress(uint16_t address) {
  SPI_tradeByte((uint8_t) (address >> 8));  // High Byte
  SPI_tradeByte((uint8_t) address);         // Low Byte
}

uint8_t EEPROM_readByte(uint16_t address) {
  EEPROM_SLAVE_SELECT;
  SPI_tradeByte(EEPROM_READ);
  EEPROM_sendAddress(address);
  SPI_tradeByte(0);
  EEPROM_SLAVE_DESELECT;
  return SPDR;
}

void EEPROM_writeByte(uint16_t address, uint8_t byte) {
  EEPROM_writeEnable();
  EEPROM_SLAVE_SELECT;
  SPI_tradeByte(EEPROM_WRITE);
  EEPROM_sendAddress(address);
  SPI_tradeByte(byte);
  EEPROM_SLAVE_DESELECT;
  while (EEPROM_readStatus() & (1 << EEPROM_WRITE_IN_PROGRESS)) { }  //TODO: Change to?: while (is_bit_set(EEPROM_readStatus(), EEPROM_WRITE_IN_PROGRESS)) { }
}

uint16_t EEPROM_readWord(uint16_t address) {
  uint16_t word;
  EEPROM_SLAVE_SELECT;
  SPI_tradeByte(EEPROM_READ);
  EEPROM_sendAddress(address);
  SPI_tradeByte(0);
  word = SPDR;
  word = (word << 8);  // High Byte
  SPI_tradeByte(0);
  word += SPDR;        // Low Byte
  EEPROM_SLAVE_DESELECT;
  return word;
}

void EEPROM_writeWord(uint16_t address, uint16_t word) {
  EEPROM_writeEnable();
  EEPROM_SLAVE_SELECT;
  SPI_tradeByte(EEPROM_WRITE);
  EEPROM_sendAddress(address);
  SPI_tradeByte((uint8_t) (word >> 8));
  SPI_tradeByte((uint8_t) word);
  EEPROM_SLAVE_DESELECT;
  while (EEPROM_readStatus() & (1 << EEPROM_WRITE_IN_PROGRESS)) { }  //TODO: Change to?: while (is_bit_set(EEPROM_readStatus(), EEPROM_WRITE_IN_PROGRESS)) { }
}

void EEPROM_clearAll(void) {
  uint8_t i;
  uint16_t pageAddress = 0;
  while (pageAddress < EEPROM_BYTES_MAX) {
    EEPROM_writeEnable();
    EEPROM_SLAVE_SELECT;
    SPI_tradeByte(EEPROM_WRITE);
    EEPROM_sendAddress(pageAddress);
    for (i = 0; i < EEPROM_BYTES_PER_PAGE; i++)
      SPI_tradeByte(0);
    EEPROM_SLAVE_DESELECT;
    pageAddress += EEPROM_BYTES_PER_PAGE;
    while (EEPROM_readStatus() & (1 << EEPROM_WRITE_IN_PROGRESS)) { }  //TODO: Change to?: while (is_bit_set(EEPROM_readStatus(), EEPROM_WRITE_IN_PROGRESS)) { }
  }
}