/* Generating sine wave using Direct-digital Synthesis technique */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/power.h>   // Power Reduction Management
#include "dds_waveforms.h"
#include "pin_config.h"


static inline void initTimer0() {
  TCCR0B |= (1 << CS00);                    // Set Timer0 clock prescaler to 1 - For sampled audio, we need all the speed we can get
  TCCR0A |= ((1 << WGM01) | (1 << WGM00));  // Fast PWM mode
  TCCR0A |= (1 << COM0A1);                  // Output PWM signal to pin OC0A (PD6)
}

int main() {
  uint16_t accumulator = 0;
  uint16_t accumulatorStep = 880;  // ~440 Hz
  uint8_t waveIdx;
  int8_t waveValue;

  clock_prescale_set(clock_div_1);  // Set CPU clock to full 8MHz speed
  BUTTON_DDR  &= ~(1 << BUTTON);    // Configure button pin as input
  BUTTON_PORT |= (1 << BUTTON);     // Enable pullup resistor on button pin
  initTimer0();

  while (1) {
    if (bit_is_clear(BUTTON_PIN, BUTTON)) {  // If button is pressed ...
      SPEAKER_DDR |= (1 << SPEAKER);       // Enable output on speaker pin (PD6)
      accumulator += accumulatorStep;      // Advance accumulator
      waveIdx = accumulator >> 8;          // Calculate lookup table entry index (bit-shift-divide by 2^8=256)
      waveValue = DDS_fullSine[waveIdx];   // Lookup voltage

      loop_until_bit_is_set(TIFR0, TOV0);  // Wait for current PWM cycle to finish
      OCR0A = waveValue + 128;             // Set PWM duty cycle = voltage for speaker pin
                                           // Signed-integers need shifting up
      TIFR0 |= (1 << TOV0);                // Reset Timer0 overflow bit
    } else {  // else button is not pressed ...
      SPEAKER_DDR &= ~(1 << SPEAKER);  // Disable output on speaker pin (PD6)
    }
  }

  return 0;
}