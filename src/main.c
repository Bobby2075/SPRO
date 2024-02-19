#define F_CPU 16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"

int main(void)
{

  uart_init();   // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication
  unsigned int time;
  TCCR1A = 0x00;
  DDRB &= ~0x01;
  PORTB |= 0x01;
  TCCR1B = (1 << ICNC1) | (1 << ICES1) | (1 << CS12) | (1 << CS10);

  while (1)
  {

    while (TIFR1 | (1 << ICF1)) // Checks if ICF1 is on a rising edge
    {
    printf("\nbit is not set");
    }
    printf("\nBit is set");
    TIFR1 = (1 << ICF1); // resets ICF1
    TCNT1 = 0;           // Resets TCNT1
    time = ICR1;         // copies ICR1 into a local variable
    printf("\ntime is: %d", time);
    _delay_ms(100);
  }

  return 0;
}