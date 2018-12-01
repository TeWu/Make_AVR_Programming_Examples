#ifndef _SPI_H_
#define _SPI_H_ 1

#include <avr/io.h>

//
// SPI_init requires following macros to be defined:
//   SPI_SS_DDR,   SPI_SS_PORT,   SPI_SS,
//   SPI_MOSI_DDR, SPI_MOSI_PORT, SPI_MOSI,
//   SPI_MISO_DDR, SPI_MISO_PORT, SPI_MISO,
//   SPI_SCK_DDR,  SPI_SCK_PORT,  SPI_SCK
//

#define SPI_SLAVE_MODE  0
#define SPI_MASTER_MODE 1


// Init SPI to run with phase, polarity = 0,0
void SPI_init(uint8_t isMaster);

// Configures pin connected to slave's SS (Slave Select) pin
void SPI_init_slave(volatile uint8_t* slave_SS_DDR, volatile uint8_t* slave_SS_PORT, uint8_t slave_SS_bit);

// Loads up SPI Data Register (SPDR) and waits until bittrading is done
void SPI_tradeByte(uint8_t byte);

#endif /* _SPI_H_ */