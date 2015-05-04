/**
 *  \file blink_led.c
 *  \brief Simple blink_led project for AVR ATMEGA8 microcontroller.
 */

#define F_CPU 16000000UL ///< CPU frequency.

#include <avr/io.h>
#include <util/delay.h> // _delay_ms requires compiler optimization enabled.

#include "blink_led.h"

/// Data direction register for LED.
#define LED_CTRL_PORT DDRD
#define LED_PORT PORTD ///< Port for LED.
#define LED_PIN 7 ///< Pin for LED.

/** 
 * \brief Main function for blinking the LED.
 * \param argc: Argument count.
 * \param argv: Argument values.
 * \return Returns 0 on success, non-zero error code otherwise.
 */
int main(int argc, char** argv)
{
    LED_CTRL_PORT = LED_CTRL_PORT | (1 << LED_PIN); // Set pin PD7 as output.
    
    // Main loop.
    while (1)
    {
        // Toggle b/w on and off each second.
        LED_PORT = LED_PORT | (1 << LED_PIN);
        _delay_ms(500);
        LED_PORT = LED_PORT & ~(1 << LED_PIN);
        _delay_ms(500);
    }
    
    return 0;
}
