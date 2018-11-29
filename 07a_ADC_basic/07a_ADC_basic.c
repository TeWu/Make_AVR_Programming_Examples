/* Example of basic ADC usage */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include "USART.h"
#include "pin_config.h"

#define SAMPLE_DELAY 50
#define THRESHOLD    512


void initADC() {
  ADCSRA |= (1 << ADPS0) | (1 << ADPS1); // Set ADC clock prescaler to 1/8
  ADMUX  |= (1 << REFS0);        // Set ADC reference voltage to AVCC pin
  ADMUX   = (0xF0 & ADMUX) | 0;  // Set channel 0 as input to ADC (This is the default channel, but doesn't hurt to make sure)
  ADCSRA |= (1 << ADEN);         // Enable ADC
}

uint16_t readADC() {
  ADCSRA |= (1 << ADSC);                    // Set ADc Start Conversion bit
  loop_until_bit_is_clear(ADCSRA, ADSC);    // Wait for convertion to complete
  return ADC;                               // Read convertion result from ADC register
}

int main() {
  LED_DDR = 0xFF;
  USART_init();
  initADC();

  uint16_t value;
  while(1) {
    value = readADC();
    if (value > THRESHOLD) LED_PORT = 0xFF;
    else LED_PORT = 0;
    USART_transmitByte((uint8_t)(value >> 2));  // Convert 10-bit value to 8-bit value by shifting by 2 bits (discarding lowest 2 bits)
    _delay_ms(SAMPLE_DELAY);
  }

  return 0;
}