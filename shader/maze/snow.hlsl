#include "../game.hlsli"

struct vs_input {
	float3 i_position : I_POSITION;
};

struct gs_input {
	float3 position : POSITION;
};

struct ps_input {
	float4 position : SV_POSITION;
};


gs_input vs( vs_input input ) {
	vs_input_p input_p;
	input_p.position = input.i_position;
	gs_input output;
	output.position = projection_standard_p_p( input_p ).position.xyz;
	return output;
}

[maxvertexcount(4)]
void gs( point gs_input input[1], inout TriangleStream<ps_input> stream, uint id : SV_PrimitiveID ) {
	ps_input output;

	float x0 = input[0].position.x;
	float y0 = input[0].position.y;
	float z  = input[0].position.z;
	float y1 = y0 + 0.1;
	float x1 = x0 + 0.1;

	output.position = float4( 0, 0, z, 1 );

	output.position.x = x1;
	output.position.y = y0;
	stream.Append( output );

//	output.position.x = x1;
	output.position.y = y1;
	stream.Append( output );

	output.position.x = x0;
	output.position.y = y0;
	stream.Append( output );

//	output.position.x = x0;
	output.position.y = y1;
	stream.Append( output );

	stream.RestartStrip();
}

float4 ps( ps_input input ) : SV_TARGET {
	return float4( 1, 1, 1, 1 );
}

float4 ps_normal( ps_input input ) : SV_TARGET {
	return depth_to_color( input.position );
}

// float4 ps_depth( ps_input input ) : SV_TARGET {
// 	float3 normal = normalize( input.normal_view );
// 	return normal_to_color( normal );
// }
