#pragma once

#include <zed.h>
#include <zed/app/ui.h>

#include "../../clay.h"
#include "../ui.h"

// string el_table_play_get_data( int x, int y ) {
// 	if ( x == 0 and y < array_count( views_play ) ) return views_play[y];
// 	return "";
// }
//
// void el_table_play_row() {
// 	int id = ui_element_start();
// 	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
// 	clay_ui_draw_button();
// 	// clay_ui_draw_fill();
//
// 	//
//
// 	self->child_position.x += 16;
//
// 	//
//
// 	int y = self->id_in_parent;
//
// 	float2 position = self->child_position;
//
// 	//
//
// 	clay_ui_text( el_table_play_get_data( 0, y ), color_fg );
// 	self->child_position = position;
//
// 	//
//
// 	el_finish;
// }
//
// void el_table_play_on_ui_event( ui_event event ) {
// 	handle_ui_event_for_list( event, &clay.ui.data_play );
// }
//
// void el_table_play() {
// 	int id = ui_element_start();
// 	ui_element_bind( clay.ui.data_play, el_table_play_on_ui_event );
// 	ui_element_set_table( 48 );
//
// 	for ( int i = 0; i < array_count( views_play ); i++ ) el_table_play_row();
//
// 	el_finish;
// }

void el_column_play() {
	int id = ui_element_start();
	clay_ui_draw_fill();
	ui_element_set_block();
	ui_element_set_padding(2);

	el_header( "PLAY" );
	// el_table_play();

	//

	el_finish;
}
