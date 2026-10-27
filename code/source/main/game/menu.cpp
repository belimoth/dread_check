#include "menu.h"

#include "../../data/gfx.h"
#include "../../data/sfx.h"
#include "../../data/names.h"
#include "../canvas.h"
#include "../game.h"
#include "../game/roster.h"
#include "../maze.h"

#include <zed.h>
#include <zed/app/audio.h>
#include <zed/app/input.h>
#include <zed/app/ui.h>

void scene_game_start_for_real();

#include "menu/action.h"
#include "menu/sfx.h"

#include "menu/event.h"

#include "menu/main.cpp"

void hud_on_select( game_menu &menu ) {
	game_menu_main( menu, game_menu_signal_select );
}

int game_menu_get_count( game_menu &menu ) {
	game_menu_main( menu, game_menu_signal_none );
	return menu.j;
}

#include "menu/draw.h"

void hud_on_n( game_menu &menu ) {
	int count = game_menu_get_count( menu );
	menu.state.y = ( menu.state.y + count - 1 ) % count;
	menu_sfx_hover();
}

void hud_on_s( game_menu &menu ) {
	int count = game_menu_get_count( menu );
	menu.state.y = ( menu.state.y + 1 ) % count;
	menu_sfx_hover();
}

void hud_on_w( game_menu &menu ) {
	game_menu_main( menu, game_menu_signal_left );
}

void hud_on_e( game_menu &menu ) {
	game_menu_main( menu, game_menu_signal_right );
}

void hud_on_start( game_menu &menu ) {
	switch ( menu.state.page ) {
		case game_menu_page_pause: menu.state.page = game_menu_page_none;       break;
		case game_menu_page_start: game_menu_push( menu, game_menu_page_play ); break;
		case game_menu_page_play:  game_menu_action_start_game_1p( menu );      break;
	}
}

void main_on_mouse_activity() {
	use_mouse = true;
	game.has_mouse = true;
	if ( not game.menu[0].state.page ) return;
	game_show_mouse();
}

zed_pad hud_ps;
zed_pad hud_ps_previous;

zed_pad hud_ps_1;
zed_pad hud_ps_1_previous;

zed_pad pad_step_0( zed_pad );
zed_pad pad_step_0_keyboard_only( zed_pad );
zed_pad pad_step_i( int i, zed_pad );

void game_menu_step_0() {
	if ( split == game_split_solo ) {
		hud_ps = pad_step_0( hud_ps_previous );
	} else {
		hud_ps = pad_step_0_keyboard_only( hud_ps_previous );
	}

	if ( game.has_mouse ) {
		game.menu[0].state.x = -1;
		game.menu[0].state.y = -1;

		game_menu_main( game.menu[0], game_menu_signal_hover );

		if ( hud_ps.start.rise ) game_menu_hide_mouse();
		if ( hud_ps.a.rise     ) game_menu_hide_mouse();
		if ( hud_ps.b.rise     ) game_menu_hide_mouse();
		if ( hud_ps.n.rise     ) game_menu_hide_mouse();
		if ( hud_ps.s.rise     ) game_menu_hide_mouse();
		if ( app_input.get.key_w     .rise ) game_menu_hide_mouse();
		if ( app_input.get.key_s     .rise ) game_menu_hide_mouse();
		if ( app_input.get.key_up    .rise ) game_menu_hide_mouse();
		if ( app_input.get.key_down  .rise ) game_menu_hide_mouse();
		if ( app_input.get.key_escape.rise ) game_menu_hide_mouse();
		if ( app_input.get.key_space .rise ) game_menu_hide_mouse();
		if ( app_input.get.key_back  .rise ) game_menu_hide_mouse();

		if ( app_input.get.key_mouse_l.rise ) hud_on_select( game.menu[0] );
	} else {
		if ( hud_ps.start.rise             ) hud_on_start         ( game.menu[0] );
		if ( hud_ps.a.rise                 ) hud_on_select        ( game.menu[0] );
		if ( hud_ps.b.rise                 ) game_menu_action_back( game.menu[0] );
		if ( app_input.get.key_escape.rise ) game_menu_action_back( game.menu[0] );
		if ( app_input.get.key_back.rise   ) game_menu_action_back( game.menu[0] );
		if ( hud_ps.n.fall                 ) hud_on_n             ( game.menu[0] );
		if ( app_input.get.key_w.fall      ) hud_on_n             ( game.menu[0] );
		if ( app_input.get.key_up.fall     ) hud_on_n             ( game.menu[0] );
		if ( hud_ps.s.fall                 ) hud_on_s             ( game.menu[0] );
		if ( app_input.get.key_s.fall      ) hud_on_s             ( game.menu[0] );
		if ( app_input.get.key_down.fall   ) hud_on_s             ( game.menu[0] );
		if ( hud_ps.w.fall                 ) hud_on_w             ( game.menu[0] );
		if ( app_input.get.key_a.fall      ) hud_on_w             ( game.menu[0] );
		if ( app_input.get.key_left.fall   ) hud_on_w             ( game.menu[0] );
		if ( hud_ps.e.fall                 ) hud_on_e             ( game.menu[0] );
		if ( app_input.get.key_d.fall      ) hud_on_e             ( game.menu[0] );
		if ( app_input.get.key_right.fall  ) hud_on_e             ( game.menu[0] );
	}

	hud_ps_previous = hud_ps;
}

void game_menu_step_1() {
	if ( split == game_split_solo ) return;
	hud_ps_1 = pad_step_i( 1, hud_ps_1_previous );

	if ( hud_ps_1.start.rise ) hud_on_start         ( game.menu[1] );
	if ( hud_ps_1.a.rise     ) hud_on_select        ( game.menu[1] );
	if ( hud_ps_1.b.rise     ) game_menu_action_back( game.menu[1] );
	if ( hud_ps_1.n.fall     ) hud_on_n             ( game.menu[1] );
	if ( hud_ps_1.s.fall     ) hud_on_s             ( game.menu[1] );

	hud_ps_1_previous = hud_ps_1;
}
