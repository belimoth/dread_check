#include "../../../data/sfx.h"
#include "../../game.h"
#include "../player.h"

#include <zed/camera.h>

void game_player_queue_interrupt( game_player &player );

void game_player_hands_unholster( game_player &player ) {
	zed_camera camera = game.data.camera[ player.i ];

	player.gun_rig_0.rotation.x = camera.rotation.x + 90;
	player.gun_rig_0.rotation.y = camera.rotation.y - 90;

	player.gun_rig_1.rotation.x = camera.rotation.x + 90;
	player.gun_rig_1.rotation.y = camera.rotation.y - 90;
}

game_item &game_player_hands_get_item( game_player &player ) {
	return player.hands.which == 0 ? player.hands.item[ player.hands.i ] : player.hands.belt[ player.hands.j ];
}

void game_player_hands_set_i( game_player &player, int i ) {
	if ( player.hands.i == i ) return;
	player.hands.i = i;
}

void game_player_hands_set_j( game_player &player, int j, bool silent = false ) {
	if ( player.hands.j == j ) return;
	player.hands.j = j;
}

void game_player_hands_set_which( game_player &player, int which, bool silent = false ) {
	player.hands.which = which;

	game_item &item = game_player_hands_get_item( player );
	player.ammo_i = item_type[ item.type.i ].ammo;

	if ( silent ) return;

	game_player_hands_unholster( player );
	game_player_queue_interrupt( player );

	switch ( game_player_hands_get_item( player ).type.i ) {
		case item_torch:
		zed_play_sound( sfx_hand_gun_deploy, -20 );
		break;

		case item_sword:
		zed_play_sound( sfx_knife_deploy, -20 );
		break;

		case item_us_1917_revolver:
		zed_play_sound( sfx_hand_gun_deploy, -20 );
		break;

		case item_wi_1897_shotgun:
		case item_ak_1947:
		case item_us_1919_bmg:
		zed_play_sound( sfx_long_gun_deploy, -20 );
		break;
	}
}

void game_player_hands_switch_primary( game_player &player, int i ) {
	if ( player.hands.i == i and player.hands.which == 0 ) return;
	game_player_hands_set_i( player, i );
	game_player_hands_set_which( player, 0 );
}

void game_player_hands_switch_primary_up( game_player &player ) {
	game_player_hands_set_i( player, ( player.hands.i + 1 ) % player.hands.item_i );
	game_player_hands_set_which( player, 0 );
	player.hint = hint_z_menu;
}

void game_player_hands_switch_primary_down( game_player &player ) {
	game_player_hands_set_i( player, ( player.hands.i + player.hands.item_i - 1 ) % player.hands.item_i );
	game_player_hands_set_which( player, 0 );
	player.hint = hint_z_menu;
}

void game_player_hands_switch( game_player &player, bool silent ) {
	game_player_hands_set_which( player, 1 - player.hands.which, silent );
}

void game_player_hands_switch_secondary( game_player &player, int j ) {
	if ( player.hands.j == j and player.hands.which == 1 ) return;
	game_player_hands_set_j( player, j );
	game_player_hands_set_which( player, 1 );
}

void game_player_hands_switch_secondary_up( game_player &player ) {
	game_player_hands_set_j( player, max( ( player.hands.j + player.hands.belt_i - 1 ) % player.hands.belt_i, 0 ) );
	game_player_hands_set_which( player, 1 );
}

void game_player_hands_switch_secondary_down( game_player &player ) {
	game_player_hands_set_j( player, ( player.hands.j + 1 ) % player.hands.belt_i );
	game_player_hands_set_which( player, 1 );
}

void game_player_hands_swap( game_player &player ) {
	if ( player.hands.j == player.hands.k ) {
		player.hands.j = 0;
	} else {
		if ( player.hands.j == 0 ) {
		} else {
			player.hands.k = player.hands.j;
		}
	}

	player.y_menu_handled = true;
}

void game_player_hands_goof( game_player &player ) {
	player.hands.goofy = not player.hands.goofy;
}

void game_player_hands_away( game_player &player ) {
	if ( player.hands.j == 0 ) {
		player.hands.j = player.hands.k;
	} else if ( player.hands.j == player.hands.k ) {
		player.hands.k = 0;
	} else {
		player.hands.j = 0;
		player.hands.k = 0;
	}

	player.y_menu_handled = true;
}
