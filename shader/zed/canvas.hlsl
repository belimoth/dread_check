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

float3 rgb_to_lms( float3 rgb ) {
	return float3(
		17.8824f    * rgb.x + 43.5161f   * rgb.y + 4.11935f * rgb.z,
		 3.45565f   * rgb.x + 27.1554f   * rgb.y + 3.86714f * rgb.z,
		 0.0299566f * rgb.x +  0.184309f * rgb.y + 1.46709f * rgb.z
	);
}

float3 lms_to_rgb( float3 lms ) {
	return float3(
		 0.0809444479f   * lms.x + -0.130504409f   * lms.y +  0.116721066f * lms.z,
		-0.0102485335f   * lms.x +  0.0540193266f  * lms.y + -0.113614708f * lms.z,
		-0.000365296938f * lms.x + -0.00412161469f * lms.y +  0.693511405f * lms.z
	);
}

float3 daltonize( float3 color ) {
	if ( vision_mode == vision_mode_none ) return color;
	color = rgb_to_lms( color );
	float3 lms = float3( 0, 0, 0 );

	switch ( vision_mode ) {
		case vision_mode_protanope:
		lms.x = 0 * color.x + 2.02344f * color.y + -2.52581f * color.z;
		lms.y = 0 * color.x + 1        * color.y +  0        * color.z;
		lms.z = 0 * color.x + 0        * color.y +  1        * color.z;
		break;

		case vision_mode_deuteranope:
		lms.x = 1         * color.x + 0 * color.y + 0        * color.z;
		lms.y = 0.494207f * color.x + 0 * color.y + 1.24827f * color.z;
		lms.z = 0         * color.x + 0 * color.y + 1        * color.z;
		break;

		case vision_mode_tritanope:
		lms.x =  1         * color.x + 0         * color.y + 0 * color.z;
		lms.y =  0         * color.x + 1         * color.y + 0 * color.z;
		lms.z = -0.395913f * color.x + 0.801109f * color.y + 0 * color.z;
		break;
	}

	return lms_to_rgb( lms );
}

ps_output_canvas ps( ps_input_svp input )  {
	ps_output_canvas output;

	float2 uv = float2( input.position.x, input.position.y ) / float2( screen_width, screen_height );
	output.color = texture_0.Sample( sampler_point, uv );
	output.depth = texture_1.Sample( sampler_point, uv ).x;

	output.color.xyz = daltonize( output.color.xyz );

	return output;
}
