#include "../game.hlsli"

struct vs_input_pntix {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;

	float2 i_position : I_POSITION;
	float  i_rotation : I_ROTATION;
	float3 i_color    : I_COLOR;
};

ps_input_pnt vs( vs_input_pntix input, uint id : SV_InstanceID ) {
	input.position.x += input.i_position.x;
	input.position.z += input.i_position.y;
	return projection_standard_pnt_pnt( (vs_input_pnt)input );
}

float4 ps( ps_input_pnt input ) : SV_TARGET { return float4( 1, 1, 1, 1 ); }
