#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time

#define DELAYTIME 1500

int main() {
  // init
  DDRB |= 0b00000001; // Data Direction Register B: writing a one to the bit enables output.

  // main loop
  while(1) {
    PORTB ^= 0b00000001;  // toggle bit/pin PB0
    _delay_ms(DELAYTIME); // wait
  }

  return 0;
}
