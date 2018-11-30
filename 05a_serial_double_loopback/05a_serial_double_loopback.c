/*  A simple test of serial-port functionality.
 *  Takes in a character at a time and sends it right back out, displaying the ASCII value on the LEDs.
 */
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"


int main(void) {
  char serialCharacter;

  LED_DDR = 0xFF;  // Set up LEDs for output
  initUSART();
  printString("Hello World!\r\n");

  while (1) {
    serialCharacter = receiveByte();
    printBinaryByte(serialCharacter);
    transmitByte(serialCharacter);
    LED_PORT = serialCharacter;  // Display ascii/numeric value of character
  }

  return 0;
}