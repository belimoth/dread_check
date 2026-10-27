#pragma once

#include <zed/app/audio.h>

zed_sound sfx_foot[4];
uint      sfx_foot_i = 0;

#define field( name, path ) zed_sound name;
#include "sfx/game.inl"
#include "sfx/wolf.inl"
#undef field

void data_sfx_init() {
	zed_load_sound( sfx_foot[0], "data/audio/player/foot_stone01.wav" );
	zed_load_sound( sfx_foot[1], "data/audio/player/foot_stone02.wav" );
	zed_load_sound( sfx_foot[2], "data/audio/player/foot_stone03.wav" );
	zed_load_sound( sfx_foot[3], "data/audio/player/foot_stone04.wav" );

	#define field( name, path ) zed_load_sound( name, path );
	#include "sfx/game.inl"
	#include "sfx/wolf.inl"
	#undef field
}
