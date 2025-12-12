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
		case game_menu_page_maze : game_menu_action_start_maze_1p( menu );      break;
		case game_menu_page_pause: menu.state.page = game_menu_page_none;       break;
		case game_menu_page_start: game_menu_push( menu, game_menu_page_play ); break;
		case game_menu_page_play : game_menu_action_start_game_1p( menu );      break;
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

zed_pad update_pad_0();
zed_pad update_pad_0_keyboard_only();
zed_pad update_pad_i( int i );

void game_menu_update_0() {
	if ( split == game_split_solo ) {
		hud_ps = update_pad_0();
	} else {
		hud_ps = update_pad_0_keyboard_only();
	}

	if ( game.has_mouse ) {
		game.menu[0].state.x = -1;
		game.menu[0].state.y = -1;

		game_menu_main( game.menu[0], game_menu_signal_hover );

		if ( not hud_ps.start and hud_ps_previous.start ) game_menu_hide_mouse();
		if ( not hud_ps.a     and hud_ps_previous.a     ) game_menu_hide_mouse();
		if ( not hud_ps.b     and hud_ps_previous.b     ) game_menu_hide_mouse();
		if ( not hud_ps.n     and hud_ps_previous.n     ) game_menu_hide_mouse();
		if ( not hud_ps.s     and hud_ps_previous.s     ) game_menu_hide_mouse();
		if ( app_input.get.key_w     .rise              ) game_menu_hide_mouse();
		if ( app_input.get.key_s     .rise              ) game_menu_hide_mouse();
		if ( app_input.get.key_up    .rise              ) game_menu_hide_mouse();
		if ( app_input.get.key_down  .rise              ) game_menu_hide_mouse();
		if ( app_input.get.key_escape.rise              ) game_menu_hide_mouse();
		if ( app_input.get.key_space .rise              ) game_menu_hide_mouse();
		if ( app_input.get.key_back  .rise              ) game_menu_hide_mouse();

		if ( app_input.get.key_mouse_l.rise ) hud_on_select( game.menu[0] );
	} else {
		if ( not hud_ps.start and hud_ps_previous.start ) hud_on_start     ( game.menu[0] );
		if ( not hud_ps.a     and hud_ps_previous.a     ) hud_on_select    ( game.menu[0] );
		if ( not hud_ps.b     and hud_ps_previous.b     ) game_menu_action_back( game.menu[0] );
		if ( app_input.get.key_escape.rise              ) game_menu_action_back( game.menu[0] );
		if ( app_input.get.key_back.rise                ) game_menu_action_back( game.menu[0] );
		if ( hud_ps.n and not hud_ps_previous.n         ) hud_on_n         ( game.menu[0] );
		if ( app_input.get.key_w.fall                   ) hud_on_n         ( game.menu[0] );
		if ( app_input.get.key_up.fall                  ) hud_on_n         ( game.menu[0] );
		if ( hud_ps.s and not hud_ps_previous.s         ) hud_on_s         ( game.menu[0] );
		if ( app_input.get.key_s.fall                   ) hud_on_s         ( game.menu[0] );
		if ( app_input.get.key_down.fall                ) hud_on_s         ( game.menu[0] );
		if ( hud_ps.w and not hud_ps_previous.w         ) hud_on_w         ( game.menu[0] );
		if ( app_input.get.key_a.fall                   ) hud_on_w         ( game.menu[0] );
		if ( app_input.get.key_left.fall                ) hud_on_w         ( game.menu[0] );
		if ( hud_ps.e and not hud_ps_previous.e         ) hud_on_e         ( game.menu[0] );
		if ( app_input.get.key_d.fall                   ) hud_on_e         ( game.menu[0] );
		if ( app_input.get.key_right.fall               ) hud_on_e         ( game.menu[0] );
	}


	hud_ps_previous = hud_ps;
}

void game_menu_update_1() {
	if ( split == game_split_solo ) return;
	hud_ps_1 = update_pad_i(1);

	if ( not hud_ps_1.start   and hud_ps_1_previous.start ) hud_on_start     ( game.menu[1] );
	if ( not hud_ps_1.a       and hud_ps_1_previous.a     ) hud_on_select    ( game.menu[1] );
	if ( not hud_ps_1.b       and hud_ps_1_previous.b     ) game_menu_action_back( game.menu[1] );
	if ( hud_ps_1.n and not hud_ps_1_previous.n           ) hud_on_n         ( game.menu[1] );
	if ( hud_ps_1.s and not hud_ps_1_previous.s           ) hud_on_s         ( game.menu[1] );

	hud_ps_1_previous = hud_ps_1;
}
