#include "../game.hlsli"

TextureCube texture_cube : register(t0);

struct ps_input {
	float4 position : SV_POSITION;
	float3 normal   : NORMAL;
	float3 uvw      : TEXCOORD;
};

ps_input vs( uint id : SV_VertexID ) {
	ps_input output;

	// todo something broke to need these *2s

	if ( id == 0 ) { output.position = float4( -1 * 2,  1 * 2,  0.5,  1 ); }
	if ( id == 1 ) { output.position = float4(  3 * 2,  1 * 2,  0.5,  1 ); }
	if ( id == 2 ) { output.position = float4( -1 * 2, -3 * 2,  0.5,  1 ); }

	// todo
	output.position = mul( output.position, camera.matrix_iwvc );

	output.position = mul( output.position,       matrix_world );

	output.uvw = output.position.xyz;

	output.position = mul( output.position, camera.matrix_view );

	// todo, wrong
	output.normal = -output.position.xyz;

	output.position = mul( output.position, camera.matrix_clip );

	output.position.z = 0.0;

	return output;
}

float4 ps( ps_input input ) : SV_TARGET {
	float s = sin( 1 / 2 * 3.1415927 );
	float c = cos( 1 / 2 * 3.1415927 );

	matrix m = {
		1,  0,  0,  0,
		0,  c, -s,  0,
		0,  s,  c,  0,
		0,  0,  0,  1,
	};

	input.uvw = mul( float4( input.uvw, 1 ), m ).xyz;

	return texture_cube.Sample( sampler_point, input.uvw );
}

float4 ps_normal( ps_input input ) : SV_TARGET {
	float3 normal = normalize( input.normal );
	return normal_to_color( normal );
}

float4 ps_depth( ps_input input ) : SV_TARGET {
	return float4( 0, 0, 0, 0 );
}
