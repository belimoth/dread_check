#pragma once

#include <zed.h>

// #include <zed/platform/audio/xaudio.h>

#pragma warning( push )
#pragma warning( disable : 4505 )
#include <zed/platform/audio/miniaudio.h>
#pragma warning( pop )

void zed_load_sound( zed_sound &sound, int    id   );
void zed_load_sound( zed_sound &sound, string file );
void zed_play_sound( zed_sound &sound, float volume = 0, float pitch = 0 );
