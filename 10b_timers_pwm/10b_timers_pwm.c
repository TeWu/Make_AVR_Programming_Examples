/* Generating PWM signal using Timer/Counter peripheral with serial (USART) control over three LEDs */
/*
        As with the rest of the timer/counter-based code demos so far, the event loop is
        quite sparse. It gets a value from the serial port and then shifts the values up a
        chain, corresponding to the output compare registers of LED1, LED2, and LED3.
        Note how we don’t need to use any more variables to store the "previous" values that
        we received over the serial line - they're stored in the OCRnx registers just as if they
        were normal variables.
        Writing those three variables takes just a couple microseconds even at 1 MHz. The
        rest of the CPU time is spent waiting for and processing our serial input.
        Note how we couldn’t do this at all with the software-based PWM approach in
        "10a_manual_pwm" - if we waited for serial input, the LEDs would stop blinking.
        Even if we just checked if the serial port had new data, it would throw off our
        PWM timings. Here, all our code has to do to keep the LEDs blinking at their appropriate
        duty cycle is write values to the appropriate OCRnx registers. The hardware takes care
        of the rest - counting, comparing, turning on and off pins. In this example, that leaves
        us free to use the CPU to talk to us over the serial port.
*/
#include <avr/io.h>      // Defines pins, ports, etc
#include <util/delay.h>  // Functions to waste time
#include "USART.h"
#include "pin_config.h"


static inline void initTimers() {
  // Timer 1 A,B
  TCCR1A |= (1 << WGM10);   // Fast PWM mode, 8-bit (part 1)
  TCCR1B |= (1 << WGM12);   // Fast PWM mode, 8-bit (part 2)
  TCCR1B |= (1 << CS11);    // PWM Freq = F_CPU/8/256
  TCCR1A |= (1 << COM1A1);  // PWM output on pin OC1A (PB1)
  TCCR1A |= (1 << COM1B1);  // PWM output on pin OC1B (PB2)

  // Timer 2
  TCCR2A |= (1 << WGM21) | (1 << WGM20);  // Fast PWM mode, 8-bit
  TCCR2B |= (1 << CS21);    // PWM Freq = F_CPU/8/256
  TCCR2A |= (1 << COM2A1);  // PWM output on pin OC2A (PB3)
}

int main() {
  uint8_t brightness;

  LEDS_DDR |= (1 << LED1) | (1 << LED2) | (1 << LED3);  // Set LED1, LED2 and LED3 pins to output mode
  initTimers();
  USART_init();

  USART_printString("\r\n-- LED PWM Demo --\r\n");
  while(1) {
    USART_printString("\r\nEnter (0-255) for PWM duty cycle: ");
    brightness = USART_receiveNumberAsString();
    OCR2A = OCR1B;
    OCR1B = OCR1A;
    OCR1A = brightness;
  }

  return 0;
}