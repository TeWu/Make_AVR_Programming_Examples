/* Generating sine wave using Direct-digital Synthesis technique */
/* Using interrupts to free main loop for other usefull work */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/interrupt.h>  // "ISR" macro, and more
#include <avr/power.h>   // Power Reduction Management
#include "dds_waveforms.h"
#include "pin_config.h"


uint16_t accumulator = 0;
uint16_t accumulatorStep = 880;  // ~440 Hz

static inline void initTimer0() {
  TCCR0B |= (1 << CS00);                    // Set Timer0 clock prescaler to 1 - For sampled audio, we need all the speed we can get
  TCCR0A |= ((1 << WGM01) | (1 << WGM00));  // Fast PWM mode
  TCCR0A |= (1 << COM0A1);                  // Output PWM signal to pin OC0A (PD6)
}

ISR(TIMER0_OVF_vect) {  // Run every time Timer0 overflows
  accumulator += accumulatorStep;                // Advance accumulator
  OCR0A = DDS_fullSine[accumulator >> 8] + 128;  // Set PWM duty cycle = voltage for speaker pin
}

int main() {
  clock_prescale_set(clock_div_1);  // Set CPU clock to full 8MHz speed
  BUTTON_DDR  &= ~(1 << BUTTON);    // Configure button pin as input
  BUTTON_PORT |= (1 << BUTTON);     // Enable pullup resistor on button pin
  initTimer0();
  sei();                            // Enable interrupts

  while (1) {
    if (bit_is_clear(BUTTON_PIN, BUTTON)) {  // If button is pressed ...
      SPEAKER_DDR |= (1 << SPEAKER);   // Enable output on speaker pin (PD6)
      TIMSK0 |= (1 << TOIE0);          // Enable Timer0 overflow interrupt
    } else {  // else button is not pressed ...
      SPEAKER_DDR &= ~(1 << SPEAKER);  // Disable output on speaker pin (PD6)
      TIMSK0 &= ~(1 << TOIE0);         // Disable Timer0 overflow interrupt
    }
    // Main loop is not waiting on PWM cycle to finish so you can do other usefull work here
  }

  return 0;
}