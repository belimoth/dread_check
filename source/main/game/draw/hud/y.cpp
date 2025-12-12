#include "../../../game/player.h"

void game_draw_hud_y( game_player &player, game_hud &hud ) {
	game_item &item = game_player_hands_get_item( player );

	hud.text   = "";
	hud.text_n = "";
	hud.text_s = "";
	hud.text_w = item_name[ player.hands.belt[ player.hands.k ].type.i ];
	hud.text_e = "AWAY";

	int j = player.hands.j;

	for ( int i = 0; i < player.hands.belt_i; i++ ) {
		hud_text( item_name[ player.hands.belt[i].type.i ], hud.x, hud.y + i * 20 - j * 20, align_center, i == j ? color_hud_fg_active : color_hud_fg );
	}
}
