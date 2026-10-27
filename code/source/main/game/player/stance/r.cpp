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

	// todo
}
