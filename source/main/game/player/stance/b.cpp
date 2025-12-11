#include "../../../game.h"
#include "../../player.h"
#include "../../player/constants.h"

#include <zed/camera.h>

void game_player_stance_hide( game_player &player ) {
	switch ( player.stance ) {
		case stance_jog:
		case stance_run:
		game_player_stance_dive( player );
		break;

		case stance_reach:
		case stance_crouch:
		player.stance = stance_walk;
		break;

		case stance_supine:
		case stance_side_left:
		case stance_side_right:
		break;

		default:
		player.stance = stance_crouch;
	}
}

void game_player_stance_dropkick( game_player &player ) {
	if ( not game_player_stance_can_jump( player ) ) return;
	player.object.position.y += ( height_stand - height_crouch ) * ( 1.0 - (-1) );
	player.object.velocity.z = jump_speed / 2;
	player.torso  = torso_none;
	player.did_jump = true;
	float speed = dive_speed;
	if ( player.stance == stance_jog ) speed = dive_speed_jog;
	if ( player.stance == stance_run ) speed = dive_speed_run;
	float2 direction = normalize( float2( player.object.velocity.x, player.object.velocity.y ) );
	player.object.velocity.x = direction.x * speed;
	player.object.velocity.y = direction.y * speed;
	player.stance = stance_dive_supine;
	game_player_queue_interrupt( player );
}

void game_player_stance_hide_raise( game_player &player ) {
	// todo switching to tall while moving causes or can cause you to trip on nothing

	switch ( player.stance ) {
		case stance_walk:
		player.stance = player.pad.joy_0.magnitude != 0 ? stance_walk : stance_reach;
		break;

		case stance_stalk:
		player.stance = stance_walk;
		break;

		case stance_crouch:
		player.stance = stance_stalk;
		break;

		case stance_crawl:
		player.stance = stance_crouch;
		break;

		case stance_prone:
		player.stance = stance_crawl;
		break;

		case stance_jog:
		case stance_run:
		game_player_stance_dropkick( player );
	}
}

void game_player_stance_slide( game_player &player ) {
	float2 direction = normalize( float2( player.object.velocity.x, player.object.velocity.y ) );
	if ( abs( direction.y ) >= abs( direction.x ) and sign( direction.y ) < 0 ) player.stance = stance_slide_prone;
	if ( abs( direction.y ) >= abs( direction.x ) and sign( direction.y ) > 0 ) player.stance = stance_slide_supine;
	if ( abs( direction.x ) >= abs( direction.y ) and sign( direction.x ) > 0 ) player.stance = stance_slide_left;
	if ( abs( direction.x ) >= abs( direction.y ) and sign( direction.x ) < 0 ) player.stance = stance_slide_right;

	game_player_queue_interrupt( player );
}

void game_player_stance_hide_lower( game_player &player ) {
	switch ( player.stance ) {
		case stance_walk:   player.stance = stance_stalk;  break;
		case stance_stalk:  player.stance = stance_crouch; break;
		case stance_crouch: player.stance = stance_crawl;  break;
		case stance_crawl:  player.stance = stance_prone;  break;

		case stance_reach:
		player.stance = stance_walk;
		game_player_hands_unholster( player ); // todo only perform gun draw when b_menu_handled changes to false
		break;

		case stance_jog:
		case stance_run:
		game_player_stance_slide( player );
		break;
	}
}

void game_player_stance_spin_right( game_player &player ) {
	zed_camera &camera = game.data.camera[ player.i ];
	if ( player.stance == stance_jog or player.stance == stance_run ) return;
	camera.rotation.y += 90;
	// player.hint = hint_spin;
	game_player_hands_unholster( player );

	switch ( player.stance ) {
		case stance_prone:
		player.stance = stance_side_left;
		break;

		case stance_side_left:
		player.stance = stance_supine;
		break;

		case stance_supine:
		player.stance = stance_side_right;
		break;

		case stance_side_right:
		player.stance = stance_prone;
		break;
	}
}

void game_player_stance_spin_left( game_player &player ) {
	zed_camera &camera = game.data.camera[ player.i ];
	if ( player.stance == stance_jog or player.stance == stance_run ) return;

	bool forward = false;

	switch ( player.stance ) {
		case stance_jog:
		case stance_run:
		forward = true;
		break;
	}

	if ( forward ) {
		player.object.velocity.x = 0;
		player.object.velocity.y = dive_speed_jog;
		player.object.velocity.y = dive_speed_run;

		switch ( player.stance ) {
			case stance_dive_right:
			break;

			case stance_dive_left:
			break;
		}
	}

	camera.rotation.y -= 90;
	player.torso = torso_hip;
	// player.hint = hint_spin;
	game_player_hands_unholster( player );

	switch ( player.stance ) {
		case stance_prone:
		player.stance = stance_side_right;
		break;

		case stance_side_left:
		player.stance = stance_prone;
		break;

		case stance_supine:
		player.stance = stance_side_left;
		break;

		case stance_side_right:
		player.stance = stance_supine;
		break;
	}
}

void game_player_stance_b_step( game_player &player ) {
	if ( not player.pad.b and player.pad_previous.b ) {
		if ( game_player_stance_can_jump( player ) and not player.b_menu_handled ) game_player_stance_hide( player );
		player.b_menu_handled = false;
		player.hint = hint_none;
	}

	if ( player.stance == stance_reach ) {
		if ( player.pad.joy_0.magnitude != 0 and not player.pad.b ) {
			player.stance = stance_walk;
			game_player_hands_unholster( player );
		}
	}

	if ( player.pad.b ) {
		if ( not player.pad_previous.b ) player.hint = hint_b_menu;

		if ( player.pad.joy_1.z > 0 or player.pad.n and not player.pad_previous.n ) {
			player.b_menu_handled = true;
			game_player_stance_hide_raise( player );
		}

		if ( player.pad.joy_1.z < 0 or player.pad.s and not player.pad_previous.s ) {
			player.b_menu_handled = true;
			game_player_stance_hide_lower( player );
		}

		if ( player.pad.w and not player.pad_previous.w ) {
			player.b_menu_handled = true;
			game_player_stance_spin_left( player );
		}

		if ( player.pad.e and not player.pad_previous.e ) {
			player.b_menu_handled = true;
			game_player_stance_spin_right( player );
		}
	}
}
