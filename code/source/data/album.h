#pragma once

#include <zed/app/graphics.h>

#define field( name, path ) zed_texture name;
#include "album/album.inl"
#undef field

void data_gfx_album_init() {
	#define field( name, path ) name = zed_texture_new_2d( path );
	#include "album/album.inl"
	#undef field
}
