/* Example of passing data from/(to) Interrupt Service Routine */
/* Flashes LED slowly when button is not pressed, and fast when it is */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/interrupt.h>  // "ISR" macro, and more
#include "pin_config.h"

#define DELAYTIME_SLOW 1500
#define DELAYTIME_FAST 400


volatile uint8_t delayTime;  // Use global volatile variables to pass data from/to ISR

void setDelayTime(void) {
  delayTime = bit_is_set(BUTTON_PIN, BUTTON) ? DELAYTIME_FAST : DELAYTIME_SLOW;
}

ISR(PCINT2_vect) {  // Run every time logical state (voltage level) on button's **PORT** changes (for any pin on that port, that has PCINT enabled - in our case only pin PD2)
  setDelayTime();
}

void initPCINT18(void) {
  // EIMSK = Pin Change Interrupt Control Register (see "External Interrupts" -> "Register Description" section in datasheet for details)
  PCICR  |= (1 << PCIE2);    // Enable PCINT interrupt for port D
  // PCMSK2 = Pin Change Mask Register 2
  PCMSK2 |= (1 << PCINT18);  // Set mask to enable PCINT18 (PCINT on pin PD2)
}

int main(void) {
  LED_DDR     |= (1 << LED);      // Configure LED pin for output
  BUTTON_DDR  &= ~(1 << BUTTON);  // Configure button pin for input
  BUTTON_PORT |= (1 << BUTTON);   // Enable internal pull-up resistor on button pin
  initPCINT18();
  sei();                          // Set global interrupt enable bit

  uint8_t i;
  while(1) {
    LED_PORT ^= (1 << LED);         // Toggle LED
    for(i = 0; i < delayTime; i++)  // Wait
      _delay_ms(1);
    // setDelayTime(); // Comment initPCINT18() call above and uncomment this line for pooling-style multitasking (a bad one too - because of _delay_ms call)
  }

  return 0;
}