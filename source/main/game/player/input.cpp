#include "../../canvas.h"
#include "../../game.h"

void menu_sfx_hover();

void game_menu_update_0();
void game_menu_update_1();
zed_pad update_pad_0_keyboard_only();
zed_pad update_pad_0();
zed_pad update_pad_i( int i );

// todo

zed_joy player_joy_0[ game_player_count_max ];

void client_update_player_i( int i ) {
	game_player &player = game.data.player[i];
	if ( game.menu[i].state.page ) return;

	if ( i == 0 ) {
		if ( split == game_split_solo ) {
			player.pad = update_pad_0();
		} else {
			player.pad = update_pad_0_keyboard_only();
		}
	} else {
		if ( split == game_split_solo ) return;
		game.data.player[i].pad = update_pad_i(i);
	}

	//

	bool pass = false;
	if ( player.pad.a and not player.a_menu_handled ) pass = true;
	if ( player.pad.b and not player.b_menu_handled ) pass = true;

	switch ( player.stance ) {
		case stance_jog:
		case stance_run:
		break;

		default:
		pass = false;
	}

	if ( pass ) player.pad.joy_0 = player_joy_0[i]; else player_joy_0[i] = player.pad.joy_0;

	//

	if ( not player.pad.start and player.pad_previous.start ) {
		game.menu[i].state = { game_menu_page_pause };
		menu_sfx_hover();
	}
}

//

void client_update_player() {
	for ( int i = 0; i < game_player_count_max; i++ ) {
		game.data.player[i].pad = {};
		game.data.player[i].pad.joy_0 = player_joy_0[i];
	}

	if ( not game.has_focus ) return;

	for ( int i = 0; i < game.player_count; i++ ) client_update_player_i( i );
	if ( game.menu[0].state.page ) game_menu_update_0();
	if ( game.menu[1].state.page ) game_menu_update_1();
}

void game_player_input_step( game_player &player ) {
	if ( player.pad.rt == 1 and player.pad_previous.rt != 1 ) {
		switch ( player.torso ) {
			case torso_hip:
			case torso_aim:
			case torso_hold:
			case torso_grab:
			game_item_try( player, action_shoot );
			break;

			case torso_throw:
			break;
		}
	}

	if ( player.pad.rt == 0 and player.pad_previous.rt != 0 ) {
		switch ( player.torso ) {
			case torso_hip:
			case torso_aim:
			case torso_hold:
			case torso_grab:
			// game_item_try( player, action_unshoot );
			break;

			case torso_throw:
			break;
		}
	}

	if ( player.pad.lt == 1 and player.pad_previous.lt != 1 ) {
		switch( player.torso ) {
			case torso_none:
			case torso_hip:
			case torso_aim:
			case torso_throw:
			game_item_try( player, action_slide_open );
			break;

			case torso_hold:
			game_item_try( player, action_push );
			break;

			case torso_grab:
			// game_item_try( player, action_grab );
			break;

			// game_item_try( player, action_throw );
			// break;
		}
	}

	if ( player.pad.lt == 0 and player.pad_previous.lt != 0 ) {
		switch( player.torso ) {
			case torso_none:
			case torso_hip:
			case torso_aim:
			case torso_throw:
			game_item_try( player, action_slide_close );
			break;

			case torso_hold:
			case torso_grab:
			break;
		}
	}

	//

	if ( player.pad.lb and not player.pad.rb and not player.hands.goofy ) player.torso = torso_grab;
	if ( player.pad.lb and not player.pad.rb and     player.hands.goofy ) player.torso = torso_hold;
	if ( player.pad.rb and not player.pad.lb and not player.hands.goofy ) player.torso = torso_hold;
	if ( player.pad.rb and not player.pad.lb and     player.hands.goofy ) player.torso = torso_grab;
	if ( player.pad.rb and player.pad.lb ) player.torso = torso_throw;
	if ( not player.pad.rb and not player.pad.lb and ( player.pad_previous.rb or player.pad_previous.lb ) ) player.torso = torso_hip;

	//

	if ( not player.pad.a and not player.pad.b and not player.pad.x and not player.pad.y ) {
		if ( player.pad.joy_1.z > 0 ) game_player_hands_switch_primary_up( player );
		if ( player.pad.joy_1.z < 0 ) game_player_hands_switch_primary_down( player );

		// todo, toggle in-game music and chat
		// if ( player.pad.n and not player.pad_previous.n ) game_player_hands_switch_primary( player, 0 );

		if ( player.pad.s and not player.pad_previous.s ) {
			game_player_hands_switch_primary( player, 0 );
			player.hint = hint_none;
		}

		if ( player.pad.e and not player.pad_previous.e ) game_player_hands_switch_primary_up  ( player );
		if ( player.pad.w and not player.pad_previous.w ) game_player_hands_switch_primary_down( player );
	}

	//

	player.pad_previous = player.pad;
}
