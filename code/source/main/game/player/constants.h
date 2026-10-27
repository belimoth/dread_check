#pragma once

#include <zed.h>

#include "../player.h"

//

float move_speed_none = 0;
float move_speed_walk = 0.04; // 0.083
float move_speed_hide = move_speed_walk * 0.8;
float move_speed_flat = move_speed_walk * 0.4;
float move_speed_run  = move_speed_walk * 2.8;
float move_speed_jog  = move_speed_walk * 1.6; // 1.4
float move_speed_aim  = move_speed_walk * 0.4;

float dive_speed     = 0.06;
float dive_speed_jog = 0.07;
float dive_speed_run = move_speed_run;

float turn_speed_walk = 2.0;
float turn_speed_hide = 1.0;
float turn_speed_flat = 0.5;
float turn_speed_run  = 0.5;
float turn_speed_jog  = 1.0;
float turn_speed_aim  = 0.5;

float move_accel_walk = move_speed_walk / 12.0;
float move_accel_hide = move_accel_walk;
float move_accel_flat = move_accel_walk;
float move_accel_run  = move_speed_walk / 36.0; // 72.0;
float move_accel_jog  = move_speed_walk / 36.0; // 72.0;
float move_accel_aim  = move_speed_walk / 12.0;
float move_accel_skid = move_speed_run  / 36.0;
float move_accel_slide = move_accel_skid * 0.5;

float turn_accel = turn_speed_walk / 12.0; // 12 frames

float jump_speed = 0.055;                   // 0.08; // 0.1; // 0.22;
float gravity = 0.0027222222; // 0x3b32674f // 0.004;

float height_stand  = 1.5;
float height_crouch = 0.9;

float posture_land = 0.75;

float time_hide = 18; // 12;

//

float game_player_get_height( game_player &player ) {
	return height_crouch + ( height_stand - height_crouch ) * player.rig.posture;
}

float game_player_get_bob_rate( game_player &player ) {
	float result = 0;

	switch( player.stance ) {
		case stance_walk:
		case stance_stalk:
		case stance_crouch:
		case stance_crawl:
		case stance_prone:
		case stance_supine:
		case stance_side_left:
		case stance_side_right:
		result = 5;
		break;

		case stance_run:
		result = 10;
		break;

		case stance_jog:
		result = 9;
		break;
	}

	if ( player.torso == torso_aim ) result =  5 * move_speed_aim / move_speed_walk;

	return result;
}

float game_player_get_bob_amount( game_player &player ) {
	float result = 0.0;

	switch ( player.stance ) {
		case stance_jog:
		result = 0.20 * 0.2;
		break;

		case stance_run:
		result = 0.10 * 0.2;
		break;

		case stance_walk:
		result = 0.08 * 0.2;
		if ( player.torso  == torso_aim ) result = 0.04 * 0.1;
		break;

		case stance_stalk:
		result = 0.06 * 0.2;
		if ( player.torso  == torso_aim ) result = 0.02 * 0.1;
		break;

		case stance_crouch:
		case stance_crawl:
		case stance_prone:
		case stance_supine:
		case stance_side_left:
		case stance_side_right:
		result = 0.02 * 0.2;
		if ( player.torso  == torso_aim ) result = 0.01 * 0.1;
		break;
	}

	return result;
}
