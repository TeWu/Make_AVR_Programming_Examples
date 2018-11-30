/* Example of ADC in free-running mode */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include "USART.h"
#include "pin_config.h"

#define SAMPLE_DELAY 20


void initFreeRunningADC(void) {
  ADCSRA |= (1 << ADPS0) | (1 << ADPS1); // Set ADC clock prescaler to 1/8
  ADMUX  |= (1 << REFS0);        // Set ADC reference voltage to AVCC pin
  ADMUX  |= (1 << ADLAR);        // Left Adjust Result - see page 142
  ADMUX   = (0xF0 & ADMUX) | 0;  // Set channel 0 as input to ADC (This is the default channel, but doesn't hurt to make sure)
  ADCSRA |= (1 << ADATE);        // ADC Auto-Trigger Enable - Use ADC in free-running mode
  ADCSRA |= (1 << ADEN);         // Enable ADC
  ADCSRA |= (1 << ADSC);         // Start first conversion - subsequent conversion is triggered by completion of previous conversion (a.k.a free-running mode)
}

int main(void) {
  USART_init();
  initFreeRunningADC();

  while(1) {
    USART_transmitByte(ADCH);
    _delay_ms(SAMPLE_DELAY);
  }

  return 0;
}