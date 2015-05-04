/****************************************************************************/
/**
 * \file spi_eeprom_25LC040A.h
 * 
 * \date 2015-05-02
 * 
 * \author Andreas
 * 
 * \brief Header fiel for driver for 25LC040A SPI EEPROM.
 * 
 * \details ...
 * 
 * \see spi_eeprom_25LC040A.c
 */
/****************************************************************************/

#ifndef SPI_EEPROM_25LC040A_H
#define SPI_EEPROM_25LC040A_H

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL ///< CPU frequency.
#endif // F_CPU

#define EEPROM_CMD_READ 0x03 ///< Read instruction, bit 4 is set to address bit 9.
#define EEPROM_CMD_WRITE 0x02 ///< Write instruction, bit 4 is set to address bit 9.
#define EEPROM_CMD_WRDI 0x04 ///< Write disable, resets the write enable latch.
#define EEPROM_CMD_WREN 0x06 ///< Write enable, sets the write enable latch.
#define EEPROM_CMD_RDSR 0x05 ///< Read status register.
#define EEPROM_CMD_WRSR 0x01 ///< Write status register.

#define EEPROM_SR_WIP 0x01 ///< Write in progress.
#define EEPROM_SR_WEL 0x02 ///< Write enable latch.
#define EEPROM_SR_BP0 0x04 ///< Block protect 0.
#define EEPROM_SR_BP1 0x08 ///< Block protect 1.

uint8_t spi_wr_init(void);
uint8_t spi_rd_init(void);
uint8_t spi_write(uint8_t* data, uint8_t len);
uint8_t spi_read(uint8_t* data, uint8_t len);
uint8_t eeprom_write(uint8_t* data, uint8_t len);
uint8_t eeprom_read(uint8_t* data, uint8_t len);

#endif // SPI_EEPROM_25LC040A_H
