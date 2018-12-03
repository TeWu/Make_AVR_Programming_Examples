/* Example of basic external interrupts usage */
/* Using PCINT18 interrupt */
/*       P = Pin
         C = Change
         I = INTerrupt
         N
         T
         1 = for pin PD2 (see datasheet)
         8
*/
/* Flashes LED0 at a fixed rate, interrupting whenever button is pressed */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/interrupt.h>  // "ISR" macro, and more
#include "pin_config.h"

#define DELAY_TIME 1500


void handleButton(void) {
  if (bit_is_clear(BUTTON_PIN, BUTTON))
    LEDS_PORT |= (1 << LED1);   // Turn on LED1
  else
    LEDS_PORT &= ~(1 << LED1);  // Turn off LED1
}

ISR(PCINT2_vect) {  // Run every time logical state (voltage level) on button's **PORT** changes (for any pin on that port, that has PCINT enabled - in our case only pin PD2)
  handleButton();
}

void initPCINT18(void) {
  // EIMSK = Pin Change Interrupt Control Register (see "External Interrupts" -> "Register Description" section in datasheet for details)
  PCICR  |= (1 << PCIE2);    // Enable PCINT interrupt for port D
  // PCMSK2 = Pin Change Mask Register 2
  PCMSK2 |= (1 << PCINT18);  // Set mask to enable PCINT18 (PCINT on pin PD2)
}

int main(void) {
  LEDS_DDR    |= (1 << LED0) | (1 << LED1);  // Configure LEDs pins for output
  BUTTON_DDR  &= ~(1 << BUTTON);             // Configure button pin for input
  BUTTON_PORT |= (1 << BUTTON);              // Enable internal pull-up resistor on button pin
  initPCINT18();
  sei();                                     // Set global interrupt enable bit

  while(1) {
    LEDS_PORT ^= (1 << LED0);  // Toggle LED0
    _delay_ms(DELAY_TIME);     // Wait
    // handleButton(); // Comment initPCINT18() call above and uncomment this line for pooling-style multitasking (a bad one too - because of _delay_ms call)
  }

  return 0;
}