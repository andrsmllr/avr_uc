/**********************************************************************/
/**
 * \file uart_echo_test.h
 * 
 * \date 2015-05-05
 * 
 * \author Andreas
 * 
 * \brief Header file for uart_echo_test.c.
 * 
 * \details ...
 * 
 * \see uart_echo_test.c
 */
/**********************************************************************/

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU (16000000UL) ///< CPU frequency.
#endif // F_CPU

#ifndef UART_ECHO_TEST_H_
#define UART_ECHO_TEST_H_

void wait_uart_tx_ready();
void wait_uart_rx_avail();

#endif // UART_ECHO_TEST_H_

