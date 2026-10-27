#include "../game.hlsli"

struct vs_input {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;

	float2 i_position : I_POSITION;
	float2 i_size     : I_SIZE;
};

ps_input_pnt vs( vs_input input, uint id : SV_InstanceID ) {
	// input.position.x = input.position.x + input.i_position.x;
	// input.position.z = input.position.z + input.i_position.y;

	input.position.x = input.position.x * input.i_size.x + input.i_position.x;
	input.position.z = input.position.z * input.i_size.y + input.i_position.y;

	return projection_standard_pnt_pnt( (vs_input_pnt)input );
}

float dither( float2 position, float c ) {
	const int bayer[64] = {
		 0, 32,  8, 40,  2, 34, 10, 42,
		48, 16, 56, 24, 50, 18, 58, 26,
		12, 44,  4, 36, 14, 46,  6, 38,
		60, 28, 52, 20, 62, 30, 54, 22,
		 3, 35, 11, 43,  1, 33,  9, 41,
		51, 19, 59, 27, 49, 17, 57, 25,
		15, 47,  7, 39, 13, 45,  5, 37,
		63, 31, 55, 23, 61, 29, 53, 21
	};

	position = float2(
		int( position.x % 8 ),
		int( position.y % 8 )
	);

	float limit = 0;
	if ( position.x < 8 ) limit = ( bayer[ position.x + position.y * 8 ] + 1 ) / 64.0;
	if( c < limit ) return 0.0;
	return 1.0;
}

float srgb_to_linear( float s ) {
    float l;

    if ( s <= 0.04045 ) {
        l = s / 12.92;
    } else {
        l = pow( ( s + 0.055 ) / 1.055, 2.4 );
    }

    return l;
}

float linear_to_srgb( float l ) {
    float s;

    if ( l <= 0.0031308 ) {
        s = l * 12.92;
    } else {
        s = 1.055 * pow( l, 1.0/2.4 ) - 0.055;
    }

    return s;
}

float4 srgb( float r, float g, float b ) {
    return float4(
        srgb_to_linear( r ),
        srgb_to_linear( g ),
        srgb_to_linear( b ),
        1.0
    );
}

float4 ps( ps_input_pnt input ) : SV_TARGET {
	float4 color = texture_0.Sample( sampler_point, input.uv );

	// float2 position_screen = input.position_clip.xy / input.position_clip.w;
	// position_screen = float2( ( position_screen.x + 1 ) / 2 * screen_width, ( position_screen.y + 1 ) / 2 * screen_height ); // todo

	float d = get_depth( input.position );

	// d = 1 - d;
	float m = 0.5;
	if ( d > m ) d = 1;
	if ( d < m ) d = d / m;
	// d = 1 - d;

	d = 1 - d;
	d = d * d;
	d = 1 - d;

	// d = 1 - d;
	// d = d * d * d;
	// d = 1 - d;

	// float ratio = 1; // was 8
	// d = dither( position_screen / ratio, d );
	// color = float4( color.xyz * d, 1 );

	// d = dither( position_screen, d * color.x );
	// color = float4( float3( 255 / 255, 85.0 / 255, 82.0 / 255 ) * d, 1 );

	return color;
}

float4 ps_normal( ps_input_pnt input ) : SV_TARGET {
	float3 normal = normalize( input.normal_view );
	return normal_to_color( normal );
}

float4 ps_depth( ps_input_pnt input ) : SV_Target {
	return depth_to_color( input.position );
}
