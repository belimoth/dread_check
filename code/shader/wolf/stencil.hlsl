#include "../game.hlsli"

ps_input_svp vs( uint id : SV_VertexID ) {
	ps_input_svp output;

	output.position.x = (float)( id / 2 ) * 4.0 - 1.0;
	output.position.y = (float)( id % 2 ) * 4.0 - 1.0;
	output.position.zw = 1.0;

	return output;
}

float4 ps( ps_input_svp input ) : SV_TARGET {
	float depth = texture_0.Sample( sampler_point, input.position.xy / float2( screen_width / 4, screen_height / 4 ) ).x;
	depth = sqrt( sqrt( depth ) );
	float far  = 1000;
	float near = 0.01;
	// depth = 1 - depth;
	// depth = near * far / ( far + depth * ( near - far ) );
	// depth = ( 2 * near ) / ( far + near - depth * ( far - near ) );
	return float4( depth, depth, depth, 1 );
}
