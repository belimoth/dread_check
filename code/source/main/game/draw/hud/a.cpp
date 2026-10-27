#include "../hud.h"

#include "../../../game.h"
#include "../../../game/player.h"

void game_draw_hud_a( game_player &player, game_hud &hud ) {
	hud.text = "--";
	if ( game_player_stance_can_jump( player ) ) hud.text = "DIVE";
	hud.text_w = hud.text;
	hud.text_e = hud.text;
	hud.text_n = hud.text;
	hud.text_s = hud.text;
	if ( game_player_stance_can_jump( player ) ) hud.text = "JUMP";
}
