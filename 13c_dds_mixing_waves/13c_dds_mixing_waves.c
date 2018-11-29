/* Generating and mixing many (phase-shifted) saw waves using Direct-digital Synthesis technique */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/power.h>   // Power Reduction Management
#include "dds_waveforms.h"
#include "pin_config.h"

#define BASEPITCH  220  // Base pitch in tuningWord steps, which are ~1/2 Hz
#define PHASE_RATE 7    // Controls speed of phasing effect
/* 2 and 4 work just fine.
   8 and 16 take too long to maintain our 31.25kHz sample rate, so the pitch shifts
   downwards and there's all sorts of aliasing. If you're just after scary sounds,
   8 and 16 are awesome, but you may want to increase the BASEPITCH to compensate.
*/
#define OSCILLATORS_COUNT 4
/* This is the number of bits to shift when volume mixing.
   2**OSCILLATOR_SHIFT = OSCILLATORS_COUNT
   If you don't change this to match the number of oscillators, you'll get clipping
   and digital distortion.
*/
#define OSCILLATOR_SHIFT 2


static inline void initTimer0() {
  TCCR0B |= (1 << CS00);                    // Set Timer0 clock prescaler to 1 - For sampled audio, we need all the speed we can get
  TCCR0A |= ((1 << WGM01) | (1 << WGM00));  // Fast PWM mode
  TCCR0A |= (1 << COM0A1);                  // Output PWM signal to pin OC0A (PD6)
}

int main() {
  uint16_t accumulators[OSCILLATORS_COUNT];
  uint8_t waveStep;
  int16_t mixer = 0;
  uint8_t i;

  clock_prescale_set(clock_div_1);  // Set CPU clock to full 8MHz speed
  SPEAKER_DDR |= (1 << SPEAKER);    // Enable output on speaker pin (PD6)
  initTimer0();

  for (i = 0; i < OSCILLATORS_COUNT; i++)  // Init all to same phase
    accumulators[i] = 0;

  while (1) {
    // Update all accumulators and mix together
    mixer = 0;
    for (i = 0; i < OSCILLATORS_COUNT; i++) {
      accumulators[i] += BASEPITCH;     // Advance accumulator
      waveStep = accumulators[i] >> 8;  // Calculate lookup table entry index (bit-shift-divide by 2^8=256)
      // Add extra phase increment.
      // Makes shifting overtones when different frequency components add/subtract
      if (waveStep == 0)                    // Roughly once per cycle ...
        accumulators[i] += PHASE_RATE * i;  // ... add extra phase
      mixer += DDS_fullSaw[waveStep];
    }
    mixer = mixer >> OSCILLATOR_SHIFT;  // Reduce volume so that signal is roughly in 0-255 range. Dividing by bit-shift is very fast.

    loop_until_bit_is_set(TIFR0, TOV0);  // Wait for current PWM cycle to finish
    TIFR0 |= (1 << TOV0);                // Reset Timer0 overflow bit
    OCR0A = 128 + mixer;                 // Set PWM duty cycle = voltage for speaker pin
  }

  return 0;
}