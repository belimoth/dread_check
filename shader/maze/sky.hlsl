#include "../game.hlsli"

struct ps_input {
	float4 position : SV_POSITION;
	float3 uvw      : POSITION;
};

ps_input vs( uint id : SV_VertexID ) {
	ps_input output;

	if ( id == 0 ) { output.position = float4( -1.0,  1.0,  0.5,  1.0 ); }
	if ( id == 1 ) { output.position = float4(  3.0,  1.0,  0.5,  1.0 ); }
	if ( id == 2 ) { output.position = float4( -1.0, -3.0,  0.5,  1.0 ); }

	output.position = mul( output.position, camera.matrix_iwvc );

	output.position = mul( output.position,       matrix_world );

	output.uvw = output.position.xyz;

	output.position = mul( output.position, camera.matrix_view  );
	output.position = mul( output.position, camera.matrix_clip  );

	output.position.z = 0.0;

	return output;
}

ps_input f( ps_input input ) {
	float s = sin( 1 / 2 * 3.1415927 );
	float c = cos( 1 / 2 * 3.1415927 );

	matrix m = {
		1,  0,  0,  0,
		0,  c, -s,  0,
		0,  s,  c,  0,
		0,  0,  0,  1,
	};

	input.uvw = mul( float4( input.uvw, 1 ), m ).xyz;

	return input;
}

float4 ps( ps_input input ) : SV_TARGET {
	input = f( input );

	float3 color;
	color = float3( 170, 170, 170 ) / 255;
	if ( input.uvw.y > 0 ) color = float3( 0, 0, 170 ) / 255;

	return float4( color.xyz, 1 );
}

float4 ps_normal( ps_input input ) : SV_TARGET {
	input = f( input );

	float3 normal;
	normal = float3( 0, 1, 0 );
	if ( input.uvw.y > 0 ) normal = float3( 0, -1, 0 );
	normal = normalize( mul( normal, (float3x3)camera.matrix_view ) );

	return normal_to_color( normal );
}

float4 ps_depth( ps_input input ) : SV_TARGET {
	input = f( input );

	return depth_to_color( input.position );
}
