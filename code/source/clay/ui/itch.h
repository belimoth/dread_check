#pragma once

#include "../ui.h"

#include <zed/app/ui.h>

void el_column_itch() {
	el_start;
	clay_ui_draw_fill();
	el_block;
	ui_element_set_padding(2);

	el_header( "ITCH" );

	el_finish;
}
