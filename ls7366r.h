/* ******************************************************
 * @file ls7366r.h
 * @brief LS7366R SPI encoder interface driver
 *
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
 * Counter modes
 *
 * FREERUN   : free runnning
 * SINGLE    : single cycle count mode, disabled upon carry/borrow, enabled by reset or load
 * RANGELIMIT: saturates to DTR or 0
 * MODULON   : modulo-n counting mode, input clock divided by (DTR+1)
 */
#define LS7366R_MODE1_COUNTER_FREERUN        (0 << 2) /* free-running count mode */
#define LS7366R_MODE1_COUNTER_SINGLE         (1 << 2) /* single-cycle count mode */
#define LS7366R_MODE1_COUNTER_RANGELIMIT     (2 << 2) /* range-limit count mode  */
#define LS7366R_MODE1_COUNTER_MODULON        (3 << 2) /* modulo-n count mode     */

/*
 * Index modes
 *
 * DISABLE      : disable index
 * LOAD_COUNTER : transfers DTR to CNTR upon index
 * RESET_COUNTER: clears CNTR upon index
 * LOAD_OTR     : transfers CNTR to OTR upon index
 */
#define LS7366R_MODE1_INDEX_DISABLE          (0 << 4) /* disable index */
#define LS7366R_MODE1_INDEX_LOAD_COUNTER     (1 << 4) /* reset CNTR    */
#define LS7366R_MODE1_INDEX_RESET_COUNTER    (2 << 4) /* reset CNTR    */
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
 * Counter length modes
 *
 * 1B: 8-bit counter
 * 2B: 16-bit counter
 * 3B: 24-bit counter
 * 4B: 32-bit counter
 */
#define LS7366R_MODE2_CTRLEN_4B      (0 << 0) /* 4 byte counter mode */
#define LS7366R_MODE2_CTRLEN_3B      (1 << 0) /* 3 byte counter mode */
#define LS7366R_MODE2_CTRLEN_2B      (2 << 0) /* 2 byte counter mode */
#define LS7366R_MODE2_CTRLEN_1B      (3 << 0) /* 1 byte counter mode */

/*
 * Counter enable
 *
 * ENABLE : enable counting
 * DISABLE: disable counting
 */
#define LS7366R_MODE2_CTR_ENABLE     (0 << 2) /* enable counter  */
#define LS7366R_MODE2_CTR_DISABLE    (1 << 2) /* disable counter */

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



#endif /* HBD035405_1F1C_428A_B7E5_C6E8E9430A8B */
