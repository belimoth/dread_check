#include "maze.h"
#include "maze.clay.h"

#include "maze/draw.cpp"

void game_player_init();
void client_update_player();
void game_object_step();

void maze_init() {
	maze = {};
	maze_new();
}

void maze_start() {
	game.data = {};

	game_player_init();

	float3 p = float3( 32, 64, 32 );
	zed_random_seed( app.time );

	for( int i = 0; i < game_player_count_max; i++ ) {
		game_player &player = game.data.player[i];
		float3 ip = p + float3( zed_random_get( -2, 2 ), i * 2, 64 + i * 16 );
		ip = mul( ip + float3( 0.5, 0, 0.5 ), scale( wolf_scale ) );
		player.object.position = ip;
		game.data.camera[i].rotation.x = 45;
		game.data.camera[i].rotation.y = 180;
		player.stance = stance_sail;
		player.hands.which = 1;
		player.hands.j = 1;
		player.hands.item[ player.hands.item_i++ ].type = item_type[ item_none ];
		player.hands.item[ player.hands.item_i++ ].type = item_type[ item_bag  ];
		player.ammo_i = item_type[ item_us_1917_revolver ].ammo;
		player.hands.belt[ player.hands.belt_i++ ].type = item_type[ item_none             ];
		player.hands.belt[ player.hands.belt_i++ ].type = item_type[ item_us_1917_revolver ];
		player.hands.belt[ player.hands.belt_i++ ].type = item_type[ item_sword            ];
		player.bag.ammo[ ammo_45acp ] = 999;
	}

	for ( int i = 0; i < game_enemy_count_max; i++ ) {
		float3 ip = p + float3( zed_random_get( -32, 32 ), 0, zed_random_get( -32, 32 ) );
		ip = mul( ip + float3( 0.5, 0, 0.5 ), scale( wolf_scale ) );
		game.data.enemy[i].position = float2( ip.x, ip.z );
	}

	for ( int i = 0; i < snow_max; i++ ) {
		maze.snow[i].position = float3( zed_random_get( -8, 8 ), zed_random_get( -2, 0 ), zed_random_get( -8, 8 ) );
	}
}

struct maze_aabb {
	float x0, y0, x1, y1, z0, z1;
};

maze_aabb maze_get_aabb( int x, int y ) {
	maze_aabb aabb = {};

	aabb.x0 = x - 64;
	aabb.x1 = x + 64;
	aabb.y0 = y - 64;
	aabb.y1 = y + 64;

	if ( x >= 0 and x < 64 and y >= 0 and y < 64 ) {
		int i = x + y * 64, j;
		j = i -  1; if ( j > 0       ) if ( maze.grid[j].color ) aabb.x0 = x + 0;
		j = i +  1; if ( j < 64 * 64 ) if ( maze.grid[j].color ) aabb.x1 = x + 1;
		j = i - 64; if ( j > 0       ) if ( maze.grid[j].color ) aabb.y0 = y + 0;
		j = i + 64; if ( j < 64 * 64 ) if ( maze.grid[j].color ) aabb.y1 = y + 1;
	}

	return aabb;
}

void maze_player_step( game_player &player ) {
	int x = floor( player.object.position.x / wolf_scale );
	int y = floor( player.object.position.z / wolf_scale );

	maze_aabb aabb = maze_get_aabb( x, y );

	aabb.x0 *= wolf_scale;
	aabb.x1 *= wolf_scale;
	aabb.y0 *= wolf_scale;
	aabb.y1 *= wolf_scale;

	aabb.x0 +=  0.2;
	aabb.x1 += -0.2;
	aabb.y0 +=  0.2;
	aabb.y1 += -0.2;

	void game_player_step( game_player &player );
	game_player_step( player );

	if ( player.object.position.y < wolf_scale ) {
		player.object.position.x = min( max( player.object.position.x, aabb.x0 ), aabb.x1 );
		player.object.position.z = min( max( player.object.position.z, aabb.y0 ), aabb.y1 );
	}
}

void maze_step() {
	client_update_player();
	if ( game.is_paused ) return;
	if ( not game.is_started ) return;
	void game_bullet_step();
	game_bullet_step();
	// game_enemy_step();
	game_object_step();
	for ( int i = 0; i < game.player_count; i++ ) maze_player_step( game.data.player[i] );
}
