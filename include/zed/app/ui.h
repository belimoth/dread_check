#pragma once

#include <zed/app.h>
#include <zed/xmath.h>

// event

enum ui_event_type {
	event_type_none,
	event_type_hover,
	event_type_down,
	event_type_click,
	event_type_click2,
	event_type_drag,
	event_type_wheel,
};

struct ui_mouse {
	int x, y, z;
};

struct ui_event {
	int type, which;
	ui_mouse mouse;
	ui_mouse delta;
	int id_target;
};

// latch

enum ui_latch {
	ui_latch_none,
	ui_latch_x,
	ui_latch_y
};

// page

enum ui_layout {
	ui_layout_void,
	ui_layout_block,
	ui_layout_flex,
	ui_layout_table,
	ui_layout_grid
};

typedef void (* ui_event_handler )( ui_event );

struct ui_element_step_node {
	float2 position;
	float2 size;

	//

	int id;
	int id_parent;
	int id_child;
	int id_in_parent;

	ui_layout layout = ui_layout_void;

	float2 child_position;
	float2 child_size;

	int *grid = 0;
	int grid_count;

	bool is_started = false;

	//

	ui_event_handler handle_ui_event = 0;

	//

	void *data;
};

#include <zed/struct_helper_before.h>

struct ui_element_draw_node {
	float2 position;
	float2 size;
	float2 uv;
	uint   color;
};

#include <zed/struct_helper_after.h>

struct ui_data {
	ui_element_step_node step_nodes[256];
	ui_element_draw_node draw_nodes[256];
};

typedef void (* ui_element_prototype)();

// data

struct ui_element_data {
	int id_self;
	int id_target;
	int id_preview;
};

//

struct app_ui {
	ui_mouse mouse_start;
	bool         mouse_down;
	int          wheel = 0;
	int          which_down;

	// event
	ui_event event;

	// latch

	int drag_latch_radius = 32;

	ui_latch latch;
	ui_mouse mouse_latch;

	// root
	void (* handle_ui_event)( ui_event ) = 0;

	// page
    ui_data data;
	ui_element_prototype el_root;

	// draw
	int id_current;
	int id_step;
	int id_parent;
	int id_draw;

	int id_hover;
	int id_active;
	int id_target;

	//

	float opacity = 0.85;
} ui;

// latch

void latch_reset() {
	ui.latch = ui_latch_none;
}

void latch_test( ui_event *event ) {
	int dx = event->delta.x;
	int dy = event->delta.y;

	for (;;) {
		if ( ui.latch == ui_latch_x ) {
			event->delta.x = event->mouse.x - ui.mouse_latch.x;
			event->delta.y = 0;

			break;
		}

		if ( ui.latch == ui_latch_y ) {
			event->delta.x = 0;
			event->delta.y = event->mouse.y - ui.mouse_latch.y;

			break;
		}

		if ( abs( dx ) > ui.drag_latch_radius ) {
			ui.latch       = ui_latch_x;
			ui.mouse_latch = event->mouse;
			event->type = event_type_down;

			break;
		}

		if ( abs( dy ) > ui.drag_latch_radius ) {
			ui.latch       = ui_latch_y;
			ui.mouse_latch = event->mouse;
			event->type = event_type_down;

			break;
		}

		event->type = event_type_none;

		break;
	}
}

// page

int  ui_element_start();
void ui_element_finish( int, string text = 0 );
void ui_element_set_block();
void ui_element_set_size_y( int );
void ui_element_set_padding( int );
void ui_element_set_padding( int, int );
void ui_element_set_padding_for_text();
void ui_element_set_flex( int*, int );
void ui_element_set_table( float child_size_y = 48 );
void ui_element_set_grid( float child_size_x = 64, float child_size_y = 64 );

// data

void ui_element_bind( ui_element_data &data, ui_event_handler event_handler = 0 ) {
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	data.id_self = ui.id_current;
	self->data = &data;
	self->handle_ui_event = event_handler;
}

void handle_ui_event_for_list( ui_event event, ui_element_data *data ) {
	if ( event.type == event_type_down or event.type == event_type_drag ) {
		if ( ui.data.step_nodes[ ui.id_hover ].id_parent != data->id_self ) {
			data->id_preview = -1;
			return;
		}

		// active
		ui.id_active = ui.id_hover;

		// preview
		int target_id_in_parent = ui.data.step_nodes[ ui.id_active ].id_in_parent;
		data->id_preview = target_id_in_parent;
	}

	if ( event.type == event_type_click ) {
		// target
		int target_id_in_parent = ui.data.step_nodes[ event.id_target ].id_in_parent;
		data->id_target = target_id_in_parent;

		// preview
		data->id_preview = -1;
	}
}

void handle_ui_event_for_tree( ui_event event, ui_element_data *data ) {
	if ( event.type == event_type_down or event.type == event_type_drag ) {
		if ( ui.data.step_nodes[ ui.id_hover ].id_parent != data->id_self ) {
			data->id_preview = -1;
			return;
		}

		// active
		ui.id_active = ui.id_hover;

		// preview
		int target_id_in_parent = ui.data.step_nodes[ ui.id_active ].id_in_parent;
		data->id_preview = target_id_in_parent;
	}

	if ( event.type == event_type_click ) {
		// target
		int target_id_in_parent = ui.data.step_nodes[ event.id_target ].id_in_parent;
		data->id_target = target_id_in_parent;

		// preview
		data->id_preview = -1;
	}
}
