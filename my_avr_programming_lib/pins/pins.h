/* Define macros that describe pins functions */
#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
#  include "pins328p.h"
#else
#  warning "No additional pins defined for this MCU"
#endif