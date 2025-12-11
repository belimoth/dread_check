#include "../game.hlsli"

struct vs_input_pc {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;
};

// struct ps_input_pc {
// 	float4 position : SV_POSITION;
// 	float2 uv       : TEXCOORD;
// };

ps_input_pnt vs( vs_input_pc input ) {
	return projection_standard_pnt_pnt( (vs_input_pnt)input );
}

float4 ps( ps_input_pnt input ) : SV_TARGET {
	return texture_0.Sample( sampler_point, input.uv );
}
