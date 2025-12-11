#pragma once

#include "../ui.h"

#include <zed/app/ui.h>

string el_table_edit_get_data( int x, int y ) {
	if ( x == 0 and y < array_count( clay.edit_model.paths ) ) {
		return clay.edit_model.paths[y];
	}

	return "";
}

void el_table_edit_row() {
	int id = ui_element_start();
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	clay_ui_draw_button();
	// clay_ui_draw_fill();

	self->child_position.x += 16;
	int y = self->id_in_parent;
	float2 position = self->child_position;

	clay_ui_text( el_table_edit_get_data( 0, y ), color_fg );
	self->child_position = position;

	ui_element_finish( id );
}

void el_table_edit_on_ui_event( ui_event event ) {
	handle_ui_event_for_list( event, &clay.ui.data_edit );
}

void el_table_edit() {
	int id = ui_element_start();
	ui_element_bind( clay.ui.data_edit, el_table_edit_on_ui_event );
	ui_element_set_table();

	el_table_edit_row();
	el_table_edit_row();
	el_table_edit_row();

	ui_element_finish( id );
}

void el_column_edit() {
	int id = ui_element_start();
	clay_ui_draw_fill();
	ui_element_set_block();
	ui_element_set_padding(2);

	el_header( "EDIT" );
	el_table_edit();

	ui_element_finish( id );
}
