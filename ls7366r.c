/* ******************************************************
 * @file ls7366r.c
 * @brief LS7366R SPI encoder interface driver
 ********************************************************/

#include "ls7366r.h"

/*
 * Dummy helpers
 */

__attribute__((weak))
void _ls7366r_chip_sel( uint8_t chip_sel )
{
	(void) chip_sel;
}

__attribute__((weak))
void _ls7366r_chip_desel( uint8_t chip_sel )
{
	(void) chip_sel;
}

__attribute__((weak))
uint8_t _ls7366r_spi_transfer( uint8_t chip_sel, uint8_t out )
{
	(void) chip_sel;
	(void) out;

	return 0;
}



