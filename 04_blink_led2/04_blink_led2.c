#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time

// Try NOT using those macros in real code - see comment in "../my_avr_programming_lib/bitwise_utils.h"
#define BV(bit) (1 << (bit))
#define setBit(byte, bit) (byte |= BV(bit))
#define clearBit(byte, bit) (byte &= ~BV(bit))
#define toggleBit(byte, bit) (byte ^= BV(bit))

// Configuration at the top of the file is usefull information about how to hook up the circut - also improves readability (PB0 vs LED macro) and maintainability (it's easy to change value of LED macro)
// Event better - move this configuration to "pin_config.h" file and import it here - see other example programs.
#define LED_DDR    DDRB
#define LED_PORT   PORTB
#define LED        PB0    // Use PB0 macro instead of integer 0 to make the code more portable across microcontrollers.
#define DELAYTIME  1500


// Use "int main(void) { ..." instead "int main() { ..." - see https://stackoverflow.com/a/693794/6231376
int main(void) {
  // Init
  setBit(LED_DDR, LED); // Data Direction Register: writing a one to the bit enables output.


  // Main loop
  while(1) {
    toggleBit(LED_PORT, LED);  // Toggle LED's bit/pin
    _delay_ms(DELAYTIME);      // Wait
  }

  return 0; // Dead code - only exists to prevent compiler warning about main not returning an int
}
