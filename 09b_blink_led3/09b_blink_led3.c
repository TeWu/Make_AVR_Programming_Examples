#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include "pin_config.h"

#define DELAY_TIME          2000
#define BLINK_DELAY_TIME    300
#define TIMER1_TICKS_PER_MS (F_CPU / 8000)


static inline void initTimer1(void) {
  TCCR1B |= (1 << CS11);   // Set Timer1 clock prescaler to 8
  // CPU clock speed: 1 MHz     => 1000 ticks per ms
  // Timer1 clock prescaler: 8  => 125  ticks per ms
  TCCR1B |= (1 << WGM12);   // Set Timer1 to CTC Mode (Clear Timer on Compare Match mode)
  TCCR1A |= (1 << COM1A0);  // Configure Timer1 Compare Output Mode (COM1) to toggle pin OC1A (PB1) on Compare Match
  OCR1A   = BLINK_DELAY_TIME * TIMER1_TICKS_PER_MS;  // Set Timer1 Output Compare Register (OCR1) to number of ticks to wait before toggling LED on pin PD6
                                                     // Also be carefull to not exceed OCR1A max value of 2^16 = 65536
}

int main(void) {
  initTimer1();

  while(1) {
    LED_DDR ^= (1 << LED);  // Toggle LED blinking by toggling LED pin between input and output mode
    _delay_ms(DELAY_TIME);   // Wait
  }

  return 0;
}