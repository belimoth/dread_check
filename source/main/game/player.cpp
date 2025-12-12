#include "player.h"

#include "../../input.h"
#include "../../data/sfx.h"
#include "../game.h"
#include "player/constants.h"

#include <zed/camera.h>
#include <zed/random.h>

void game_player_init() {
	for ( int i = 0; i < game_player_count_max; i++ ) {
		game_player &player = game.data.player[i];
		player.i = i;
		player.object.position = { (float)i, 0, 0 };
		game.data.camera[i].rotation.y = 180;
		game_player_vitals_init( player );
		player.stance = stance_walk;
	}
}

void game_player_movement_step( game_player &player ) {
	zed_camera &camera = game.data.camera[ player.i ];
	float3 velocity = player.object.velocity;

// 	if ( false ) {
// 		float length_velocity = length( velocity );
//
// 		if ( length_velocity > posture_penalty ) {
// 			posture_penalty = 0;
// 			velocity = velocity - normalize( velocity ) * posture_penalty;
// 		} else {
// 			posture_penalty -= length_velocity;
// 			velocity = {};
// 		}
// 	}

	float dx = velocity.x;
	float dy = velocity.y;

	float3 move = zed_camera_walk( camera, dx, dy, 0 );

	player.object.position.x += move.x;
	player.object.position.y += move.y;
	player.object.position.z += move.z;

	player.object.position.y += player.object.velocity.z;
}

void game_player_navigation_step( game_player &player ) {
	if ( game.scene != scene_game ) return;

	player.object.nav = 0;

	if ( player.object.position.x > 0 and player.object.position.z > 0 and player.object.position.x < 64 and player.object.position.z < 64 ) {
		int x = floor( player.object.position.x );
		int y = floor( player.object.position.z );
		int i = x + y * 64;
		player.object.nav = &game_data_world[i];
	}

	if ( player.object.nav != player.object.nav_previous and not game_player_stance_is_airborne( player ) ) {
		float dy = 0;

		if ( player.object.nav          ) dy += player.object.nav->p.z;
		if ( player.object.nav_previous ) dy -= player.object.nav_previous->p.z;

		float fall_max = -2 * 1.5 / 5;

		if ( dy < fall_max - 0.01 ) {
			dy = fall_max;
			player.stance = stance_jump;
		}

		player.object.position.y += dy;
		player.rig.posture -= dy / ( height_stand - height_crouch );

		if ( player.pad.b ) {
			game_player_stance stance_previous = player.stance;
			if ( player.rig.posture <  1.0 + 0.25 ) player.stance = stance_walk;
			if ( player.rig.posture <  0.5 + 0.25 ) player.stance = stance_stalk;
			if ( player.rig.posture <  0.0 + 0.25 ) player.stance = stance_crouch;
			if ( player.rig.posture < -0.5 + 0.25 ) player.stance = stance_crawl;
			if ( player.rig.posture < -1.0 + 0.25 ) player.stance = stance_prone;

			if ( player.stance != stance_previous ) {
				player.b_menu_handled = true;
				player.hint = hint_none;
			}
		}
	}

	player.object.nav_previous = player.object.nav;
}

void game_player_step_after_movement( game_player &player ) {
	if ( player.stance == stance_run and player.pad.joy_0.y < 0.7 ) {
		player.stance = stance_jog;
		player.torso  = torso_hip;
		game_player_hands_unholster( player );
	}

	if ( player.stance == stance_jog and player.object.velocity.x == 0 and player.object.velocity.y == 0 ) {
		player.stance = stance_walk;
	}

	float ground = 0;
	if ( player.object.nav ) ground = player.object.nav->p.z;

	if ( player.stance == stance_jump ) {
		if ( player.object.velocity.z < -0.06 ) player.stance = stance_fall;
	}

	float z_ground = ground - ( height_stand - height_crouch ) * ( 1.0 - posture_land );

	if ( player.object.position.y < z_ground ) switch ( player.stance ) {
		case stance_jump:
		case stance_sail:
		case stance_fall:
		game_player_stance_land( player );
		break;
	}

	if ( player.object.position.y < ground ) switch ( player.stance ) {
		case stance_dive_prone:
		game_player_stance_land( player, stance_prone );
		break;

		case stance_dive_supine:
		game_player_stance_land( player, stance_supine );
		break;

		case stance_dive_right:
		game_player_stance_land( player, stance_side_right );
		break;

		case stance_dive_left:
		game_player_stance_land( player, stance_side_left );
		break;
	}
}

#include "player/hands.cpp"
#include "player/input.cpp"
#include "player/item.cpp"
#include "player/movement.cpp"
#include "player/physics.cpp"
#include "player/rig.cpp"
#include "player/stance.cpp"
#include "player/torso.cpp"
#include "player/vitals.cpp"

void game_player_step( game_player &player ) {
	// before

	switch ( player.stance ) {
		case stance_jump:
		case stance_fall:
		case stance_sail:
		case stance_dive_prone:
		case stance_dive_supine:
		case stance_dive_left:
		case stance_dive_right:
		player.object.velocity.z -= gravity;
		break;
	}

	switch ( player.stance ) {
		case stance_sail:
		player.object.velocity.z = max( -0.2 * sin( dtor( game.data.camera[ player.i ].rotation.x ) ), player.object.velocity.z );

		case stance_jump:
		case stance_fall:
		case stance_dive_prone:
		case stance_dive_supine:
		case stance_dive_left:
		case stance_dive_right:
		player.object.velocity.z = max( -50, player.object.velocity.z );
		break;
	}

	//

	game_player_stance_step    ( player );
	game_player_steering_step  ( player );
	game_player_gun_rig_step   ( player );
	game_player_physics_before ( player );
	game_player_movement_step  ( player );
	game_player_physics_after  ( player );
	game_player_navigation_step( player );

	// after

	game_player_step_after_movement( player );
	game_player_queue_step         ( player );
	game_player_input_step         ( player );
	game_player_vitals_step        ( player );
	game_player_rig_step           ( player );

	//

	game_player_physics_step( player );
}
