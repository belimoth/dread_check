#include "../game.hlsli"

struct vs_input_face {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;
	uint   i_tile   : I_TILE;
};


ps_input_pnt vs( vs_input_face input ) {
	ps_input_pnt output;

	// projection

	float4 position_model = float4( input.position, 1.0 );
	float4 position_world = mul( position_model, matrix_world );

	output.position_world = position_world;
	output.position_view  = position_world;
	output.position_clip  = position_world;
	output.position       = position_world;

	//

	float3 normal_model = input.normal;
	float3 normal_world = mul( normal_model, (float3x3)matrix_world       );
	float3 normal_view  = mul( normal_world, (float3x3)camera.matrix_view );

	output.normal_world = normalize( normal_world );
	output.normal_view  = normalize( normal_view  );

	//

	float u = input.i_tile % 15;
	float v = ( input.i_tile - u ) / 15;
	input.uv.x = ( input.uv.x + u ) / 15;
	input.uv.y = ( input.uv.y + v ) / 10;

	output.uv = input.uv;

	//

	return output;
}

float4 ps( ps_input_pnt input ) : SV_TARGET {
	float4 color = texture_0.Sample( sampler_point, input.uv );
	return color;
}
