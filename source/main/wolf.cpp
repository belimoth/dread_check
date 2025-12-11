#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/app/input.h>
#include <zed/app/ui.h>

#include "../data/sfx.h"
#include "../main.h"
#include "game/draw.h"

#include "wolf.h"

#include "wolf/level.cpp"
#include "wolf/player.cpp"
#include "wolf/draw.cpp"

int wolf_level = 0;
// int wolf_level = 20;
// int wolf_level = 50;

void wolf_start() {
	wolf_level_load( wolf_level );
}

void scene_wolf_start() {
	game.data = {};

	void game_player_init();
	game_player_init();

	float3 p = float3( wolf_player_start_x, 0, wolf_player_start_y );

	for( int i = 0; i < game_player_count_max; i++ ) {
		game.data.player[i].object.position = mul( p + float3( 0.5, 0, 0.5 ), scale( wolf_scale ) );
		game.data.camera[i].rotation.y =  wolf_player_start_rotation;
	}
}

void wolf_step() {
	void client_update_player();
	client_update_player();
	if ( game.is_paused ) return;
	if ( not game.is_started ) return;

	wolf_player_step( game.data.player[0] );

	int2 position;
	static int2 position_previous;

	position.x = floor( game.data.player[0].object.position.x / wolf_scale );
	position.y = floor( game.data.player[0].object.position.z / wolf_scale );

	// update_enemies

	frame_time = frame_time + 1;

	for ( int i = 0; i < wolf.enemy_i; i++ ) {
		if ( wolf.enemy[i].frame == frame_dead ) continue;
		if ( wolf.enemy[i].frame == 0          ) continue;

		if ( frame_time % 200 == 0 ) {
			switch ( wolf.enemy[i].face ) {
				case wolf_8e : wolf.enemy[i].position = wolf.enemy[i].position + float3( -1,  0,  0 ); break;
				case wolf_8ne: wolf.enemy[i].position = wolf.enemy[i].position + float3( -1,  0, -1 ); break;
				case wolf_8n : wolf.enemy[i].position = wolf.enemy[i].position + float3(  0,  0, -1 ); break;
				case wolf_8nw: wolf.enemy[i].position = wolf.enemy[i].position + float3(  1,  0, -1 ); break;
				case wolf_8w : wolf.enemy[i].position = wolf.enemy[i].position + float3(  1,  0,  0 ); break;
				case wolf_8sw: wolf.enemy[i].position = wolf.enemy[i].position + float3(  1,  0,  1 ); break;
				case wolf_8s : wolf.enemy[i].position = wolf.enemy[i].position + float3(  0,  0,  1 ); break;
				case wolf_8se: wolf.enemy[i].position = wolf.enemy[i].position + float3( -1,  0,  1 ); break;
			}

			int x = int( wolf.enemy[i].position.x );
			int y = int( wolf.enemy[i].position.z );

			switch ( wolf.grid[ x + y * 64 ].a ) {
				case wolf_object_turn_e : wolf.enemy[i].face = wolf_8e ; break;
				case wolf_object_turn_ne: wolf.enemy[i].face = wolf_8ne; break;
				case wolf_object_turn_n : wolf.enemy[i].face = wolf_8n ; break;
				case wolf_object_turn_nw: wolf.enemy[i].face = wolf_8nw; break;
				case wolf_object_turn_w : wolf.enemy[i].face = wolf_8w ; break;
				case wolf_object_turn_sw: wolf.enemy[i].face = wolf_8sw; break;
				case wolf_object_turn_s : wolf.enemy[i].face = wolf_8s ; break;
				case wolf_object_turn_se: wolf.enemy[i].face = wolf_8se; break;
			}
		}
	}

	// update doors

	for ( int i = 0; i < 64 * 64; i++ ) {
		if ( wolf.grid[i].s == 1 ) {
			int j[4];

			j[0] = i -  1;
			j[1] = i +  1;
			j[2] = i - 64;
			j[3] = i + 64;

			for ( int k = 0; k < 4; k++ ) {
				if ( i == j[k] ) {
					zed_play_sound( sfx_wall_slide );
					wolf.grid[i].s = 0;
					wolf.grid[i].color = 106;
				}
			}
		}

		// floor
		if ( wolf.grid[i].color > 105 ) continue;
		// door
		else if ( wolf.grid[i].color > 53 ) {

		}
		// wall
		else continue;

		wolf.grid[i].t = min( max( wolf.grid[i].t * 64 + wolf.grid[i].d, 0 ), 64 ) / 64.0;

		if ( i == position.x + position.y * 64 ) {
			if ( wolf.grid[i].t == 0 ) zed_play_sound( sfx_door_open );
			wolf.grid[i].d = 1;
			wolf.grid[i].c = 2 * 64;
			// todo
			if ( wolf.grid[i].color == 100 or wolf.grid[i].color == 101 ) {
				wolf_level++;
				wolf_level_load( wolf_level );
				break;
			}
		} else {
			wolf.grid[i].c -= 1;

			if ( wolf.grid[i].c == 0 ) {
				zed_play_sound( sfx_door_close );
				wolf.grid[i].d = -1;
			}
		}
	}

	// update items

	for ( int i = 0; i < wolf.sprite_i; i++ ) {
		if (
			int( wolf.sprite[i].position.x + 0.5 ) == position.x &&
			int( wolf.sprite[i].position.z + 0.5 ) == position.y
		) {
			switch ( int( wolf.sprite[i].color + 0.5 ) ) {
				case wolf_item_food_dog    : zed_play_sound( sfx_foodup ); break;
				case wolf_item_key_gold    : zed_play_sound( sfx_getkey ); break;
				case wolf_item_key_silver  : zed_play_sound( sfx_getkey ); break;
				case wolf_item_food        : zed_play_sound( sfx_foodup ); break;
				case wolf_item_ifak        : zed_play_sound( sfx_mediup ); break;
				case wolf_item_ammo        : zed_play_sound( sfx_ammoup ); break;
				case wolf_item_gun_mach    : zed_play_sound( sfx_mgunup ); break;
				case wolf_item_gun_mini    : zed_play_sound( sfx_cgunup ); break;
				case wolf_item_loot_cross  : zed_play_sound( sfx_bonus1 ); break;
				case wolf_item_loot_chalice: zed_play_sound( sfx_bonus2 ); break;
				case wolf_item_loot_chest  : zed_play_sound( sfx_bonus3 ); break;
				case wolf_item_loot_crown  : zed_play_sound( sfx_bonus4 ); break;
				case wolf_item_extra_life  : zed_play_sound( sfx_bns1up ); break;
				default: continue;
			}

			wolf.sprite[i] = wolf.sprite[--wolf.sprite_i];
			if ( i == 0 ) break;
			i--;
			continue;
		}
	}

	//

	position_previous = position;
}
