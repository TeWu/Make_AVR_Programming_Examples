#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_ 1

#include <avr/io.h>

#define SPEAKER_DDR   DDRD
#define SPEAKER_PORT  PORTD
#define SPEAKER_PIN   PIND
#define SPEAKER       PD6    // OC0A

/* Not used in code, but usefull information about how to hook up the circut
#define USART_RX PD0  // RXD
#define USART_TX PD1  // TXD
*/

#endif /* _PIN_CONFIG_H_ */