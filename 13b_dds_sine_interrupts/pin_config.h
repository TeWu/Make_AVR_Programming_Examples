#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_ 1

#include <avr/io.h>

#define BUTTON_DDR  DDRD
#define BUTTON_PORT PORTD
#define BUTTON_PIN  PIND
#define BUTTON      PD2

#define SPEAKER_DDR   DDRD
#define SPEAKER_PORT  PORTD
#define SPEAKER_PIN   PIND
#define SPEAKER       PD6    // OC0A

#endif /* _PIN_CONFIG_H_ */