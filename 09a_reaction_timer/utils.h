 /* Support functions that otherwise make the main code more readable */
#ifndef _UTILS_H_
#define _UTILS_H_ 1

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"


// Given a value in milliseconds, prints out how many seconds you took over the serial port.
// Does ASCII conversion, prints decimal point, and drops extra leading zeros.
void USART_printMilliseconds(uint16_t value);

// Given a value in milliseconds, rates your reaction time
void USART_printComment(uint16_t value);

// Waits for a "random" delay between 1 and 3.5 sec. Requires timer 1 initialized and running.
// It's not really random, but very hard to control like coin-flipping.
void randomDelay(void);

#endif /* _UTILS_H_ */