/* ******************************************************
 * @file encoders.c
 * @brief Robot arm encoders driver file
 * Created Nov 7 2018
 *
 * Modify this file as needed
 *
 * Contributors:
 * 		John Yu
 ********************************************************/
#include <string.h>
#include "encoders.h"
#include "ls7366r.h"

struct {

	/* polling frequency */
	ENCODERS_FREQUENCY_TYPE poll_frequency;

	/* absolute position since power-up */
	encoders_array_degrees_t position_absolute;

	/* reference position */
	encoders_array_degrees_t position_reference;

	/* degrees per 1000 tick */
	encoders_array_degrees_t degrees_per_1000_tick;

	/* speed in degrees per second */
	encoders_array_degrees_t speed;
} state;

const ls7366r_init_t encoder_config =
{
		/* mode 1 */
		LS7366R_MODE1_QUAD_X1 |
		LS7366R_MODE1_COUNTER_FREERUN |
		LS7366R_MODE1_INDEX_DISABLE |
		LS7366R_MODE1_FCLK_DIV1,

		/* mode 2 */
		LS7366R_MODE2_CTRLEN_4B |
		LS7366R_MODE2_CTR_ENABLE |
		LS7366R_MODE2_FLAG_NONE
};

void encoders_init( const encoders_init_t *p_init )
{
	uint8_t counter;

	_encoders_lock_global();
	state.poll_frequency = p_init->poll_frequency;

	memset( &state.position_absolute, 0, sizeof(encoders_array_degrees_t) );

	memset( &state.speed, 0, sizeof(encoders_array_degrees_t) );

	memcpy( &state.position_reference, p_init->p_position_ref,
			sizeof(encoders_array_degrees_t) );

	memcpy( &state.degrees_per_1000_tick, p_init->p_degrees_per_1000_tick,
			sizeof(encoders_array_degrees_t));

	_encoders_unlock_global();

	for( counter = 0; counter < ENCODERS_NUM_JOINTS; counter++ )
		ls7366r_init(counter, &encoder_config);
}

void encoders_get_speed( encoders_array_degrees_t *p_speed )
{
	_encoders_lock_global();
	memcpy( p_speed, &state.speed, sizeof(encoders_array_degrees_t) );
	_encoders_unlock_global();
}

void encoders_get_position_abs( encoders_array_degrees_t *p_pos )
{
	_encoders_lock_global();
	memcpy( p_pos, &state.position_absolute, sizeof(encoders_array_degrees_t) );
	_encoders_unlock_global();
}

void encoders_get_position_rel( encoders_array_degrees_t *p_pos )
{
	uint8_t counter = 0;

	_encoders_lock_global();
	for( counter = 0; counter < ENCODERS_NUM_JOINTS; counter++ )
	{
		p_pos->val[counter] = state.position_absolute.val[counter] -
				state.position_reference.val[counter];
	}
	_encoders_unlock_global();
}

void encoders_set_position_ref( const encoders_array_degrees_t *p_ref )
{
	_encoders_lock_global();
	memcpy( &state.position_reference, p_ref, sizeof(encoders_array_degrees_t));
	_encoders_unlock_global();
}

void encoders_poll(void)
{
	ENCODERS_DEGREE_TYPE temp;
	uint32_t ticks[ENCODERS_NUM_JOINTS];
	uint8_t counter;

	/*
	 * read-in raw ticks first, buffer locally without
	 * locking globals because ls7366r function is assumed
	 * to be slow
	 */
	for( counter = 0; counter < ENCODERS_NUM_JOINTS; counter++ )
	{
		ticks[counter] = ls7366r_get_counter_4b(counter);
	}

	_encoders_lock_global();
	for( counter = 0; counter < ENCODERS_NUM_JOINTS; counter++ )
	{
		temp = ticks[counter] / 1000 * state.degrees_per_1000_tick.val[counter];

		state.speed.val[counter] = (temp - state.position_absolute.val[counter]) *
				state.poll_frequency;

		state.position_absolute.val[counter] = temp;
	}
	_encoders_unlock_global();
}

/*
 * Dummy functions
 */
__attribute__((weak))
void _encoders_lock_global( void )
{
	return;
}

__attribute__((weak))
void _encoders_unlock_global( void )
{
	return;
}
