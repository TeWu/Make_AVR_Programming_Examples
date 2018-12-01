/* Example of basic TWI (a.k.a I2C) usage */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/power.h>   // Power Reduction Management
#include <string.h>      // 'memset' function
#include "USART.h"
#include "TWI.h"
#include "pin_config.h"

#define TWI_PEER_ADDRESS 0b00000000
#define TWI_PEER_MESSAGE 0b10101100  // 172

#define BUFFER_SIZE 5
#define DELAYTIME   5000


int main(void) {
  uint8_t i;
  uint8_t buffer[BUFFER_SIZE];

  clock_prescale_set(clock_div_1);  // Set CPU clock to full 8MHz speed
  USART_init();
  TWI_init();

  while(1) {
    // Send message over TWI
    TWI_start(TWI_PEER_ADDRESS, TWI_WRITE_MODE);  // Start connection in write mode
    TWI_send(TWI_PEER_MESSAGE);
    // Receive data over TWI
    TWI_start(TWI_PEER_ADDRESS, TWI_READ_MODE);   // To restart in read mode, just call TWI_start again
    for (i = 0; i < BUFFER_SIZE - 2; i++)
      buffer[i] = TWI_readAndAck();
    buffer[i] = TWI_readAndNack(); // Last byte received in connection should be with NACK - but why??
    TWI_stop();

    // Transmit buffer's content over USART
    for (i = 0; i < BUFFER_SIZE - 1; i++)
      USART_printByte(buffer[i]);

    // Clear buffer and wait
    memset(buffer, 0, BUFFER_SIZE);
    _delay_ms(DELAYTIME);
  }

  return 0;
}