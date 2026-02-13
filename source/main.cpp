#include "main.h"

#include <zed.h>
#define  zed_platform_windows
#include <zed/platform/windows-minimal-before.h>
#include <zed/app.h>
#include <zed/app/input.h>
#include <zed/heap.h>
#include <zed/camera.h>
#include <zed/random.h>

#include <zed/platform/github.h>
#include <zed/platform/itch.h>
// #include <zed/platform/discord.h>
#include <zed/platform/x64.h>

#include "clay.cpp"
#include "clay/midi.cpp"

#include "main/debug.cpp"
#include "main/edit.cpp"

#include "main/canvas.cpp"

#include "main/game.cpp"
#include "main/maze.cpp"
#include "main/wolf.cpp"

#include "input.cpp"
#include "haptic.cpp"

void app_ui_draw();
void app_ui_on_system_event( app_system_event );

void main_init() {
	app.config.title = "DREAD CHECK";
	app.config.window.type = app_window_type_game;
}

void main_size() {
	// todo probable game_draw_per_scene_update
}

void main_idle() {
	//
}

void main_start() {
	if ( app.options.debug ) debug_main();
	if ( app.options.debug ) sprintf( app.user, "zach" );
	if ( app.options.debug ) sprintf( itch.user, "belimoth" );

	zed_x64_init();
	zed_random_seed( 90u, 82u );
	heap_init();

	itch_init();
	// zed_discord_init();
	// network_init_server();
	github_init();
	// haptic_init();

	game_canvas_init();

	game_init();
	game_start();
	scene_game_start();

	clay_init();
}

void main_step() {
	if ( app_input.get.key_escape.fall ) app_exit();

	if ( app_input.get.key_oem_3.fall ) {
		if ( app_input.get.key_control.held ) {
			clay_toggle();
		} else {
			view_mode = ( view_mode + 1 ) % 4;
		}
	}

	if ( clay.show ) {
		clay_step();
	} else {
		// haptic_step();

		switch ( game.scene ) {
			case scene_game: game_step(); break;
			case scene_maze: maze_step(); break;
			case scene_wolf: wolf_step(); break;
		}

		if ( game.has_focus and not show_mouse and not app.system.idle ) app_center_cursor();
	}
}

void main_draw() {
	if ( clay.show ) {
		game_canvas_before();

		switch ( clay.page ) {
			case clay_page_menu_play:
			case clay_page_menu_view:
			game_draw();
			break;

			case clay_page_menu_edit:
			case clay_page_menu_find:
			clay_draw();
			break;

			case clay_page_menu_sync:
			case clay_page_menu_itch:
			case clay_page_menu_user:
			break;
		}

		game_canvas_after();
		app_ui_draw();
	} else {
		game_canvas_before();
		game_draw();
		game_canvas_after();
		game_draw_ui();
	}
}

void main_on_system_event( app_system_event event ) {
	app_ui_on_system_event( event );
}

void main_exit() {

}

void main_midi( midi_event event ) {
	clay_midi( event );
}

#include "zed/app.cpp"
