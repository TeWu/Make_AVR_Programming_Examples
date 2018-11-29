#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_ 1

#include <avr/io.h>

#define LED_DDR  DDRB
#define LED_PORT PORTB
#define LED      PB0

#define POT_ADC_CHANNEL          0
#define LIGHT_SENSOR_ADC_CHANNEL 1

#define POT PC0           // ADC0     // <--- Not used in code, but usefull information about how to hook up the circut
#define LIGHT_SENSOR PC1  // ADC1     // <--- Not used in code, but usefull information about how to hook up the circut

#endif /* _PIN_CONFIG_H_ */