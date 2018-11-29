#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_ 1

#include <avr/io.h>

#define TWI_SCL_DDR   DDRC
#define TWI_SCL_PORT  PORTC
#define TWI_SCL_PIN   PINC
#define TWI_SCL       PC5    // SCL

#define TWI_SDA_DDR   DDRC
#define TWI_SDA_PORT  PORTC
#define TWI_SDA_PIN   PINC
#define TWI_SDA       PC4    // SDA

/* Not used in code, but usefull information about how to hook up the circut
#define USART_RX PD0  // RXD
#define USART_TX PD1  // TXD
*/

#endif /* _PIN_CONFIG_H_ */