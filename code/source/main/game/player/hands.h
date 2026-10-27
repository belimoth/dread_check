#pragma once

#include "item.h"

struct game_player_hands {
	bool goofy;
	int i, j, k, which;
	game_item item[8]; int item_i;
	game_item belt[8]; int belt_i;
};
