#pragma once

#include <zed.h>
#include <zed/random.h>
#include <zed/platform/itch.h>
#include <zed/platform/xxhash.h>

#include "../../data/names.h"

struct game_roster_character {
	uint seed;

	int name_i;
	int face_i;
	int age;
	int height;
	int weight;
	int primary;
	int secondary;
	int equipment;
	int cash;
};

game_roster_character roster[15];

void game_roster_init( uint page = 0 ) {
	game.seed = itch.user == 0 ? zed_hash( app.user ) : zed_hash( itch.user );

	zed_random_seed( game.seed, page );

	for ( int i = 0; i < 15; i ++ ) {
		roster[i] = {};
		roster[i].seed = zed_random_get();
		if ( i == 0 and page == 0 and strcmp( app.user, "zach" ) == 0 and strcmp( itch.user, "belimoth" ) == 0 ) roster[i].seed = 0;
	}

	for ( int i = 0; i < 15; i ++ ) {
		zed_random_seed( roster[i].seed );
		roster[i].name_i    = zed_random_get( 0, 209 );
		roster[i].face_i    = zed_random_get( 0, 149 );
		roster[i].age       = zed_random_get( 20, 80 );
		roster[i].height    = 140 + zed_random_get( 0, 30 ) + zed_random_get( 0, 30 );
		float bmi           = zed_random_get( 20, 30 );
		roster[i].weight    = roster[i].height * roster[i].height * bmi / 10000;
		roster[i].primary   = zed_random_get( 0, 7 );
		roster[i].secondary = zed_random_get( 0, 7 );
		roster[i].equipment = zed_random_get( 0, 7 );
		roster[i].cash      = 100 - zed_random_get( 0, 10 ) - zed_random_get( 0, 20 ) - zed_random_get( 0, 30 ) - zed_random_get( 0, 40 );
	}
}
