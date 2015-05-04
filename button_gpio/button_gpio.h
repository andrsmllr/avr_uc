/****************************************************************************/
/**
 * \file button_gpio.h
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
 * \see button_gpio.c
 */
/****************************************************************************/

#ifndef F_CPU
#define F_CPU 16000000UL ///< CPU frequency.
#endif // F_CPU


#ifndef _BUTTON_GPIO_H
#define _BUTTON_GPIO_H

#define BUTTON_A_CTRL_PORT DDRD
#define BUTTON_A_PORT PORTD
#define BUTTON_A_PIN PIND
#define BUTTON_A_BIT 4

#define BUTTON_B_CTRL_PORT DDRD
#define BUTTON_B_PORT PORTD
#define BUTTON_B_PIN PIND
#define BUTTON_B_BIT 3

#define BUTTON_C_CTRL_PORT DDRD
#define BUTTON_C_PORT PORTD
#define BUTTON_C_PIN PIND
#define BUTTON_C_BIT 2

#define BUTTON_D_CTRL_PORT DDRD
#define BUTTON_D_PORT PORTD
#define BUTTON_D_PIN PIND
#define BUTTON_D_BIT 1

#define LED_CTRL_PORT DDRD
#define LED_PORT PORTD
#define LED_PIN PIND
#define LED_BIT 7

#endif // _BUTTON_GPIO_H
