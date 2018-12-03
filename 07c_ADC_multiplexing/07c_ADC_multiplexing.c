/* Simple example of ADC multiplexing - using multiple "analog inputs" */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include "pin_config.h"


void initADC(void){
  ADCSRA |= (1 << ADPS0) | (1 << ADPS1); // Set ADC clock prescaler to 8
  ADMUX  |= (1 << REFS0);        // Set ADC reference voltage to AVCC pin
  ADCSRA |= (1 << ADEN);         // Enable ADC
}

uint16_t readADC(uint8_t channel){
  ADMUX   = (0xF0 & ADMUX) | channel;  // Set ADC channel (pin) to sample value from
  ADCSRA |= (1 << ADSC);               // Start conversion
  loop_until_bit_is_clear(ADCSRA, ADSC); // Wait for conversion result
  return ADC;                          // Return conversion result
}

int main(void){
  LED_DDR |= (1 << LED);  // Set LED as output
  initADC();

  uint8_t threshold, sensorValue;
  while(1) {
    threshold = readADC(POT_ADC_CHANNEL);
    sensorValue = readADC(LIGHT_SENSOR_ADC_CHANNEL);
    if (sensorValue > threshold)
      LED_PORT |= (1 << LED);   // Turn on the LED
    else
      LED_PORT &= ~(1 << LED);  // Turn off the LED
  }

  return 0;
}