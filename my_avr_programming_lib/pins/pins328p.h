#ifndef _PINS_328P_H_
#define _PINS_328P_H_ 1

///////  USART  ///////
// Port
#define USART_DDR  DDRD
#define USART_PORT PORTD
#define USART_PIN  PIND
// Pins
#define USART_RX PD0  // RXD
#define USART_TX PD1  // TXD


///////  SPI  ///////
// Port
#define SPI_DDR  DDRB
#define SPI_PORT PORTB
#define SPI_PIN  PINB
// Pins
#define SPI_SS   PB2  // ~SS
#define SPI_MOSI PB3  // MOSI
#define SPI_MISO PB4  // MISO
#define SPI_SCK  PB5  // SCK


///////  TWI  ///////
// Port
#define TWI_DDR   DDRC
#define TWI_PORT  PORTC
#define TWI_PIN   PINC
// Pins
#define TWI_SCL   PC5    // SCL
#define TWI_SDA   PC4    // SDA

#endif /* _PINS_328P_H_ */