/* Pushbutton debounce example */
#include <avr/io.h>
#include <util/delay.h>
#include "pin_config.h"

#define DEBOUNCE_TIME 1000 // microseconds


uint8_t debounce(uint8_t pin, uint8_t bit) {
  if (bit_is_clear(pin, bit)) {
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(pin, bit))
      return 1;
  }
  return 0;
}

int main(void) {
  LED_DDR |= (1 << LED);         // Set up LED for output
  BUTTON_DDR &= ~(1 << BUTTON);  // Set up button for input
  BUTTON_PORT |= (1 << BUTTON);  // Enable the pull-up resistor on the button pin

  uint8_t isButtonPressed = 0;
  while (1) {
    if(debounce(BUTTON_PIN, BUTTON)) {
      if (isButtonPressed)
        LED_PORT ^= (1 << LED);  // Toggle LED
      isButtonPressed = 1;
    } else
      isButtonPressed = 0;
  }

  return 0;
}