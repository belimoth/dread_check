#include "../../player.h"
#include "../../player/constants.h"

bool game_player_stance_can_jump( game_player &player );
void game_player_queue_interrupt( game_player &player );

void game_player_stance_jump( game_player &player ) {
	player.object.velocity.z = jump_speed;
	player.stance   = stance_jump;
	player.torso    = torso_none;
	player.did_jump = true;
	game_player_queue_interrupt( player );
}

void game_player_stance_land( game_player &player, game_player_stance stance ) {
	float ground = 0;
	if ( player.object.nav ) ground = player.object.nav->p.z;
	player.object.position.y = ground;
	player.object.velocity.z = 0;
	player.torso = torso_hip;
	game_player_hands_unholster( player );
	player.stance = stance;

	switch ( player.stance ) {
		case stance_prone:
		case stance_supine:
		case stance_side_left:
		case stance_side_right:
		break;

		case stance_walk:
		player.rig.posture = posture_land;
		float speed = sqrt( player.object.velocity.x * player.object.velocity.x + player.object.velocity.y * player.object.velocity.y );

		if ( speed > move_speed_run + 0.05 ) {
			player.stance = stance_skid;
		} else if ( speed > 0 ) {
			player.stance = stance_jog;
		} else {
			player.stance = stance_walk;
		}

		break;
	}
}

void game_player_stance_dive( game_player &player ) {
	if ( not game_player_stance_can_jump( player ) ) return;
	float speed = dive_speed;
	if ( player.stance == stance_jog ) speed = dive_speed_jog;
	if ( player.stance == stance_run ) speed = dive_speed_run;
	player.object.position.y += ( height_stand - height_crouch ) * ( 1.0 - (-1) );
	player.object.velocity.z = jump_speed / 2;
	player.torso  = torso_none;
	player.did_jump = true;
	float2 direction = normalize( float2( player.object.velocity.x, player.object.velocity.y ) );
	player.object.velocity.x = direction.x * speed;
	player.object.velocity.y = direction.y * speed;
	if ( abs( direction.y ) >= abs( direction.x ) and sign( direction.y ) > 0 ) player.stance = stance_dive_prone;
	if ( abs( direction.y ) >= abs( direction.x ) and sign( direction.y ) < 0 ) player.stance = stance_dive_supine;
	if ( abs( direction.x ) >= abs( direction.y ) and sign( direction.x ) < 0 ) player.stance = stance_dive_left;
	if ( abs( direction.x ) >= abs( direction.y ) and sign( direction.x ) > 0 ) player.stance = stance_dive_right;
	game_player_queue_interrupt( player );
}

void game_player_stance_dive( game_player &player, game_player_stance stance ) {
	if ( not game_player_stance_can_jump( player ) ) return;
	player.object.position.y += ( height_stand - height_crouch ) * ( 1.0 - (-1) );
	player.object.velocity.z = jump_speed / 2;
	player.stance = stance;
	player.torso  = torso_none;
	player.did_jump = true;

	switch( player.stance ) {
		case stance_dive_prone:
		player.object.velocity.x = 0;
		player.object.velocity.y = dive_speed;
		break;

		case stance_dive_supine:
		player.object.velocity.x =  0;
		player.object.velocity.y = -dive_speed;
		break;

		case stance_dive_right:
		player.object.velocity.x = dive_speed;
		player.object.velocity.y = 0;
		break;

		case stance_dive_left:
		player.object.velocity.x = -dive_speed;
		player.object.velocity.y =  0;
		break;
	}

	game_player_queue_interrupt( player );
}

void game_player_stance_a_step( game_player &player ) {
	if ( not player.pad.a and player.pad_previous.a ) {
		if ( game_player_stance_can_jump( player ) and not player.a_menu_handled ) {
			game_player_stance_jump( player );
		} else {
			switch ( player.stance ) {
				case stance_sail:
				player.stance = stance_jump;
				break;

				case stance_fall:
				case stance_jump:
				player.stance = stance_sail;
				break;
			}
		}

		player.hint = hint_none;
		player.a_menu_handled = false;
	}

	if ( player.pad.a ) {
		if ( not player.pad_previous.a ) player.hint = hint_a_menu;

		if ( player.pad.joy_1.z > 0 or player.pad.n and not player.pad_previous.n ) {
			player.a_menu_handled = true;
			game_player_stance_dive( player, stance_dive_prone );
		}

		if ( player.pad.joy_1.z < 0 or player.pad.s and not player.pad_previous.s ) {
			player.a_menu_handled = true;
			game_player_stance_dive( player, stance_dive_supine );
		}

		if ( player.pad.w and not player.pad_previous.w ) {
			player.a_menu_handled = true;
			game_player_stance_dive( player, stance_dive_left );
		}

		if ( player.pad.e and not player.pad_previous.e ) {
			player.a_menu_handled = true;
			game_player_stance_dive( player, stance_dive_right );
		}
	}
}
