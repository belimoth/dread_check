#pragma once

#include "../../input.h"
#include "menu.h"
#include "object.h"
#include "world.h"

#include "player/bag.h"
#include "player/hands.h"
#include "player/hud.h"
#include "player/item.h"
#include "player/queue.h"
#include "player/rig.h"
#include "player/stance.h"
#include "player/torso.h"
#include "player/vitals.h"

#include <zed/xmath.h>

// main

struct game_player {
	game_object object = {};

	int i;

	float turn_speed;
	float jump_speed;
	float fall_speed;

	game_player_bag    bag;
	game_player_hands  hands;
	game_player_torso  torso;
	game_player_stance stance;
	game_player_vitals vitals;

	bool did_sprint;
	bool did_jump;
	bool holding_breath;

	game_action action;
	uint action_timer;
	game_action action_queue[8] = {};
	uint action_queue_length = 0;

	uint exertion_stress_timer;
	float t_stress_damage_flash;

	float nerves_timer;

	game_player_rig rig;
	game_gun_rig gun_rig_0;
	game_gun_rig gun_rig_1;

	// todo

	float t;
	zed_pad pad;
	zed_pad pad_previous;
	uint heart;

	float trigger;

	bool a_menu_handled;
	bool b_menu_handled;
	bool x_menu_handled;
	bool y_menu_handled;

	//

	int ammo_i;

	//

	game_player_hint hint;
};

// constants

float game_player_get_height    ( game_player &player );
float game_player_get_bob_rate  ( game_player &player );
float game_player_get_bob_amount( game_player &player );

// item

void game_item_init();
bool game_item_can   ( game_item, game_action );
void game_item_try( game_player &player, game_action action );
void game_item_do    ( game_player &, game_action );
void game_item_finish( game_player &, game_item &, game_action, bool );


// hands

void game_player_hands_unholster   ( game_player &player );
game_item &game_player_hands_get_item( game_player &player );
void game_player_hands_switch( game_player &, bool silent = false );
void game_player_hands_switch_primary     ( game_player &player, int i );
void game_player_hands_switch_primary_up  ( game_player &player );
void game_player_hands_switch_primary_down( game_player &player );
void game_player_hands_switch_secondary_up( game_player & );
void game_player_hands_switch_secondary_down( game_player & );
void game_player_hands_swap( game_player & );
void game_player_hands_away( game_player & );

// stance

bool game_player_stance_is_airborne( game_player &player );
bool game_player_stance_relax( game_player &player );
void game_player_stance_land( game_player &player, game_player_stance stance = stance_walk );
void game_player_stance_dive( game_player &player );
void game_player_stance_dive( game_player &player, game_player_stance stance );
bool game_player_stance_can_jump( game_player & );
void game_player_stance_hide_raise( game_player & );
void game_player_stance_hide_lower( game_player & );
void game_player_stance_spin_left ( game_player & );
void game_player_stance_spin_right( game_player & );
bool player_stance_is_ready( game_player &player );

// vitals

void game_player_vitals_init( game_player &player );
void game_player_vitals_stress( game_player &player, int damage = 1 );

void game_player_vitals_step();
