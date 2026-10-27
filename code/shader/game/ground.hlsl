#include "../game.hlsli"

#include "main-ps.hlsli"

struct vs_input_pnt {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;
};

ps_input vs( vs_input_pnt input ) {
	ps_input output;

	//

	float3 normal_model = input.normal;
	float3 normal_world = mul( normal_model, (float3x3)matrix_world );
	// float3 normal_view  = mul( normal_model, (float3x3)camera.matrix_view );

	float3 normal_view  = mul( normal_model, (float3x3)camera.matrix_tiwv );

	// output.normal_model = normalize( input.normal );
	output.normal_world = normalize( normal_world );
	output.normal_view  = normalize( normal_view  );

	output.uv = input.uv;

	return output;
}
