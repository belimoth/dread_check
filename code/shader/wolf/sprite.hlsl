#include "../game.hlsli"

struct vs_input_wolf_sprite {
	float3 position   : POSITION;
	float3 normal     : NORMAL;
	float2 uv         : TEXCOORD;
	float3 i_position : I_POSITION;
	uint   i_tile     : I_TILE;
};

ps_input_pnt vs( vs_input_wolf_sprite input ) {
	input.uv.x += input.i_tile % 8;
	input.uv.y += ( input.i_tile - ( input.i_tile % 8 ) ) / 8;
	input.uv = input.uv / 8;

	return projection_standard_pnt_pnt( (vs_input_pnt)input, input.i_position, 2.4384 );
}

float4 ps( ps_input_pnt input ) : SV_TARGET {
	float4 color = texture_0.Sample( sampler_point, input.uv );
	if ( color.w == 0 ) discard;

	//

	return color;
}

float4 ps_normal( ps_input_pnt input ) : SV_TARGET {
	float4 color = texture_0.Sample( sampler_point, input.uv );
	if ( color.w == 0 ) discard;

	//

	return depth_to_color( input.position );
}

float4 ps_depth( ps_input_pnt input ) : SV_TARGET {
	float4 color = texture_0.Sample( sampler_point, input.uv );
	if ( color.w == 0 ) discard;

	//

	float3 normal = normalize( input.normal_view );
	return normal_to_color( normal );
}
