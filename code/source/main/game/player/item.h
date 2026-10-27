#pragma once

#include "../object.h"
#include "../player.h"
#include "ammo.h"

enum game_item_i {
	item_none = 0,
	item_bag,
	item_ammo,
	item_torch,
	item_sword,
	item_grenade,
	item_us_1917_revolver,
	item_wi_1897_shotgun,
	item_ak_1947,
	item_us_1919_bmg,
	item_max
};

enum game_item_kind {
	item_kind_none,
	item_kind_hand,
	item_kind_long,
	item_kind_heavy,
	item_kind_max
};

struct game_item_mass {
	float stiffness;
	float damping;
};

struct game_item_type {
	game_item_i    i;
	game_item_kind kind;
	game_item_mass mass;
	game_ammo      ammo;
};

//

enum game_item_slide {
	slide_close,
	slide_open,
};

enum game_item_chamber {
	chamber_spent = -1,
	chamber_empty =  0,
	chamber_ready =  1,
	chamber_ghost =  2,
};

struct game_item_magazine {
	int count;
};

//

struct game_item {
	game_object object;

	game_item_type     type;
	game_item_slide    slide;
	game_item_chamber  chamber;
	game_item_magazine magazine;
};

//

enum game_action {
	action_none,

	action_sprint_enter,
	action_sprint_leave,

	action_aim_enter,
	action_aim_leave,

	action_jump,
	action_land,
	action_trip,

	action_shoot,
	action_unshoot,
	action_slide_open,
	action_slide_close,
	action_reload,
	action_unload,

	action_push,
	action_grab,
	action_throw
};

string         item_name[ item_max ];
game_item_type item_type[ item_max ];
game_item_mass item_mass_by_kind[ item_kind_max ];
