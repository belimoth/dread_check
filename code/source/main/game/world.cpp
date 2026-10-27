#include <zed/random.h>

#include "../game.h"

void game_world_init() {
	game.data.wall[0] = { { 4 - 8, 0, 4 - 8 }, { 5 - 12, 0, 5 - 8 } };
	game.data.wall[1] = { { 7 - 8, 0, 7 - 8 }, { 9 - 12, 0, 8 - 8 } };

	//

	int w = 64;
	int h = 64;

	float height_top = 1.5;

	for ( int x = 0; x < w; x++ ) {
	for ( int y = 0; y < h; y++ ) {
		int i = x + y * w;
		game_data_world[i].p.x = x;
		game_data_world[i].p.y = y;
		game_data_world[i].p.z = max( 0, (float)( x + zed_random_get( -1, 1 ) ) * height_top / 5 );
		if ( y == 0 or x == 63 or y == 63 ) game_data_world[i].p.z = 0;
	}}
}
