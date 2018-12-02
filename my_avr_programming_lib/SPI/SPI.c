#include "SPI.h"


void SPI_init(uint8_t isMaster, uint8_t clockRateSelector, uint8_t lsbFirst, uint8_t mode)  {
  uint8_t clockRate = (clockRateSelector >> 1);
  uint8_t dblClock = (clockRateSelector & 1);

  // Configure SPI pins
  if (isMaster) {
    if (bit_is_clear(SPI_DDR, SPI_SS))  // If SS (Slave Select) pin configured as input...
      SPI_PORT |= (1 << SPI_SS);          // ... Enable pull-up resistor on SS pin
    SPI_DDR  |=  (1 << SPI_MOSI);  // Configure MOSI (Master Out Slave In) pin as output
    SPI_DDR  &= ~(1 << SPI_MISO);  // Configure MISO (Master In Slave Out) pin as input
    SPI_PORT |=  (1 << SPI_MISO);  // Enable pull-up resistor on MISO pin
    SPI_DDR  |=  (1 << SPI_SCK);   // Configure SCK (Serial cloCK) pin as output
  } else {
    SPI_DDR  &= ~(1 << SPI_SS);    // Configure SS (Slave Select) pin as input
    SPI_PORT |=  (1 << SPI_SS);    // Enable pull-up resistor on SS pin
    SPI_DDR  &= ~(1 << SPI_MOSI);  // Configure MOSI (Master Out Slave In) pin as input
    SPI_PORT |=  (1 << SPI_MOSI);  // Enable pull-up resistor on MOSI pin
    SPI_DDR  |=  (1 << SPI_MISO);  // Configure MISO (Master In Slave Out) pin as output
    SPI_DDR  &= ~(1 << SPI_SCK);   // Configure SCK (Serial cloCK) pin as input
    SPI_PORT |=  (1 << SPI_SCK);   // Enable pull-up resistor on SCK pin (to avoid High-Z state when SPI master device is in reset)
  }

  // Configure SPI hardware peripheral
  // SPSR = SPI Status Register, SPCR = SPi Control Register
  SPSR = ((dblClock & __SPI_DBLCLOCK_MASK) << SPI2X);  // Set Double SPI Speed Bit if requested
  SPCR |= (
            ((isMaster & __SPI_MASTER_MASK) << MSTR) |      // Set SPI Master/Slave mode
            ((clockRate & __SPI_CLOCKRATE_MASK) << SPR0) |  // Set SCK frequency
            ((lsbFirst & __SPI_LSBFIRST_MASK) << DORD) |    // Set LSB/MSB data ordering
            ((mode & __SPI_MODE_MASK) << CPHA) |            // Set data mode - clock phase (CPHA) and polarity (CPOL)
            (1 << SPE)                                      // Enable SPI
          );
}

void SPI_init_slave(volatile uint8_t* slave_SS_DDR, volatile uint8_t* slave_SS_PORT, uint8_t slave_SS_bit) {
  *slave_SS_DDR  |= (1 << slave_SS_bit);  // Configure pin connected to slave's SS (Slave Select) pin as output
  *slave_SS_PORT |= (1 << slave_SS_bit);  // Start off not selected (high)
}

void SPI_tradeByte(uint8_t byte) {
  // SPDR = SPi Data Register
  SPDR = byte;  // SPI starts sending immediately
  loop_until_bit_is_set(SPSR, SPIF);  // Wait until done
  // SPDR now contains the received byte
}