#pragma once

#include "gfx/game.h"
#include "gfx/maze.h"
#include "gfx/wolf.h"

void data_gfx_init() {
	data_gfx_game_init();
	data_gfx_maze_init();
	data_gfx_wolf_init();
}
