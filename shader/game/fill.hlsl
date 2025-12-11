#include "../game.hlsli"

ps_input_p vs( vs_input_pnt input ) {
	ps_input_p output;

	// projection

	float4 position_model = float4( input.position, 1.0 );
	float4 position_world = mul( position_model, matrix_world );

	output.position_world = position_world;
	output.position_view  = position_world;
	output.position_clip  = position_world;
	output.position       = position_world;

	//

	return output;
}

float4 ps( ps_input_p input ) : SV_TARGET {
	return float4( 1, 1, 1, 1 );
}
