#pragma once

#define XAUDIO2_HELPER_FUNCTIONS
#include <xaudio2.h>
// #pragma comment( lib, "xaudio2.lib" )

struct zed_sound {
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;
	IXAudio2SourceVoice *pSourceVoice;
};
