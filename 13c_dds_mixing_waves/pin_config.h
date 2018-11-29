#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_ 1

#include <avr/io.h>

#define SPEAKER_DDR   DDRD
#define SPEAKER_PORT  PORTD
#define SPEAKER_PIN   PIND
#define SPEAKER       PD6    // OC0A

#endif /* _PIN_CONFIG_H_ */