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

zed_pad update_pad_0_keyboard_only() {
	zed_pad pad = {};

	pad.joy_0 = get_joy_via_keyboard();
	pad.joy_1 = get_joy_via_mouse();

	if ( app_input.get.key_mouse_r.held ) pad.lt    = 1;
	if ( app_input.get.key_mouse_l.held ) pad.rt    = 1;
	if ( app_input.get.key_space  .held ) pad.a     = 1;
	if ( app_input.get.key_control.held ) pad.b     = 1;
	if ( app_input.get.key_r      .held ) pad.x     = 1;
	if ( app_input.get.key_tab    .held ) pad.y     = 1;
	if ( app_input.get.key_e      .held ) pad.rb    = 1;
	if ( app_input.get.key_q      .held ) pad.lb    = 1;
	if ( app_input.get.key_f      .held ) pad.rs    = 1;
	if ( app_input.get.key_mouse_m.held ) pad.rs    = 1;
	if ( app_input.get.key_shift  .held ) pad.ls    = 1;
	if ( app_input.get.key_mouse_x.held ) pad.e     = 1;
	if ( app_input.get.key_mouse_y.held ) pad.w     = 1;
	if ( app_input.get.key_return.held  ) pad.start = 1;
	if ( app_input.get.key_back.held    ) pad.back  = 1;

	return pad;
}

zed_pad update_pad_0() {
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

		if ( app_input.get.key_space  .held ) pad.a     = 1;
		if ( app_input.get.key_control.held ) pad.b     = 1;
		if ( app_input.get.key_c      .held ) pad.b     = 1;
		if ( app_input.get.key_r      .held ) pad.x     = 1;
		if ( app_input.get.key_tab    .held ) pad.y     = 1;
		if ( app_input.get.key_e      .held ) pad.rb    = 1;
		if ( app_input.get.key_q      .held ) pad.lb    = 1;
		if ( app_input.get.key_f      .held ) pad.rs    = 1;
		if ( app_input.get.key_shift  .held ) pad.ls    = 1;
		if ( app_input.get.key_return .held ) pad.start = 1;
		if ( app_input.get.key_back   .held ) pad.back  = 1;

		if ( false and use_mouse ) {
			if ( app_input.get.key_1.held ) game_player_hands_switch_primary( game.data.player[0], 0 );
			if ( app_input.get.key_2.held ) game_player_hands_switch_primary( game.data.player[0], 1 );
			if ( app_input.get.key_3.held ) game_player_hands_switch_primary( game.data.player[0], 2 );
			if ( app_input.get.key_4.held ) game_player_hands_switch_primary( game.data.player[0], 3 );
		} else {
			if ( app_input.get.key_1.held ) pad.n = 1;
			if ( app_input.get.key_2.held ) pad.e = 1;
			if ( app_input.get.key_3.held ) pad.s = 1;
			if ( app_input.get.key_4.held ) pad.w = 1;
		}

		if ( app_input.get.key_5.held ) game_player_hands_switch_secondary( game.data.player[0], 0 );
		if ( app_input.get.key_6.held ) game_player_hands_switch_secondary( game.data.player[0], 1 );
		if ( app_input.get.key_7.held ) game_player_hands_switch_secondary( game.data.player[0], 2 );
		if ( app_input.get.key_8.held ) game_player_hands_switch_secondary( game.data.player[0], 3 );
		if ( app_input.get.key_9.held ) game_player_hands_switch_secondary( game.data.player[0], 4 );
	}

	if ( result or use_mouse ) {
		pad.joy_1 = get_joy_via_mouse();

		if ( app_input.get.key_mouse_r.held ) pad.lt    = 1;
		if ( app_input.get.key_mouse_l.held ) pad.rt    = 1;

		if ( app_input.get.key_mouse_m.held ) pad.rs    = 1;
		if ( app_input.get.key_mouse_x.held ) pad.e     = 1;
		if ( app_input.get.key_mouse_y.held ) pad.w     = 1;
	}

	if ( result ) return pad;

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

	pad.a     |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_A              );
	pad.b     |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_B              );
	pad.x     |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_X              );
	pad.y     |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y              );
	pad.rb    |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER );
	pad.lb    |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER  );
	pad.rs    |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB    );
	pad.ls    |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB     );
	pad.n     |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP        );
	pad.e     |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT     );
	pad.s     |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN      );
	pad.w     |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT      );
	pad.start |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_START          );
	pad.back  |= (bool)( pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK           );

	if ( pad.a or pad.b or pad.x or pad.y ) use_mouse = false;

	if ( use_mouse and not game.menu[0].state.page ) {
		pad.a |= pad.s;
		pad.b |= pad.e;
		pad.x |= pad.w;
		pad.y |= pad.n;

		pad.s = 0;
        pad.e = 0;
        pad.w = 0;
        pad.n = 0;
	}

	return pad;
}

zed_pad update_pad_i( int i ) {
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

	pad.a     = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	pad.b     = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	pad.x     = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	pad.y     = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	pad.rb    = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	pad.lb    = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	pad.rs    = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
	pad.ls    = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
	pad.n     = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	pad.e     = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	pad.s     = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	pad.w     = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	pad.start = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	pad.back  = pad_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;

	return pad;
}
