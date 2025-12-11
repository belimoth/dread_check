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
	input.normal_world = normalize( input.normal_world );
	input.normal_view  = normalize( input.normal_view  );

	//

	float3 color = light_ambient_1( input.normal_world, float3( 0.5, 0.5, 0.6 ) );

	//

	float3 ray = normalize( input.position_world.xyz - camera.camera_position.xyz ).xyz;
	float3 sun = { 0, 0, -1 };
	color = float3( fog_3( color.xyz, -input.position_view.z, ray, sun ) );

	//

	return float4( color.xyz, 1 * alpha );
}
