#include "SPI.h"


void SPI_init(uint8_t ssBit,   volatile uint8_t* ssDDR,   volatile uint8_t* ssPort,
              uint8_t mosiBit, volatile uint8_t* mosiDDR,
              uint8_t misoBit, volatile uint8_t* misoDDR, volatile uint8_t* misoPort,
              uint8_t sckBit,  volatile uint8_t* sckDDR)  {
  // SS pin configuration
  *ssDDR  |= (1 << ssBit);  // Configure SS pin as output
  *ssPort |= (1 << ssBit);  // Start off not selected (high)
  // MOSI pin configuration
  *mosiDDR |= (1 << mosiBit);  // Configure MOSI pin as output
  // MISO pin configuration
  *misoDDR  &= ~(1 << misoBit);  // Configure MISO pin as input
  *misoPort |=  (1 << misoBit);  // Enable pull-up resistor on MISO pin
  // SCK pin configuration
  *sckDDR |= (1 << sckBit);  // Configure SCK pin as output

  // AVR's hardware SPI peripheral configuration
  // SPCR = SPi Control Register
  SPCR |= (1 << SPR1);  // Set SPI clock prescaler to 16 (safer for breadboards)
                        // Not setting clock phase and polarity
  SPCR |= (1 << MSTR);  // Set SPI Master mode
  SPCR |= (1 << SPE);   // Enable SPI
}

void SPI_tradeByte(uint8_t byte) {
  // SPDR = SPi Data Register
  SPDR = byte;  // SPI starts sending immediately
  loop_until_bit_is_set(SPSR, SPIF);  // Wait until done
  // SPDR now contains the received byte
}