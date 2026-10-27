#include <zed/platform/windows.h>
#include <zed/platform/xinput.h>

void load_xinput() {
	HMODULE xinput_lib = LoadLibraryA( "xinput1_4.dll" );
	if ( ! xinput_lib ) xinput_lib = LoadLibraryA( "xinput9_1_0.dll" );
	if ( ! xinput_lib ) xinput_lib = LoadLibraryA( "xinput1_3.dll" );
	if ( ! xinput_lib ) zed_die();

	#pragma warning( suppress : 4191 )
	xinput_get_state = (xinput_get_state_t *)GetProcAddress( xinput_lib, "XInputGetState" );

	if ( ! xinput_get_state ) {
		xinput_get_state = xinput_get_state_stub;
	}
}
