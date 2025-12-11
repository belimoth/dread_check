#pragma once

#include <zed/app/ui.h>

#include "../ui.h"

//

void el_column_tools() {
	int id = ui_element_start();
	clay_ui_draw_fill();
	ui_element_set_block();

	el_header( "TOOLS" );

	ui_element_finish( id );
}
