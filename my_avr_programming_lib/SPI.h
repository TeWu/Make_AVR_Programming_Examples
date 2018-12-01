#ifndef _SPI_H_
#define _SPI_H_ 1

#include <avr/io.h>


// Init SPI to run with phase, polarity = 0,0
void SPI_init(uint8_t ssBit,   volatile uint8_t* ssDDR,   volatile uint8_t* ssPort,
              uint8_t mosiBit, volatile uint8_t* mosiDDR,
              uint8_t misoBit, volatile uint8_t* misoDDR, volatile uint8_t* misoPort,
              uint8_t sckBit,  volatile uint8_t* sckDDR);

// Loads up SPI Data Register (SPDR) and waits until bittrading is done
void SPI_tradeByte(uint8_t byte);

#endif /* _SPI_H_ */