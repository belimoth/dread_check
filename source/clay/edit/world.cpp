#include "../../clay.h"
#include "../../data/gfx.h"
#include "../../main.h"
#include "../../main/canvas.h"
#include "../../main/game/draw.h"

#include "world.h"
#include "world/tools.cpp"
#include "world/ui.cpp"

#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

void clay_edit_world_init() {
	clay.camera.position.x =  -0.5;
	clay.camera.position.y =  10;
	clay.camera.position.z = -12;
	clay.camera.rotation.x =  45;

	// todo

	// ui.root.handle_ui_event = edit_world_on_ui_event;

	ui.handle_ui_event = clay_edit_world_on_ui_event;
}

void clay_edit_world_step() {
	if ( app_input.get.key_escape.fall ) app_exit();
	clay_edit_world_ui_step();
}

void clay_edit_world_draw_walls( float height, float thickness ) {
	for ( int i = 0; i < clay_we_data.brushes_count; i++ ) {
		matrix temp = identity;

		float3 scaling     = { 1, 1, 1 };
		float3 translation = { 0, 0, 0 };

		clay_edit_world_brush brush = clay_we_data.brushes[i];

		float x_min =  FLT_MAX;
		float y_min =  FLT_MAX;
		float x_max = -FLT_MAX;
		float y_max = -FLT_MAX;

		x_min = min( x_min, brush.p0.x );
		x_min = min( x_min, brush.p1.x );
		y_min = min( y_min, brush.p0.z );
		y_min = min( y_min, brush.p1.z );
		x_max = max( x_max, brush.p0.x );
		x_max = max( x_max, brush.p1.x );
		y_max = max( y_max, brush.p0.z );
		y_max = max( y_max, brush.p1.z );

		scaling.x = ( x_max - x_min + 1 + thickness );
		scaling.y = height;
		scaling.z = ( y_max - y_min + 1 + thickness );

		translation.x = x_min - 0.5 - thickness / 2;
		translation.y = brush.p0.y;
		translation.z = y_min - 0.5 - thickness / 2;

		temp = mul( temp, scale    ( scaling     ) );
		temp = mul( temp, translate( translation ) );

		game.draw.per_object.matrix_world = temp;
		game_draw_per_object_update();

		zed_mesh_draw( mesh_cube );
	}
}

void clay_edit_world_draw_cursor() {
	if ( cursor.x >  7.5 ) return;
	if ( cursor.z >  7.5 ) return;
	if ( cursor.x < -8.5 ) return;
	if ( cursor.z < -8.5 ) return;

	//

	game.draw.per_object.matrix_world = identity;
	game_draw_per_object_update();

	switch ( tool_i ) {
		case tool_pick: tool_pick_draw(); break;
		case tool_room: tool_room_draw(); break;
		case tool_yard: tool_yard_draw(); break;
		case tool_wall: tool_wall_draw(); break;
		case tool_tour: tool_tour_draw(); break;
	}
}

void clay_edit_world_draw() {
	clay.camera.position.y = 10 + floor_i * wall_height;

	// zed_camera_update( clay.camera, &game.camera );
	// game_draw_per_frame_update();

	//

	pass_main.bs = blend_states.alpha;
	zed_pass_reset( pass_main );
	pass_main.bs = 0;
	clay_edit_world_draw_walls( wall_height, wall_thickness );
	// if ( floor_i < 0 ) game_draw_alpha_set( 0.2 );
	// game.draw.per_object.matrix_world = identity;
	// game_draw_per_object_update();
	// zed_mesh_draw( mesh_clay_grid );

	// game_draw_alpha_set( 1.0 );

	//

	clay_edit_world_draw_cursor();
}

void clay_edit_world_draw_ui() {
	zed_pass_reset( clay.gfx.pass_grid );
	game.draw.per_object.matrix_world = mul( identity, translate( 0, floor_i * wall_height + 0.01, 0 ) );
	game_draw_per_object_update();
	zed_mesh_draw( clay.gfx.mesh_grid );
}
