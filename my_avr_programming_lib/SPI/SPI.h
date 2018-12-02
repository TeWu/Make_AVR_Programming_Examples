#ifndef _SPI_H_
#define _SPI_H_ 1

#include <avr/io.h>
#include "pins.h"

#define SPI_SLAVE_MODE  0
#define SPI_MASTER_MODE 1

#define SPI_F_SCK_4   0b000
#define SPI_F_SCK_16  0b010
#define SPI_F_SCK_64  0b100
#define SPI_F_SCK_128 0b110
#define SPI_F_SCK_2   0b001
#define SPI_F_SCK_8   0b011
#define SPI_F_SCK_32  0b101

#define SPI_MSB_FIRST 0
#define SPI_LSB_FIRST 1

#define SPI_MODE_NOPOL_NOPHA 0
#define SPI_MODE_NOPOL_PHA   1
#define SPI_MODE_POL_NOPHA   2
#define SPI_MODE_POL_PHA     3


#define __SPI_MASTER_MASK    0b01
#define __SPI_LSBFIRST_MASK  0b01
#define __SPI_CLOCKRATE_MASK 0b11
#define __SPI_MODE_MASK      0b11
#define __SPI_DBLCLOCK_MASK  0b01


// Init SPI bus
//   isMaster  -- If SPI_SLAVE_MODE:  SPI Slave mode is used,
//                If SPI_MASTER_MODE: SPI Master mode is used
//   clockRateSelector -- Determine the SPI bus clock frequency.
//                        Valid values are defined as SPI_F_SCK_x macros
//                          =========================================
//                          | clockRateSelector |  Clock frequency  |
//                          ----------------------------------------|
//                          | SPI_F_SCK_2       |  F_CPU / 2        |
//                          | SPI_F_SCK_4       |  F_CPU / 4        |
//                          | SPI_F_SCK_8       |  F_CPU / 8        |
//                          | SPI_F_SCK_16      |  F_CPU / 16       |
//                          | SPI_F_SCK_32      |  F_CPU / 32       |
//                          | SPI_F_SCK_64      |  F_CPU / 64       |
//                          | SPI_F_SCK_128     |  F_CPU / 128      |
//                          =========================================
//   lsbFirst  -- If SPI_MSB_FIRST: Most  Significant Bit is transmitted first
//                If SPI_LSB_FIRST: Least Significant Bit is transmitted first
//   mode      -- Determine the data mode - clock phase (CPHA) and polarity (CPOL).
//                Valid values are defined as SPI_MODE__x macros:
//                  ======================================================================================
//                  | mode                 |  Conditions    |  Leading clock edge |  Trailing clock edge |
//                  |------------------------------------------------------------------------------------|
//                  | SPI_MODE_NOPOL_NOPHA | CPOL=0, CPHA=0 | sample (rising)     | setup (falling)      |
//                  | SPI_MODE_NOPOL_PHA   | CPOL=0, CPHA=1 | setup (rising)      | sample (falling)     |
//                  | SPI_MODE_POL_NOPHA   | CPOL=1, CPHA=0 | sample (falling)    | setup (rising)       |
//                  | SPI_MODE_POL_PHA     | CPOL=1, CPHA=1 | setup (falling)     | sample (rising)      |
//                  ======================================================================================
//  EXAMPLE: SPI_init(SPI_MASTER_MODE, SPI_F_SCK_4, SPI_MSB_FIRST, SPI_MODE_NOPOL_NOPHA)
void SPI_init(uint8_t isMaster, uint8_t clockRateSelector, uint8_t lsbFirst, uint8_t mode);

// Configures pin connected to slave's SS (Slave Select) pin
void SPI_init_slave(volatile uint8_t* slave_SS_DDR, volatile uint8_t* slave_SS_PORT, uint8_t slave_SS_bit);

// Loads up SPI Data Register (SPDR) and waits until bittrading is done
void SPI_tradeByte(uint8_t byte);

#endif /* _SPI_H_ */