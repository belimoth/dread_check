#include "../player.h"

void game_player_torso_relax( game_player &player ) {
	if ( player.torso == torso_aim ) player.torso = torso_hip;
}
