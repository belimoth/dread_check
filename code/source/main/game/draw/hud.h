#pragma once

#include "../../../data/color.h"
#include "../draw/split.h"
#include <zed/app/graphics.h>

struct hud_rect {
	float x0, y0, x1, y1;
};

hud_rect hud_rect_get() {
	hud_rect r = {};

	r.x0 = ( canvas_x1.size.x - 320 ) / 2;
	r.y0 = ( canvas_x1.size.y - 240 ) / 2;
	r.x1 = r.x0 + 320;
	r.y1 = r.y0 + 240;

	if ( split == game_split_duo ) {
		r.x0 = 0;
		r.y0 = ( canvas_x1.size.y - 240 ) / 2;
		r.x1 = r.x0 + canvas_x1.size.x / 2 - 2;
		r.y1 = r.y0 + 240;
	}

	return r;
}

enum hud_text_align {
	align_left,
	align_center,
	align_right,
};

void hud_text( string text, float x, float y, hud_text_align align = align_left, uint color = color_hud_fg ) {
	if ( align == align_center ) x = x - (float)floor( app_graphics_text_measure( text ) / 2 );
	if ( align == align_right  ) x = x - (float)floor( app_graphics_text_measure( text ) );
	app_graphics_draw_text_new( text, x, y, color );
}

struct game_hud {
	string text;
	string text_n;
	string text_s;
	string text_w;
	string text_e;
	float x, y;
};
