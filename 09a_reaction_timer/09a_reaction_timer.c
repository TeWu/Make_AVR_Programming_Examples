/* Example of Timer/Counter Hardware usage - use TCNT1 register to determine how much time has elapsed */
/*
   Press the button as quickly as you can after the LEDs light up.
   Your time is printed out over the serial port.
*/
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/interrupt.h>  // "ISR" macro, and more
#include "USART.h"
#include "pin_config.h"
#include "utils.h"


static inline void initTimer1(void) {
  // TCCR1B = Timer/Counter1 Control Register B
  TCCR1B |= (1 << CS10) | (1 << CS11);  // Configure Timer1:
  //                                         1) Set Timer1 clock prescaler to 64          (set bits CS10 and CS11)
  //                                         2) Use Timer1 in Normal mode, just counting  (this is default = no bits set)
  // CPU clock speed: 1 MHz      => 1000   ticks per ms
  // Timer1 clock prescaler: 64  => 15.625 ticks per ms
  // No special output modes configured
}

int main(void) {
  LED_DDR     |= (1 << LED);      // Configure LED pin for output
  BUTTON_DDR  &= ~(1 << BUTTON);  // Configure button pin for input
  BUTTON_PORT |= (1 << BUTTON);   // Enable internal pull-up resistor on button pin
  USART_init();
  initTimer1();

  USART_printString("\r\nReaction Timer:\r\n");
  USART_printString("---------------\r\n");
  USART_printString("Press any key to start.\r\n");

  uint16_t timerValue;
  while (1) {
    USART_receiveByte();  // Wait for any key
    USART_printString("\r\nGet ready... ");
    randomDelay();

    USART_printString("Go!\r\n");
    LED_PORT |= (1 << LED);  // Turn on LED
    // TCNT1 = TCNT1H and TCNT1L combined
    //         TCNT1L = Timer/Counter1 - Counter Register Low Byte
    //         TCNT1H = Timer/Counter1 - Counter Register High Byte
    TCNT1 = 0;  // Reset counter

    // Wait until button pressed, save timer value.
    loop_until_bit_is_clear(BUTTON_PIN, BUTTON);
    timerValue = TCNT1 >> 4;  // Each tick is approx 1/16 milliseconds, so we bit-shift divide

    USART_printMilliseconds(timerValue);
    USART_printComment(timerValue);

    // Clear LED and start again
    LED_PORT &= ~(1 << LED);
    USART_printString("\r\nPress any key to try again.\r\n");
  }

  return 0;
}