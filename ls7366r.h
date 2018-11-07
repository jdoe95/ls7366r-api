/* ******************************************************
 * @file ls7366r.h
 * @brief LS7366R SPI encoder interface driver
 * Created Nov 4 2018
 * Contributors:
 * 		John Yu
 ********************************************************/
#ifndef HBD035405_1F1C_428A_B7E5_C6E8E9430A8B
#define HBD035405_1F1C_428A_B7E5_C6E8E9430A8B

#include <stdint.h>

/*
 * Quadrature modes
 *
 * Non quadrature mode: A=clock, B=direction, not filtered, asynchronous index
 * x1 quadrature mode : 1 count per quadrature cycle, filter clock, sync or async index
 * x2 quadrature mode : 2 counts per quadrature cycle, filter clock, sync or async index
 * x4 quadrature mode : 4 counts per quadrature cycle, filter clock, sync or async index
 */
#define LS7366R_MODE1_QUAD_NONE              (0 << 0) /* non quadrature count mode */
#define LS7366R_MODE1_QUAD_X1                (1 << 0) /* x1 quadrature count mode  */
#define LS7366R_MODE1_QUAD_X2                (2 << 0) /* x2 quadrature count mode  */
#define LS7366R_MODE1_QUAD_X4                (3 << 0) /* x4 quadrature count mode  */

/*
 * data modes
 *
 * FREERUN   : free running
 * SINGLE    : single cycle count mode, disabled upon carry/borrow, enabled by reset or load
 * RANGELIMIT: saturates to DTR or 0
 * MODULON   : modulo-n counting mode, input clock divided by (DTR+1)
 */
#define LS7366R_MODE1_data_FREERUN        (0 << 2) /* free-running count mode */
#define LS7366R_MODE1_data_SINGLE         (1 << 2) /* single-cycle count mode */
#define LS7366R_MODE1_data_RANGELIMIT     (2 << 2) /* range-limit count mode  */
#define LS7366R_MODE1_data_MODULON        (3 << 2) /* modulo-n count mode     */

/*
 * Index modes
 *
 * DISABLE      : disable index
 * LOAD_data : transfers DTR to CNTR upon index
 * RESET_data: clears CNTR upon index
 * LOAD_OTR     : transfers CNTR to OTR upon index
 */
#define LS7366R_MODE1_INDEX_DISABLE          (0 << 4) /* disable index */
#define LS7366R_MODE1_INDEX_LOAD_data     (1 << 4) /* reset CNTR    */
#define LS7366R_MODE1_INDEX_RESET_data    (2 << 4) /* reset CNTR    */
#define LS7366R_MODE1_INDEX_LOAD_OTR         (3 << 4) /* load OTR      */

/*
 * Index synchronous modes
 *
 * ASYNC: asynchronous index
 * SYNC : synchronous index
 */
#define LS7366R_MODE1_INDEXSYNC_ASYNC        (0 << 6) /* asynchronous index */
#define LS7366R_MODE1_INDEXSYNC_SYNC         (1 << 6) /* synchronous index  */

/*
 * Filter clock division
 *
 * DIV1: filter clock divided by 1
 * DIV2: filter clock divided by 2
 */
#define LS7366R_MODE1_FCLK_DIV1              (0 << 7) /* filter clock division by 1 */
#define LS7366R_MODE1_FCLK_DIV2              (1 << 7) /* filter clock division by 2 */

/*
 * data length modes
 *
 * 1B: 8-bit data
 * 2B: 16-bit data
 * 3B: 24-bit data
 * 4B: 32-bit data
 */
#define LS7366R_MODE2_CTRLEN_4B      (0 << 0) /* 4 byte data mode */
#define LS7366R_MODE2_CTRLEN_3B      (1 << 0) /* 3 byte data mode */
#define LS7366R_MODE2_CTRLEN_2B      (2 << 0) /* 2 byte data mode */
#define LS7366R_MODE2_CTRLEN_1B      (3 << 0) /* 1 byte data mode */

/*
 * data enable
 *
 * ENABLE : enable counting
 * DISABLE: disable counting
 */
#define LS7366R_MODE2_CTR_ENABLE     (0 << 2) /* enable data  */
#define LS7366R_MODE2_CTR_DISABLE    (1 << 2) /* disable data */

/*
 * Flag modes
 *
 * NONE : IFLAG and DFLAG outputs no action
 * INDEX: activate IFLAG and DFLAG upon index
 * CMP  : activate IFLAG and DFLAG when CNTR=DTR
 * BW   : activate IFLAG and DFLAG when borrow
 * CY   : activate IFLAG and DFLAG when carry
 */
#define LS7366R_MODE2_FLAG_NONE      (0)      /* no flags        */
#define LS7366R_MODE2_FLAG_INDEX     (1 << 4) /* flag on index   */
#define LS7366R_MODE2_FLAG_CMP       (1 << 5) /* flag on compare */
#define LS7366R_MODE2_FLAG_BW        (1 << 6) /* flag on borrow  */
#define LS7366R_MODE2_FLAG_CY        (1 << 7) /* flag on carry   */

/* status register bit definitions */
#define LS7366R_STATUS_IS_CARRY            (1 << 7) /* set if data overflow   */
#define LS7366R_STATUS_IS_BORROW           (1 << 6) /* set if data underflow  */
#define LS7366R_STATUS_IS_COMPARE          (1 << 5) /* set if data = data     */
#define LS7366R_STATUS_IS_INDEX            (1 << 4) /* set if index pin          */
#define LS7366R_STATUS_IS_COUNT_ENABLE     (1 << 3) /* set if data enable pin */
#define LS7366R_STATUS_IS_POWER_LOSS       (1 << 2) /* set upon power up         */
#define LS7366R_STATUS_IS_COUNT_UP         (1 << 1) /* set if count up           */
#define LS7366R_STATUS_IS_NEGATIVE         (1 << 0) /* set if negative           */

/*
 * Initialization configuration for a single encoder
 */
typedef struct {
	uint8_t mode1;
	uint8_t mode2;
} ls7366r_init_t;

/*
 * Define these functions to automatically replace
 * the dummy functions included with this library.
 */
void _ls7366r_chip_sel( uint8_t chip_sel );
void _ls7366r_chip_desel( uint8_t chip_sel );
uint8_t _ls7366r_spi_transfer( uint8_t chip_sel, uint8_t out );

#define _LS7366R_CMD_CLEAR_MDR0        (0x08) /* clear mode register 0           */
#define _LS7366R_CMD_CLEAR_MDR1        (0x10) /* clear mode register 1           */
#define _LS7366R_CMD_CLEAR_CNTR        (0x20) /* clear data                   */
#define _LS7366R_CMD_CLEAR_STR         (0x30) /* clear status register           */

#define _LS7366R_CMD_READ_MDR0         (0x48) /* read mode register 0            */
#define _LS7366R_CMD_READ_MDR1         (0x50) /* read mode register 1            */
#define _LS7366R_CMD_READ_CNTR_OTR     (0x60) /* read data -> output register */
#define _LS7366R_CMD_READ_OTR          (0x68) /* read output register            */
#define _LS7366R_CMD_READ_STR          (0x70) /* read status register            */

#define _LS7366R_CMD_WRITE_MDR0        (0x88) /* write mode register 0           */
#define _LS7366R_CMD_WRITE_MDR1        (0x90) /* write mode register 1           */
#define _LS7366R_CMD_WRITE_DTR         (0x98) /* write data register             */

#define _LS7366R_CMD_LOAD_DTR_CNTR     (0xE0) /* load data register -> data   */
#define _LS7366R_CMD_LOAD_CNTR_OTR     (0xE8) /* load data -> output register */

/*
 * Function prototypes
 */
static __inline void      ls7366r_init( uint8_t chip_sel, const ls7366r_init_t *p_init);

static __inline uint8_t   ls7366r_get_status( uint8_t chip_sel );
static __inline void      ls7366r_clear_status( uint8_t chip_sel );

static __inline void      ls7366r_clear_counter( uint8_t chip_sel );
static __inline void      ls7366r_load_counter( uint8_t chip_sel );

static __inline void      ls7366r_set_data_1b( uint8_t chip_sel, uint8_t val );
static __inline void      ls7366r_set_data_2b( uint8_t chip_sel, uint16_t val );
static __inline void      ls7366r_set_data_3b( uint8_t chip_sel, uint32_t val );
static __inline void      ls7366r_set_data_4b( uint8_t chip_sel, uint32_t val );

static __inline uint8_t   ls7366r_get_counter_1b( uint8_t chip_sel );
static __inline uint16_t  ls7366r_get_counter_2b( uint8_t chip_sel );
static __inline uint32_t  ls7366r_get_counter_3b( uint8_t chip_sel );
static __inline uint32_t  ls7366r_get_counter_4b( uint8_t chip_sel );

static __inline uint8_t   ls7366r_get_last_counter_1b( uint8_t chip_sel );
static __inline uint16_t  ls7366r_get_last_counter_2b( uint8_t chip_sel );
static __inline uint32_t  ls7366r_get_last_counter_3b( uint8_t chip_sel );
static __inline uint32_t  ls7366r_get_last_counter_4b( uint8_t chip_sel );

/*
 * Function definitions
 */

/**
 * @brief Initializes a ls7366r
 * @param chip_sel chip selection
 * @param p_init initialization structure
 * @return none
 */
static __inline void ls7366r_init( uint8_t chip_sel, const ls7366r_init_t *p_init) {
	/* write mode 0 */
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_WRITE_MDR0);
	_ls7366r_spi_transfer(chip_sel, p_init->mode1);
	_ls7366r_chip_desel(chip_sel);

	/* write mode 1 */
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_WRITE_MDR1);
	_ls7366r_spi_transfer(chip_sel, p_init->mode2);
	_ls7366r_chip_desel(chip_sel);

	/* clear counter register */
	ls7366r_clear_counter(chip_sel);
}

/**
 * @brief Returns status
 * @param chip_sel chip selection
 * @return the status register, can be compared using the provided
 * mask, for example
 * ```C
 * if(ls7366r_get_status(0) & LS7366R_STATUS_IS_COMPARE)
 * {
 *  	// do something
 * }
 * ```
 */
static __inline uint8_t ls7366r_get_status( uint8_t chip_sel ) {
	uint8_t ret;
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_READ_STR );
	ret = _ls7366r_spi_transfer( chip_sel, 0x00 ); /* send dummy value */
	_ls7366r_chip_desel(chip_sel);
	return ret;
}

/**
 * @brief Clears the status register
 * @param chip_sel chip selection
 * @return none
 */
static __inline void ls7366r_clear_status( uint8_t chip_sel ) {
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_CLEAR_STR);
	_ls7366r_chip_desel(chip_sel);
}

/**
 * @brief Clears counter
 * @param chip_sel chip selection
 * @return none
 */
static __inline void ls7366r_clear_counter( uint8_t chip_sel ) {
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_CLEAR_CNTR);
	_ls7366r_chip_desel(chip_sel);
}

/**
 * @brief Loads data register into counter
 * @param chip_sel chip selection
 * @return none
 * @details Use @ref ls7366r_set_data_1b, @ref ls7366r_set_data_2b,
 * @ref ls7366r_set_data_3b, or @ref ls7366r_set_data_4b to first
 * load the value into the data register, then call this function
 * to load the value from the data register to the counter.
 */
static __inline void ls7366r_load_counter(uint8_t chip_sel) {
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_LOAD_DTR_CNTR);
	_ls7366r_chip_desel(chip_sel);
}

/**
 * @brief Sets the data register
 * @param chip_sel chip selection
 * @param val value to set
 * @return none
 * @brief Use these routines to set the data register so that it
 * can be used as comparison value or be loaded into the counter.
 * This function is used when the counter is configured as 1 byte.
 */
static __inline void ls7366r_set_data_1b(uint8_t chip_sel, uint8_t val) {
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_WRITE_DTR);
	_ls7366r_spi_transfer(chip_sel, val);
	_ls7366r_chip_desel(chip_sel);
}

/**
 * @brief Sets the data register
 * @param chip_sel chip selection
 * @param val value to set
 * @return none
 * @brief Use these routines to set the data register so that it
 * can be used as comparison value or be loaded into the counter.
 * This function is used when the counter is configured as 2 bytes.
 */
static __inline void ls7366r_set_data_2b(uint8_t chip_sel, uint16_t val) {
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_WRITE_DTR);
	_ls7366r_spi_transfer(chip_sel, (uint8_t)(val >> 8) );
	_ls7366r_spi_transfer(chip_sel, (uint8_t)(val & 0xFF) );
	_ls7366r_chip_desel(chip_sel);
}

/**
 * @brief Sets the data register
 * @param chip_sel chip selection
 * @param val value to set
 * @return none
 * @brief Use these routines to set the data register so that it
 * can be used as comparison value or be loaded into the counter.
 * This function is used when the counter is configured as 3 bytes.
 */
static __inline void ls7366r_set_data_3b(uint8_t chip_sel, uint32_t val) {
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_WRITE_DTR);
	_ls7366r_spi_transfer(chip_sel, (uint8_t)(val >> 16) );
	_ls7366r_spi_transfer(chip_sel, (uint8_t)(val >> 8) );
	_ls7366r_spi_transfer(chip_sel, (uint8_t)(val & 0xFF) );
	_ls7366r_chip_desel(chip_sel);
}

/**
 * @brief Sets the data register
 * @param chip_sel chip selection
 * @param val value to set
 * @return none
 * @brief Use these routines to set the data register so that it
 * can be used as comparison value or be loaded into the counter.
 * This function is used when the counter is configured as 4 bytes.
 */
static __inline void ls7366r_set_data_4b(uint8_t chip_sel, uint32_t val) {
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_WRITE_DTR);
	_ls7366r_spi_transfer(chip_sel, (uint8_t)(val >> 24) );
	_ls7366r_spi_transfer(chip_sel, (uint8_t)(val >> 16) );
	_ls7366r_spi_transfer(chip_sel, (uint8_t)(val >> 8) );
	_ls7366r_spi_transfer(chip_sel, (uint8_t)(val & 0xFF) );
	_ls7366r_chip_desel(chip_sel);
}

/**
 * @brief Gets the counter
 * @param chip_sel chip selection
 * @param val value to set
 * @return value of the counter
 * @brief This function affects the value in the output register.
 * This function is used when the counter is configured as 1 byte.
 */
static __inline uint8_t ls7366r_get_counter_1b(uint8_t chip_sel) {
	uint8_t ret = 0;
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_READ_CNTR_OTR);
	ret = _ls7366r_spi_transfer(chip_sel, 0x00); /* send dummy value */
	_ls7366r_chip_desel(chip_sel);
	return ret;
}

/**
 * @brief Gets the counter
 * @param chip_sel chip selection
 * @param val value to set
 * @return value of the counter
 * @brief This function affects the value in the output register.
 * This function is used when the counter is configured as 2 bytes.
 */
static __inline uint16_t ls7366r_get_counter_2b(uint8_t chip_sel) {
	uint16_t ret = 0;
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_READ_CNTR_OTR);
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 8;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00);
	_ls7366r_chip_desel(chip_sel);
	return ret;
}

/**
 * @brief Gets the counter
 * @param chip_sel chip selection
 * @param val value to set
 * @return value of the counter
 * @brief This function affects the value in the output register.
 * This function is used when the counter is configured as 3 bytes.
 */
static __inline uint32_t ls7366r_get_counter_3b(uint8_t chip_sel) {
	uint32_t ret = 0;
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_READ_CNTR_OTR);
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 16;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 8;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00);
	_ls7366r_chip_desel(chip_sel);
	return ret;
}

/**
 * @brief Gets the counter
 * @param chip_sel chip selection
 * @param val value to set
 * @return value of the counter
 * @brief This function affects the value in the output register.
 * This function is used when the counter is configured as 4 bytes.
 */
static __inline uint32_t ls7366r_get_counter_4b(uint8_t chip_sel) {
	uint32_t ret = 0;
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_READ_CNTR_OTR);
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 24;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 16;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 8;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00);
	_ls7366r_chip_desel(chip_sel);
	return ret;
}

/**
 * @brief Gets the output register
 * @param chip_sel chip selection
 * @param val value to set
 * @return value of the counter
 * @brief This function is used when the counter is configured as 1 byte.
 */
static __inline uint8_t ls7366r_get_last_counter_1b(uint8_t chip_sel) {
	uint8_t ret = 0;
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_READ_OTR);
	ret = _ls7366r_spi_transfer(chip_sel, 0x00); /* send dummy value */
	_ls7366r_chip_desel(chip_sel);
	return ret;
}

/**
 * @brief Gets the output register
 * @param chip_sel chip selection
 * @param val value to set
 * @return value of the counter
 * @brief This function is used when the counter is configured as 2 bytes.
 */
static __inline uint16_t ls7366r_get_last_counter_2b(uint8_t chip_sel) {
	uint16_t ret = 0;
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_READ_OTR);
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 8;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00);
	_ls7366r_chip_desel(chip_sel);
	return ret;
}

/**
 * @brief Gets the output register
 * @param chip_sel chip selection
 * @param val value to set
 * @return value of the counter
 * @brief This function is used when the counter is configured as 3 bytes.
 */
static __inline uint32_t ls7366r_get_last_counter_3b(uint8_t chip_sel) {
	uint32_t ret = 0;
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_READ_OTR);
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 16;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 8;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00);
	_ls7366r_chip_desel(chip_sel);
	return ret;
}

/**
 * @brief Gets the output register
 * @param chip_sel chip selection
 * @param val value to set
 * @return value of the counter
 * @brief This function is used when the counter is configured as 4 bytes.
 */
static __inline uint32_t ls7366r_get_last_counter_4b(uint8_t chip_sel) {
	uint32_t ret = 0;
	_ls7366r_chip_sel(chip_sel);
	_ls7366r_spi_transfer(chip_sel, _LS7366R_CMD_READ_OTR);
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 24;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 16;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00) << 8;
	ret |= _ls7366r_spi_transfer(chip_sel, 0x00);
	_ls7366r_chip_desel(chip_sel);
	return ret;
}


#endif /* HBD035405_1F1C_428A_B7E5_C6E8E9430A8B */
