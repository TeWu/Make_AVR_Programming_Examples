#include "utils.h"


void USART_printMilliseconds(uint16_t value) {
  uint8_t digit;

  USART_printString("\r\nYou took ");
  // Add up ten-thousands
  digit = 0;
  while (value >= 10000) {
    digit++;
    value -= 10000;
  }
  if (digit) USART_transmitByte('0' + digit);
  // Add up thousands
  digit = 0;
  while (value >= 1000) {
    digit++;
    value -= 1000;
  }
  USART_transmitByte('0' + digit);
  // decimal point here b/c dividing by 1000
  USART_transmitByte('.');
  // Add up hundreds
  digit = 0;
  while (value >= 100) {
    digit++;
    value -= 100;
  }
  USART_transmitByte('0' + digit);
  // Add up tens
  digit = 0;
  while (value >= 10) {
    digit++;
    value -= 10;
  }
  USART_transmitByte('0' + digit);
  // Ones digit is easy
  USART_transmitByte('0' + value);

  USART_printString(" seconds.\r\n");
}

void USART_printComment(uint16_t value) {
  if (value > 2000)      USART_printString("---->  Ummm...this is a reaction timer...\r\n");
  else if (value > 1000) USART_printString("---->  Hello?\r\n");
  else if (value > 500)  USART_printString("---->  Slow\r\n");
  else if (value > 250)  USART_printString("---->  Have another cup of coffee\r\n");
  else if (value > 200)  USART_printString("---->  Respectable\r\n");
  else if (value > 150)  USART_printString("---->  Fast\r\n");
  else                   USART_printString("---->  Amazing!\r\n");
}

void randomDelay() {
  uint8_t randomTime;
  _delay_ms(1000); // Wait at least 1 sec
  randomTime = (uint8_t) TCNT1;  // Type-casting the 16-bit TCNT1 as an 8-bit number keeps only the 8 least-significant (fastest-changing) bits
  while (--randomTime) // Max value is 255 ~= 2.5 sec
    _delay_ms(10);
}