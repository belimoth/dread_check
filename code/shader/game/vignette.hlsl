#include "../game.hlsli"

struct ps_input {
	float4 position_world : POSITION0;
	float4 position_view  : POSITION1;
	float4 position_clip  : POSITION2;
	float4 position : SV_POSITION;
};

ps_input vs( uint id : SV_VertexID ) {
	ps_input output;

	// todo move this into a function

	if ( id == 0 ) { output.position = float4( -1.0,  1.0,  0.5,  1.0 ); }
	if ( id == 1 ) { output.position = float4(  3.0,  1.0,  0.5,  1.0 ); }
	if ( id == 2 ) { output.position = float4( -1.0, -3.0,  0.5,  1.0 ); }

	output.position = mul( output.position, camera.matrix_iwvc );

	//

	output.position = mul( output.position, matrix_world );
	output.position_world = output.position;

	output.position = mul( output.position, camera.matrix_view  );
	output.position_view  = output.position;

	output.position = mul( output.position, camera.matrix_clip  );
	output.position_clip  = output.position;

	output.position.z = 0.0;

	return output;
}

static const float size = 0.2;

float4 ps( ps_input input ) : SV_TARGET {
	float2 uv = input.position_view.xy;

	float roundness    = vignette.roundness;
	float radius_min   = vignette.radius_min;
	float radius_max   = vignette.radius_max;
	float aspect_ratio = vignette.aspect_ratio;

	// Calculate distance
	float2 squareDist = abs( uv );

	// Make vignette more circular
	if( roundness > 0 ) squareDist.x *= 1 + ( aspect_ratio - 1 ) * ( roundness );

	// Calculate ellipse vignette
	float ellipseDist = length( squareDist );
	float ellipseMask = smoothstep( radius_min, radius_max, ellipseDist );

	// Start calculating the vignette mask
	float mask = ellipseMask;

	// Check if roundness should go to square
	if( roundness < 0 ) {
		// Calculate square vignette
		float absRoundness = abs( roundness );
		float squaredMask = smoothstep( radius_min, radius_max, squareDist.x );
		squaredMask += smoothstep( radius_min, radius_max, squareDist.y );

		// Interpolate between round and square vignette based on roundness
		mask = lerp(ellipseMask, squaredMask, absRoundness);
	}

	mask = saturate(mask);

	float c = 0;
	float4 color;

	// c = squareDist.x;
	// c = squareDist.y;
	// c = ellipseDist;
	c = 1.0 - mask;

	// color = float4( input.position_view.xy, 0.0, 1.0 );
	// color = float4( squareDist.x, squareDist.y, 0, 1.0 );
	color = float4( vignette.color.xyz, 1.0 - c );

	return color;
}
