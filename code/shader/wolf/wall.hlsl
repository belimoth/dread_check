#include "../game.hlsli"

struct vs_input_wolf {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;
	uint   i_tile   : I_TILE;
};

ps_input_pnt vs( vs_input_wolf input, uint id : SV_InstanceID ) {
	input.position.x += id % 64;
	input.position.z += ( id - ( id % 64 ) ) / 64;

	// floor
	if ( input.i_tile > 105 ) { input.position = float3( 0, 0, 0 ); }
	// door
	else if ( input.i_tile > 53 ) { input.position = float3( 0, 0, 0 ); }
	// secret door
	else if ( input.i_tile == 98 ) { input.position = float3( 0, 0, 0 ); }
	// wall
	else {}

	//

	// fixes samples from outside uv range without padding
	float e = 0.000018;
	// todo should be 1 - instead of 2 -, interacts badly with day/night uv implementation
	input.uv.x = clamp( input.uv.x, e, 2 - 2 * e );
	input.uv.y = clamp( input.uv.y, e, 1 - 2 * e );

	//

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

float4 ps_normal( ps_input_pnt input ) : SV_TARGET {
	float3 normal = normalize( input.normal_view );
	return normal_to_color( normal );
}

float4 ps_depth( ps_input_pnt input ) : SV_Target {
	return depth_to_color( input.position );
}
