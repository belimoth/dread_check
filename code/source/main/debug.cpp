#include <zed/app.h>
#include <zed/app/debug.h>

void app_system_profiler_report();

void debug_main() {
	zed_debug_say( "简体中文\n" );

	app_system_profiler_report();

	if ( app.options.headless ) app_exit();
}
