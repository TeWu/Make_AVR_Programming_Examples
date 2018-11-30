#include "TWI.h"


// NOT USING THIS BECAUSE: see comment about TWI_BITRATE_UNPRESCALED in TWI.h
// uint8_t TWI_SCLPrescaler(void) {
//     // Calculate TWI SCL Prescaler value - for more info see datasheet description of TWPS (TWI Prescaler Bits) in TWSR register
//   switch (TWSR & 0b00000011) {
//     case 0: return 1;
//     case 1: return 4;
//     case 2: return 16;
//   }
//   return 64;
// }
//
// uint8_t TWI_bitRate(void) {
//   return TWI_BITRATE_UNPRESCALED / (uint32_t) TWI_SCLPrescaler();
// }

// Call it like this: "TWI_init(&TWI_SCL_PORT, TWI_SCL, TWI_SDA);"
void TWI_init(uint8_t* port, uint8_t scl_bit, uint8_t sda_bit) {
  port |= ((1 << scl_bit) | (1 << sda_bit));  // Set pull-up resistors for SDA and SCL pins
  TWBR = TWI_BITRATE;   // Set TWBR (TWI Bit Rate Register), so that we get requested TWI_SCL_FREQUENCY
  TWCR |= (1 << TWEN);  // Enable TWI
}

void TWI_wait(void) {
  // TWCR  = TWI Control Register
  // TWINT = TWI Interrupt Flag    - This bit is set by hardware when the TWI has finished its current job and expects application software response
  loop_until_bit_is_set(TWCR, TWINT);
}

void TWI_start(uint8_t address, uint8_t mode) {
  TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTA));
  TWI_wait();
  if (mode == TWI_WRITE_MODE)  // 8th address bit is read/write mode selector bit = Clear it for write mode or set it for read mode
    TWI_send(address & (~1));
  else
    TWI_send(address | 1);
}

void TWI_stop(void) {
  TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTO));
}

void TWI_send(uint8_t data) {
  TWDR = data;
  TWCR = ((1 << TWEN) | (1 << TWINT));
  TWI_wait();
}

uint8_t TWI_readAndAck(void) {
  TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWEA));
  TWI_wait();
  return TWDR;
}

uint8_t TWI_readAndNack(void) {
  TWCR = ((1 << TWEN) | (1 << TWINT));
  TWI_wait();
  return TWDR;
}