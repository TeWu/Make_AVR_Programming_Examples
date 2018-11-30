#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time

#define DELAYTIME 1500


// Use "int main(void) { ..." instead "int main() { ..." - see https://stackoverflow.com/a/693794/6231376
int main(void) {
  // init
  DDRB |= 0b00000001; // Data Direction Register B: writing a one to the bit enables output.

  // main loop
  while(1) {
    PORTB ^= 0b00000001;  // toggle bit/pin PB0
    _delay_ms(DELAYTIME); // wait
  }

  return 0;
}
