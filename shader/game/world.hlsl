#include "../game.hlsli"

struct vs_input_pntix {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;

	float3 i_position : I_POSITION;
};

ps_input_pnt vs( vs_input_pntix input, uint id : SV_InstanceID ) {
	input.position.x += input.i_position.x;
	input.position.y *= input.i_position.z; // note
	input.position.z += input.i_position.y;

	return projection_standard_pnt_pnt( (vs_input_pnt)input );
}

ps_standard_imp;
