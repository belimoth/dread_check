#include <zed.h>

#include "vitals.h"
#include "../player.h"

void game_player_vitals_init( game_player &player ) {
	player.vitals        = {};
	player.vitals.health = 1000;
	player.vitals.stress = 5;
	player.vitals.hunger = 100;
	player.vitals.thirst = 100;
}

void game_player_vitals_stress( game_player &player, int damage ) {
	player.vitals.stress += damage;
	if ( player.vitals.stress > 1000 ) player.vitals.stress = 1000;

	player.vitals.nerves += damage * nerves_ratio;
	// if ( player.vitals.nerves > 1000 ) player.vitals.nerves = 1000;

	player.t_stress_damage_flash = 1.0;
}

void game_player_vitals_step( game_player &player ) {
	// exertn

	if ( player.did_sprint ) {
		player.vitals.exertn += cost_sprint;
		player.did_sprint = false;
	} else {
		if ( player.stance == stance_jog ) {
			if      ( player.vitals.exertn <= rest_jog - cost_jog_p ) player.vitals.exertn += cost_jog_p;
			else if ( player.vitals.exertn >= rest_jog - cost_jog_n ) player.vitals.exertn += cost_jog_n;
			else                                                      player.vitals.exertn = rest_jog;
		} else if ( player.stance == stance_run or player.holding_breath == true ) {
			player.vitals.exertn += cost_run;
		} else if ( player.stance == stance_skid or player.stance == stance_slide_supine ) {
			player.vitals.exertn += cost_skid;
		} else {
			player.vitals.exertn += cost_walk;
		}
	}

	if ( player.pad.joy_0.magnitude < 0.2 and player.pad.ls ) {
		player.vitals.exertn += cost_breath;
	}

	if ( player.did_jump ) {
		player.vitals.exertn += cost_jump;
		player.did_jump = false;
	}

	if ( player.stance == stance_jump or player.stance == stance_dive_prone or player.stance == stance_dive_supine or player.stance == stance_dive_left or player.stance == stance_dive_right ) player.vitals.exertn += 1;

	player.vitals.exertn = min( max( player.vitals.exertn, 0 ), exertn_max );

	// stress

	if ( player.vitals.exertn == exertn_max ) {
		player.exertion_stress_timer += 1;

		if ( player.exertion_stress_timer == 60 ) {
			player.exertion_stress_timer = 0;
			game_player_vitals_stress( player );
		}
	}

	// if ( player.stance == stance_walk or player.stance == stance_hide ) {
	// 	if ( player.vitals.exertn > 0 ) {
	// 		int damage = floor( player.vitals.exertn / 100 );
	// 		game_player_vitals_stress( damage );
	// 		player.vitals.exertn = 0;
	// 	}
	// }

	// todo

	int max_health  = 1000 - player.vitals.stress;

	// nerves

	if ( player.vitals.nerves > 0 ) {
		player.vitals.nerves -= 1;
	}

	player.nerves_timer += 1;

	if ( player.nerves_timer >= 20 ) {
		player.nerves_timer = 0;
	}
}
