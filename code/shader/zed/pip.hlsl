#include "../game.hlsli"

ps_input_svp vs( uint id : SV_VertexID ) {
	ps_input_svp output;

	output.position.x = (float)( id / 2 ) * 4.0 - 1.0;
	output.position.y = (float)( id % 2 ) * 4.0 - 1.0;
	output.position.zw = 1.0;

	return output;
}

struct ps_output_canvas {
	float4 color : SV_TARGET;
	float  depth : SV_DEPTH;
};

ps_output_canvas ps( ps_input_svp input )  {
	ps_output_canvas output;

	float2 uv = float2( input.position.x - 116, input.position.y - 98 ) / float2( 320, 240 );
	output.color = texture_0.Sample( sampler_point, uv );
	output.depth = texture_1.Sample( sampler_point, uv ).x;

	return output;
}
