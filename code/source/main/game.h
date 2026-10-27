#pragma once

#include "game/draw.h"

#include "game/player.h"
#include "game/bullet.h"
#include "game/enemy.h"
#include "game/world.h"
#include "game/menu.h"

#include <zed/app/graphics.h>
#include <zed/camera.h>
#include <zed/xmath.h>

enum game_scene {
	scene_none,
	scene_game,
	scene_maze,
	scene_wolf,

	scene_max
};

struct game_t {
	char user[32];
	uint seed;

	bool has_mouse;
	bool has_focus = true;
	bool is_paused;
	bool is_muted;
	bool is_started;

	bool config_enable_haptics = true;
	bool config_update_enemy   = true;
	bool config_render_ground  = true;
	bool config_render_city    = true;
	bool config_render_enemy   = true;
	bool config_render_gun     = true;
	bool config_render_hud     = true;

	struct game_config {
	} config;

	zed_camera camera;
	game_draw_t draw;

	game_menu menu[4];

	int player_count;

	struct game_data {
		#define game_player_count_max   64
		#define game_enemy_count_max   512
		#define game_wall_count_max      2
		#define game_bullet_count_max 1024
		#define game_flash_count_max    32
		#define game_shine_count_max    32
		#define game_chest_count_max    32
		#define game_object_count_max 1024

		zed_camera  camera[ game_player_count_max ];
		game_player player[ game_player_count_max ];
		game_enemy  enemy [ game_enemy_count_max  ];
		game_bullet bullet[ game_bullet_count_max ]; int bullet_i; int flash_i;
		game_shine  shine [ game_shine_count_max  ];
		game_wall   wall  [ game_wall_count_max   ];
		game_chest  chest [ game_chest_count_max  ];
		game_object object[ game_object_count_max ]; int object_i;

		float4 world_data[1024];
	} data;

	struct game_history {
		struct game_history_data {
			struct game_history_player_data {

			} player[ game_player_count_max ];
		} data[16];
	} history;

	game_world world;
	game_scene scene;
} game;

int view_mode;

//

bool show_mouse;

void game_show_mouse() {
	if ( show_mouse ) return;
	app_show_cursor();
	show_mouse = true;
}

void game_cursor_hide() {
	if ( not show_mouse ) return;
	app_hide_cursor();
	show_mouse = false;
}

void game_cursor_refresh() {
	if ( not game.has_mouse ) {
		app_hide_cursor();
		show_mouse = false;
	}
}
