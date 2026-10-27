#pragma once

#include <zed/xmath.h>

struct game_enemy {
	float2 alignas( 8) position;
	float  alignas( 4) orientation;
};
