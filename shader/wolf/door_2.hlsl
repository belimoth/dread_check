#include "../game.hlsli"
#include "../wolf.hlsli"

ps_input_pnt vs( vs_input_wolf input, uint id : SV_InstanceID ) {
	input.position.z += 0.5;
	input.position.x += input.t;

	// floor
	if ( input.i_tile > 105 ) { 	input.position = float3( 0, 0, 0 ); }

	// secret door
	else if ( input.i_tile == 98 ) {

	}

	// door
	else if ( input.i_tile > 53 ) { input.position = float3( 0, 0, 0 ); }

	// wall
	else { 	input.position = float3( 0, 0, 0 ); }

	//

	input.position.x += id % 64;
	input.position.z += ( id - ( id % 64 ) ) / 64;

	//

	// floor
	if ( input.i_tile > 105 ) { input.position = float3( 0, 0, 0 ); }

	// door
	else if ( input.i_tile > 53 ) { input.position = float3( 0, 0, 0 ); }

	// wall
	else { input.position = float3( 0, 0, 0 ); }

	//

	// fixes samples from outside uv range without padding
	float e = 0.000018;

	input.uv.x = clamp( input.uv.x, e, 2 - 2 * e );
	input.uv.y = clamp( input.uv.y, e, 1 - 2 * e );

	input.i_tile = ( input.i_tile - 1 ) * 2; // day and night
	float u = input.i_tile % 16;
	float v = ( input.i_tile - u ) / 16;
	input.uv.x = ( input.uv.x + u ) / 16;
	input.uv.y = ( input.uv.y + v ) / 16;

	//

	ps_input_pnt output = projection_standard_pnt_pnt( (vs_input_pnt)input );
	return output;
}

float4 ps( ps_input_pnt input ) : SV_TARGET {
	return texture_0.Sample( sampler_point, input.uv );
}
