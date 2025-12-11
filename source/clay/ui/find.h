#pragma once

#include <zed/app/ui.h>

#include "../ui.h"

string el_table_find_get_data( int x, int y ) {
	if ( x == 0 and y < array_count( clay.edit_model.paths ) ) {
		return clay.edit_model.paths[y];
	}

	return "";
}

void el_table_find_row() {
	int id = ui_element_start();
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	clay_ui_draw_button();
	// draw_fill();

	self->child_position.x += 16;
	int y = self->id_in_parent;
	float2 position = self->child_position;
	clay_ui_text( el_table_find_get_data( 0, y ), color_fg );
	self->child_position = position;

	ui_element_finish( id );
}

void el_table_find_on_ui_event( ui_event event ) {
	handle_ui_event_for_list( event, &clay.ui.data_find );
}

void el_table_find() {
	int id = ui_element_start();
	ui_element_bind( clay.ui.data_find, el_table_find_on_ui_event );
	ui_element_set_table();

	el_table_find_row();
	el_table_find_row();
	el_table_find_row();

	ui_element_finish( id );
}

void el_column_find() {
	int id = ui_element_start();
	clay_ui_draw_fill();
	ui_element_set_block();
	ui_element_set_padding(2);

	el_header( "FIND" );
	// el_table_find();

	ui_element_finish( id );
}
