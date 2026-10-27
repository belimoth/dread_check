#include "../game.hlsli"

struct vs_input_wolf_enemy {
	float3 position   : POSITION;
	float3 normal     : NORMAL;
	float2 uv         : TEXCOORD;
	float3 i_position : I_POSITION;
	uint   i_tile     : I_TILE;
	uint   i_face     : I_FACE;
	uint   i_frame    : I_FRAME;
};

ps_input_pnt vs( vs_input_wolf_enemy input ) {
	uint i = ( 16 - input.i_face ) % 8 + input.i_frame * 8;
	input.uv.x += i % 8;
	input.uv.y += ( i - ( i % 8 ) ) / 8;
	input.uv = input.uv / 8;

	return projection_standard_pnt_pnt( (vs_input_pnt)input, input.i_position, 2.4384 );
}

float4 ps( ps_input_pnt input ) : SV_TARGET {
	float4 color = texture_0.Sample( sampler_point, input.uv );
	if ( color.w == 0 ) discard;
	return color;
}
