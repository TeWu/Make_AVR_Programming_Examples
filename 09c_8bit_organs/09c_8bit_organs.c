/* Example of Timer/Counter Hardware usage - use timer's Output Mode to toggle pin, and generate audiable frequencies directly */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include "pin_config.h"
#include "scale8.h"      // 8-bit scale


static inline void initTimer0(void) {
  TCCR0B |= (1 << CS00) | (1 << CS01);  // Set Timer0 clock prescaler to 64
  TCCR0A |= (1 << WGM01);               // Set Timer0 to CTC Mode
  TCCR0A |= (1 << COM0A0);              // Configure Timer0 to toggle pin OC0A (PD6) each cycle through
}

static inline void playNote(uint8_t period, uint16_t duration) {
  TCNT0 = 0;      // Reset the Timer/Counter0
  OCR0A = period; // Set pitch
  SPEAKER_DDR |= (1 << SPEAKER);  // Turn on the speaker
  while (duration--)  // Variable delay - Note: loops with _delay_xx(1) invocation may lead to inaccurate timing (?)
    _delay_ms(1);
  SPEAKER_DDR &= ~(1 << SPEAKER);  // Turn the speaker off
}

int main(void) {
  initTimer0();

  while (1) {
    playNote(E3, 200);
    _delay_ms(100);
    playNote(E3, 200);
    _delay_ms(200);
    playNote(E3, 200);
    _delay_ms(200);
    playNote(C3, 200);
    playNote(E3, 200);
    _delay_ms(200);
    playNote(G3, 400);
    _delay_ms(500);
    playNote(G2, 400);
    _delay_ms(2500);
  }

  return 0;
}