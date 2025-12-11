
#include "../../../main.h"
#include "../../game.h"
#include "../../game/draw.h"

#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/camera.h>
#include <zed/xmath.h>
#include <zed/platform/d3d11.h>

//

void game_draw_per_scene_update() {
	// note
	game.draw.per_scene.screen_width  = app.graphics.render_target.size.x;
	game.draw.per_scene.screen_height = app.graphics.render_target.size.y;

	zed_buffer_update( data_per_scene, &game.draw.per_scene, sizeof( game_draw_per_scene ), 0 );
}

void game_draw_per_frame_update() {
	float fov = 60;

	game.draw.camera.matrix_clip = zed_camera_get_projection_matrix( fov );
	// todo
	game.draw.camera.matrix_tiwv = transpose( inverse( game.draw.per_object.matrix_world * game.draw.camera.matrix_view ) );
	// todo
	game.draw.camera.matrix_iwvc = inverse( game.draw.per_object.matrix_world * game.draw.camera.matrix_view * game.draw.camera.matrix_clip );

	game_draw_per_frame data = {};

	data.camera = {
		game.draw.camera.matrix_view,
		game.draw.camera.matrix_clip,

		game.draw.camera.matrix_tiwv,
		game.draw.camera.matrix_iwvc,

		game.camera.position,
		game.draw.camera.look,
	};

	data.light    = game.draw.light;
	data.vignette = game.draw.vignette;

	zed_buffer_update( data_per_frame, &data, sizeof( data ), 0 );
}

void game_draw_per_object_update() {
	zed_buffer_update( data_per_object, &game.draw.per_object, sizeof( game_draw_per_object ), 0 );
}

//

void game_draw_per_object_set( float3 position ) {
	game.draw.per_object.matrix_world = translate( position );
	game_draw_per_object_update();
}

void game_draw_per_object_set( float3 position, float3 rotation ) {
	matrix temp = identity;

	temp = temp * zed_camera_get_rotation_matrix( rotation );
	temp = temp * translate                     ( position );

	game.draw.per_object.matrix_world = temp;

	game_draw_per_object_update();
}

void game_draw_per_object_set_for_player( float3 position, float3 handle, float3 rotation, float3 rotationBefore ) {
	matrix temp = identity;

	temp = temp * zed_camera_get_rotation_matrix( rotationBefore );
	temp = temp * translate                     ( handle         );
	temp = temp * zed_camera_get_rotation_matrix( rotation       );
	temp = temp * translate                     ( position       );

	game.draw.per_object.matrix_world = temp;

	game_draw_per_object_update();
}

void game_draw_alpha_set( float value ) {
	union alignas(16) { float alpha; };
	alpha = value;
	zed_buffer_update( data_alpha, &alpha, sizeof( game_draw_alpha ), 0 );
}
