/* Direct-digital Synthesis technique and ADSR dynamic volume envelope Example */
/* Simple piano - play over USART sending a, s, d, f, g, h, j, k, l, ; and ' chars */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/power.h>   // Power Reduction Management
#include "USART.h"
#include "dds_waveforms.h"
#include "dds_scale.h"
#include "pin_config.h"

#define VOLUME_BITDEPTH 5   // 5-bit volume
#define FULL_VOLUME     31  // 5-bit volume max value

// ADSR envelope values
#define ATTACK_RATE    8	    // 0-255
#define DECAY_RATE     120	  // 0-255
#define SUSTAIN_LEVEL  25	    // 0-255
#define SUSTAIN_TIME   4000   // 0-65535
#define RELEASE_RATE   200	  // 0-65535
// Compute these constants
#define ATTACK_TIME   (ATTACK_RATE * FULL_VOLUME)
#define DECAY_TIME    (ATTACK_TIME + (FULL_VOLUME-SUSTAIN_LEVEL) * DECAY_RATE)
#define RELEASE_TIME  (DECAY_TIME + SUSTAIN_TIME)


static inline uint16_t lookupPitch(char c) {
  switch(c) {
    case 'a': return G1;
    case 's': return A1;
    case 'd': return B1;
    case 'f': return C2;
    case 'g': return D2;
    case 'h': return E2;
    case 'j': return F2;
    case 'k': return G2;
    case 'l': return A2;
    case ';': return B2;
    case '\'': return C3;
  }
  return C1; // Default value - if pressed some other key
}

static inline void initTimer0() {
  TCCR0B |= (1 << CS00);                    // Set Timer0 clock prescaler to 1 - For sampled audio, we need all the speed we can get
  TCCR0A |= ((1 << WGM01) | (1 << WGM00));  // Fast PWM mode
  TCCR0A |= (1 << COM0A1);                  // Output PWM signal to pin OC0A (PD6)
}

int main() {
  uint8_t  volume = 0;
  uint16_t accumulator = 0;
  uint16_t accumulatorStep = C1;
  uint16_t noteClock = 0;
  int16_t  mixer = 0;
  uint8_t  waveStep;
  char     serialInput;

  clock_prescale_set(clock_div_1);  // Set CPU clock to full 8MHz speed
  SPEAKER_DDR |= (1 << SPEAKER);    // Enable output on speaker pin (PD6)
  initTimer0();
  USART_init();

  USART_printString("\r\n  Serial Synth\r\n");
  USART_printString("Notes: asdfghjkl;'\r\n");

  while (1) {
    // Dynamic volume calculations
    if (noteClock) {  // If note clock already running
      noteClock++;
      // ATTACK
      if (noteClock < ATTACK_TIME &&            // If in ATTACK part of the ADSR envelope, and
          noteClock > ATTACK_RATE * volume  &&  // if time to increase volume, and
          volume < 31)                          // if not already at max volume
        volume++;
      // DECAY
      else if (noteClock < DECAY_TIME &&  // If in DECAY part of the ADSR envelope, and
               noteClock - ATTACK_TIME > (FULL_VOLUME - volume) * DECAY_RATE  &&  // if time to decrease volume, and
               volume > SUSTAIN_LEVEL)    // if not already at SUSTAIN volume
        volume--;
      // RELEASE
      else if (noteClock > RELEASE_TIME &&  // If in RELEASE part of the ADSR envelope, and
               noteClock - RELEASE_TIME > (SUSTAIN_LEVEL - volume) * RELEASE_RATE &&  // if time to decrease volume, and
               volume > 0)                  // if not already at min volume
        volume--;
      else
        noteClock = 0;
    }

    // Update mixer
    accumulator += accumulatorStep;    // Advance accumulator
    waveStep = accumulator >> 8;       // Calculate lookup table entry index (bit-shift-divide by 2^8=256)
    mixer = DDS_fullSaw[waveStep] * volume;
    mixer = mixer >> VOLUME_BITDEPTH;  // Reduce volume so that signal is roughly in 0-255 range. Dividing by bit-shift is very fast.

    // Set voltage at speaker pin
    loop_until_bit_is_set(TIFR0, TOV0);  // Wait for current PWM cycle to finish
    TIFR0 |= (1 << TOV0);                // Reset Timer0 overflow bit
    OCR0A = 128 + ((uint8_t) mixer);     // Set PWM duty cycle = voltage for speaker pin

    // Process USART input - pooling style (using interrupts would typically be a better way - but in this example main loop is running really frequently (31.25 kHz), so the delay between a received character and playing the note is so short that a human will never know)
    if (bit_is_set(UCSR0A, RXC0)) {  // If data received over USART
       //  RXC0 bit in UCSR0A is automatically cleared whenever the USART data register (UDR0) is read,
       //  so we don't have to tell the USART that we're ready for the next byte; it knows automatically.
      serialInput = UDR0;                          // Read received character
      accumulatorStep = lookupPitch(serialInput);  // Convert it to accumulator increment rate
      noteClock = 1;                               // Reset note clock to restart ADSR volume modulation from beginning
    }
  }

  return 0;
}