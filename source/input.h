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

	bool a, b, x, y;
	bool n, e, s, w;
	bool ls, rs;
	bool lb, rb;
	float lt, rt;

	bool start, back;

	float3 gyro;
};

zed_pad update_pad();
zed_pad update_pad_0();
