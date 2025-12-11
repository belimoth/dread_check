#include "../game.hlsli"

float4 ps( ps_input_pnt input ) : SV_Target {
	return float4( 1, 1, 0, 0.05 );
}
