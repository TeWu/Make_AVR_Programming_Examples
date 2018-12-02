#include "SPI.h"


void SPI_init(uint8_t isMaster)  {
  if (isMaster) {
    if (is_bit_clear(SPI_DDR, SPI_SS))  // If SS (Slave Select) pin configured as input...
      SPI_PORT |= (1 << SPI_SS);          // ... Enable pull-up resistor on SS pin
    SPI_DDR  |=  (1 << SPI_MOSI);  // Configure MOSI (Master Out Slave In) pin as output
    SPI_DDR  &= ~(1 << SPI_MISO);  // Configure MISO (Master In Slave Out) pin as input
    SPI_PORT |=  (1 << SPI_MISO);  // Enable pull-up resistor on MISO pin
    SPI_DDR  |=  (1 << SPI_SCK);   // Configure SCK (Serial cloCK) pin as output
    SPCR |= (1 << MSTR);           // Set SPI Master mode
  } else {
    SPI_DDR  &= ~(1 << SPI_SS);    // Configure SS (Slave Select) pin as input
    SPI_PORT |=  (1 << SPI_SS);    // Enable pull-up resistor on SS pin
    SPI_DDR  &= ~(1 << SPI_MOSI);  // Configure MOSI (Master Out Slave In) pin as input
    SPI_PORT |=  (1 << SPI_MOSI);  // Enable pull-up resistor on MOSI pin
    SPI_DDR  |=  (1 << SPI_MISO);  // Configure MISO (Master In Slave Out) pin as output
    SPI_DDR  &= ~(1 << SPI_SCK);   // Configure SCK (Serial cloCK) pin as input
    SPI_PORT |=  (1 << SPI_SCK);   // Enable pull-up resistor on SCK pin (to avoid High-Z state when SPI master device is in reset)
    SPCR &= ~(1 << MSTR);          // Set SPI Slave mode
  }

  // SPCR = SPi Control Register
  SPCR |= (1 << SPR1);  // Set SPI clock prescaler to 16 (safer for breadboards)
                        // Not setting clock phase and polarity
  SPCR |= (1 << SPE);   // Enable SPI
}

void SPI_init_slave(volatile uint8_t* slave_SS_DDR, volatile uint8_t* slave_SS_PORT, uint8_t slave_SS_bit) {
  slave_SS_DDR  |= (1 << slave_SS_bit);  // Configure pin connected to slave's SS (Slave Select) pin as output
  slave_SS_PORT |= (1 << slave_SS_bit);  // Start off not selected (high)
}

void SPI_tradeByte(uint8_t byte) {
  // SPDR = SPi Data Register
  SPDR = byte;  // SPI starts sending immediately
  loop_until_bit_is_set(SPSR, SPIF);  // Wait until done
  // SPDR now contains the received byte
}