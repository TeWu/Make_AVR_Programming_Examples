#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_ 1

#include <avr/io.h>

#define SPI_SLAVE_DDR   DDRB
#define SPI_SLAVE_PORT  PORTB
#define SPI_SLAVE       PB1

/* Not used in code, but usefull information about how to hook up the circut
#define SPI_SS   PB2  // ~SS
#define SPI_MOSI PB3  // MOSI
#define SPI_MISO PB4  // MISO
#define SPI_SCK  PB5  // SCK

#define USART_RX PD0  // RXD
#define USART_TX PD1  // TXD
*/

#endif /* _PIN_CONFIG_H_ */