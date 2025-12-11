#pragma once

#include "../../data/sfx.h"
#include "../../input.h"
#include "../../main.h"
#include "../game.h"
#include "../game/player.h"
#include "../game/player/constants.h"
#include "../wolf.h"

#include <zed/camera.h>

void wolf_player_update_rig() {
	game.data.camera[0].position = game.data.player[0].object.position;
	game.data.camera[0].position.y += 1.5;

	// lol
	// game.data.camera[0].position.y += 1.9;

	game.data.camera[0].rotation.x += -game.data.player[0].pad.joy_1.y;
	game.data.camera[0].rotation.x = min( game.data.camera[0].rotation.x,  90.0 );
	game.data.camera[0].rotation.x = max( game.data.camera[0].rotation.x, -90.0 );

	game.data.camera[0].rotation.y += game.data.player[0].turn_speed;
}

void wolf_player_step( game_player &player ) {
	player.pad = update_pad_0();

	{
		float target_speed = turn_speed_walk;
		target_speed *= player.pad.joy_1.x;
		player.turn_speed = converge( player.turn_speed, target_speed, turn_accel );
	}

	float target_speed = move_speed_walk;
	float move_accel   = move_accel_walk;

	//

	float3 temp = { player.pad.joy_0.x, player.pad.joy_0.y, 0 };
	float3 target_velocity = temp * target_speed;
//
// 	if ( player.did_sprint ) {
// 		player.object.velocity = target_velocity;
// 	} else {
		float3 diff = target_velocity - player.object.velocity;

		if ( length( diff ) <= move_accel ) {
			player.object.velocity = target_velocity;
		} else {
			float3 accel = normalize( diff ) * move_accel;
			player.object.velocity = player.object.velocity + accel;
		}
	// }

	float dx = player.object.velocity.x;
	float dy = player.object.velocity.y;

	float3 move = zed_camera_walk( game.camera, dx, dy, 0 );

	//

	float x_min =  0;
	float x_max = 64;
	float y_min =  0;
	float y_max = 64;

	int x = floor( player.object.position.x / wolf_scale );
	int y = floor( player.object.position.z / wolf_scale );
	int i = x + y * 64;
	int j;
	int color;

	//

	j = i - 1;

	if ( j > 0 ) {
		color = wolf.grid[j].color;

		// floor
		if ( color > 105 ) {}
		// secret door
		else if ( wolf.grid[i].s ) {}
		// door
		else if ( color > 53 ) {}
		// wall
		else { x_min = x; }

		if ( wolf.grid[j].s == 1 && wolf.grid[j].t == 0 ) {
			wolf.grid[j].color = 106;
			wolf.grid[j].s = 0;
			zed_play_sound( sfx_wall_slide, -10 );
		}
	}

	//

	j = i + 1;

	if ( j < 64 * 64 ) {
		color = wolf.grid[j].color;

		// floor
		if ( color > 105 ) {}
		// secret door
		else if ( wolf.grid[i].s ) {}
		// door
		else if ( color > 53 ) {}
		// wall
		else { x_max = x + 1; }

		if ( wolf.grid[j].s == 1 && wolf.grid[j].t == 0 ) {
			wolf.grid[j].color = 106;
			wolf.grid[j].s = 0;
			zed_play_sound( sfx_wall_slide, -10 );
		}
	}

	//

	j = i - 64;

	if ( j > 0 ) {
		color = wolf.grid[j].color;

		// floor
		if ( color > 105 ) {}
		// secret door
		else if ( wolf.grid[i].s ) {}
		// door
		else if ( color > 53 ) {}
		// wall
		else { y_min = y; }

		if ( wolf.grid[j].s == 1 && wolf.grid[j].t == 0 ) {
			wolf.grid[j].color = 106;
			wolf.grid[j].s = 0;
			zed_play_sound( sfx_wall_slide, -10 );
		}
	}

	//

	j = i + 64;

	if ( j < 64 * 64 ) {
		color = wolf.grid[j].color;

		// floor
		if ( color > 105 ) {}
		// secret door
		else if ( wolf.grid[i].s ) {}
		// door
		else if ( color > 53 ) {}
		// wall
		else { y_max = y + 1; }

		if ( wolf.grid[j].s == 1 && wolf.grid[j].t == 0 ) {
			wolf.grid[j].color = 106;
			wolf.grid[j].s = 0;
			zed_play_sound( sfx_wall_slide, -10 );
		}
	}

	//

	x_min *= wolf_scale;
	x_max *= wolf_scale;
	y_min *= wolf_scale;
	y_max *= wolf_scale;

	//

	x_min = x_min + 0.2;
	x_max = x_max - 0.2;
	y_min = y_min + 0.2;
	y_max = y_max - 0.2;

	//

	player.object.position.x = min( max( player.object.position.x + move.x, x_min ), x_max );
	player.object.position.y = player.object.position.y + move.y;
	player.object.position.z = min( max( player.object.position.z + move.z, y_min ), y_max );

	player.object.position.y += player.object.velocity.z;

	//

	wolf_player_update_rig();
}
