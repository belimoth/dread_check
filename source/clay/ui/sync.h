#pragma once

#include "../ui.h"

#include <zed/app/ui.h>

void el_column_sync() {
	int id = ui_element_start();
	clay_ui_draw_fill();
	ui_element_set_block();
	ui_element_set_padding(2);

	el_header( "SYNC" );

	el_finish;
}
