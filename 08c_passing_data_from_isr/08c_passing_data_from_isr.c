/* Example of passing data from/(to) Interrupt Service Routine */
/* Flashes LED slowly when button is not pressed, and fast when it is */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/interrupt.h>  // "ISR" macro, and more
#include "pin_config.h"

#define DELAY_TIME_SLOW 600
#define DELAY_TIME_FAST 100


volatile uint16_t delayTime = DELAY_TIME_SLOW;  // Use global volatile variables to pass data from/to ISR
uint16_t isButtonPressed = 0;

void setDelayTime(void) {
  if (bit_is_clear(BUTTON_PIN, BUTTON)) {  // Debouncing omitted for clarity
    if(!isButtonPressed)
      delayTime = delayTime == DELAY_TIME_SLOW  ? DELAY_TIME_FAST : DELAY_TIME_SLOW;
    isButtonPressed = 1;
  }
  else isButtonPressed = 0;

  if (delayTime == DELAY_TIME_FAST)  // If delayTime is fast
    LEDS_PORT |= (1 << LED1);        // Turn on LED1
  else                          // else
    LEDS_PORT &= ~(1 << LED1);  // Turn off LED1
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

void delay() {
  switch(delayTime) {
    case DELAY_TIME_SLOW: _delay_ms(DELAY_TIME_SLOW);
    case DELAY_TIME_FAST: _delay_ms(DELAY_TIME_FAST);
  }
}

int main(void) {
  LEDS_DDR    |= ((1 << LED0) | (1 << LED1)); // Configure LED0 and LED1 pins for output
  BUTTON_DDR  &= ~(1 << BUTTON);  // Configure button pin for input
  BUTTON_PORT |= (1 << BUTTON);   // Enable internal pull-up resistor on button pin
  initPCINT18();
  sei();                          // Set global interrupt enable bit

  while(1) {
    LEDS_PORT ^= (1 << LED0);  // Toggle LED
    delay();                   // Wait
    // setDelayTime(); // Comment initPCINT18() call above and uncomment this line for pooling-style multitasking (a bad one too - because of _delay_ms call)
  }

  return 0;
}