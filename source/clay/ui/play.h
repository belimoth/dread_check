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
// 	el_start;
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
// void el_table_play_on( ui_event event ) {
// 	handle_ui_event_for_list( event, &clay.ui.data_play );
// }
//
// void el_table_play() {
// 	el_start;
// 	ui_element_bind( clay.ui.data_play, el_table_play_on );
// 	ui_element_set_table( 48 );
//
// 	for ( int i = 0; i < array_count( views_play ); i++ ) el_table_play_row();
//
// 	el_finish;
// }


//

void ui_element_set_size_x( int x ) {
	ui_element_step_node &self   = ui.data.step_nodes[ ui.id_current  ];
	ui_element_step_node &parent = ui.data.step_nodes[ self.id_parent ];
	if ( parent.layout != ui_layout_block ) zed_die();
	self.size.x = x;
}

void el_game_interior() {
	el_start;
	ui_element_set_size_x( 320 );
	ui_element_set_size_y( 240 );
	clay_ui_draw_fill();
	el_finish;
}

void el_game() {
	el_start;
	el_block;
	ui_element_set_size_x( 480 );
	ui_element_set_size_y( 240 );

	clay_ui_draw_border();
	ui_element_set_padding( 2 );

	el_game_interior();

	el_finish;
}

//


void el_play() {
	el_start;
	el_block;
	ui_element_set_padding( 16, 0 );

	el_game();

	el_finish;

}

void el_column_play() {
	el_start;
	clay_ui_draw_fill();
	el_block;
	ui_element_set_padding(2);

	el_header( "PLAY" );
	el_play();

	el_finish;
}
