#pragma once

struct {
	float x, y, z;
} game_mouse;

// midi

#include <zed.h>

struct midi_event {
	char channel;
	char command;
	char data_0;
	char data_1;
};

void midi_init();
void main_midi( midi_event event );

// keyboard

enum zed_key {
	key_mouse_l = 0x01,
	key_mouse_r = 0x02,
	key_cancel  = 0x03,
	key_mouse_m = 0x04,
	key_mouse_x = 0x05,
	key_mouse_y = 0x06,

	key_back = 0x08,
	key_tab  = 0x09,

	key_clear  = 0x0C,
	key_return = 0x0D,

	key_shift   = 0x10,
	key_control = 0x11,
	key_menu    = 0x12,
	key_pause   = 0x13,
	key_capital = 0x14,

	key_escape = 0x1B,

	key_space    = 0x20,
	key_prior    = 0x21,
	key_next     = 0x22,
	key_end      = 0x23,
	key_home     = 0x24,
	key_left     = 0x25,
	key_up       = 0x26,
	key_right    = 0x27,
	key_down     = 0x28,
	key_select   = 0x29,
	key_print    = 0x2A,
	key_execute  = 0x2B,
	key_snapshot = 0x2C,
	key_insert   = 0x2D,
	key_delete   = 0x2E,
	key_help     = 0x2F,

	key_0 = 0x30,
	key_1 = 0x31,
	key_2 = 0x32,
	key_3 = 0x33,
	key_4 = 0x34,
	key_5 = 0x35,
	key_6 = 0x36,
	key_7 = 0x37,
	key_8 = 0x38,
	key_9 = 0x39,

	key_a = 0x41,
	key_b = 0x42,
	key_c = 0x43,
	key_d = 0x44,
	key_e = 0x45,
	key_f = 0x46,
	key_g = 0x47,
	key_h = 0x48,
	key_i = 0x49,
	key_j = 0x4A,
	key_k = 0x4B,
	key_l = 0x4C,
	key_m = 0x4D,
	key_n = 0x4E,
	key_o = 0x4F,
	key_p = 0x50,
	key_q = 0x51,
	key_r = 0x52,
	key_s = 0x53,
	key_t = 0x54,
	key_u = 0x55,
	key_v = 0x56,
	key_w = 0x57,
	key_x = 0x58,
	key_y = 0x59,
	key_z = 0x5A,

	key_numpad_0 = 0x60,
	key_numpad_1 = 0x61,
	key_numpad_2 = 0x62,
	key_numpad_3 = 0x63,
	key_numpad_4 = 0x64,
	key_numpad_5 = 0x65,
	key_numpad_6 = 0x66,
	key_numpad_7 = 0x67,
	key_numpad_8 = 0x68,
	key_numpad_9 = 0x69,

	key_numpad_multiply  = 0x6A,
	key_numpad_add       = 0x6B,
	key_numpad_separator = 0x6C,
	key_numpad_subtract  = 0x6D,
	key_numpad_decimal   = 0x6E,
	key_numpad_divide    = 0x6F,

	key_f1  = 0x70,
	key_f2  = 0x71,
	key_f3  = 0x72,
	key_f4  = 0x73,
	key_f5  = 0x74,
	key_f6  = 0x75,
	key_f7  = 0x76,
	key_f8  = 0x77,
	key_f9  = 0x78,
	key_f10 = 0x79,
	key_f11 = 0x7A,
	key_f12 = 0x7B,
	key_f13 = 0x7C,
	key_f14 = 0x7D,
	key_f15 = 0x7E,
	key_f16 = 0x7F,
	key_f17 = 0x80,
	key_f18 = 0x81,
	key_f19 = 0x82,
	key_f20 = 0x83,
	key_f21 = 0x84,
	key_f22 = 0x85,
	key_f23 = 0x86,
	key_f24 = 0x87,

	key_numlock = 0x90,
	key_scroll  = 0x91,

	key_lshift   = 0xA0,
	key_rshift   = 0xA1,
	key_lcontrol = 0xA2,
	key_rcontrol = 0xA3,
	key_lmenu    = 0xA4,
	key_rmenu    = 0xA5,

	key_browser_back      = 0xA6,
	key_browser_forward   = 0xA7,
	key_browser_refresh   = 0xA8,
	key_browser_stop      = 0xA9,
	key_browser_search    = 0xAA,
	key_browser_favorites = 0xAB,
	key_browser_home      = 0xAC,

	key_volume_mute         = 0xAD,
	key_volume_down         = 0xAE,
	key_volume_up           = 0xAF,
	key_media_next_track    = 0xB0,
	key_media_prev_track    = 0xB1,
	key_media_stop          = 0xB2,
	key_media_play_pause    = 0xB3,
	key_launch_mail         = 0xB4,
	key_launch_media_select = 0xB5,
	key_launch_app1         = 0xB6,
	key_launch_app2         = 0xB7,

	key_oem_1      = 0xBA,
	key_oem_plus   = 0xBB,
	key_oem_comma  = 0xBC,
	key_oem_minus  = 0xBD,
	key_oem_period = 0xBE,
	key_oem_2      = 0xBF,
	key_oem_3      = 0xC0,

	key_gamepad_a                       = 0xC3,
	key_gamepad_b                       = 0xC4,
	key_gamepad_x                       = 0xC5,
	key_gamepad_y                       = 0xC6,
	key_gamepad_right_shoulder          = 0xC7,
	key_gamepad_left_shoulder           = 0xC8,
	key_gamepad_left_trigger            = 0xC9,
	key_gamepad_right_trigger           = 0xCA,
	key_gamepad_dpad_up                 = 0xCB,
	key_gamepad_dpad_down               = 0xCC,
	key_gamepad_dpad_left               = 0xCD,
	key_gamepad_dpad_right              = 0xCE,
	key_gamepad_menu                    = 0xCF,
	key_gamepad_view                    = 0xD0,
	key_gamepad_left_thumbstick_button  = 0xD1,
	key_gamepad_right_thumbstick_button = 0xD2,
	key_gamepad_left_thumbstick_up      = 0xD3,
	key_gamepad_left_thumbstick_down    = 0xD4,
	key_gamepad_left_thumbstick_right   = 0xD5,
	key_gamepad_left_thumbstick_left    = 0xD6,
	key_gamepad_right_thumbstick_up     = 0xD7,
	key_gamepad_right_thumbstick_down   = 0xD8,
	key_gamepad_right_thumbstick_right  = 0xD9,
	key_gamepad_right_thumbstick_left   = 0xDA,
};

struct app_input_key_state {
	bool fall;
	bool held;
	bool rise;
	uint time;
};

struct app_input {
	union {
		app_input_key_state keys[0x100];

		struct app_input_keys {
			app_input_key_state key_unassigned_00;

			//

			app_input_key_state key_mouse_l;
			app_input_key_state key_mouse_r;
			app_input_key_state key_cancel;
			app_input_key_state key_mouse_m;
			app_input_key_state key_mouse_x;
			app_input_key_state key_mouse_y;

			//

			app_input_key_state key_unassigned_07;

			//

			app_input_key_state key_back;
			app_input_key_state key_tab;

			//

			app_input_key_state key_unassigned_0A;
			app_input_key_state key_unassigned_0B;

			//

			app_input_key_state key_clear;
			app_input_key_state key_return;

			//

			app_input_key_state key_unassigned_0E;
			app_input_key_state key_unassigned_0F;

			//

			app_input_key_state key_shift;
			app_input_key_state key_control;
			app_input_key_state key_menu;
			app_input_key_state key_pause;
			app_input_key_state key_capital;

			//

			app_input_key_state key_kana;

			//

			app_input_key_state key_unassigned_16;

			//

			app_input_key_state key_junja;
			app_input_key_state key_final;
			app_input_key_state key_kanji;

			//

			app_input_key_state key_unassigned_1A;

			//

			app_input_key_state key_escape;

			//

			app_input_key_state key_convert;
			app_input_key_state key_nonconvert;
			app_input_key_state key_accept;
			app_input_key_state key_modechange;

			//

			app_input_key_state key_space;
			app_input_key_state key_prior;
			app_input_key_state key_next;
			app_input_key_state key_end;
			app_input_key_state key_home;
			app_input_key_state key_left;
			app_input_key_state key_up;
			app_input_key_state key_right;
			app_input_key_state key_down;
			app_input_key_state key_select;
			app_input_key_state key_print;
			app_input_key_state key_execute;
			app_input_key_state key_snapshot;
			app_input_key_state key_insert;
			app_input_key_state key_delete;
			app_input_key_state key_help;

			//

			app_input_key_state key_0;
			app_input_key_state key_1;
			app_input_key_state key_2;
			app_input_key_state key_3;
			app_input_key_state key_4;
			app_input_key_state key_5;
			app_input_key_state key_6;
			app_input_key_state key_7;
			app_input_key_state key_8;
			app_input_key_state key_9;

			//

			app_input_key_state key_unassigned_3A;
			app_input_key_state key_unassigned_3B;
			app_input_key_state key_unassigned_3C;
			app_input_key_state key_unassigned_3D;
			app_input_key_state key_unassigned_3E;
			app_input_key_state key_unassigned_3F;
			app_input_key_state key_unassigned_40;

			//

			app_input_key_state key_a;
			app_input_key_state key_b;
			app_input_key_state key_c;
			app_input_key_state key_d;
			app_input_key_state key_e;
			app_input_key_state key_f;
			app_input_key_state key_g;
			app_input_key_state key_h;
			app_input_key_state key_i;
			app_input_key_state key_j;
			app_input_key_state key_k;
			app_input_key_state key_l;
			app_input_key_state key_m;
			app_input_key_state key_n;
			app_input_key_state key_o;
			app_input_key_state key_p;
			app_input_key_state key_q;
			app_input_key_state key_r;
			app_input_key_state key_s;
			app_input_key_state key_t;
			app_input_key_state key_u;
			app_input_key_state key_v;
			app_input_key_state key_w;
			app_input_key_state key_x;
			app_input_key_state key_y;
			app_input_key_state key_z;

			//

			app_input_key_state key_lwin;
			app_input_key_state key_rwin;
			app_input_key_state key_apps;

			//

			app_input_key_state key_unassigned_5E;


			//

			app_input_key_state key_sleep;

			//

			app_input_key_state key_numpad_0;
			app_input_key_state key_numpad_1;
			app_input_key_state key_numpad_2;
			app_input_key_state key_numpad_3;
			app_input_key_state key_numpad_4;
			app_input_key_state key_numpad_5;
			app_input_key_state key_numpad_6;
			app_input_key_state key_numpad_7;
			app_input_key_state key_numpad_8;
			app_input_key_state key_numpad_9;

			//

			app_input_key_state key_numpad_multiply;
			app_input_key_state key_numpad_add;
			app_input_key_state key_numpad_separator;
			app_input_key_state key_numpad_subtract;
			app_input_key_state key_numpad_decimal;
			app_input_key_state key_numpad_divide;

			//

			app_input_key_state key_f1;
			app_input_key_state key_f2;
			app_input_key_state key_f3;
			app_input_key_state key_f4;
			app_input_key_state key_f5;
			app_input_key_state key_f6;
			app_input_key_state key_f7;
			app_input_key_state key_f8;
			app_input_key_state key_f9;
			app_input_key_state key_f10;
			app_input_key_state key_f11;
			app_input_key_state key_f12;
			app_input_key_state key_f13;
			app_input_key_state key_f14;
			app_input_key_state key_f15;
			app_input_key_state key_f16;
			app_input_key_state key_f17;
			app_input_key_state key_f18;
			app_input_key_state key_f19;
			app_input_key_state key_f20;
			app_input_key_state key_f21;
			app_input_key_state key_f22;
			app_input_key_state key_f23;
			app_input_key_state key_f24;

			//

			app_input_key_state key_navigation_view;
			app_input_key_state key_navigation_menu;
			app_input_key_state key_navigation_up;
			app_input_key_state key_navigation_down;
			app_input_key_state key_navigation_left;
			app_input_key_state key_navigation_right;
			app_input_key_state key_navigation_accept;
			app_input_key_state key_navigation_cancel;

			//

			app_input_key_state key_numlock;
			app_input_key_state key_scroll;

			//

			app_input_key_state key_oem_fj_jisho;
			app_input_key_state key_oem_fj_masshou;
			app_input_key_state key_oem_fj_touroku;
			app_input_key_state key_oem_fj_loya;
			app_input_key_state key_oem_fj_roya;

			//

			app_input_key_state key_unassigned_97;
			app_input_key_state key_unassigned_98;
			app_input_key_state key_unassigned_99;
			app_input_key_state key_unassigned_9A;
			app_input_key_state key_unassigned_9B;
			app_input_key_state key_unassigned_9C;
			app_input_key_state key_unassigned_9D;
			app_input_key_state key_unassigned_9E;
			app_input_key_state key_unassigned_9F;


			//

			app_input_key_state key_lshift;
			app_input_key_state key_rshift;
			app_input_key_state key_lcontrol;
			app_input_key_state key_rcontrol;
			app_input_key_state key_lmenu;
			app_input_key_state key_rmenu;

			//

			app_input_key_state key_browser_back;
			app_input_key_state key_browser_forward;
			app_input_key_state key_browser_refresh;
			app_input_key_state key_browser_stop;
			app_input_key_state key_browser_search;
			app_input_key_state key_browser_favorites;
			app_input_key_state key_browser_home;

			//

			app_input_key_state key_volume_mute;
			app_input_key_state key_volume_down;
			app_input_key_state key_volume_up;
			app_input_key_state key_media_next_track;
			app_input_key_state key_media_prev_track;
			app_input_key_state key_media_stop;
			app_input_key_state key_media_play_pause;
			app_input_key_state key_launch_mail;
			app_input_key_state key_launch_media_select;
			app_input_key_state key_launch_app1;
			app_input_key_state key_launch_app2;

			//

			app_input_key_state key_unassigned_B8;
			app_input_key_state key_unassigned_B9;

			//

			app_input_key_state key_oem_1;
			app_input_key_state key_oem_plus;
			app_input_key_state key_oem_comma;
			app_input_key_state key_oem_minus;
			app_input_key_state key_oem_period;
			app_input_key_state key_oem_2;
			app_input_key_state key_oem_3;

			//

			app_input_key_state key_unassigned_C1;
			app_input_key_state key_unassigned_C2;

			//

			app_input_key_state key_gamepad_a;
			app_input_key_state key_gamepad_b;
			app_input_key_state key_gamepad_x;
			app_input_key_state key_gamepad_y;
			app_input_key_state key_gamepad_right_shoulder;
			app_input_key_state key_gamepad_left_shoulder;
			app_input_key_state key_gamepad_left_trigger;
			app_input_key_state key_gamepad_right_trigger;
			app_input_key_state key_gamepad_dpad_up;
			app_input_key_state key_gamepad_dpad_down;
			app_input_key_state key_gamepad_dpad_left;
			app_input_key_state key_gamepad_dpad_right;
			app_input_key_state key_gamepad_menu;
			app_input_key_state key_gamepad_view;
			app_input_key_state key_gamepad_left_thumbstick_button;
			app_input_key_state key_gamepad_right_thumbstick_button;
			app_input_key_state key_gamepad_left_thumbstick_up;
			app_input_key_state key_gamepad_left_thumbstick_down;
			app_input_key_state key_gamepad_left_thumbstick_right;
			app_input_key_state key_gamepad_left_thumbstick_left;
			app_input_key_state key_gamepad_right_thumbstick_up;
			app_input_key_state key_gamepad_right_thumbstick_down;
			app_input_key_state key_gamepad_right_thumbstick_right;
			app_input_key_state key_gamepad_right_thumbstick_left;

			//

			app_input_key_state key_oem_4;
			app_input_key_state key_oem_5;
			app_input_key_state key_oem_6;
			app_input_key_state key_oem_7;
			app_input_key_state key_oem_8;

			//

			app_input_key_state key_unassigned_E0;

			//

			app_input_key_state key_oem_ax;
			app_input_key_state key_oem_102;
			app_input_key_state key_ico_help;
			app_input_key_state key_ico_00;
			app_input_key_state key_processkey;
			app_input_key_state key_ico_clear;
			app_input_key_state key_packet;

			//

			app_input_key_state key_unassigned_E8;

			//

			app_input_key_state key_oem_reset;
			app_input_key_state key_oem_jump;
			app_input_key_state key_oem_pa1;
			app_input_key_state key_oem_pa2;
			app_input_key_state key_oem_pa3;
			app_input_key_state key_oem_wsctrl;
			app_input_key_state key_oem_cusel;
			app_input_key_state key_oem_attn;
			app_input_key_state key_oem_finish;
			app_input_key_state key_oem_copy;
			app_input_key_state key_oem_auto;
			app_input_key_state key_oem_enlw;
			app_input_key_state key_oem_backtab;

			//

			app_input_key_state key_attn;
			app_input_key_state key_crsel;
			app_input_key_state key_exsel;
			app_input_key_state key_ereof;
			app_input_key_state key_play;
			app_input_key_state key_zoom;
			app_input_key_state key_noname;
			app_input_key_state key_pa1;
			app_input_key_state key_oem_clear;

			//

			app_input_key_state key_unassigned_FF;
		} get;
	};
} app_input = {};

// static_assert( ( &app_input.get.key_mouse_l                         - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_mouse_l                         );
// static_assert( ( &app_input.get.key_mouse_r                         - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_mouse_r                         );
// static_assert( ( &app_input.get.key_cancel                          - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_cancel                          );
// static_assert( ( &app_input.get.key_mouse_m                         - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_mouse_m                         );
// static_assert( ( &app_input.get.key_mouse_x                         - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_mouse_x                         );
// static_assert( ( &app_input.get.key_mouse_y                         - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_mouse_y                         );
// static_assert( ( &app_input.get.key_back                            - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_back                            );
// static_assert( ( &app_input.get.key_tab                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_tab                             );
// static_assert( ( &app_input.get.key_clear                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_clear                           );
// static_assert( ( &app_input.get.key_return                          - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_return                          );
// static_assert( ( &app_input.get.key_shift                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_shift                           );
// static_assert( ( &app_input.get.key_control                         - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_control                         );
// static_assert( ( &app_input.get.key_menu                            - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_menu                            );
// static_assert( ( &app_input.get.key_pause                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_pause                           );
// static_assert( ( &app_input.get.key_capital                         - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_capital                         );
// static_assert( ( &app_input.get.key_escape                          - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_escape                          );
// static_assert( ( &app_input.get.key_space                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_space                           );
// static_assert( ( &app_input.get.key_prior                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_prior                           );
// static_assert( ( &app_input.get.key_next                            - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_next                            );
// static_assert( ( &app_input.get.key_end                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_end                             );
// static_assert( ( &app_input.get.key_home                            - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_home                            );
// static_assert( ( &app_input.get.key_left                            - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_left                            );
// static_assert( ( &app_input.get.key_up                              - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_up                              );
// static_assert( ( &app_input.get.key_right                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_right                           );
// static_assert( ( &app_input.get.key_down                            - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_down                            );
// static_assert( ( &app_input.get.key_select                          - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_select                          );
// static_assert( ( &app_input.get.key_print                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_print                           );
// static_assert( ( &app_input.get.key_execute                         - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_execute                         );
// static_assert( ( &app_input.get.key_snapshot                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_snapshot                        );
// static_assert( ( &app_input.get.key_insert                          - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_insert                          );
// static_assert( ( &app_input.get.key_delete                          - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_delete                          );
// static_assert( ( &app_input.get.key_help                            - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_help                            );
// static_assert( ( &app_input.get.key_0                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_0                               );
// static_assert( ( &app_input.get.key_1                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_1                               );
// static_assert( ( &app_input.get.key_2                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_2                               );
// static_assert( ( &app_input.get.key_3                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_3                               );
// static_assert( ( &app_input.get.key_4                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_4                               );
// static_assert( ( &app_input.get.key_5                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_5                               );
// static_assert( ( &app_input.get.key_6                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_6                               );
// static_assert( ( &app_input.get.key_7                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_7                               );
// static_assert( ( &app_input.get.key_8                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_8                               );
// static_assert( ( &app_input.get.key_9                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_9                               );
// static_assert( ( &app_input.get.key_a                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_a                               );
// static_assert( ( &app_input.get.key_b                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_b                               );
// static_assert( ( &app_input.get.key_c                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_c                               );
// static_assert( ( &app_input.get.key_d                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_d                               );
// static_assert( ( &app_input.get.key_e                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_e                               );
// static_assert( ( &app_input.get.key_f                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f                               );
// static_assert( ( &app_input.get.key_g                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_g                               );
// static_assert( ( &app_input.get.key_h                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_h                               );
// static_assert( ( &app_input.get.key_i                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_i                               );
// static_assert( ( &app_input.get.key_j                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_j                               );
// static_assert( ( &app_input.get.key_k                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_k                               );
// static_assert( ( &app_input.get.key_l                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_l                               );
// static_assert( ( &app_input.get.key_m                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_m                               );
// static_assert( ( &app_input.get.key_n                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_n                               );
// static_assert( ( &app_input.get.key_o                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_o                               );
// static_assert( ( &app_input.get.key_p                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_p                               );
// static_assert( ( &app_input.get.key_q                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_q                               );
// static_assert( ( &app_input.get.key_r                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_r                               );
// static_assert( ( &app_input.get.key_s                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_s                               );
// static_assert( ( &app_input.get.key_t                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_t                               );
// static_assert( ( &app_input.get.key_u                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_u                               );
// static_assert( ( &app_input.get.key_v                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_v                               );
// static_assert( ( &app_input.get.key_w                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_w                               );
// static_assert( ( &app_input.get.key_x                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_x                               );
// static_assert( ( &app_input.get.key_y                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_y                               );
// static_assert( ( &app_input.get.key_z                               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_z                               );
// static_assert( ( &app_input.get.key_numpad_0                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_0                        );
// static_assert( ( &app_input.get.key_numpad_1                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_1                        );
// static_assert( ( &app_input.get.key_numpad_2                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_2                        );
// static_assert( ( &app_input.get.key_numpad_3                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_3                        );
// static_assert( ( &app_input.get.key_numpad_4                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_4                        );
// static_assert( ( &app_input.get.key_numpad_5                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_5                        );
// static_assert( ( &app_input.get.key_numpad_6                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_6                        );
// static_assert( ( &app_input.get.key_numpad_7                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_7                        );
// static_assert( ( &app_input.get.key_numpad_8                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_8                        );
// static_assert( ( &app_input.get.key_numpad_9                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_9                        );
// static_assert( ( &app_input.get.key_numpad_multiply                 - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_multiply                 );
// static_assert( ( &app_input.get.key_numpad_add                      - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_add                      );
// static_assert( ( &app_input.get.key_numpad_separator                - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_separator                );
// static_assert( ( &app_input.get.key_numpad_subtract                 - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_subtract                 );
// static_assert( ( &app_input.get.key_numpad_decimal                  - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_decimal                  );
// static_assert( ( &app_input.get.key_numpad_divide                   - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numpad_divide                   );
// static_assert( ( &app_input.get.key_f1                              - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f1                              );
// static_assert( ( &app_input.get.key_f2                              - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f2                              );
// static_assert( ( &app_input.get.key_f3                              - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f3                              );
// static_assert( ( &app_input.get.key_f4                              - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f4                              );
// static_assert( ( &app_input.get.key_f5                              - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f5                              );
// static_assert( ( &app_input.get.key_f6                              - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f6                              );
// static_assert( ( &app_input.get.key_f7                              - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f7                              );
// static_assert( ( &app_input.get.key_f8                              - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f8                              );
// static_assert( ( &app_input.get.key_f9                              - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f9                              );
// static_assert( ( &app_input.get.key_f10                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f10                             );
// static_assert( ( &app_input.get.key_f11                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f11                             );
// static_assert( ( &app_input.get.key_f12                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f12                             );
// static_assert( ( &app_input.get.key_f13                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f13                             );
// static_assert( ( &app_input.get.key_f14                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f14                             );
// static_assert( ( &app_input.get.key_f15                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f15                             );
// static_assert( ( &app_input.get.key_f16                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f16                             );
// static_assert( ( &app_input.get.key_f17                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f17                             );
// static_assert( ( &app_input.get.key_f18                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f18                             );
// static_assert( ( &app_input.get.key_f19                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f19                             );
// static_assert( ( &app_input.get.key_f20                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f20                             );
// static_assert( ( &app_input.get.key_f21                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f21                             );
// static_assert( ( &app_input.get.key_f22                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f22                             );
// static_assert( ( &app_input.get.key_f23                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f23                             );
// static_assert( ( &app_input.get.key_f24                             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_f24                             );
// static_assert( ( &app_input.get.key_numlock                         - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_numlock                         );
// static_assert( ( &app_input.get.key_scroll                          - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_scroll                          );
// static_assert( ( &app_input.get.key_lshift                          - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_lshift                          );
// static_assert( ( &app_input.get.key_rshift                          - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_rshift                          );
// static_assert( ( &app_input.get.key_lcontrol                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_lcontrol                        );
// static_assert( ( &app_input.get.key_rcontrol                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_rcontrol                        );
// static_assert( ( &app_input.get.key_lmenu                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_lmenu                           );
// static_assert( ( &app_input.get.key_rmenu                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_rmenu                           );
// static_assert( ( &app_input.get.key_browser_back                    - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_browser_back                    );
// static_assert( ( &app_input.get.key_browser_forward                 - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_browser_forward                 );
// static_assert( ( &app_input.get.key_browser_refresh                 - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_browser_refresh                 );
// static_assert( ( &app_input.get.key_browser_stop                    - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_browser_stop                    );
// static_assert( ( &app_input.get.key_browser_search                  - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_browser_search                  );
// static_assert( ( &app_input.get.key_browser_favorites               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_browser_favorites               );
// static_assert( ( &app_input.get.key_browser_home                    - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_browser_home                    );
// static_assert( ( &app_input.get.key_volume_mute                     - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_volume_mute                     );
// static_assert( ( &app_input.get.key_volume_down                     - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_volume_down                     );
// static_assert( ( &app_input.get.key_volume_up                       - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_volume_up                       );
// static_assert( ( &app_input.get.key_media_next_track                - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_media_next_track                );
// static_assert( ( &app_input.get.key_media_prev_track                - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_media_prev_track                );
// static_assert( ( &app_input.get.key_media_stop                      - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_media_stop                      );
// static_assert( ( &app_input.get.key_media_play_pause                - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_media_play_pause                );
// static_assert( ( &app_input.get.key_launch_mail                     - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_launch_mail                     );
// static_assert( ( &app_input.get.key_launch_media_select             - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_launch_media_select             );
// static_assert( ( &app_input.get.key_launch_app1                     - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_launch_app1                     );
// static_assert( ( &app_input.get.key_launch_app2                     - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_launch_app2                     );
// static_assert( ( &app_input.get.key_oem_1                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_oem_1                           );
// static_assert( ( &app_input.get.key_oem_plus                        - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_oem_plus                        );
// static_assert( ( &app_input.get.key_oem_comma                       - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_oem_comma                       );
// static_assert( ( &app_input.get.key_oem_minus                       - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_oem_minus                       );
// static_assert( ( &app_input.get.key_oem_period                      - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_oem_period                      );
// static_assert( ( &app_input.get.key_oem_2                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_oem_2                           );
// static_assert( ( &app_input.get.key_oem_3                           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_oem_3                           );
// static_assert( ( &app_input.get.key_gamepad_a                       - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_a                       );
// static_assert( ( &app_input.get.key_gamepad_b                       - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_b                       );
// static_assert( ( &app_input.get.key_gamepad_x                       - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_x                       );
// static_assert( ( &app_input.get.key_gamepad_y                       - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_y                       );
// static_assert( ( &app_input.get.key_gamepad_right_shoulder          - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_right_shoulder          );
// static_assert( ( &app_input.get.key_gamepad_left_shoulder           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_left_shoulder           );
// static_assert( ( &app_input.get.key_gamepad_left_trigger            - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_left_trigger            );
// static_assert( ( &app_input.get.key_gamepad_right_trigger           - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_right_trigger           );
// static_assert( ( &app_input.get.key_gamepad_dpad_up                 - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_dpad_up                 );
// static_assert( ( &app_input.get.key_gamepad_dpad_down               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_dpad_down               );
// static_assert( ( &app_input.get.key_gamepad_dpad_left               - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_dpad_left               );
// static_assert( ( &app_input.get.key_gamepad_dpad_right              - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_dpad_right              );
// static_assert( ( &app_input.get.key_gamepad_menu                    - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_menu                    );
// static_assert( ( &app_input.get.key_gamepad_view                    - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_view                    );
// static_assert( ( &app_input.get.key_gamepad_left_thumbstick_button  - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_left_thumbstick_button  );
// static_assert( ( &app_input.get.key_gamepad_right_thumbstick_button - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_right_thumbstick_button );
// static_assert( ( &app_input.get.key_gamepad_left_thumbstick_up      - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_left_thumbstick_up      );
// static_assert( ( &app_input.get.key_gamepad_left_thumbstick_down    - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_left_thumbstick_down    );
// static_assert( ( &app_input.get.key_gamepad_left_thumbstick_right   - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_left_thumbstick_right   );
// static_assert( ( &app_input.get.key_gamepad_left_thumbstick_left    - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_left_thumbstick_left    );
// static_assert( ( &app_input.get.key_gamepad_right_thumbstick_up     - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_right_thumbstick_up     );
// static_assert( ( &app_input.get.key_gamepad_right_thumbstick_down   - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_right_thumbstick_down   );
// static_assert( ( &app_input.get.key_gamepad_right_thumbstick_right  - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_right_thumbstick_right  );
// static_assert( ( &app_input.get.key_gamepad_right_thumbstick_left   - &app_input.keys[0] ) / sizeof( app_input_key_state ) == key_gamepad_right_thumbstick_left   );
