/**********************************************************************/
/**
 * \file uart_echo_test.c
 * 
 * \date 2015-05-05
 * 
 * \author Andreas
 * 
 * \brief Simple test of UART on ATMEGA8.
 * 
 * \details ...
 * 
 * \see ...
 */
/**********************************************************************/

#include "uart_echo_test.h"
#include <avr/io.h>
#include <util/delay.h>

#define BAUD_RATE 9600UL

int main(int argc, char** argv)
{
    UBRRH = (uint8_t)((F_CPU/(16*BAUD_RATE))>>8); // Set baud rate.
    UBRRL = (uint8_t)((F_CPU/(16*BAUD_RATE)));
    UCSRB |= (1<<RXEN)|(1<<TXEN); // Enable rx and tx.
    UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
    //~(1<<USBS)~(1<<UMSEL)
    // Main loop.
    while (1)
    {
        while (!(UCSRA & (1<<UDRE)))
        {} // Wait for tx register ready.
        UDR = 0xFF;
        _delay_ms(1000);
    }
    
    return 0;
}

