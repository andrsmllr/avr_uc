/****************************************************************************/
/**
 * \file button_gpio.c
 * 
 * \date 2015-03-14
 * 
 * \author Andreas
 * 
 * \brief Tutorial for the usage of push button switches to control GPIOs.
 * 
 * \details Use several GPIO pins to read the state of some push buttons
 * to control an LED (turn it on/off). Apply and test some debouncing
 * techniques where appropriate.
 * 
 * \see button_gpio.h
 */
/****************************************************************************/

#include "button_gpio.h"

#include <avr/io.h>
#include <util/delay.h>


/**
 * \brief Main function.
 * \details
 * \param
 * \return
 */
int main(int argc, char** argv)
{
    // Set push button pins as inputs.
    BUTTON_A_CTRL_PORT &= ~(1<<BUTTON_A_BIT);
    BUTTON_B_CTRL_PORT &= ~(1<<BUTTON_B_BIT);
    BUTTON_C_CTRL_PORT &= ~(1<<BUTTON_C_BIT);
    BUTTON_D_CTRL_PORT &= ~(1<<BUTTON_D_BIT);
    
    // Activate internal pull-up resistors.
    BUTTON_A_PORT |= (1<<BUTTON_A_BIT);
    BUTTON_B_PORT |= (1<<BUTTON_B_BIT);
    BUTTON_C_PORT |= (1<<BUTTON_C_BIT);
    BUTTON_D_PORT |= (1<<BUTTON_D_BIT);
    
    // Set LED pin as output.
    LED_CTRL_PORT |= (1<<LED_BIT);
    LED_PORT |= (1<<LED_BIT);
    
    uint8_t button_a;
    uint8_t button_b;
    uint8_t button_c;
    uint8_t button_d;
    
    while (1)
    {
        // Get current state of push button switches.
        button_a = (0 == (BUTTON_A_PIN & (1<<BUTTON_A_BIT)) ? 1 : 0);
        
        button_b = (0 == (BUTTON_B_PIN & (1<<BUTTON_B_BIT)) ? 1 : 0);
        
        button_c = (0 == (BUTTON_C_PIN & (1<<BUTTON_C_BIT)) ? 1 : 0);
        
        button_d = (0 == (BUTTON_D_PIN & (1<<BUTTON_D_BIT)) ? 1 : 0);
        
        if (button_a+button_b+button_c+button_d)
            LED_PORT |= (1<<LED_BIT);
        else
            LED_PORT &= ~(1<<LED_BIT);
        
    }
}
