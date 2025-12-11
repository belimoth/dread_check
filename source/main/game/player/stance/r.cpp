#include "../../player.h"

bool game_player_stance_can_jump( game_player &player ) {
	switch ( player.stance ) {
		case stance_jump:
		case stance_fall:
		case stance_sail:
		case stance_skid:
		case stance_trip:
		case stance_dive_prone:
		case stance_dive_supine:
		case stance_dive_left:
		case stance_dive_right:
		return false;
	}

	return true;
}

void game_player_stance_r_step( game_player &player ) {
	if ( not game_player_stance_can_jump( player ) ) return; // note

	if ( player.pad.rs and not player.pad_previous.rs ) {
		if ( player.torso != torso_aim ) {
			if ( player.action == action_none ) {
				player.torso = torso_aim;
				if ( player.stance == stance_reach ) player.stance = stance_walk;
				if ( player.stance == stance_run   ) player.stance = stance_walk;
				if ( player.stance == stance_jog   ) player.stance = stance_walk;
			}
		} else {
			player.torso = torso_hip;
		}
	}
}
