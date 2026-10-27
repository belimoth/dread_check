#pragma once

#ifdef zed_mode_debug
#include <stdio.h>
#include <zed/app.h>
#include <zed/platform/windows.h>
#define zed_debug_say( ... ) { if ( app.options.debug ) printf( __VA_ARGS__ ); }
#else
#define zed_debug_say( ... ) {}
#endif
