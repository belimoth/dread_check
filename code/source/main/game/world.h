#pragma once

#include <zed/xmath.h>

//

struct game_data_world_item {
	float3 alignas(16) p;
	float padding;
};

game_data_world_item game_data_world[ 64 * 64 ];

//

struct game_wall {
	float3 alignas(16) p0, p1;
};

//

enum zed_space_type {
	space_type_none,
	space_type_grid,
	space_type_tree,
	space_type_mesh,
};

enum zed_space_grid_type {
	space_grid_type_xx,   // square
	space_grid_type_xy,   // rectangular
	space_grid_type_xyxy, // alternating
};

struct zed_space_grid {
	zed_space_grid_type type;
	int2 position;
	int2 size;
};

enum zed_space_tree_type {

};

struct zed_space_tree {
	zed_space_tree_type type;
	int2 position;
	int2 size;
};

struct zed_space {
	zed_space_type type;

	union {
		zed_space_grid grid;
		zed_space_tree tree;
	};

	zed_space *children;
};

//

enum game_world_node_type {
	game_world_node_type_none,
	game_world_node_type_grid,
	game_world_node_type_hmap,
	game_world_node_type_wmap,
};

struct game_world_node {
	game_world_node_type type;
	handle               data;
	game_world_node     *node;
	int                  node_count;
};

#define game_world_node_count_max 256

struct game_world {
	game_world_node node[ game_world_node_count_max ];
	int node_count;
};

//

struct game_chest {
	game_data_world_item as_item;
};
