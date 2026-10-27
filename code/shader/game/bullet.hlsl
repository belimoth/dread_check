#include "../game.hlsli"

struct vs_input_pntix {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;

	matrix i_matrix   : I_MATRIX;
	float3 i_position : I_POSITION;
	float3 i_rotation : I_ROTATION;
	float3 i_color    : I_COLOR;
};

ps_input_pnt vs( vs_input_pntix input, uint id : SV_InstanceID ) {
	input.position = mul( float4( input.position, 1.0 ), input.i_matrix ).xyz;
	return projection_standard_pnt_pnt( (vs_input_pnt)input );
}

float4 ps( ps_input_pnt input ) : SV_TARGET {
	float3 ray = normalize( input.position_world.xyz - camera.camera_position.xyz ).xyz;
	float3 sun = { 0, 0, -1 };
	float3 color = { 1, 1, 1 };
	color = fog_1( color, -input.position_view.z, ray, sun );
	return float4( color.xyz, 1 );
}
