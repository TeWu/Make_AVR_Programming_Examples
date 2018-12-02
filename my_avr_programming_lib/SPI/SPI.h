#ifndef _SPI_H_
#define _SPI_H_ 1

#include <avr/io.h>
#include "pins.h"

#define SPI_SLAVE_MODE  0
#define SPI_MASTER_MODE 1


// Init SPI to run with phase, polarity = 0,0
void SPI_init(uint8_t isMaster);

// Configures pin connected to slave's SS (Slave Select) pin
void SPI_init_slave(volatile uint8_t* slave_SS_DDR, volatile uint8_t* slave_SS_PORT, uint8_t slave_SS_bit);

// Loads up SPI Data Register (SPDR) and waits until bittrading is done
void SPI_tradeByte(uint8_t byte);

#endif /* _SPI_H_ */