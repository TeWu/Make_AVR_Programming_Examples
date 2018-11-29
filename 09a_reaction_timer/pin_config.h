#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_ 1

#include <avr/io.h>

#define LED_DDR  DDRB
#define LED_PORT PORTB
#define LED      PB0

#define BUTTON_DDR  DDRD
#define BUTTON_PORT PORTD
#define BUTTON_PIN  PIND
#define BUTTON      PD2

/* Not used in code, but usefull information about how to hook up the circut
#define USART_RX PD0  // RXD
#define USART_TX PD1  // TXD
*/

#endif /* _PIN_CONFIG_H_ */