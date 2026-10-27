#pragma once

#include "world.h"

#include <zed/xmath.h>

struct game_aabb {
	float x0, y0, x1, y1, z0, z1;
};

struct game_object {
	float3 position;
	float3 rotation;
	float3 velocity;

	game_data_world_item *nav;
	game_data_world_item *nav_previous;

	game_aabb aabb_move;
};
