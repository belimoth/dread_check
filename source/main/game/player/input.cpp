#include "../../canvas.h"
#include "../../game.h"

void menu_sfx_hover();

void game_menu_step_0();
void game_menu_step_1();

zed_pad pad_step_0_keyboard_only( zed_pad );
zed_pad pad_step_0( zed_pad );
zed_pad pad_step_i( int i, zed_pad );

// todo

zed_joy player_joy_0[ game_player_count_max ];

void client_update_player_i( int i ) {
	game_player &player = game.data.player[i];
	if ( game.menu[i].state.page ) return;

	if ( i == 0 ) {
		if ( split == game_split_solo ) {
			player.pad = pad_step_0( player.pad_previous );
		} else {
			player.pad = pad_step_0_keyboard_only( player.pad_previous );
		}
	} else {
		if ( split == game_split_solo ) return;
		player.pad = pad_step_i( i, player.pad_previous );
	}

	//

	bool pass = false;
	if ( player.pad.a.held and not player.a_menu_handled ) pass = true;
	if ( player.pad.b.held and not player.b_menu_handled ) pass = true;

	switch ( player.stance ) {
		case stance_jog:
		case stance_run:
		break;

		default:
		pass = false;
	}

	if ( pass ) player.pad.joy_0 = player_joy_0[i]; else player_joy_0[i] = player.pad.joy_0;

	//

	if ( player.pad.start.rise ) {
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
	if ( game.menu[0].state.page ) game_menu_step_0();
	if ( game.menu[1].state.page ) game_menu_step_1();
}

void game_player_input_step_lb_rb( game_player &player ) {
	switch ( player.torso ) {
		case torso_throw:
		if ( player.pad.rb.fall and not player.pad.lb.held ) player.torso = torso_hip;
		if ( player.pad.rb.fall and     player.pad.lb.held ) player.torso = torso_aim;
		break;

		case torso_hip:
		if ( not player.pad.rb.held and not player.pad.lb.held ) player.torso = torso_throw;
		if (     player.pad.rb.held and     player.pad.lb.held ) player.torso = torso_aim;
		break;

		case torso_aim:
		if (     player.pad.rb.held and not player.pad.lb.held ) player.torso = torso_hip;
		if ( not player.pad.rb.held and     player.pad.lb.held ) player.torso = torso_hold;
		break;

		case torso_hold:
		if ( not player.pad.rb.held and not player.pad.lb.held ) player.torso = torso_throw;
		break;

		default:
		player.torso = torso_throw;
	}
}

void game_player_input_step_lt_rt( game_player &player ) {
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
}

void game_player_input_step_ab_xy( game_player &player ) {
	if ( not player.pad.a.held and not player.pad.b.held and not player.pad.x.held and not player.pad.y.held ) {
		if ( player.pad.joy_1.z > 0 ) game_player_hands_switch_primary_up( player );
		if ( player.pad.joy_1.z < 0 ) game_player_hands_switch_primary_down( player );

		// todo, toggle in-game music and chat
		// if ( player.pad.n.fall ) game_player_hands_switch_primary( player, 0 );

		if ( player.pad.s.fall ) {
			game_player_hands_switch_primary( player, 0 );
			player.hint = hint_none;
		}

		if ( player.pad.e.fall ) game_player_hands_switch_primary_up  ( player );
		if ( player.pad.w.fall ) game_player_hands_switch_primary_down( player );
	}
}

void game_player_input_step( game_player &player ) {
	game_player_input_step_lt_rt( player );
	game_player_input_step_lb_rb( player );
	game_player_input_step_ab_xy( player );
	player.pad_previous = player.pad;
}
