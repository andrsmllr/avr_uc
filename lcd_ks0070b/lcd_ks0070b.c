/**********************************************************************/
/**
 * \file lcd2x16_ks0070b.c
 * 
 * \date 2015-02-25
 * 
 * \author Andreas
 * 
 * \brief Simple 2x16 LCD project for AVR ATMEGA8 microcontroller.
 * 
 * \details Driver for a 2x16 LCD character display with KS0070B
 *          controller IC.
 * 
 * \see Datasheet Displaytech Ltd. LCD Module 162C BC BC (KS0070B).
 */
/**********************************************************************/

#include "lcd_ks0070b.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


// Protocol used to control the KS0070B.
#define USE_8BIT_INTERFACE 0
#define LCD_CTRL_DISP_CLR 0x001 // Display clear.
#define LCD_CTRL_RET_HOME 0x002 // Return home.
#define LCD_CTRL_ENT_MODE 0x004 // Entry mode set.
#define LCD_CTRL_ENT_MODE_SH_BIT 0x001 
#define LCD_CTRL_ENT_MODE_ID_BIT 0x002
#define LCD_CTRL_DISP_ON 0x008 // Display on/off.
#define LCD_CTRL_DISP_ON_B_BIT 0x001
#define LCD_CTRL_DISP_ON_C_BIT 0x002
#define LCD_CTRL_DISP_ON_D_BIT 0x004
#define LCD_CTRL_SHIFT 0x010 // Shift.
#define LCD_CTRL_SHIFT_RL_BIT 0x004
#define LCD_CTRL_SHIFT_SC_BIT 0x008
#define LCD_CTRL_SET_FUNC 0x020 // Set function.
#define LCD_CTRL_SET_FUNC_F_BIT 0x004
#define LCD_CTRL_SET_FUNC_N_BIT 0x008
#define LCD_CTRL_SET_FUNC_DL_BIT 0x010
#define LCD_CTRL_SET_CGRAM_ADDR 0x040 // Set CG RAM address.
#define LCD_CTRL_SET_CGRAM_ADDR_ADDR_BITS 0x03F
#define LCD_CTRL_SET_DDRAM_ADDR 0x080 // Set DD RAM address.
#define LCD_CTRL_SET_DDRAM_ADDR_ADDR_BITS 0x07F
#define LCD_CTRL_RD_BUSY_ADDR 0x100 // Read busy flag and address.
#define LCD_CTRL_RD_BUSY_ADDR_ADDR_COUNTER_BITS 0x07F
#define LCD_CTRL_RD_BUSY_ADDR_BF_BIT 0x080
#define LCD_CTRL_WR_DATA 0x200 // Write data.
#define LCD_CTRL_WR_DATA_DATA_BITS 0x0FF

#define SET_PIN(PORT, PIN) ((PORT) = (PORT) | (1<<(PIN)))
#define UNSET_PIN(PORT, PIN) ((PORT) = (PORT) & ~(1<<(PIN)))

/**********************************************************************/

/** 
 * \brief Main function for controlling the 2x16 character LCD.
 * \param argc: Argument count.
 * \param argv: Argument values.
 * \return Returns 0 on success, non-zero error code otherwise.
 */
int main(int argc, char** argv)
{
    lcd_init();
    // Write test character.
    lcd_print_string("HEY SEBI, ANDI ROCKS! LADIDARALA\0");
    lcd_set_pos(7,0);
    lcd_print_char('O');
    //lcd_init();
    
    // Configure input pin for button A.
    BUTTON_A_CTRL_PORT &= ~(0<<BUTTON_A_BIT);
    BUTTON_A_PORT |= (1<<BUTTON_A_BIT);
    DDRD |= (1<<7);
    PORTD &= ~(1<<7);
    
    // Main loop.
    while (1)
    {
        if (BUTTON_A_PIN & (1<<BUTTON_A_BIT))
        {
            PORTD |= (1<<7);
        }
        else
        {
            PORTD &= ~(1<<7);
        }
    }
    
    return 0;
}

/**
 * \brief Initialize and clear display.
 * \return Return 0 on success, non-zero error code otherwise.
 */
uint8_t lcd_init()
{
    // Port configuration for initialization.
    LCD_DB7_CTRL_PORT = LCD_DB7_CTRL_PORT | (1<<LCD_DB7_PIN);
    LCD_DB6_CTRL_PORT = LCD_DB6_CTRL_PORT | (1<<LCD_DB6_PIN);
    LCD_DB5_CTRL_PORT = LCD_DB5_CTRL_PORT | (1<<LCD_DB5_PIN);
    LCD_DB4_CTRL_PORT = LCD_DB4_CTRL_PORT | (1<<LCD_DB4_PIN);
    
    LCD_E_CTRL_PORT = LCD_E_CTRL_PORT | (1<<LCD_E_PIN);
    LCD_RW_CTRL_PORT = LCD_RW_CTRL_PORT | (1<<LCD_RW_PIN);
    LCD_RS_CTRL_PORT = LCD_RS_CTRL_PORT | (1<<LCD_RS_PIN);
    
    // Initialize display.
    _delay_ms(4*15); // Wait for more than 15 ms.
    lcd_send_raw(0x0020); // Init.
    _delay_ms(2*4); // Wait for more than 4.1 ms.
    lcd_send_raw(0x0020); // Init.
    //_delay_ms(2); // Wait for more than 100 us.
    lcd_send_raw(0x0020); // Init.
    //_delay_ms(2);
    lcd_send_raw(0x0020 | 0x0008); // Function set.
    lcd_command(LCD_OFF); // Display off.
    lcd_command(LCD_CLEAR); // Display clear.
    lcd_send_raw(0x0004 | 0x0002); // Entry mode set.
    lcd_command(LCD_ON); // Display on.
    
    return 0;
}

/** 
 * \brief Send raw data/command to the LCD.
 * \param data: 16 bit data. Only 10 LSBs are used.
 * \return Return 0 on success, non-zero error code otherwise.
 */
uint8_t lcd_send_raw(uint16_t data)
{
    if (data & 0x0200)
        SET_PIN(LCD_RS_PORT, LCD_RS_PIN);
    else
        UNSET_PIN(LCD_RS_PORT, LCD_RS_PIN);
    
    if (data & 0x0100)
        SET_PIN(LCD_RW_PORT, LCD_RW_PIN);
    else
        UNSET_PIN(LCD_RW_PORT, LCD_RW_PIN);
    
    _delay_us(1);
    SET_PIN(LCD_E_PORT, LCD_E_PIN);
    
    // Upper nibble.
    if (data & 0x80)
        SET_PIN(LCD_DB7_PORT, LCD_DB7_PIN);
    else
        UNSET_PIN(LCD_DB7_PORT, LCD_DB7_PIN);
    if (data & 0x40)
        SET_PIN(LCD_DB6_PORT, LCD_DB6_PIN);
    else
        UNSET_PIN(LCD_DB6_PORT, LCD_DB6_PIN);
    if (data & 0x20)
        SET_PIN(LCD_DB5_PORT, LCD_DB5_PIN);
    else
        UNSET_PIN(LCD_DB5_PORT, LCD_DB5_PIN);
    if (data & 0x10)
        SET_PIN(LCD_DB4_PORT, LCD_DB4_PIN);
    else
        UNSET_PIN(LCD_DB4_PORT, LCD_DB4_PIN);
    
    if (USE_8BIT_INTERFACE == 0)
    {
        UNSET_PIN(LCD_E_PORT, LCD_E_PIN);
        _delay_us(1);
        SET_PIN(LCD_E_PORT, LCD_E_PIN);
        _delay_us(1);
    }
    
    // Lower nibble.
    if (data & 0x08)
        SET_PIN(LCD_DB7_PORT, LCD_DB7_PIN);
    else
        UNSET_PIN(LCD_DB7_PORT, LCD_DB7_PIN);
    if (data & 0x04)
        SET_PIN(LCD_DB6_PORT, LCD_DB6_PIN);
    else
        UNSET_PIN(LCD_DB6_PORT, LCD_DB6_PIN);
    if (data & 0x02)
        SET_PIN(LCD_DB5_PORT, LCD_DB5_PIN);
    else
        UNSET_PIN(LCD_DB5_PORT, LCD_DB5_PIN);
    if (data & 0x01)
        SET_PIN(LCD_DB4_PORT, LCD_DB4_PIN);
    else
        UNSET_PIN(LCD_DB4_PORT, LCD_DB4_PIN);
    
    _delay_us(1);
    UNSET_PIN(LCD_E_PORT, LCD_E_PIN);
    _delay_ms(2);
    return 0;
}

/**
 * \brief Wait until busy flag goes low.
 * \return Busy flag value. 0 on successful wait, 1 on wait timeout.
 * \todo This function needs to be tested and verified.
 */
uint8_t lcd_wait_busyflag()
{
    const uint8_t MAX_RETRIES = 100;
    uint8_t rd_data;
    
    // Set data pins as inputs.
    LCD_DB7_CTRL_PORT &= ~(1<<LCD_DB7_PIN);
    //LCD_DB6_CTRL_PORT &= ~(1<<LCD_DB6_PIN);
    //LCD_DB5_CTRL_PORT &= ~(1<<LCD_DB5_PIN);
    //LCD_DB4_CTRL_PORT &= ~(1<<LCD_DB4_PIN);
    
    SET_PIN(LCD_RW_PORT, LCD_RW_PIN);
    UNSET_PIN(LCD_RS_PORT, LCD_RS_PIN);
    
    uint8_t n = 0;
    while (n < MAX_RETRIES)
    {
        SET_PIN(LCD_E_PORT, LCD_E_PIN);
        rd_data = 0x80 & LCD_DB7_PORT;
        UNSET_PIN(LCD_E_PORT, LCD_E_PIN);
        if (rd_data != 0)
            break;
        n++;
    }
    
    // Set data pins as outputs.
    LCD_DB7_CTRL_PORT |= (1<<LCD_DB7_PIN);
    //LCD_DB6_CTRL_PORT |= (1<<LCD_DB6_PIN);
    //LCD_DB5_CTRL_PORT |= (1<<LCD_DB5_PIN);
    //LCD_DB4_CTRL_PORT |= (1<<LCD_DB4_PIN);
    return rd_data;
}

/**
 * \brief Send a command.
 * \param cmd: A command to control the LCD.
 * \return Return 0 on success, non-zero error code otherwise.
 * \todo Make this the primary public function to control the LCD.
 */
uint8_t lcd_command(lcd_command_t cmd)
{
    switch (cmd)
    {
        case LCD_INIT:
            return lcd_init();
            break;
        case LCD_ON:
            return lcd_send_raw(0x000F);
            break;
        case LCD_OFF:
            return lcd_send_raw(0x0008);
            break;
        case LCD_CLEAR:
            return lcd_send_raw(0x0001);
            break;
        case LCD_HOME:
            return lcd_send_raw(0x0002);
            break;
        default:
            return -1;
    }
}

/**
 * \brief Move cursor to position.
 * \param x: Offset position from start of line.
 * \param y: Line number.
 * \return Return 0 on success, non-zero error code otherwise.
 */
uint8_t lcd_set_pos(uint8_t x, uint8_t y)
{
    if (x >= 16)
        return 1;
    if (y >= 2)
        return 2;
    
    lcd_send_raw(0x0080 | (y*0x40+x));
    
    return 0;
}

/** 
 * \brief Print a character to the LCD.
 * \param c: A single character.
 * \return Return 0 on success, non-zero error code otherwise.
 */
uint8_t lcd_print_char(char c)
{
    char * cp = malloc(sizeof(char)*2);
    cp[0] = c;
    cp[1] = '\0';
    return lcd_print_string(cp);
}

/** 
 * \brief Print a string to the LCD.
 * \param s: A null terminated string not longer than 32 characters.
 * \return Returns number of written characters on success, negative
 *         values on error.
 */
uint8_t lcd_print_string(char* s)
{
    uint8_t i = 0;
    while (1)
    {
        if (s[i] != 0)
        {
            lcd_wait_busyflag();
            lcd_send_raw(0x0200 | (s[i] & 0x00FF));
            i++;
            if (i==16)
            {
                lcd_wait_busyflag();
                lcd_set_pos(0,1);
            }
        }
        else
        {
            break;
        }
    }
    return i;
}
