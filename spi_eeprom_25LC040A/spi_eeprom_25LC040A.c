/****************************************************************************/
/**
 * \file spi_eeprom_25LC040A.c
 * 
 * \date 2015-05-02
 * 
 * \author Andreas
 * 
 * \brief Driver for 4 kb 25LC040A SPI EEPROM.
 *        The memory is organized as 512 x 8 bit, with a page size of 16 bytes.
 * 
 * \details ...
 * 
 * \see ...
 */
/****************************************************************************/

#include "spi_eeprom_25LC040A.h"

#define SS_LOW (PORTB &= ~(1<<PB2))
#define SS_HIGH (PORTB |= (1<<PB2))

int main(int argc, char** argv)
{
    // Initialize SPI pins for SPI master operation.
    DDRB |= (1<<PB5); // Set SCK to output.
    DDRB &= ~(1<<PB4); // Set MISO to input.
    DDRB |= (1<<PB3); // Set MOSI to output.
    DDRB |= (1<<PB2); // Set SSB to output.
    // SPI Control Register.
    SPCR &= ~(1<<SPR0) & ~(1<<SPR1); // F_SCK = F_OSC/4.
    SPCR &= ~(1<<CPOL) & ~(1<<CPHA); // SCK phase 0, SCK polatiry 0.
    SPCR |= (1<<MSTR); // SPI master.
    SPCR &= ~(1<<DORD); // MSB first.
    SPCR |= (1<<SPE); // SPI enable.
    SPCR &= ~(1<<SPIE); // SPI interrupt disable.
    // SPI Status Register.
    SPSR &= ~(1<<SPI2X); // F_SCK = F_OSC/4.
    
    // For testing write some values to some addresses.
    uint8_t wr_val = 0;
    uint16_t wr_addr = 0;
    uint8_t wr_count = 0;
    
    SS_LOW;
    SPDR = EEPROM_SR_WEL;
    while (!SPSR & (1<<SPIF)) {} // Wait wait complete.
    SS_HIGH;
    
    while (1)
    {
        SS_LOW;
        
        SPDR = EEPROM_CMD_WRITE; // Write command.
        while (!SPSR & (1<<SPIF)) {}
        
        SPDR = ((wr_addr & 0xFF00) >> 8); // Write address.
        while (!SPSR & (1<<SPIF)) {}
        SPDR = wr_addr & 0xFF;
        while (!SPSR & (1<<SPIF)) {}
        
        while (wr_count < 16)
        {
            SPDR = wr_val; // Write datum.
            wr_val++;
            wr_addr++;
            wr_count++;
            while (!SPSR & (1<<SPIF)) {}
        }
        
        SS_HIGH;
        
        uint8_t write_complete = 0;
        while (!write_complete)
        {
            SPDR = EEPROM_CMD_RDSR;
            while (!SPSR & (1<<SPIF)) {}
            SPDR = 0x00;
            while (!SPSR & (1<<SPIF)) {}
            write_complete = ~(SPDR & 0x01);
        }
    }
    
    return 0;
}

uint8_t eeprom_write(uint8_t* data, uint8_t len)
{
    uint8_t wr_count = 0;
    
    // Ensure the write enable latch is set.
    
    
    uint8_t i;
    for (i = 0; i < len; i++)
    {
        ;
    }
    
    return wr_count;
}

uint8_t eeprom_read(uint8_t* data, uint8_t len)
{
    uint8_t rd_count = 0;
    
    return rd_count;
}
