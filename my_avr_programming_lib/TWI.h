#ifndef _TWI_H_
#define _TWI_H_ 1

#include <avr/io.h>

#define TWI_BITRATE 32  // Should give us TWI clock frequency of 100kHz at F_CPU = 8MHz

#define TWI_WRITE_MODE 0
#define TWI_READ_MODE  1


// Sets pull-up resistors and initializes bus speed to 100kHz (assuming F_CPU = 8MHz)
void TWI_init(volatile uint8_t* port, uint8_t scl_bit, uint8_t sda_bit);
// Waits until the hardware finishes its current job
void TWI_wait(void);
// Sends a start condition (sets TWSTA) and then the divice address with read/write bit set or cleared appropriately for read or write mode
void TWI_start(uint8_t address, uint8_t mode);
// Sends a stop condition (sets TWSTO)
void TWI_stop(void);
// Loads data, sends it out, waiting for completion
void TWI_send(uint8_t data);
// Read in from slave, sending ACK (sets TWEA bit) when done
uint8_t TWI_readAndAck(void);
// Read in from slave, sending NACK (no TWEA bit) when done
uint8_t TWI_readAndNack(void);

#endif /* _TWI_H_ */