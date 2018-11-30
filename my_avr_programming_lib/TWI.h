#ifndef _TWI_H_
#define _TWI_H_ 1

#include <avr/io.h>

// NOTE: **NOT USING THIS BECAUSE**:
//       TWI_BITRATE_UNPRESCALED not calculated correctly for some values of F_CPU and TWI_SCL_FREQUENCY
//       For example: it wil note work for F_CPU = 1MHz and TWI_SCL_FREQUENCY = 100kHz
//       Also be carefull so that F_CPU reflect real CPU clock frequency (e.g. when you're using clock_prescale_set from avr/power.h library)
  // Set default TWI clock frequency
  //// #ifndef TWI_SCL_FREQUENCY
  //// #define TWI_SCL_FREQUENCY 100000UL  // 100kHz
  //// #endif
  ////
  // Used in TWI_init to calculate bitrate
  //   Fram datasheet we know that:
  //       SCL_freqency = F_CPU / (16 + 2 * TWBR * prescaler)
  //   so:
  //       TWBR = (( (F_CPU / 2) / SCL_freqency) - 8) / prescaler
  // For more info see datasheet chapter "2-wire Serial Interface" -> "Bit Rate Generator Unit"
  //// #define TWI_BITRATE_UNPRESCALED ((F_CPU / 2) / TWI_SCL_FREQUENCY) - 8)

#define TWI_BITRATE 32  // Should give us TWI clock frequency of 100kHz at F_CPU = 8MHz

#define TWI_WRITE_MODE 0
#define TWI_READ_MODE  1


// Sets pull-up resistors and initializes bus speed to 100kHz (assuming F_CPU = 8MHz)
void TWI_init(uint8_t* port, uint8_t scl_bit, uint8_t sda_bit);
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