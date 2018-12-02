#ifndef _BITWISE_UTILS_H_
#define _BITWISE_UTILS_H_ 1

/* Make sure we've already got sfr_defs loaded */
#include  <avr/sfr_defs.h>

/* Reminder: the following useful bit-twiddling macros are
   always included in "avr/sfr_defs.h", which is called from "avr/io.h"

   #define is_bit_set(sfr, bit)    (_SFR_BYTE(sfr) & BV(bit))
   #define is_bit_clear(sfr, bit)  (!(_SFR_BYTE(sfr) & BV(bit)))
   #define loop_until_bit_is_set(sfr, bit)    (do { } while (bit_is_clear(sfr, bit)))
   #define loop_until_bit_is_clear(sfr, bit)  (do { } while (bit_is_set(sfr, bit)))

*/

/* Define up the full complement of bit-twiddling macros */
/* Try NOT using those because you will have to read other people's code (e.g. in datasheets), so you should get used to using bitwise operations */
/* PERFORMANCE NOTE: The two invocations "set_bit(REGISTER, i);" and "set_bit(REGISTER, j);" ends up taking twice as many instructions in machine code as "REGISTER |= (1 << i) | (1 << j);". You can check this by compiling your code to assembler - for more see "Alternative Representations for Setting Bits" on page 181 */
#define BV(bit)               (1 << (bit))
#define set_bit(sfr, bit)     (_SFR_BYTE(sfr) |= BV(bit))
#define clear_bit(sfr, bit)   (_SFR_BYTE(sfr) &= ~BV(bit))
#define toggle_bit(sfr, bit)  (_SFR_BYTE(sfr) ^= BV(bit))

#endif /* _BITWISE_UTILS_H_ */