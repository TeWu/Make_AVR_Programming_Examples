#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_ 1

#include <avr/io.h>

#define LED_DDR  DDRB
#define LED_PORT PORTB
#define LED      PB0

#define BUTTON_DDR  DDRB
#define BUTTON_PORT PORTB
#define BUTTON_PIN  PINB
#define BUTTON      PB1

#endif /* _PIN_CONFIG_H_ */