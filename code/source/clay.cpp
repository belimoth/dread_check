#include "clay.h"
#include "clay/ui.cpp"
#include "clay/edit/model.cpp"
#include "clay/edit/world.cpp"

void clay_init() {
	clay_gfx_init();
	clay_edit_model_init();
	clay_edit_world_init();
	clay_find_init();
	clay_sync_init();
	clay_ui_init();
	clay.scene = clay_scene_edit_model;
	clay.page_edit = clay_page_edit_model;
}

void clay_step() {
	if ( not clay.show ) return;

	switch( clay.scene ) {
		case clay_scene_none:
		break;

		case clay_scene_edit_model:
		clay_edit_model_step();
		break;

		case clay_scene_edit_world:
		clay_edit_world_step();
		break;
	}
}

void clay_draw() {
	if ( not clay.show ) return;

	switch( clay.scene ) {
		case clay_scene_none:
		break;

		case clay_scene_edit_model:
		clay_edit_model_draw();
		break;

		case clay_scene_edit_world:
		clay_edit_world_draw();
		break;
	}
}
