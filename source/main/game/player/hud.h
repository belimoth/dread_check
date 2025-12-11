#pragma once

enum game_player_hint {
	hint_none   = 0,
	hint_prone  = 1,
	hint_crawl  = 2,
	hint_crouch = 3,
	hint_stalk  = 4,
	hint_stand  = 5,
	hint_reach  = 6,

	hint_supine,
	hint_side,

	hint_a_menu,
	hint_b_menu,
	hint_x_menu,
	hint_y_menu,
	hint_z_menu,

	hint_jog,
	hint_run,
	hint_jump,
	hint_fall,
	hint_sail,
	hint_skid,
	hint_trip,
	hint_dive,
	hint_spin,
	hint_slide,

	hint_aim,
	hint_load,
	hint_rack,
	hint_swap,

	hint_hold,
	hint_grab,
	hint_push,
	hint_toss,
};
