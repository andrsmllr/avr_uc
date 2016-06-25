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
 * \details On power-up send welcome message, then continue to echo
 *          whatever is received by the UART.
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
    char msg [12] = "Hello UART!\n";
    int i = 0;
    uint8_t rxd = 0;
    
    UBRRH = (uint8_t)((F_CPU / (16 * BAUD_RATE)) >> 8); // Set baud rate.
    UBRRL = (uint8_t)((F_CPU / (16 * BAUD_RATE)));
    UCSRB |= (1<<RXEN) | (1<<TXEN); // Enable rx and tx.
    UCSRC |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0); // 8 data bits, 1 stop bit.
    
    for (i = 0; i < 12; i++)
    {
        wait_uart_tx_ready();
        UDR = msg[i]; // Send test message.
    }
    
    _delay_ms(1000); // Wait.
    
    // Echo loop. Echo each received frame/character immediately (no buffering).
    while (1)
    {
        wait_uart_rx_avail();
        rxd = UDR;
        wait_uart_tx_ready();
        UDR = rxd;
    }
    
    return 0;
}

void wait_uart_tx_ready() 
{
    while (!(UCSRA & (1<<UDRE)))
    {} // Wait for tx register ready.
    return;
}

void wait_uart_rx_avail()
{
    while (!(UCSRA & (1<<RXC)))
    {} // Wait until rx data available.
    return;
}
