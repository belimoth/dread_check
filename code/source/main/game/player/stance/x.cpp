#include "../../player.h"

void game_player_stance_x_step( game_player &player ) {
	if ( player.pad.x.rise ) {
		if ( not player.x_menu_handled ) if ( player.ammo_i == 0 or player.bag.ammo[ player.ammo_i ] != 0 ) if ( player.torso != torso_aim ) game_item_try( player, action_reload );
		player.x_menu_handled = false;
		player.hint = hint_none;
	}

	if ( player.pad.x.held ) {
		if ( player.pad.x.fall ) player.hint = hint_x_menu;

		if ( player.pad.joy_1.z > 0 or player.pad.n.fall ) {
			player.x_menu_handled = true;
			// todo
		}

		if ( player.pad.joy_1.z < 0 or player.pad.s.fall ) {
			player.x_menu_handled = true;
			// todo
		}

		if ( player.pad.w.fall ) {
			player.x_menu_handled = true;
			// todo
		}

		if ( player.pad.e.fall ) {
			player.x_menu_handled = true;
			// todo
		}
	}
}
