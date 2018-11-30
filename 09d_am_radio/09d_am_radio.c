/* Example of Timer/Counter Hardware advanced usage */
/* Plays a simple tune, broadcasts it in the AM radio band */
/*      We have the Timer 0 count up to a value that determines its frequency, and then clear
        the counter and start over at zero. Every time it resets, it will toggle a pin.
        Only this time, it’s toggling the pin at roughly 1 MHz and emitting radio waves rather
        than audio. This is the carrier frequency.
        To modulate the carrier, we’re going to use another timer, Timer 1. Timer 1 is also
        run in CTC mode to generate variable frequencies. Only instead of toggling a pin
        directly, it calls an interrupt service routine every time it resets. Inside the ISR, we
        simply turn on and off the carrier signal to modulate it, generating the audio on
        top.
        All that’s left to do is set the pitch in Timer 1’s OCR1A, and let it run for a given
        amount of time to sound the note.
*/
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/interrupt.h>  // "ISR" macro, and more
#include <avr/power.h>   // Power Reduction Management
#include "pin_config.h"
#include "scale16.h"      // 16-bit scale

// From f = F_CPU / ( 2 * N * (1 + OCRnx) )
// Good values for the AM band from 2 to 6: pick one that's clear
// Divide by two because we're toggling on or off each loop;
//  a full cycle of the carrier takes two loops.
// 8Mhz / (2 * 1 * (1+2)) = 1333 kHz
// 8Mhz / (2 * 1 * (1+3)) = 1000 kHz
// 8Mhz / (2 * 1 * (1+4)) = 800 kHz
// 8Mhz / (2 * 1 * (1+5)) = 670 kHz
// 8Mhz / (2 * 1 * (1+6)) = 570 kHz
// 8Mhz / (2 * 1 * (1+7)) = 500 kHz
#define COUNTER_VALUE 3  // determines carrier frequency


static inline void initTimer0(void) {
  TCCR0A |= (1 << WGM01);   // Set Timer0 to CTC mode
  TCCR0A |= (1 << COM0B0);  // Set Timer0 Compare Output Mode to toggle OC0A (PD6) pin each time through
  TCCR0B |= (1 << CS00);    // Set Timer0 clock prescaler to 1 = Timer0 clock at CPU frequency, ~8MHz
  OCR0A = COUNTER_VALUE;    // Set Timer0 Output Compare Register to achieve oscillation (toggling) at carrier frequency
}

static inline void initTimer1(void) {
  TCCR1B |= (1 << WGM12);   // Set Timer1 to CTC mode
  TCCR1B |= (1 << CS11);    // Set Timer1 clock prescaler to 8
                            //   F_CPU / 8 = ~1MHz
  TIMSK1 |= (1 << OCIE1A);  // OCIE = Output Compare Interrupt Enable
}

ISR(TIMER1_COMPA_vect) {  // Interrupt Service Routine for audio-rate Timer 1
  ANTENNA_DDR ^= (1 << ANTENNA);  // Toggle carrier on and off
}

static inline void transmitBeep(uint16_t pitch, uint16_t duration) {
  OCR1A = pitch;    // Set pitch for Timer1
  sei();            // Enable global interrupt flag
  do {
    _delay_ms(1);   // Delay for pitch cycles
    duration--;
  } while (duration > 0);
  cli();            // Disable global interrupt flag = Disables ISR, so that it stops toggling
  ANTENNA_DDR |= (1 << ANTENNA);  // Turn on full carrier
}

int main(void) {
  clock_prescale_set(clock_div_1);  // Set CPU clock to full 8MHz speed
  initTimer0();
  initTimer1();

  while(1) {
    transmitBeep(E3, 200);
    _delay_ms(100);
    transmitBeep(E3, 200);
    _delay_ms(200);
    transmitBeep(E3, 200);
    _delay_ms(200);
    transmitBeep(C3, 200);
    transmitBeep(E3, 200);
    _delay_ms(200);
    transmitBeep(G3, 400);
    _delay_ms(500);
    transmitBeep(G2, 400);
    _delay_ms(2500);
  }

  return 0;
}