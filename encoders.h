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

typedef struct {
	/* position reference in degrees */
	ENCODERS_DEGREE_TYPE position_ref[ENCODERS_NUM_JOINTS];
} encoders_position_ref_t;

typedef struct {
	/* polling frequency in Hz */
	ENCODERS_FREQUENCY_TYPE poll_frequency;

	/* degrees per tick for each joint */
	ENCODERS_DEGREE_TYPE degrees_per_tick[ENCODERS_NUM_JOINTS];

	/* initial assumption of position */
	encoders_position_ref_t position_ref;
} encoders_init_t;

typedef struct {
	/* relative position to the position reference */
	ENCODERS_DEGREE_TYPE relative_position[ENCODERS_NUM_JOINTS];

	/* speed in degrees per second */
	ENCODERS_DEGREE_TYPE speed[ENCODERS_NUM_JOINTS];
} encoders_state_t;

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
 * @brief Obtains information of encoders
 * @param p_state pointer to a writable struct
 * @return none
 * @note This function is thread safe.
 */
void encoders_get_last_state( encoders_state_t *p_state );

/**
 * @brief Changes position reference in runtime
 * @param p_ref position reference
 * @return none
 * @note This function is thread safe.
 */
void encoders_set_position_ref( const encoders_position_ref_t *p_ref );

/**
 * @brief Polls the encoder
 * @return none
 * @details Must be called periodically with the
 * frequency specified in the config to work properly
 * @note This function is thread-safe.
 */
void encoders_poll(void);

#endif /* H432AD0B7_77AE_494F_92B0_A8D8E4687562 */
