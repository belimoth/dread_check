#include "../../game.h"
#include "../player.h"
#include "constants.h"

#include <zed/app/input.h>
#include <zed/xmath.h>

#include "stance/a.cpp"
#include "stance/b.cpp"
#include "stance/x.cpp"
#include "stance/y.cpp"
#include "stance/l.cpp"
#include "stance/r.cpp"

bool player_stance_is_ready( game_player &player ) {
	switch ( player.stance ) {
		case stance_run:
		case stance_jump:
		case stance_fall:
		case stance_sail:
		case stance_skid:
		case stance_slide_prone:
		case stance_slide_supine:
		case stance_slide_left:
		case stance_slide_right:
		return false;
	}

	return true;
}

void game_player_stance_step( game_player &player ) {
	game_player_stance_skid_step( player );
	game_player_stance_a_step( player );
	game_player_stance_b_step( player );
	game_player_stance_l_step( player );
	game_player_stance_y_step( player );
	game_player_stance_x_step( player );
	game_mouse.z = 0; // todo
	game_player_stance_r_step( player );
}
