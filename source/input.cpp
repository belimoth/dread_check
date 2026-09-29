#include "input.h"
#include "main/game.h"

#include <zed/app.h>
#include <zed/app/input.h>
#include <zed/platform/xinput.h>

void game_player_hands_switch_secondary( game_player &player, int j );

zed_joy get_joy_via_keyboard() {
	float x = 0, y = 0;

	if ( app_input.get.key_a.held ) x -= 1;
	if ( app_input.get.key_d.held ) x += 1;

	if ( app_input.get.key_s.held ) y -= 1;
	if ( app_input.get.key_w.held ) y += 1;

	float magnitude = sqrt( x * x + y * y );
	float direction = atan2( y, x );

	if ( magnitude > 1.0 ) {
		magnitude = 1.0;

		x = cos( direction ) * magnitude;
		y = sin( direction ) * magnitude;
	}

	zed_joy joy = {};
	joy.x         = x;
	joy.y         = y;
	joy.magnitude = magnitude;
	joy.direction = direction;

	return joy;
}

zed_joy get_joy_via_mouse() {
	const float SENS_X =  5; // 10; //25; // 50
	const float SENS_Y = 10; // 10;

	float x = game_mouse.x;
	float y = game_mouse.y;
	float z = game_mouse.z;

	if ( x >  SENS_X ) x =  SENS_X;
	if ( x < -SENS_X ) x = -SENS_X;

	if ( y >  SENS_Y ) y =  SENS_Y;
	if ( y < -SENS_Y ) y = -SENS_Y;

	x /=  SENS_X;
	y /= -SENS_Y;

	zed_joy joy = {};
	joy.x         = x;
	joy.y         = y;
	joy.magnitude = sqrt( x * x + y * y );
	joy.direction = atan2( y, x );
	joy.z         = z;

	// game_mouse.x = 0;
	// game_mouse.y = 0;
	// game_mouse.z = 0; // note

	if ( game_mouse.x > 1 ) {
		game_mouse.x -= 1;
	} else if ( game_mouse.x < -1 ) {
		game_mouse.x += 1;
	} else {
		game_mouse.x = 0;
	}

	if ( game_mouse.y > 1 ) {
		game_mouse.y -= 1;
	} else if ( game_mouse.y < -1 ) {
		game_mouse.y += 1;
	} else {
		game_mouse.y = 0;
	}

	return joy;
}

zed_joy get_joy( float x, float y ) {
	float magnitude = sqrt( x * x + y * y );
	float direction = atan2( y, x );

	float dx = 0;
	float dy = 0;

	if ( magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) {
		if ( magnitude > 32767 ) magnitude = 32767;
		magnitude = magnitude - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		magnitude = magnitude / ( 32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE );

		dx = cos( direction ) * magnitude;
		dy = sin( direction ) * magnitude;
	} else {
		magnitude = 0;
		direction = 0;
	}

	zed_joy joy   = {};
	joy.x         = dx;
	joy.y         = dy;
	joy.magnitude = magnitude;
	joy.direction = direction;

	return joy;
}

bool has_pad() {
	XINPUT_STATE pad_state;
	uint result = xinput_get_state( 0, &pad_state );
	if ( result ) return false;
	return true;
}

bool has_pad_2() {
	XINPUT_STATE pad_state;
	uint result = xinput_get_state( 1, &pad_state );
	if ( result ) return false;
	return true;
}

zed_pad pad_step_after( zed_pad pad, zed_pad pad_previous ) {
	pad.a    .fall = pad.a    .held and not pad_previous.a    .held;
	pad.b    .fall = pad.b    .held and not pad_previous.b    .held;
	pad.x    .fall = pad.x    .held and not pad_previous.x    .held;
	pad.y    .fall = pad.y    .held and not pad_previous.y    .held;
	pad.rb   .fall = pad.rb   .held and not pad_previous.rb   .held;
	pad.lb   .fall = pad.lb   .held and not pad_previous.lb   .held;
	pad.rs   .fall = pad.rs   .held and not pad_previous.rs   .held;
	pad.ls   .fall = pad.ls   .held and not pad_previous.ls   .held;
	pad.n    .fall = pad.n    .held and not pad_previous.n    .held;
	pad.e    .fall = pad.e    .held and not pad_previous.e    .held;
	pad.s    .fall = pad.s    .held and not pad_previous.s    .held;
	pad.w    .fall = pad.w    .held and not pad_previous.w    .held;
	pad.start.fall = pad.start.held and not pad_previous.start.held;
	pad.back .fall = pad.back .held and not pad_previous.back .held;

	pad.a    .rise = not pad.a    .held and pad_previous.a    .held;
	pad.b    .rise = not pad.b    .held and pad_previous.b    .held;
	pad.x    .rise = not pad.x    .held and pad_previous.x    .held;
	pad.y    .rise = not pad.y    .held and pad_previous.y    .held;
	pad.rb   .rise = not pad.rb   .held and pad_previous.rb   .held;
	pad.lb   .rise = not pad.lb   .held and pad_previous.lb   .held;
	pad.rs   .rise = not pad.rs   .held and pad_previous.rs   .held;
	pad.ls   .rise = not pad.ls   .held and pad_previous.ls   .held;
	pad.n    .rise = not pad.n    .held and pad_previous.n    .held;
	pad.e    .rise = not pad.e    .held and pad_previous.e    .held;
	pad.s    .rise = not pad.s    .held and pad_previous.s    .held;
	pad.w    .rise = not pad.w    .held and pad_previous.w    .held;
	pad.start.rise = not pad.start.held and pad_previous.start.held;
	pad.back .rise = not pad.back .held and pad_previous.back .held;

	return pad;
}

zed_pad pad_step_0_keyboard_only( zed_pad pad_previous ) {
	zed_pad pad = {};

	pad.joy_0 = get_joy_via_keyboard();
	pad.joy_1 = get_joy_via_mouse();

	if ( app_input.get.key_mouse_r.held ) pad.lt = 1;
	if ( app_input.get.key_mouse_l.held ) pad.rt = 1;

	pad.a     = app_input.get.key_space;
	pad.b     = app_input.get.key_control;
	pad.x     = app_input.get.key_r;
	pad.y     = app_input.get.key_tab;
	pad.rb    = app_input.get.key_e;
	pad.lb    = app_input.get.key_q;
	pad.rs    = app_input.get.key_f;
	pad.rs    = app_input.get.key_mouse_m;
	pad.ls    = app_input.get.key_shift;
	pad.e     = app_input.get.key_mouse_x;
	pad.w     = app_input.get.key_mouse_y;
	pad.start = app_input.get.key_return;
	pad.back  = app_input.get.key_back;

	return pad;
}

zed_pad pad_step_0( zed_pad pad_previous ) {
	XINPUT_STATE pad_state;
	uint result = xinput_get_state( 0, &pad_state );

	zed_pad pad = {};
	zed_joy joy = get_joy_via_keyboard();
	if ( not joy.magnitude == 0 ) use_keyboard = true;

	if ( app_input.get.key_space  .held ) use_keyboard = true;
	if ( app_input.get.key_control.held ) use_keyboard = true;
	if ( app_input.get.key_c      .held ) use_keyboard = true;
	if ( app_input.get.key_r      .held ) use_keyboard = true;
	if ( app_input.get.key_tab    .held ) use_keyboard = true;
	if ( app_input.get.key_e      .held ) use_keyboard = true;
	if ( app_input.get.key_q      .held ) use_keyboard = true;
	if ( app_input.get.key_f      .held ) use_keyboard = true;
	if ( app_input.get.key_shift  .held ) use_keyboard = true;
	if ( app_input.get.key_return .held ) use_keyboard = true;
	if ( app_input.get.key_back   .held ) use_keyboard = true;
	if ( app_input.get.key_1      .held ) use_keyboard = true;
	if ( app_input.get.key_2      .held ) use_keyboard = true;
	if ( app_input.get.key_3      .held ) use_keyboard = true;
	if ( app_input.get.key_4      .held ) use_keyboard = true;

	if ( result or use_keyboard ) {
		pad.joy_0 = joy;

		pad.a     = app_input.get.key_space;
		pad.b     = app_input.get.key_control;
		pad.b     = app_input.get.key_c;
		pad.x     = app_input.get.key_r;
		pad.y     = app_input.get.key_tab;
		pad.rb    = app_input.get.key_e;
		pad.lb    = app_input.get.key_q;
		pad.rs    = app_input.get.key_f;
		pad.ls    = app_input.get.key_shift;
		pad.start = app_input.get.key_return;
		pad.back  = app_input.get.key_back;

		if ( false and use_mouse ) {
			if ( app_input.get.key_1.held ) game_player_hands_switch_primary( game.data.player[0], 0 );
			if ( app_input.get.key_2.held ) game_player_hands_switch_primary( game.data.player[0], 1 );
			if ( app_input.get.key_3.held ) game_player_hands_switch_primary( game.data.player[0], 2 );
			if ( app_input.get.key_4.held ) game_player_hands_switch_primary( game.data.player[0], 3 );
		} else {
			pad.n = app_input.get.key_1;
			pad.e = app_input.get.key_2;
			pad.s = app_input.get.key_3;
			pad.w = app_input.get.key_4;
		}

		if ( app_input.get.key_5.held ) game_player_hands_switch_secondary( game.data.player[0], 0 );
		if ( app_input.get.key_6.held ) game_player_hands_switch_secondary( game.data.player[0], 1 );
		if ( app_input.get.key_7.held ) game_player_hands_switch_secondary( game.data.player[0], 2 );
		if ( app_input.get.key_8.held ) game_player_hands_switch_secondary( game.data.player[0], 3 );
		if ( app_input.get.key_9.held ) game_player_hands_switch_secondary( game.data.player[0], 4 );
	}

	if ( result or use_mouse ) {
		pad.joy_1 = get_joy_via_mouse();

		if ( app_input.get.key_mouse_r.held ) pad.lt = 1;
		if ( app_input.get.key_mouse_l.held ) pad.rt = 1;

		pad.rs = app_input.get.key_mouse_m;
		pad.e  = app_input.get.key_mouse_x;
		pad.w  = app_input.get.key_mouse_y;
	}

	if ( result ) return pad_step_after( pad, pad_previous );

	joy = get_joy( pad_state.Gamepad.sThumbLX, pad_state.Gamepad.sThumbLY );
	if ( not joy.magnitude == 0 ) use_keyboard = false;
	if ( not use_keyboard ) pad.joy_0 = joy;

	zed_joy joy_1 = get_joy( pad_state.Gamepad.sThumbRX, pad_state.Gamepad.sThumbRY );
	if ( not joy_1.magnitude == 0 ) use_mouse = false;
	if ( not use_mouse ) pad.joy_1 = joy_1;

	if ( pad_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ) {
		pad.lt = pad_state.Gamepad.bLeftTrigger / 255.0;
	}

	if ( pad_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ) {
		pad.rt = pad_state.Gamepad.bRightTrigger / 255.0;
	}

	pad.a    .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_A              );
	pad.b    .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_B              );
	pad.x    .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_X              );
	pad.y    .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y              );
	pad.rb   .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER );
	pad.lb   .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER  );
	pad.rs   .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB    );
	pad.ls   .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB     );
	pad.n    .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP        );
	pad.e    .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT     );
	pad.s    .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN      );
	pad.w    .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT      );
	pad.start.held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_START          );
	pad.back .held |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK           );

	if ( pad.a.held or pad.b.held or pad.x.held or pad.y.held ) use_mouse = false;

	if ( use_mouse and not game.menu[0].state.page ) {
		pad.a.held |= pad.s.held;
		pad.b.held |= pad.e.held;
		pad.x.held |= pad.w.held;
		pad.y.held |= pad.n.held;

		pad.s.held = 0;
        pad.e.held = 0;
        pad.w.held = 0;
        pad.n.held = 0;
	}

	pad = pad_step_after( pad, pad_previous );

	return pad;
}

zed_pad pad_step_i( int i, zed_pad pad_previous ) {
	XINPUT_STATE pad_state;
	uint result = xinput_get_state( i - 1, &pad_state );
	zed_pad pad = {};
	if ( result ) return pad;

	pad.joy_0 = get_joy( pad_state.Gamepad.sThumbLX, pad_state.Gamepad.sThumbLY );
	pad.joy_1 = get_joy( pad_state.Gamepad.sThumbRX, pad_state.Gamepad.sThumbRY );

	if ( pad_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ) {
		pad.lt = pad_state.Gamepad.bLeftTrigger / 255.0;
	}

	if ( pad_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ) {
		pad.rt = pad_state.Gamepad.bRightTrigger / 255.0;
	}

	pad.a    .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_A              );
	pad.b    .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_B              );
	pad.x    .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_X              );
	pad.y    .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y              );
	pad.rb   .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER );
	pad.lb   .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER  );
	pad.rs   .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB    );
	pad.ls   .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB     );
	pad.n    .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP        );
	pad.e    .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT     );
	pad.s    .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN      );
	pad.w    .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT      );
	pad.start.held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_START          );
	pad.back .held = (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK           );

	pad = pad_step_after( pad, pad_previous );

	return pad;
}
