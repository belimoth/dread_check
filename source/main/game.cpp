#include "../data/gfx.h"

#include "../main.h"
#include "game.h"
#include "game/draw.h"

#include "game/bullet.cpp"
#include "game/enemy.cpp"
#include "game/menu.cpp"
#include "game/object.cpp"
#include "game/player.cpp"
#include "game/roster.h"
#include "game/world.cpp"

#include "game/draw.cpp"

#include <zed/app.h>
#include <zed/app/system.h>
#include <zed/app/graphics.h>
#include <zed/app/input.h>

void game_init() {
	data_sfx_init();
	data_gfx_init();

	game_draw_init();
	game_draw_per_scene_update();

	game_item_init();
	game_roster_init();

	app_hide_cursor();
}

void scene_game_start() {
	game.data = {};

	game_world_init();
	game_enemy_init();
	game_player_init();

	for ( int i = 0; i < game_player_count_max; i++ ) {
		game_player &player = game.data.player[i];
		player.torso = torso_hip;
		player.hands = {};
		player.hands.j = 3;
		player.hands.item[ player.hands.item_i++ ].type = item_type[ item_none             ];
		player.hands.item[ player.hands.item_i++ ].type = item_type[ item_wi_1897_shotgun  ];
		player.hands.item[ player.hands.item_i++ ].type = item_type[ item_ak_1947          ];
		player.hands.item[ player.hands.item_i++ ].type = item_type[ item_bag              ];

		player.hands.belt[ player.hands.belt_i++ ].type = item_type[ item_none             ];
		player.hands.belt[ player.hands.belt_i++ ].type = item_type[ item_ammo             ];
		player.hands.belt[ player.hands.belt_i++ ].type = item_type[ item_torch            ];
		player.hands.belt[ player.hands.belt_i++ ].type = item_type[ item_us_1917_revolver ];
		player.hands.belt[ player.hands.belt_i++ ].type = item_type[ item_sword            ];
		player.hands.belt[ player.hands.belt_i++ ].type = item_type[ item_grenade          ];
		player.bag.ammo[ ammo_12ga_bird ] = 6 * 5;
		player.bag.ammo[ ammo_12ga_buck ] = 6 * 5;
		player.bag.ammo[ ammo_12ga_slug ] = 6 * 5;
		player.bag.ammo[ ammo_45acp     ] = 999;
	}
}

void scene_game_start_for_real() {
	for ( int i = 0; i < game_player_count_max; i++ ) {
		game_player_hands_switch_primary( game.data.player[i], 1 );
	}
}

void game_start() {
	game.is_started = false;
	game.is_paused  = false;
	game.player_count = 1;
	split = game_split_solo;
	game.menu[0].state = { game_menu_page_start };
	game.scene = scene_game;
	scene_game_start();
}

void game_step() {
	client_update_player();
	if ( game.is_paused ) return;
	// if ( not game.is_started ) return;
	game_bullet_step();
	game_enemy_step();
	game_object_step();
	for ( int i = 0; i < game.player_count; i++ ) game_player_step( game.data.player[i] );
}
