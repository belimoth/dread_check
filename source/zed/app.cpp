#include "app/0_config.cpp"
#include "app/1_system.cpp"
#include "app/2_graphics.cpp"
#include "app/3_audio.cpp"
#include "app/4_input.cpp"
#include "app/5_ui.cpp"
#include "app/debug.cpp"

// user

void main_init();
void main_size();
void main_idle();
void main_start();
void main_step();
void main_draw();
void main_on_system_event( app_system_event );
void main_exit();

//

void app_init() {
	// thread
	CoInitialize(0);

	app_system_init_before();
	app_options_init();
	app_config_init_default();
	main_init();

	app_debug_init();
	app_system_init();

	// todo why resize twice
	app_graphics_size();
	app_graphics_init();
	app_graphics_size();

	app_audio_init();
	app_input_init();
	app_ui_init();

	//
	app_system_init_after();

	// user
	main_start();
}

void app_exit() {
	main_exit();
	CoUninitialize();
	app_graphics_exit();
	exit(0);
}

void app_step() {
	app_system_step();
	main_step();
	app_input_step();
}

void app_draw() {
	if ( app.size ) { app.size = false; app_graphics_size(); }
	app_graphics_draw();
}

int main() {
	app_init();

	while ( not app.quit ) {
		app_step();
		app_draw();
		app.time += 1;
	}

	app_exit();
	return 0;
}

//

void app_quit() {
	app.quit = true;
}

void app_hide_cursor() {
	ShowCursor( false );
	SetCapture( (HWND)app.system.window );
}

void app_show_cursor() {
	ShowCursor( true );
	ReleaseCapture();
}

void app_center_cursor() {
	RECT client;
	GetClientRect( (HWND)app.system.window, &client );

	ClipCursor( &client );

	SetCursorPos(
		( client.left + client.right  ) / 2,
		( client.top  + client.bottom ) / 2
	);
}
