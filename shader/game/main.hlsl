#include "../game.hlsli"

ps_input_pnt vs( vs_input_pnt input ) {
	return projection_standard_pnt_pnt( input );
}

ps_standard_imp;
