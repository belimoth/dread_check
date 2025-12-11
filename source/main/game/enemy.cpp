#include <zed/random.h>
#include <zed/xmath.h>

#include "../game.h"
#include "player.h"

const float enemy_speed = 0.02;

float colors[9] = {
	0.5, 0, 0,
	0, 0.5, 0,
	0, 0, 0.5,
};

void game_enemy_init() {
	for ( int i = 0; i < game_enemy_count_max; i++ ) {
		game.data.enemy[i].position.x = zed_random_get( -8, 8 ) / 2.0;
		game.data.enemy[i].position.y = zed_random_get( -512, 0 ) - 64;
	}
}

void game_enemy_step() {
	for ( int i = 0; i < game_enemy_count_max; i++ ) {
		float2 position = game.data.enemy[i].position;

		position.y += enemy_speed;

		game.data.enemy[i].position = position;
	}
}
