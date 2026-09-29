#pragma once

bool use_mouse;
bool use_keyboard;

struct zed_joy {
	float x, y, magnitude, direction;
	float z; // hack for mouse wheel
};

struct zed_pad {
	zed_joy joy_0;
	zed_joy joy_1;

	app_input_key_state a, b, x, y;
	app_input_key_state n, e, s, w;
	app_input_key_state ls, rs;
	app_input_key_state lb, rb;
	float lt, rt;

	app_input_key_state start, back;

	float3 gyro;
};

zed_pad pad_step( zed_pad );
zed_pad pad_step_0( zed_pad );
