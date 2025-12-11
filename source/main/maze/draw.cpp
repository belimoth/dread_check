#include "../../data/gfx.h"
#include "../game/draw/split.h"

#include <zed/app.h>
#include <zed/app/graphics.h>

void game_draw_player();
void game_draw_bullet();

void maze_draw_maze() {
	zed_mesh_draw_instanced( mesh_cube, &data_maze, maze_max );
}

void maze_draw_sky() {
	zed_camera temp = game.camera;
	temp.position   = { 0, 0, 0 };
	zed_camera_update( temp, &game.draw.camera );
	game_draw_per_frame_update();

	zed_mesh_draw_primitive( zed_primitive_triangle_list, 3 );
}

void maze_draw_chest() {
	zed_mesh_draw_instanced( mesh_cube, &data_chest, maze.chest_i );
}

void maze_draw_snow() {
	float3 position = game.camera.position;
	game_draw_per_object_set( position );
	zed_mesh_draw_primitive( zed_primitive_point_list, snow_max - 1 );
}

void maze_draw() {
	// game.camera = game.data.camera[0];
	// zed_camera_update( game.camera, &game.draw.camera );
	// game_draw_per_frame_update();

	game.draw.per_object.matrix_world = identity * scale( wolf_scale );
	game_draw_per_object_update();

	pass_ante = pass_null;
	if ( view_mode == 1 ) pass_ante = pass_debug_normal;
	if ( view_mode == 2 ) pass_ante = pass_debug_depth;
	if ( view_mode == 3 ) pass_ante = pass_debug_overdraw;

	int j = 0;

	for ( int y = 0; y < 64; y++ ) {
	for ( int x = 0; x < 64; x++ ) {
		int i = x + y * 64;

		if ( maze.grid[i].color == 1 ) {
			maze_cell_r cell = {};
			cell.position.x = x;
			cell.position.y = y;
			cell.size.x = 1;
			cell.size.y = 1;
			maze.data[ j++ ] = cell;
		}

		if ( j == maze_max ) break;
	}
		if ( j == maze_max ) break;
	}

	zed_buffer_update( data_maze, zed_data( maze.data ) );

	zed_pass_reset();
	zed_pass_set( pass_maze );
	zed_pass_set( pass_ante );
	// zed_pass_use( gfx_maze       );
	// zed_pass_use( gfx_maze_mm    );
	zed_pass_use( gfx_maze_mm_nn );
	// zed_pass_use( gfx_maze_lod_a );
	// zed_pass_use( gfx_maze_lod_b );
	// zed_pass_use( gfx_maze_mm_x2 );
	// zed_pass_use( gfx_maze_mm_x4 );
	// zed_pass_use( gfx_maze_mm_x8 );
	// zed_pass_use( gfx_maze_mm_xx );
	game_draw_set_camera_i maze_draw_maze();

	//

	zed_pass_reset();
	zed_pass_set( pass_main_maze );
	zed_pass_set( pass_ante );

	// player

	game_draw_player();

	// enemy

	game.draw.per_object.matrix_world = identity;
	game_draw_per_object_update();
	zed_buffer_update( data_enemy, zed_data( game.data.enemy ) );
	zed_pass_reset();
	zed_pass_set( pass_enemy_maze );
	zed_pass_set( pass_ante  );
	game_draw_set_camera_i zed_mesh_draw_instanced( mesh_player, &data_enemy, game_enemy_count_max );

	// chests

	zed_pass_reset();
	zed_pass_set( pass_chest );
	game.draw.per_object.matrix_world = identity * scale( wolf_scale );
	game_draw_per_object_update();
	zed_buffer_update( data_chest, zed_data( maze.chest ) );
	game_draw_set_camera_i maze_draw_chest();

	// bullets

	zed_pass_reset( pass_bullet );
	game.draw.per_object.matrix_world = identity;
	game_draw_per_object_update();
	zed_buffer_update( data_bullet, zed_data( game.data.bullet ) );
	game_draw_set_camera_i game_draw_bullet();

	// snow

	// zed_pass_reset( pass_snow );
	// game.draw.per_object.matrix_world = identity;
	// game_draw_per_object_update();
	// zed_buffer_update( data_snow, zed_data( maze.snow ) );
	// game_draw_set_camera_i maze_draw_snow();

	// sky

	zed_pass_reset();
	zed_pass_set( pass_sky_maze );
	// zed_pass_set( pass_ante_floor );
	game_draw_set_camera_i maze_draw_sky();
}
