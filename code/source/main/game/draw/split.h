#pragma once

#include "../../canvas.h"

#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/camera.h>

#define game_draw_set_camera_i for ( int i = 0; game_draw_set_camera( i ); i++ )

bool game_draw_set_camera( int i ) {
	if ( split == game_split_quad and i >= 4 ) return false;
	if ( split == game_split_trio and i >= 3 ) return false;
	if ( split == game_split_duo  and i >= 2 ) return false;
	if ( split == game_split_solo and i >= 1 ) return false;

	game_canvas_set_split_view(i);
	game.camera = game.data.camera[i];
	zed_camera_update( game.camera, &game.draw.camera );
	game_draw_per_frame_update();

	return true;
}
