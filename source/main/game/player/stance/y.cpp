#include "../../player.h"

void game_player_stance_y_step( game_player &player ) {
	if ( not player.pad.y and player.pad_previous.y ) {
		if ( not player.y_menu_handled ) game_player_hands_switch( player );
		player.hint = hint_none;
		player.y_menu_handled = false;
	} else if ( player.pad.y ) {
		if ( not player.pad_previous.y ) player.hint = hint_y_menu;

		if ( player.pad.joy_1.z > 0 or player.pad.n and not player.pad_previous.n ) {
			player.y_menu_handled = true;
			game_player_hands_switch_secondary_up( player );
		}

		if ( player.pad.joy_1.z < 0 or player.pad.s and not player.pad_previous.s ) {
			player.y_menu_handled = true;
			game_player_hands_switch_secondary_down( player );
		}

		if ( player.pad.w and not player.pad_previous.w ) {
			player.did_sprint = true;
			game_player_hands_swap( player );
		}

		if ( player.pad.e and not player.pad_previous.e ) {
			player.y_menu_handled = true;
			game_player_hands_away( player );
		}
	}
}
