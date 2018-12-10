#ifndef _USART_H_
#define _USART_H_ 1

#include <avr/io.h>
#include <util/setbaud.h>

// initUSART requires BAUD to be defined in order to calculate the bit-rate multiplier
#ifndef BAUD       // If not defined in Makefile...
#define BAUD 9600  // Set a safe default baud rate
#endif

#define USART_HAS_DATA  (bit_is_set(UCSR0A, RXC0))
#define USART_READY     (bit_is_set(UCSR0A, UDRE0))


// Takes the defined BAUD and F_CPU, calculates the bit-clock multiplier, and configures the hardware USART
void USART_init(void);

// Blocking transmit and receive functions.
// When you call receiveByte() your program will hang until data comes through.
void USART_transmitByte(uint8_t data);
uint8_t USART_receiveByte(void);

// Utility function to transmit/receive an entire string from/to RAM
void USART_printString(const char myString[]);
void USART_printNewLine(void);
void USART_readString(char myString[], uint8_t maxLength);

void USART_printByte(uint8_t byte);         // Prints a byte out as its 3-digit ascii equivalent
void USART_printWord(uint16_t word);        // Prints a word (16-bits) out as its 5-digit ascii equivalent
void USART_printBinaryByte(uint8_t byte);   // Prints a byte out in 0s and 1s
void USART_printHexByte(uint8_t byte);      // Prints a byte as its hexadecimal equivalent
uint8_t USART_receiveNumberAsString(void);  // Receives up to three ascii digits (number 0-255 as string) from the serial port, then converts from string to number.


#endif /* _USART_H_ */