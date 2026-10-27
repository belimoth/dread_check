#include "../../data/gfx/clay.h"
#include "../../main.h"
#include "../../main/game.h"
#include "../../clay.h"

#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/app/ui.h>

void tool_camera_on( ui_event event ) {
	switch( event.type ) {
		case event_type_wheel:
		clay.edit_model.camera_zoom += -event.delta.z * 0.1;
		break;

		case event_type_down:
		latch_reset();
		break;

		case event_type_drag:
		latch_test( &event );

		switch ( event.type ) {
			case event_type_none:
			break;

			case event_type_down:
			clay.edit_model.rotation_start_x = game.camera.rotation.x;
			clay.edit_model.rotation_start_y = game.camera.rotation.y;
			clay.edit_model.rotation_delta_x = 0;
			clay.edit_model.rotation_delta_y = 0;
			break;

			default:
			clay.edit_model.rotation_delta_x = event.delta.y;
			clay.edit_model.rotation_delta_y = event.delta.x;
		}

		break;

		case event_type_click2:
		// todo tween back to zero instead of snapping
		clay.edit_model.rotation_start_x = 0;
		clay.edit_model.rotation_start_y = 0;
		clay.edit_model.rotation_delta_x = 0;
		clay.edit_model.rotation_delta_y = 0;
		break;
	}
}

void tool_cursor_on( ui_event event ) {
	switch( event.type ) {
		case event_type_wheel:
		clay.edit_model.camera_zoom += -event.delta.z * 0.1;
		break;

		case event_type_down:
		latch_reset();
		break;

		case event_type_drag:
		latch_test( &event );

		switch ( event.type ) {
			case event_type_none:
			break;

			case event_type_down:
			clay.edit_model.cursor_start = game.camera.position;
			clay.edit_model.cursor_delta = {};
			break;

			default:
			// todo handle other planes
			clay.edit_model.cursor_delta.x = -event.delta.x / 1024.0;
			clay.edit_model.cursor_delta.y =  event.delta.y / 1024.0;
		}

		break;

		case event_type_click2:
		// todo tween back to zero instead of snapping
		clay.edit_model.cursor_start = {};
		clay.edit_model.cursor_delta = {};
		break;
	}
}

void edit_model_on( ui_event event ) {
	switch ( event.type ) {
		case event_type_wheel:
		tool_camera_on( event );
		break;

		case event_type_down:
		case event_type_drag:
		case event_type_click:
		case event_type_click2:

		switch ( event.which ) {
			case 0: break;
			case 1: tool_camera_on( event ); break;
			case 2: tool_cursor_on( event ); break;
		}

		break;
	}
}

#include "../studio.cpp"

void clay_edit_model_init() {
	studio_init();

	clay.edit.path[ clay.edit.path_i++ ] = "data/model/enemy.obj";
	clay.edit.path[ clay.edit.path_i++ ] = "data/model/player.obj";
	clay.edit.path[ clay.edit.path_i++ ] = "data/model/shotgun.obj";
	clay.edit.path[ clay.edit.path_i++ ] = "game/demo.world";
}

void clay_edit_model_step() {
	// zed_show_cursor();

	// game.draw_camera.rotation.x += midi.control[16] * 360.0 / 16.0;
	// game.draw_camera.rotation.y += midi.control[17] * 360.0 / 16.0;
	// game.draw_camera.rotation.z += midi.control[18] * 360.0 / 16.0;

	if ( clay.ui.data_inspect.id_target == 0 ) {
		clay.edit_model.studio.ambient_0.x += midi.control[16] / 255.0;
		clay.edit_model.studio.ambient_0.y += midi.control[17] / 255.0;
		clay.edit_model.studio.ambient_0.z += midi.control[18] / 255.0;

		clay.edit_model.studio.ambient_0.x = clamp( clay.edit_model.studio.ambient_0.x );
        clay.edit_model.studio.ambient_0.y = clamp( clay.edit_model.studio.ambient_0.y );
        clay.edit_model.studio.ambient_0.z = clamp( clay.edit_model.studio.ambient_0.z );
	}

	if ( clay.ui.data_inspect.id_target == 1 ) {
		clay.edit_model.studio.ambient_1.x += midi.control[16] / 255.0;
		clay.edit_model.studio.ambient_1.y += midi.control[17] / 255.0;
		clay.edit_model.studio.ambient_1.z += midi.control[18] / 255.0;

		clay.edit_model.studio.ambient_1.x = clamp( clay.edit_model.studio.ambient_1.x );
        clay.edit_model.studio.ambient_1.y = clamp( clay.edit_model.studio.ambient_1.y );
        clay.edit_model.studio.ambient_1.z = clamp( clay.edit_model.studio.ambient_1.z );
	}

	midi = {};

	// camera

	game.camera.rotation.x = clay.edit_model.rotation_start_x + clay.edit_model.rotation_delta_x / 16.0;
	game.camera.rotation.y = clay.edit_model.rotation_start_y + clay.edit_model.rotation_delta_y /  8.0;

	game.camera.rotation.x = clamp( game.camera.rotation.x, -90 + 0.001, 90 - 0.001 );

	// cursor

	game.camera.position = clay.edit_model.cursor_start + clay.edit_model.cursor_delta;
}

void clay_edit_model_draw() {
	zed_camera_update_orbit( game.camera, &game.draw.camera, clay.edit_model.camera_zoom );
	game_draw_per_frame_update();

	if ( false ) {
		zed_pass_reset( clay.gfx.pass_plane );

		// game.draw.per_object.matrix_world = identity;
		// game_draw_per_object( game.camera.position );

		zed_mesh_draw( clay.gfx.mesh_plane );
	}

	int id = clay.ui.data_layers.id_target;
	if ( clay.ui.data_layers.id_preview != -1 ) id = clay.ui.data_layers.id_preview;

	if ( id == 0 ) zed_pass_reset( clay.gfx.pass_composite );
	if ( id == 1 ) zed_pass_reset( clay.gfx.pass_normals   );
	if ( id == 2 ) zed_pass_reset( clay.gfx.pass_wireframe );

	game.draw.per_object.matrix_world = identity;
	game_draw_per_object_update();

	// todo
	zed_buffer_update( clay.edit_model.buffer_studio, &clay.edit_model.studio, sizeof(clay.edit_model.studio), 0 );
	zed_buffer_use_uniform( clay.edit_model.buffer_studio, 3 );

	zed_mesh_draw( clay.edit_model.mesh );
}
