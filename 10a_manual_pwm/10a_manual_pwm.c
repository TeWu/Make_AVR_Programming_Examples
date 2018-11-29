/* Generating PWM signal manually (without Timer/Counter peripheral) - notice that we lock up the entire CPU just brightening and dimming */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include "pin_config.h"

#define PWM_FREQUENCY 60  // Hz
#define PWM_DELAY     (1000000 / (PWM_FREQUENCY * 255))  // microseconds


int main() {
  uint8_t brightness = 0;
  int8_t  direction  = 1;
  uint8_t i;

  LEDS_DDR = 0xFF;

  // Pulse LEDs on and off
  while(1) {
    // Output one PWM cycle to LEDS_PORT
    for (i = 0; i < 255; i++) {
      if (i < brightness) LEDS_PORT = 0xFF;
      else                LEDS_PORT = 0;
      _delay_us(PWM_DELAY);
    }
    // Brighten and dim
    if (brightness == 0)   direction = 1;
    if (brightness == 255) direction = -1;
    brightness += direction;
  }

  return 0;
}