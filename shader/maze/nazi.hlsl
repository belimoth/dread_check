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

float4 ps( ps_input_pnt input ) : SV_TARGET {
	input.normal_world = normalize( input.normal_world );
	// input.normal_world = float3( sign( input.normal_world ) );

	//

	float3 albedo = float3( 1, 1, 1 );
	float3 color  = albedo * light_ambient_1( input.normal_world, float3( 1, 1, 1 ) );

	//

	if ( color.x > 0.4 ) color = float3( 252, 252, 84 ) / 255; else color = float3( 0, 0, 0 );

	//

	for ( int i = 0; i < 8; i++ ) {
		color += albedo * light_point  ( light.light_point  [i], input.position_world.xyz, input.normal_world );
		color += albedo * light_capsule( light.light_capsule[i], input.position_world.xyz, input.normal_world );
	}

	//

	if ( color.z > 0.4 ) color = float3( 1, 1, 1 ); else if ( color.x <= 0.4 ) color = float3( 0, 0, 0 );

	//

	return float4( color.xyz, 1 * alpha );
}
