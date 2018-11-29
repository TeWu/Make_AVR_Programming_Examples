/*
  Quick and dirty functions that make serial communications work.

  Note that receiveByte() blocks -- it sits and waits _forever_ for
   a byte to come in.  If you're doing anything that's more interesting,
   you'll want to implement this with interrupts.

  initUSART requires BAUD to be defined in order to calculate
    the bit-rate multiplier.  9600 is a reasonable default.

  May not work with some of the older chips:
    Tiny2313, Mega8, Mega16, Mega32 have different pin macros
    If you're using these chips, see (e.g.) iom8.h for how it's done.
    These old chips don't specify UDR0 vs UDR1.
    Correspondingly, the macros will just be defined as UDR.
*/

#include "USART.h"


void USART_init() {
  // Set USART clock prescaler value based on values of BAUD and F_CPU macros - for more info see at the bottom of page 91 of "Make: AVR Programming" book, and https://www.nongnu.org/avr-libc/user-manual/setbaud_8h_source.html (line 58)
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  #if USE_2X
    UCSR0A |= (1 << U2X0);
  #else
    UCSR0A &= ~(1 << U2X0);
  #endif
  // UCSR0B = USART Control and Status Register 0 B
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);    // Enable USART transmitter and receiver
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Set frame format: 8 data bits and 1 stop bit
}

void USART_transmitByte(uint8_t data) {
  loop_until_bit_is_set(UCSR0A, UDRE0); // Wait for empty transmit buffer
  UDR0 = data;                          // Send data
}

uint8_t USART_receiveByte() {
  loop_until_bit_is_set(UCSR0A, RXC0); // Wait for incoming data
  return UDR0;                         // Return register value
}


void USART_printString(const char myString[]) {
  uint8_t i = 0;
  while (myString[i])
    USART_transmitByte(myString[i++]);
}

void USART_readString(char myString[], uint8_t maxLength) {
  char response;
  uint8_t i = 0;
  while (i < (maxLength - 1)) {
    response = USART_receiveByte();
    if (response == '\r')  break;
    else myString[i++] = response;
  }
  myString[i] = 0; // Append terminal NULL character
}

void USART_printByte(uint8_t byte) {
  // Convert a byte to a string of decimal text, then send it
  USART_transmitByte('0' + (byte / 100));       // Hundreds
  USART_transmitByte('0' + ((byte / 10) % 10)); // Tens
  USART_transmitByte('0' + (byte % 10));        // Ones
}

void USART_printWord(uint16_t word) {
  // Convert a word (16-bits) to a string of decimal text, then send it
  USART_transmitByte('0' + (word / 10000));       // Ten-thousands
  USART_transmitByte('0' + ((word / 1000) % 10)); // Thousands
  USART_transmitByte('0' + ((word / 100) % 10));  // Hundreds
  USART_transmitByte('0' + ((word / 10) % 10));   // Tens
  USART_transmitByte('0' + (word % 10));          // Ones
}

void USART_printBinaryByte(uint8_t byte) {
  // Convert a byte to a series of 0's and 1's, then send it
  for (uint8_t bit = 7; bit < 255; bit--)
    USART_transmitByte(bit_is_set(byte, bit) ? '1' : '0');
}

char integerToHexCharacter(uint8_t integer) {
  // Convert (4 bit) integer into hexadecimal character
  if (integer < 10)
    return '0' + integer;
  else
    return 'A' + integer - 10;
}

void USART_printHexByte(uint8_t byte) {
  // Convert a byte to its hexadecimal equivalent, then send it
  USART_transmitByte(integerToHexCharacter(byte >> 4));
  USART_transmitByte(integerToHexCharacter(byte & 0b00001111));
}

uint8_t USART_receiveNumberAsString() {
  // Receive up to three ascii digits (number 0-255 as string) from the serial port, then convert from string to number.
  char hundreds = '0';
  char tens = '0';
  char ones = '0';
  char thisChar = '0';
  do {
    hundreds = tens;
    tens = ones;
    ones = thisChar;
    thisChar = USART_receiveByte();
  } while (thisChar != '\r');
  return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
}
