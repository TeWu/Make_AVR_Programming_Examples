/* Example of Timer/Counter Hardware usage - use timer's Output Mode to toggle pin, and generate audiable frequencies directly */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include "pin_config.h"
#include "scale8.h"      // 8-bit scale


static inline void initTimer0() {
  TCCR0B |= (1 << CS00) | (1 << CS01);  // Set Timer0 clock prescaler to 64
  TCCR0A |= (1 << WGM01);               // Set Timer0 to CTC Mode
  TCCR0A |= (1 << COM0A0);              // Configure Timer0 to toggle pin OC0A (PD6) each cycle through
}

static inline void playNote(uint8_t period, uint16_t duration) {
  TCNT0 = 0;      // Reset the Timer/Counter0
  OCR0A = period; // Set pitch
  SPEAKER_DDR |= (1 << SPEAKER);  // Turn on the speaker
  while (duration) {  // Variable delay
    _delay_ms(1);
    duration--;
  }
  SPEAKER_DDR &= ~(1 << SPEAKER);  // Turn the speaker off
}

int main() {
  initTimer0();

  while (1) {
    playNote(C2, 200);
    playNote(E2, 300);
    playNote(G2, 200);
    playNote(C3, 500);
    _delay_ms(1000);  // TODO: delay 3 times?? Why? Is it really needed?
    _delay_ms(1000);
    _delay_ms(1000);
  }

  return 0;
}