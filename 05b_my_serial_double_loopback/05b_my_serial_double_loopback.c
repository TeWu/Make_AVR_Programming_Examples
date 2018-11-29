/*  A simple test of serial-port functionality.
 *  Takes in a character at a time and sends it right back out, displaying the ASCII value on the LEDs.
 */
#include <util/delay.h>
#include "pin_config.h"
#include "USART.h"


int main() {
  char serialCharacter;

  LED_DDR = 0xFF;  // Set up LEDs for output
  USART_init();
  USART_printString("Hello World!\r\n");

  while (1) {
    serialCharacter = USART_receiveByte();
    USART_printBinaryByte(serialCharacter);
    USART_transmitByte(serialCharacter);
    LED_PORT = serialCharacter;  // Display ascii/numeric value of character
  }

  return 0;
}