#pragma once

#include <zed/app.h>
#include <zed/app/graphics.h>

#include "../main.h"
#include "game.h"
#include "game/draw.h"

enum game_split {
	game_split_solo = 0,
	game_split_duo  = 1,
	game_split_trio = 2,
	game_split_quad = 3,
};

game_split split;

zed_canvas canvas_x1;
zed_canvas canvas_x2;
zed_canvas canvas_x4;
size2 canvas_size;
bool canvas_to_size;

void game_canvas_init();
void game_canvas_set_split_view( int i );
void game_canvas_before();
void game_canvas_after();
