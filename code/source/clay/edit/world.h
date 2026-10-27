#pragma once

#include <zed/app/graphics.h>
#include <zed/app/ui.h>
#include <zed/xmath.h>

const float wall_height    = 3.0;
const float wall_thickness = 0.2;

enum clay_edit_world_tool {
	tool_null = 0,
	tool_pick,
	tool_room,
	tool_yard,
	tool_wall,
	tool_tour,
	tool_end
};

enum {
	brush_room,
	brush_yard,
	brush_wall,
	brush_tour,
};

struct clay_edit_world_brush {
	float3 p0;
	float3 p1;
	int brush_type = 0;
};

const uint brushes_capacity = 0xFFFF;

struct clay_edit_world_data {
	clay_edit_world_brush brushes[ brushes_capacity ];
	int brushes_count = 0;
};

float3 cursor;

int tool_i = 1;

int floor_i = 0;

bool dragging = false;

clay_edit_world_data clay_we_data;

void pick();
