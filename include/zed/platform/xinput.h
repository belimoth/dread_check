#pragma once

#ifndef zed_platform_windows
#error bad platform
#endif

#include <zed.h>

#include <xinput.h>
#pragma comment( lib, "xinput.lib" )

#pragma warning( push )
#pragma warning( disable : 4100 )

#define xinput_get_state_s( name ) uint32_t __stdcall name( uint32_t user_index, XINPUT_STATE *state )
typedef xinput_get_state_s( xinput_get_state_t );
xinput_get_state_s( xinput_get_state_stub ) { return ERROR_DEVICE_NOT_CONNECTED; }
xinput_get_state_t *xinput_get_state;

#define xinput_set_state_s( name ) uint32_t __stdcall name( uint32_t user_index, XINPUT_VIBRATION* vibration )
typedef xinput_set_state_s( xinput_set_state_t );
xinput_set_state_s( xinput_set_state_stub ) { return ERROR_DEVICE_NOT_CONNECTED; }
xinput_set_state_t *xinput_set_state;

#pragma warning( pop )
