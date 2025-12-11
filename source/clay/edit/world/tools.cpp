#include "../../../data/gfx.h"

#include "../../../main.h"
#include "../../../main/game/draw.h"
#include "../../../main/game.h"
#include "../world.h"

#include <zed/app/graphics.h>
#include <zed/xmath.h>

void game_draw_per_scene_update();
void game_draw_per_frame_update();
void game_draw_per_object_update();

void snap_to_corner( float3 *position ) {
	position->x = floor( position->x ) + 0.5;
	position->z = floor( position->z ) + 0.5;
}

void snap_to_border( float3 *position ) {
	// todo
}

void snap_to_center( float3 *position ) {
	position->x = round( position->x );
	position->z = round( position->z );
}

void snap_to_either( float3 *position ) {
	position->x = round( position->x * 2 ) / 2;
	position->z = round( position->z * 2 ) / 2;
}

void tool_room_on_ui_event( ui_event event ) {
	pick();
	float3 position = cursor;
	snap_to_center( &position );

	switch ( event.type ) {
		case event_type_down: {
			if ( cursor.x >  7.5 ) return;
			if ( cursor.z >  7.5 ) return;
			if ( cursor.x < -8.5 ) return;
			if ( cursor.z < -8.5 ) return;

			dragging = true;

			clay_edit_world_brush brush = {};
			// todo floor( float3, etc ) in xmath.h
			brush.p0.x = position.x;
			brush.p0.y = position.y;
			brush.p0.z = position.z;
			brush.p1.x = position.x;
			brush.p1.y = position.y;
			brush.p1.z = position.z;
			clay_we_data.brushes[ clay_we_data.brushes_count++ ] = brush;

			// todo implement prevent_drag() in zed_ui, in case the brush creation is rejected

			break;
		}

		case event_type_drag: {
			if ( ! dragging ) return;

			if ( position.x >  7 ) position.x =  7;
			if ( position.z >  7 ) position.z =  7;
			if ( position.x < -8 ) position.x = -8;
			if ( position.z < -8 ) position.z = -8;

			clay_we_data.brushes[ clay_we_data.brushes_count - 1 ].p1.x = position.x;
			clay_we_data.brushes[ clay_we_data.brushes_count - 1 ].p1.y = position.y;
			clay_we_data.brushes[ clay_we_data.brushes_count - 1 ].p1.z = position.z;

			break;
		}

		case event_type_click: {

			// dragging = false;

			break;
		}
	}
}

void tool_pick_draw() {
	//
}

void tool_room_draw() {
	float3 position = cursor;
	snap_to_center( &position );

	game_draw_alpha_set( 0.5 );

	matrix temp    = identity;
	float3 handle  = { -0.5, 0, -0.5 };
	float3 scaling = { 1, 3, 1 };
	temp = mul( temp, translate( handle   ) );
	temp = mul( temp, scale    ( scaling  ) );
	temp = mul( temp, translate( position ) );
	game.draw.per_object.matrix_world = temp;
	game_draw_per_object_update();
	zed_mesh_draw( mesh_cube );

	game_draw_alpha_set( 1.0 );
}

void tool_yard_draw() {
	float3 position = cursor;
	snap_to_center( &position );

	game_draw_alpha_set( 0.5 );

	float3 handle  = { -0.5, 0, -0.5 };
	float3 scaling = { 1, 0.2, 1 };
	matrix temp = identity;
	temp = mul( temp, translate( handle   ) );
	temp = mul( temp, scale    ( scaling  ) );
	temp = mul( temp, translate( position ) );
	game.draw.per_object.matrix_world = temp;
	game_draw_per_object_update();
	zed_mesh_draw( mesh_cube );

	game_draw_alpha_set( 1.0 );
}

void tool_wall_draw() {
	float3 position = cursor;
	snap_to_corner( &position );

	game_draw_alpha_set( 0.5 );

	float3 handle  = { -0.5, 0, -0.5 };
	float3 scaling = { wall_thickness, wall_height, wall_thickness };
	matrix temp = identity;
	temp = mul( temp, translate( handle   ) );
	temp = mul( temp, scale    ( scaling  ) );
	temp = mul( temp, translate( position ) );
	game.draw.per_object.matrix_world = temp;
	game_draw_per_object_update();
	zed_mesh_draw( mesh_cube );

	game_draw_alpha_set( 1.0 );
}

void tool_tour_draw() {
	float3 position = cursor;
	snap_to_either( &position );

	matrix temp = identity;
	temp = mul( temp, translate( position ) );
	game.draw.per_object.matrix_world = temp;
	game_draw_per_object_update();
	zed_mesh_draw( mesh_player );
}
