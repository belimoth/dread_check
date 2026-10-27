#pragma once

#include <zed/xmath.h>

uint vtoh( float3 v ) {
	return (
		( (uint8_t)floor( v.x * 255 ) << 16 ) |
		( (uint8_t)floor( v.y * 255 ) <<  8 ) |
		( (uint8_t)floor( v.z * 255 )       )
	);
}

void htoh( char *string, uint rgb ) {
	sprintf( string, "%06x", rgb );
}

float4 htov( string string ) {
	if ( string[0] == '#' ) string++;

	int r, g, b;
	sscanf( string, "%02x%02x%02x", &r, &g, &b );
	return { (float)r / 255, (float)g / 255, (float)b / 255, 1 };
}

float4 htov( uint rgb ) {
	return float4(
		float( ( rgb >> 16 ) & 0xff ) / 255,
		float( ( rgb >>  8 ) & 0xff ) / 255,
		float( ( rgb       ) & 0xff ) / 255,
		1
	);
}

// todo

// constexpr float4 htov( const uint h ) {
// 	return
// }

// constexpr xm_float4 COLOR_HEX( string text ) {
// 	return
// }
