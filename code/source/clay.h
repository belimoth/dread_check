#pragma once

#include "clay/edit.h"
#include "clay/studio.h"
#include "main/game.h"

#include <zed/app/ui.h>
#include <zed/camera.h>
#include <zed/app/graphics.h>

struct clay_edit_model {
	// content

	zed_mesh mesh;

	int path = 0;

	// camera

	float rotation_start_x;
	float rotation_start_y;

	float rotation_delta_x;
	float rotation_delta_y;

	float camera_zoom;

	// cursor

	float3 cursor_start;
	float3 cursor_delta;

	//

	clay_draw_studio studio;

	ui_mouse mouse;

	zed_buffer buffer_studio;
};

struct clay_gfx {
	zed_pass pass_plane;
	zed_mesh mesh_plane;

	zed_pass pass_composite;
	zed_pass pass_normals;
	zed_pass pass_wireframe;
	zed_pass pass_geo_edges;
	zed_pass pass_geo_vertices;

	zed_pass pass_grid;
	zed_mesh mesh_grid;
};

//

char table_buffer[256] = {};

struct clay_ui {
	ui_element_data data_menu;

	ui_element_data data_play;
	ui_element_data data_view;
	ui_element_data data_edit;
	ui_element_data data_find;
	ui_element_data data_sync;

	ui_element_data data_tool;

	ui_element_data data_layers;
	ui_element_data data_inspect;
	ui_element_data data_palette;
};

//

enum clay_scene {
	clay_scene_none = 0,
	clay_scene_edit_model,
	clay_scene_edit_world,
};

enum clay_page_menu {
	clay_page_menu_play = 0,
	clay_page_menu_view = 1,
	clay_page_menu_edit = 2,
	clay_page_menu_find = 3,
	clay_page_menu_sync = 4,
	clay_page_menu_itch = 5,
	clay_page_menu_user = 6,
};

string view_names[] = {
	"Game",
	"Disk",
	"Memory",
	"Performance",
	"Video",
	"Audio",
	"Input",
};

enum clay_page_view {
	clay_page_view_game,
	clay_page_view_disk,
	clay_page_view_size,
	clay_page_view_perf,
	clay_page_view_video,
	clay_page_view_audio,
	clay_page_view_input,
};

enum clay_page_edit {
	clay_page_edit_none,
	clay_page_edit_image,
	clay_page_edit_maze,
	clay_page_edit_model,
	clay_page_edit_world,
};


struct clay_edit_tool {

};

string clay_edit_tool_name[64];

struct clay_tool {
	clay_edit_tool tool[64];
	int tool_i;
};

struct clay_t {
	bool show;

	zed_camera camera;

	clay_gfx gfx;
	clay_ui  ui;

	clay_scene scene;

	clay_page_menu page;
	clay_page_view page_view;
	clay_page_edit page_edit;

	clay_edit       edit;
	clay_edit_model edit_model;

	clay_tool tool;
} clay;

struct {
	int control[256];
} midi;

void clay_toggle() {
	clay.show = not clay.show;

	if ( clay.show ) {
		app_show_cursor();
		game.has_focus = false;
	} else {
		game_cursor_refresh();
		game.has_focus = true;
	}
}
