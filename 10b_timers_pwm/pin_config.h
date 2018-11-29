#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_ 1

#include <avr/io.h>

#define LEDS_DDR  DDRB
#define LED1      PB1   // OC1A
#define LED2      PB2   // OC1B
#define LED3      PB3   // OC2A

/* Not used in code, but usefull information about how to hook up the circut
#define USART_RX PD0  // RXD
#define USART_TX PD1  // TXD
*/

#endif /* _PIN_CONFIG_H_ */