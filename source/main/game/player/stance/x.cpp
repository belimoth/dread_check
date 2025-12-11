#include "../../player.h"

void game_player_stance_x_step( game_player &player ) {
	if ( not player.pad.x and player.pad_previous.x ) {
		if ( not player.x_menu_handled ) if ( player.ammo_i == 0 or player.bag.ammo[ player.ammo_i ] != 0 ) game_item_try( player, action_reload );
		player.x_menu_handled = false;
		player.hint = hint_none;
	}

	if ( player.pad.x ) {
		if ( not player.pad_previous.x ) player.hint = hint_x_menu;

		if ( player.pad.joy_1.z > 0 or player.pad.n and not player.pad_previous.n ) {
			player.x_menu_handled = true;
			// todo
		}

		if ( player.pad.joy_1.z < 0 or player.pad.s and not player.pad_previous.s ) {
			player.x_menu_handled = true;
			// todo
		}

		if ( player.pad.w and not player.pad_previous.w ) {
			player.x_menu_handled = true;
			// todo
		}

		if ( player.pad.e and not player.pad_previous.e ) {
			player.x_menu_handled = true;
			// todo
		}
	}
}
