#include "../game.hlsli"

struct vs_input {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;

	float2 i_position : I_POSITION;
};

ps_input_pnt vs( vs_input input, uint id : SV_InstanceID ) {
	input.position.x = input.position.x + input.i_position.x;
	input.position.z = input.position.z + input.i_position.y;
	return projection_standard_pnt_pnt( (vs_input_pnt)input );
}


float4 ps( ps_input_pnt input ) : SV_TARGET {
	float3 color = float3( 84, 252, 84 ) / 255;
	return float4( color.xyz, 1 );
}

float4 ps_normal( ps_input_pnt input ) : SV_TARGET {
	float3 normal = normalize( input.normal_view );
	return normal_to_color( normal );
}

float4 ps_depth( ps_input_pnt input ) : SV_Target {
	return depth_to_color( input.position );
}
