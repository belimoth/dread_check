#pragma once

#define MA_ENABLE_ONLY_SPECIFIC_BACKENDS
#define MA_ENABLE_WASAPI
#define MINIAUDIO_IMPLEMENTATION
#pragma warning( push )
#pragma warning( disable : 4191 )
#pragma warning( disable : 4365 )
#pragma warning( disable : 4459 )
#pragma warning( disable : 5219 )
#pragma warning( disable : 5262 )
#include <miniaudio/miniaudio.h>
#pragma warning( pop )

struct zed_sound {
	ma_decoder decoder;

	// todo introduce "zed_voice"

	bool is_playing;
	float volume;
};
