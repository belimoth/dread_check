#include "../hud.h"

#include "../../../../data/color.h"
#include "../../../game.h"
#include "../../../game/player.h"

void game_draw_hud_b( game_player &player, game_hud &hud ) {
	game_player player_copy;

	if ( player.stance == stance_jog or player.stance == stance_run ) {
		hud.text   = "DIVE";
		hud.text_w = "--"; // "SPIN";
		hud.text_e = "--"; // "SPIN";
		hud.text_n = "DROP";
		hud.text_s = "SLIDE";
	} else {
		hud.text = "--";
		player_copy = player;
		game_player_stance_spin_left( player_copy );
		hud.text_w = "SPIN";

		switch ( player_copy.stance ) {
			case stance_prone:      hud.text_w = "PRONE";  break;
			case stance_supine:     hud.text_w = "SUPINE"; break;
			case stance_side_left:  hud.text_w = "SIDE";   break;
			case stance_side_right: hud.text_w = "SIDE";   break;
		}

		player_copy = player;
		game_player_stance_spin_right( player_copy );
		hud.text_e = "SPIN";

		switch ( player_copy.stance ) {
			case stance_prone:      hud.text_e = "PRONE";  break;
			case stance_supine:     hud.text_e = "SUPINE"; break;
			case stance_side_left:  hud.text_e = "SIDE";   break;
			case stance_side_right: hud.text_e = "SIDE";   break;
		}

		player_copy = player;
		game_player_stance_hide_raise( player_copy );
		hud.text_n =  "--";

		switch( player_copy.stance ) {
			case stance_reach:  hud.text_n = "REACH";  break;
			case stance_walk:   hud.text_n = "STAND";  break;
			case stance_stalk:  hud.text_n = "STALK";  break;
			case stance_crouch: hud.text_n = "CROUCH"; break;
			case stance_crawl:  hud.text_n = "CRAWL";  break;
			case stance_prone:  hud.text_n = "PRONE";  break;
		}

		if ( player_copy.stance == player.stance ) hud.text_n = "--";

		player_copy = player;
		game_player_stance_hide_lower( player_copy );
		hud.text_s = "--";

		switch( player_copy.stance ) {
			case stance_reach:  hud.text_s = "REACH";  break;
			case stance_walk:   hud.text_s = "STAND";  break;
			case stance_stalk:  hud.text_s = "STALK";  break;
			case stance_crouch: hud.text_s = "CROUCH"; break;
			case stance_crawl:  hud.text_s = "CRAWL";  break;
			case stance_prone:  hud.text_s = "PRONE";  break;
		}

		player_copy = player;
		game_player_stance_hide_lower( player_copy );

		if ( player_copy.stance == player.stance ) hud.text_s = "--";

		int k = 6 - player.stance;

		player_copy = player;
		game_player_stance_hide_raise( player_copy );

		if ( player.stance <= stance_reach ) {
			string texts[] = {
				"REACH",
				"STAND",
				"STALK",
				"CROUCH",
				"CRAWL",
				"PRONE",
			};

			player_copy = player;
			game_player_stance_hide_lower( player_copy );

			if ( player_copy.stance == player.stance ) {
				for ( int i = 6 - player.stance + 1; i < 6; i++ ) {
					texts[i] = "--";
				}
			}

			for ( int i = 0; i < 6; i++ ) {
				hud_text( texts[i], hud.x, hud.y - 120 + i * 20 - k * 20 + 6 * 20, align_center, k == i ? color_hud_fg_active : color_hud_fg );
			}

			hud.text   = {};
			hud.text_n = {};
			hud.text_s = {};
		}
	}
}
