/**********************************************************************/
/**
 * \file lcd_ks0070b.h
 * 
 * \brief Header file for lcd_ks0070b.c.
 * 
 * \todo Decide which functions to make public and make the rest
 *       private.
 */
/**********************************************************************/

#ifndef _LCD_KS0070B_H
#define _LCD_KS0070B_H

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL ///< CPU frequency.
#endif // F_CPU

// Connection from MCU to KS0070B LCD.
#define LCD_DB7_CTRL_PORT DDRC
#define LCD_DB7_PORT PORTC
#define LCD_DB7_PIN 3
#define LCD_DB6_CTRL_PORT DDRC
#define LCD_DB6_PORT PORTC
#define LCD_DB6_PIN 2
#define LCD_DB5_CTRL_PORT DDRC
#define LCD_DB5_PORT PORTC
#define LCD_DB5_PIN 1
#define LCD_DB4_CTRL_PORT DDRC
#define LCD_DB4_PORT PORTC
#define LCD_DB4_PIN 0
#define LCD_DB3_CTRL_PORT DDRC
#define LCD_DB3_PORT PORTC
#define LCD_DB3_PIN 0xff
#define LCD_DB2_CTRL_PORT DDRC
#define LCD_DB2_PORT PORTC
#define LCD_DB2_PIN 0xff
#define LCD_DB1_CTRL_PORT DDRC
#define LCD_DB1_PORT PORTC
#define LCD_DB1_PIN 0xff
#define LCD_DB0_CTRL_PORT DDRC
#define LCD_DB0_PORT PORTC
#define LCD_DB0_PIN 0xff
#define LCD_E_CTRL_PORT DDRB
#define LCD_E_PORT PORTB
#define LCD_E_PIN 2
#define LCD_RW_CTRL_PORT DDRB
#define LCD_RW_PORT PORTB
#define LCD_RW_PIN 1
#define LCD_RS_CTRL_PORT DDRB
#define LCD_RS_PORT PORTB
#define LCD_RS_PIN 0

#define LCD_X_POS_MAX 15
#define LCD_Y_POS_MAX 1

/// \todo Remove button for LED control.
#define BUTTON_A_CTRL_PORT DDRD
#define BUTTON_A_PORT PORTD
#define BUTTON_A_PIN PIND
#define BUTTON_A_BIT 4

typedef enum {LCD_INIT, LCD_ON, LCD_OFF, LCD_CLEAR, LCD_HOME} lcd_command_t;

uint8_t lcd_init();

uint8_t lcd_send_raw(uint16_t data);

uint8_t lcd_send_raw_block(uint16_t* data, uint8_t length);

uint8_t lcd_wait_busyflag();

uint8_t lcd_command(lcd_command_t cmd);

uint8_t lcd_set_pos(uint8_t x, uint8_t y);

uint8_t lcd_print_char(char c);

uint8_t lcd_print_string(char* c);

#endif //_LCD_KS0070B_H
