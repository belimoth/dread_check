#include <stdio.h>

#include <zed.h>
#include <zed/app.h>
#include <zed/platform/windows.h>

void app_debug_init() {
	if ( not app.options.debug ) return;

	if ( AttachConsole( ATTACH_PARENT_PROCESS ) or AllocConsole() ) {
		freopen( "CONOUT$", "w", stdout );
		freopen( "CONOUT$", "w", stderr );
	}

	SetConsoleOutputCP( CP_UTF8 );
}

void app_debug_exit() {
	//
}
