/* Example of basic external interrupts usage - using "fancy" INT0 interrupt */
/* Flashes LED0 at a fixed rate, interrupting whenever button is pressed */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/interrupt.h>  // "ISR" macro, and more
#include "pin_config.h"

#define DELAYTIME 500


void handleButton(void) {
  if (bit_is_set(BUTTON_PIN, BUTTON))
    LEDS_PORT |= (1 << LED1);   // Turn on LED1
  else
    LEDS_PORT &= ~(1 << LED1);  // Turn off LED1
}

ISR(INT0_vect) {  // Run every time logical state (voltage level) on button pin changes
  handleButton();
}

void initINT0(void) {
  // EIMSK = External Interrupt Mask Register (see "External Interrupts" -> "Register Description" section in datasheet for details)
  EIMSK |= (1 << INT0);   // Enable INT0 interrupt
  // EICRA = External Interrupt Control Register A
  EICRA |= (1 << ISC00);  // Configure INT0 to trigger on (INT0 = PD2) pin logical state (voltage level) change
}

int main(void) {
  LEDS_DDR    |= (1 << LED0) | (1 << LED1);  // Configure LEDs pins for output
  BUTTON_DDR  &= ~(1 << BUTTON);             // Configure button pin for input
  BUTTON_PORT |= (1 << BUTTON);              // Enable internal pull-up resistor on button pin
  initINT0();
  sei();                                     // Set global interrupt enable bit

  while(1) {
    LEDS_PORT ^= (1 << LED0);  // Toggle LED0
    _delay_ms(DELAYTIME);      // Wait
    // handleButton(); // Comment initINT0() call above and uncomment this line for pooling-style multitasking (a bad one too - because of _delay_ms call)
  }

  return 0;
}