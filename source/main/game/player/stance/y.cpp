#include "../../player.h"

void game_player_stance_y_step( game_player &player ) {
	if ( player.pad.y.rise ) {
		if ( not player.y_menu_handled ) game_player_hands_switch( player );
		player.hint = hint_none;
		player.y_menu_handled = false;
	} else if ( player.pad.y.held ) {
		if ( player.pad.y.fall ) player.hint = hint_y_menu;

		if ( player.pad.joy_1.z > 0 or player.pad.n.fall ) {
			player.y_menu_handled = true;
			game_player_hands_switch_secondary_up( player );
		}

		if ( player.pad.joy_1.z < 0 or player.pad.s.fall ) {
			player.y_menu_handled = true;
			game_player_hands_switch_secondary_down( player );
		}

		if ( player.pad.w.fall ) {
			player.did_sprint = true;
			game_player_hands_swap( player );
		}

		if ( player.pad.e.fall ) {
			player.y_menu_handled = true;
			game_player_hands_away( player );
		}
	}
}
