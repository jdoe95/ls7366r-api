/* ******************************************************
 * @file encoders.h
 * @brief Robot arm encoders driver file
 * Created Nov 7 2018
 *
 * Modify this file as needed
 *
 * Contributors:
 * 		John Yu
 ********************************************************/

#ifndef H432AD0B7_77AE_494F_92B0_A8D8E4687562
#define H432AD0B7_77AE_494F_92B0_A8D8E4687562

#include <stdint.h>

/*
 * Number of joints
 */
#define ENCODERS_NUM_JOINTS (6)

/*
 * Types
 */
#define ENCODERS_DEGREE_TYPE 		float
#define ENCODERS_FREQUENCY_TYPE 	float

/*
 * Array of encoder degrees
 */
typedef struct {
	ENCODERS_DEGREE_TYPE val[ENCODERS_NUM_JOINTS];
} encoders_array_degrees_t;

typedef struct {
	/* polling frequency in Hz */
	ENCODERS_FREQUENCY_TYPE poll_frequency;

	/* degrees per 1000 tick for each joint */
	const encoders_array_degrees_t *p_degrees_per_1000_tick;

	/* initial assumption of position */
	const encoders_array_degrees_t *p_position_ref;
} encoders_init_t;

/*
 * Define these functions to replace the dummy
 * provided with this library.
 */
void _encoders_lock_global( void );
void _encoders_unlock_global( void );

/**
 * @brief Initializes encoder interfaces
 * @param p_init pointer to initialization routines
 * @return none
 * @note This function is thread safe.
 */
void encoders_init( const encoders_init_t *p_init );

/**
 * @brief Obtains speed information of encoders
 * @param p_speed pointer to a writable struct
 * @return none
 * @note This function is thread safe.
 */
void encoders_get_speed( encoders_array_degrees_t *p_speed );

/**
 * @brief Obtains absolute position (since power-up) of encoders
 * @param p_speed pointer to a writable struct
 * @return none
 * @note This function is thread safe.
 */
void encoders_get_position_abs( encoders_array_degrees_t *p_pos );

/**
 * @brief Obtains relative position of encoders
 * @param p_speed pointer to a writable struct
 * @return none
 * @note This function is thread safe.
 */
void encoders_get_position_rel( encoders_array_degrees_t *p_pos );

/**
 * @brief Changes position reference in runtime
 * @param p_ref position reference
 * @return none
 * @note This function is thread safe.
 */
void encoders_set_position_ref( const encoders_array_degrees_t *p_ref );

/**
 * @brief Polls the encoder
 * @return none
 * @details Must be called periodically with the
 * frequency specified in the config to work properly
 * @note This function is thread-safe.
 */
void encoders_poll(void);

#endif /* H432AD0B7_77AE_494F_92B0_A8D8E4687562 */
