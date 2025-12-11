#include <zed.h>

#include "../../game.h"
#include "../player.h"
#include "constants.h"

struct test_result {
	bool  pass;
	float dx, dy, dz;
};

// todo z

test_result test_aabb( game_aabb a, game_aabb b ) {
	float x0, x1, xs, y0, y1, ys, z0, z1, zs;

	if ( a.x0 < b.x0 ) { x0 = b.x0; x1 = a.x1; xs = -1; } else { x0 = a.x0; x1 = b.x1; xs = 1; }
	if ( a.y0 < b.y0 ) { y0 = b.y0; y1 = a.y1; ys = -1; } else { y0 = a.y0; y1 = b.y1; ys = 1; }
	if ( a.z0 < b.z0 ) { z0 = b.z0; z1 = a.z1; zs = -1; } else { z0 = a.z0; z1 = b.z1; zs = 1; }

	if ( x0 > x1 or y0 > y1 or z0 > z1 ) return { false, 0, 0, 0 };

	float dx = x1 - x0;
	float dy = y1 - y0;
	float dz = z1 - z0;

	float most = max( max( dx, dy ), dz );

	if ( dx == most ) return { true, 0, dy * ys, 0 };
	if ( dy == most ) return { true, dx * xs, 0, 0 };
	                  return { true, 0, 0, dz * zs };
}

game_aabb game_get_aabb( game_player &player ) {
	int x = floor( player.object.position.x );
	int y = floor( player.object.position.z );
	int z = floor( player.object.position.y );

	game_aabb aabb = {};

	aabb.x0 = x - 64;
	aabb.x1 = x + 64;
	aabb.y0 = y - 64;
	aabb.y1 = y + 64;
	aabb.z0 = z - 64;
	aabb.z1 = z + 64;

	float z_ground = 0;
	if ( player.object.nav ) z_ground = player.object.nav->p.z;
	if ( game_player_stance_is_airborne( player ) ) z_ground = player.object.position.y;

	if ( x >= 0 and x < 64 and y >= 0 and y < 64 ) {
		int i = x + y * 64, j;
		j = i -  1; if ( j > 0       ) if ( game_data_world[j].p.z > z_ground + 0.3 * 2.5 ) aabb.x0 = x + 0;
		j = i +  1; if ( j < 64 * 64 ) if ( game_data_world[j].p.z > z_ground + 0.3 * 2.5 ) aabb.x1 = x + 1;
		j = i - 64; if ( j > 0       ) if ( game_data_world[j].p.z > z_ground + 0.3 * 2.5 ) aabb.y0 = y + 0;
		j = i + 64; if ( j < 64 * 64 ) if ( game_data_world[j].p.z > z_ground + 0.3 * 2.5 ) aabb.y1 = y + 1;
	}

	return aabb;
}

void game_player_physics_before( game_player &player ) {
	if ( game.scene != scene_game ) return;
	player.object.aabb_move = game_get_aabb( player );

	player.object.aabb_move.x0 +=  0.2;
	player.object.aabb_move.x1 += -0.2;
	player.object.aabb_move.y0 +=  0.2;
	player.object.aabb_move.y1 += -0.2;
}

void game_player_physics_after( game_player &player ) {
	if ( game.scene != scene_game ) return;
	player.object.position.x = min( max( player.object.position.x, player.object.aabb_move.x0 ), player.object.aabb_move.x1 );
	player.object.position.z = min( max( player.object.position.z, player.object.aabb_move.y0 ), player.object.aabb_move.y1 );
	player.object.position.y = min( max( player.object.position.y, player.object.aabb_move.z0 ), player.object.aabb_move.z1 );
}

void game_player_physics_step( game_player &player ) {
	// note
	return;

	game_aabb aabb_player = {};
	aabb_player.x0 = player.object.position.x - 0.3;
	aabb_player.y0 = player.object.position.z - 0.3;
	aabb_player.x1 = player.object.position.x + 0.3;
	aabb_player.y1 = player.object.position.z + 0.3;

	for ( int i = 0; i < game_wall_count_max; i++ ) {
		game_wall w = game.data.wall[i];

		game_aabb aabb_wall = {};
		aabb_wall.x0 = w.p0.x;
		aabb_wall.y0 = w.p0.z;
		aabb_wall.x1 = w.p1.x;
		aabb_wall.y1 = w.p1.z;

		test_result result = test_aabb( aabb_player, aabb_wall );

		if ( result.pass ) {
			player.object.position.x += result.dx;
			player.object.position.z += result.dy;

			if ( player.stance == stance_jog or player.stance == stance_run ) {
				player.stance = stance_walk;
			}
		}
	}
}
