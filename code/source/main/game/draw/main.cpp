#include "../draw/split.h"

#include "../../../data/gfx.h"
#include "../../game/draw.h"
#include "../../game.h"
#include "../player.h"

#include <zed/app.h>
#include <zed/camera.h>
#include <zed/xmath.h>
#include <zed/platform/d3d11.h>

#include "main/player.cpp"

void zed_canvas_fill( zed_canvas &canvas, uint color_in );

// enemy

void game_draw_enemy() {
	zed_mesh_draw_instanced( mesh_enemy, &data_enemy, game_enemy_count_max );
}

void game_draw_enemy_hitbox() {
	zed_mesh_draw_instanced( mesh_cube, &data_enemy, game_enemy_count_max );
}

// bullet

void game_draw_bullet() { zed_mesh_draw_instanced( mesh_bullet, &data_bullet, game.data.bullet_i ); }

// ground

void game_draw_ground() {
	float3 position = game.camera.position;
	position.x = position.x + 1024 * 16;
	position.y = 0;
	position.z = position.z + 1024 * 16;

	game_draw_per_object_set( position );

	zed_mesh_draw( mesh_ground );
}

// world

void game_draw_world() {
	zed_mesh_draw_instanced( mesh_cube, &data_world, 64 * 64 );
}

// pc

// matrix pc_position = translate( 0, 1, -4 );
// matrix pc_position = translate( 0, 1, -1.5 );
// matrix pc_position = translate( -0.15, 1, -1.1 );
matrix pc_position = translate( 0, 1, -4 );

void game_draw_pc() {
	game.draw.per_object.matrix_world = rotate( 0, dtor(-90), 0 ) * scale(0.3) * pc_position;
	game_draw_per_object_update();
	zed_mesh_draw( mesh_pc );

	game.draw.per_object.matrix_world = translate( -0.5, -1, -0.5 ) * scale( 1.6, 0.05, 1.6) * pc_position;
	game_draw_per_object_update();
	zed_mesh_draw( mesh_cube );

	game.draw.per_object.matrix_world = translate( -0.5, -1, -0.5 ) * scale( 0.1, 1, 0.1 ) * pc_position;
	game_draw_per_object_update();
	zed_mesh_draw( mesh_cube );

	game.draw.per_object.matrix_world = translate( -0.5, 0, -0.5 ) * scale( 0.5, 0.05, 0.5 ) * translate( 0, -0.4 * 2.4384, 0 ) * pc_position;
	game_draw_per_object_update();
	zed_mesh_draw( mesh_cube );
}

void game_draw_pc_screen() {
	game.draw.per_object.matrix_world = rotate( 0, dtor(-90), 0 ) * scale(0.3) * pc_position;
	game_draw_per_object_update();
	zed_mesh_draw( mesh_pc_screen );
}

void game_draw_ciws() {
	game.draw.per_object.matrix_world = translate( 0, 0, -1 );
	game_draw_per_object_update();
	zed_mesh_draw( mesh_ciws );
}

void game_draw_main() {
	zed_pass pass_ante = pass_null;

	if ( view_mode == 1 ) pass_ante = pass_wolf_wall_n;
	if ( view_mode == 2 ) pass_ante = pass_wolf_wall_d;
	if ( view_mode == 3 ) pass_ante = pass_debug_overdraw;

	//

	zed_pass_reset();
	zed_pass_set( pass_main );
	zed_pass_set( pass_ante );

	// player
	game_draw_player();

	// walls

// 	game.draw.per_object.matrix_world = identity;
// 	game_draw_per_object_update();
//
// 	for ( int i = 0; i < game_wall_count_max; i++ ) {
// 		float3 position = game.data.wall[i].p0;
// 		float3 rotation = {};
// 		game_draw_per_object_set( position, rotation );
//
// 		zed_mesh_draw( mesh_cube );
// 	}

	// us navy phalanx mk 15 ciws

	// game.draw.per_object.matrix_world = identity;
	// game_draw_per_object_update();
	// zed_pass_reset();
	// zed_pass_set( pass_world );
	// zed_pass_set( pass_ante  );
	// game_draw_set_camera_i ciws_draw();

	// pc canvas before

	// todo move this somewhere where we don't have to reset render target
	zed_set_render_target( canvas_pc_screen.render_target );
	zed_canvas_fill( canvas_pc_screen, 0 );
	zed_set_render_target( canvas_x1.render_target );

	// pc

	zed_pass_reset();
	zed_pass_set( pass_pc_screen );
	zed_pass_set( pass_ante );
	game.draw.per_object.matrix_world = pc_position;
	game_draw_per_object_update();

	if ( game.is_started ) {
		zed_use_canvas_3d( canvas_pc_screen );
	} else {
		zed_pass_use( gfx_start_1984 );
	}

	game_draw_set_camera_i game_draw_pc_screen();

	zed_pass_reset();
	zed_pass_set( pass_main );
	zed_pass_set( pass_ante );
	game_draw_set_camera_i game_draw_pc();

	game.draw.per_object.matrix_world = identity;

	// world

	game.draw.per_object.matrix_world = identity;
	game_draw_per_object_update();
	zed_buffer_update( data_world, zed_data( game_data_world ) );
	zed_pass_reset();
	zed_pass_set( pass_world );
	zed_pass_set( pass_ante  );
	game_draw_set_camera_i game_draw_world();

	// enemy

	game.draw.per_object.matrix_world = identity;
	game_draw_per_object_update();
	zed_buffer_update( data_enemy, zed_data( game.data.enemy ) );
	zed_pass_reset();
	zed_pass_set( pass_enemy );
	zed_pass_set( pass_ante  );
	game_draw_set_camera_i game_draw_enemy();

	// ground

	game_draw_set_camera_i game_draw_ground();
}
