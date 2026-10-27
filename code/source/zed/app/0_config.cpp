#include <zed/app.h>

#pragma warning( push )
#pragma warning( disable: 4365 )
#pragma warning( disable: 4530 )
#pragma warning( disable: 4800 )
#include <argh.h>
#pragma warning( pop )

argh::parser parser( __argv );

void app_options_init() {
	app.options.debug    = parser[{ "debug"    }];
	app.options.headless = parser[{ "headless" }];

	// note --headless implies --debug
	app.options.debug |= app.options.headless;
}

bool app_options_check( string flag ) {
	return parser[{ flag }];
}

void app_config_init_default() {
	app.config.title = "Game";
}
