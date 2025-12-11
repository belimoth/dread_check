#include <zed/app/ui.h>
#include <zed/color.h>

#include "../clay.h"
#include "ui.h"

#include "ui/menu.h"

#include "ui/play.h"
#include "ui/view.h"
#include "ui/edit.h"
#include "ui/find.h"
#include "ui/sync.h"
#include "ui/itch.h"
#include "ui/user.h"

#include "ui/tools.h"
#include "ui/main.h"
#include "ui/inspect.h"

void el_root() {
	int id = ui_element_start();
	int size = 560; // 792;
	int flex[] = { 96, 2, size, 2, 192, 2, 0, 2, size };
	ui_element_set_flex( array_and_count( flex ) );

	el_column_menu();
	el_border();

	switch ( clay.page ) {
		case clay_page_menu_play:
		el_column_play();
		el_border();
		break;

		case clay_page_menu_view:
		el_column_view();
		el_border();
		break;

		case clay_page_menu_edit:

		switch ( clay.page_edit ) {
			case clay_page_edit_none:
			el_column_edit();
			el_border();
			break;

			case clay_page_edit_image:
			break;

			case clay_page_edit_maze:
			break;

			case clay_page_edit_model:
			el_column_edit();
			el_border();
			el_column_tools();
			el_border();
			el_column_main();
			el_border();
			el_column_inspect();
			break;

			case clay_page_edit_world:
			break;
		}

		break;

		case clay_page_menu_find:
		el_column_find();
		el_border();
		break;

		case clay_page_menu_sync:
		el_column_sync();
		el_border();
		break;

		case clay_page_menu_itch:
		el_column_itch();
		el_border();
		break;

		case clay_page_menu_user:
		el_column_user();
		el_border();
		break;
	}

	ui_element_finish( id );
}

void clay_ui_init() {
	ui.el_root = el_root;
	if ( app.options.headless ) zed_die();
	// clay.ui.data_menu.id_target = 2; // note
}
