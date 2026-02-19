#pragma once

#include "../ui.h"

#include <zed/app/ui.h>

string sync_path[64];
int sync_path_i;

void clay_sync_init() {
	sync_path[ sync_path_i++ ] = "Code";
	sync_path[ sync_path_i++ ] = "Data";
}

string el_table_sync_get_data( int x, int y ) {
	if ( x != 0 or y >= array_count( sync_path ) ) return "";
	return sync_path[y];
}

void el_table_sync_row() {
	el_start;
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	clay_ui_draw_button();
	// draw_fill();

	self->child_position.x += 16;
	int y = self->id_in_parent;
	float2 position = self->child_position;
	clay_ui_text( el_table_sync_get_data( 0, y ), color_clay_fg );
	self->child_position = position;

	el_finish;
}

void el_table_sync_on( ui_event event ) {
	handle_ui_event_for_list( event, &clay.ui.data_sync );
}

void el_table_sync() {
	el_start;
	el_bind( clay.ui.data_sync, el_table_sync_on );
	ui_element_set_table();

	for ( int i = 0; i < sync_path_i; i++ ) el_table_sync_row();

	el_finish;
}

void el_column_sync() {
	el_start;
	clay_ui_draw_fill();
	el_block;
	ui_element_set_padding(2);

	el_header( "SYNC" );

	el_table_sync();

	el_finish;
}
