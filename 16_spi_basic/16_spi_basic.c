/* Example of basic SPI (Serial Peripheral Interface) usage */
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include <avr/power.h>   // Power Reduction Management
#include <string.h>      // 'memset' function
#include "USART.h"
#include "SPI.h"
#include "pin_config.h"

#define SPI_SLAVE_MESSAGE 0b10101100  // 172
#define BUFFER_SIZE 5
#define DELAYTIME   5000

#define SPI_SLAVE_SELECT    (SPI_SLAVE_PORT &= ~(1 << SPI_SLAVE))
#define SPI_SLAVE_DESELECT  (SPI_SLAVE_PORT |=  (1 << SPI_SLAVE))


int main(void) {
  uint8_t i;
  uint8_t buffer[BUFFER_SIZE];

  clock_prescale_set(clock_div_1);  // Set CPU clock to full 8MHz speed
  USART_init();
  SPI_init_slave(&SPI_SLAVE_DDR, &SPI_SLAVE_PORT, SPI_SLAVE);
  SPI_init(SPI_MASTER_MODE, SPI_F_SCK_64, SPI_MSB_FIRST, SPI_MODE_NOPOL_NOPHA);

  while(1) {
    SPI_SLAVE_SELECT;
    // Send message over SPI
    SPI_tradeByte(SPI_SLAVE_MESSAGE);
    // Receive data over SPI  (There is no send/receive in SPI - you always trade byte for byte - here we are sending 0s to receive some bytes)
    for (i = 0; i < BUFFER_SIZE - 1; i++) {
      SPI_tradeByte(0);
      buffer[i] = SPDR;
    }
    SPI_SLAVE_DESELECT;

    // Transmit buffer's content over USART
    for (i = 0; i < BUFFER_SIZE - 1; i++)
      USART_printByte(buffer[i]);

    // Clear buffer and wait
    memset(buffer, 0, BUFFER_SIZE);
    _delay_ms(DELAYTIME);
  }

  return 0;
}