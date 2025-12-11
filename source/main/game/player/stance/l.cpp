#include "../../player.h"

bool game_player_stance_is_airborne( game_player &player ) {
	switch ( player.stance ) {
		case stance_sail:
		case stance_jump:
		case stance_fall:
		case stance_dive_prone:
		case stance_dive_supine:
		case stance_dive_left:
		case stance_dive_right:
		return true;
	}

	return false;
}

bool game_player_stance_relax( game_player &player ) {
	if ( player.stance == stance_run ) {
		player.stance = stance_jog;
		player.torso  = torso_hip;
		game_player_hands_unholster( player );
		return true;
	}

	if ( player.stance == stance_reach ) {
		player.stance = stance_walk;
		player.torso  = torso_hip;
		game_player_hands_unholster( player );
		return true;
	}

	return false;
}

void game_player_stance_skid( game_player &player ) {
	if ( player.stance == stance_run ) {
		player.torso  = torso_hip;
		game_player_hands_unholster( player );
	}

	player.stance = stance_skid;
}

void game_player_stance_sprint( game_player &player ) {
	if ( player.pad.joy_0.y < 0.7 ) {
		if ( player.stance == stance_jog ) {
			player.stance = stance_walk;
		} else {
			player.stance     = stance_jog;
			player.torso      = torso_hip;
			player.did_sprint = true;
		}
	} else {
		player.stance     = stance_run;
		player.torso      = torso_none;
		player.did_sprint = true;
	}

	game_player_queue_interrupt( player );
}

void game_player_stance_unsprint( game_player &player ) {
	// todo

	// player.holding_breath = false;

	if ( player.stance == stance_run ) {
		// TEMP
		// player.stance = stance_trip;
		// return;

		player.stance = stance_jog;
		player.torso  = torso_hip;
		game_player_hands_unholster( player );
	}
}

void game_player_stance_skid_step( game_player &player ) {
	if ( player.object.velocity.x == 0 and player.object.velocity.y == 0 ) switch( player.stance ) {
		case stance_skid:
		// void game_player_stance_sprint( game_player &player );
		// if ( player.pad.joy_0.x > 0.7 or player.pad.joy_0.x < -0.7 or player.pad.joy_0.y > 0.7 ) game_player_stance_sprint( player ); else
		player.stance = stance_walk;
		break;

		case stance_slide_prone:
		player.stance = stance_prone;
		break;

		case stance_slide_supine:
		player.stance = stance_supine;
		player.torso  = torso_hip;
		game_player_hands_unholster( player );
		break;

		case stance_slide_left:
		player.stance = stance_side_left;
		game_player_hands_unholster( player );
		break;

		case stance_slide_right:
		player.stance = stance_side_right;
		game_player_hands_unholster( player );
		break;

	}


	if ( player.stance == stance_jog or player.stance == stance_run ) {
		float2 target_velocity = { player.pad.joy_0.x, player.pad.joy_0.y };
		float2 player_velocity = player.object.velocity;
		float result = dot( target_velocity, player_velocity ).x;
		if ( result < 0 ) game_player_stance_skid( player );
	}

	if ( player.stance == stance_skid ) {
		float2 target_velocity = { player.pad.joy_0.x, player.pad.joy_0.y };
		float2 player_velocity = player.object.velocity;
		float result = dot( target_velocity, player_velocity ).x;
		if ( result > 0 and player_velocity.y <= move_speed_jog ) player.stance = stance_jog;
	}
}

void game_player_stance_l_step( game_player &player ) {
	if ( not game_player_stance_can_jump( player ) ) return; // note
	if ( player.pad.ls and not player.pad_previous.ls ) game_player_stance_sprint( player );
	// if ( player.pad_previous.ls and not player.pad.ls ) game_player_stance_unsprint( player );
}
