#pragma once

#include <zed.h>

#pragma warning( push )
#pragma warning( disable : 4146 )
#include "../local/vend/source/pcg/pcg_basic.c"
#pragma warning( pop )

pcg32_random_t rng;

void zed_random_seed( uint x, uint y = 0 ) {
	pcg32_srandom_r( &rng, x, y );
}

uint zed_random_get() {
	return pcg32_random_r( &rng );
}

int zed_random_get( int lower, int upper ) {
	return (int)pcg32_boundedrand_r( &rng, (uint)( upper + 1 - lower ) ) + lower;
}

float zed_random_get_float( float lower = 0, float upper = 1 ) {
	return ldexp( pcg32_random_r( &rng ), -32 ) * ( nextafter( upper, upper + 1 ) - lower ) + lower;
}
