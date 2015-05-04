/**
 * \file blink_led.c
 * 
 * \date 2015-02-18
 * 
 * \author Andreas
 * 
 * \brief Simple shreg_ssdisp project for AVR ATMEGA8 microcontroller.
 * 
 * \details The task of this project is to drive a seven segment
 * display using a 74HCT164 type 8 bit shift register.
 * We assume the mapping b/w 74HCT164 data ports and seven segment
 * display as: QA->g, QB->f, QB->e, QB->d, QB->DP, QB->c, QB->b, QB->a.
 * The 74HCT164 will be abbreviated as "IC" throughout this file.
 * 
 * \see
 */

#define F_CPU 16000000UL ///< CPU frequency.

#include <avr/io.h>
#include <util/delay.h>

// Local user defines.
#define IC_CLOCK_CTRL_PORT DDRD ///< Data direction register for shift
                                /// register clock input.
#define IC_CLOCK_PORT PORTD ///< Port for shift register clock.
#define IC_CLOCK_PIN 0 ///< Pin for shift register clock.
#define IC_CLEAR_CTRL_PORT DDRD ///< Data direction register for shift register clear.
#define IC_CLEAR_PORT PORTD
#define IC_CLEAR_PIN 1
#define IC_SERIAL_A_CTRL_PORT DDRD
#define IC_SERIAL_A_PORT PORTD
#define IC_SERIAL_A_PIN 2
#define IC_SERIAL_B_CTRL_PORT NA
#define IC_SERIAL_B_PORT NA
#define IC_SERIAL_B_PIN NA

/** 
 * \brief Main function for writing to the shift register to control the
 * seven segement display.
 * \param argc: Argument count.
 * \param argv: Argument values.
 * \return Returns 0 on success, non-zero error code otherwise.
 */
int main(int argc, char** argv)
{
    // lookup table.
    // index: integer to display, value: seven segment display
    // representation of integer.
    uint8_t ssdisp_lut[16] = {
        0xEE, 0x60, 0xCD, 0xE9, 0x63, 0xAB, 0xAF, 0xE0, 0xEF, 0xEB,
        0xE7, 0xEF, 0x8E, 0xEE, 0x8F, 0x87
    };
    
    // Configure outputs.
    IC_CLOCK_CTRL_PORT = IC_CLOCK_CTRL_PORT | (1<<IC_CLOCK_PIN);
    IC_CLEAR_CTRL_PORT = IC_CLEAR_CTRL_PORT | (1<<IC_CLEAR_PIN);
    IC_SERIAL_A_CTRL_PORT = IC_SERIAL_A_CTRL_PORT | (1<<IC_SERIAL_A_PIN);
    // Port B of IC is not used here, but assumed to be pulled to '1'.
    // IC_SERIAL_B_CTRL_PORT = IC_SERIAL_B_CTRL_PORT | (1<<IC_SERIAL_B_PIN);
    
    // Clear shift register initially.
    IC_CLEAR_PORT = IC_CLEAR_PORT & ~(1<<IC_CLEAR_PIN);
    _delay_us(1); // Clear must be asserted at least 19 ns.
    IC_CLEAR_PORT = IC_CLEAR_PORT | (1<<IC_CLEAR_PIN);
    
    // Number to display.
    int number = 1;
    
    // Main loop.
    while (1)
    {
        int i;
        // Shift new value into register.
        for (i=7; i>=0; i--)
        //for (i=0; i<8; i++)
        {
            if (~ssdisp_lut[number] & (1<<i))
            {
                IC_SERIAL_A_PORT = IC_SERIAL_A_PORT | (1<<IC_SERIAL_A_PIN);
            }
            else
            {
                IC_SERIAL_A_PORT = IC_SERIAL_A_PORT & ~(1<<IC_SERIAL_A_PIN);
            }
            // Generate a short clock pulse to shift next value.
            IC_CLOCK_PORT = IC_CLOCK_PORT | (1<<IC_CLOCK_PIN);
            _delay_us(1);
            IC_CLOCK_PORT = IC_CLOCK_PORT & ~(1<<IC_CLOCK_PIN);
        }
        
        // Wait some time.
        _delay_ms(500);
        // Calculate next number to display.
        number = (number+1) % 16;
    }
    
    return 0;
}
