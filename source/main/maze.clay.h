#include "maze.h"

void maze_new() {
	zed_random_seed( app.time );

	maze_clear();

	maze_room(  1,  1, 15, 11 );
	maze_room( 16,  1, 15, 11 );
	maze_room( 31,  1, 15, 11 );
	maze_room( 46,  1, 15, 11 );
	maze_room(  1, 12, 15, 11 );
	maze_room( 16, 12, 15, 11 );
	maze_room( 31, 12, 15, 11 );
	maze_room( 46, 12, 15, 11 );
	maze_room(  1, 23, 15, 11 );
	maze_room( 16, 23, 15, 11 );
	maze_room( 31, 23, 15, 11 );
	maze_room( 46, 23, 15, 11 );
	maze_room(  1, 34, 15, 11 );
	maze_room( 16, 34, 15, 11 );
	maze_room( 31, 34, 15, 11 );
	maze_room( 46, 34, 15, 11 );
	maze_room(  1, 45, 15, 11 );
	maze_room( 16, 45, 15, 11 );
	maze_room( 31, 45, 15, 11 );
	maze_room( 46, 45, 15, 11 );

	maze_empty(  0,  0, 64,  1 );
	maze_empty(  0,  0,  1, 64 );
	maze_empty( 62,  1,  3, 64 );
	maze_empty(  1, 57, 64, 10 );

	//

	struct maze_door_i {
		int i;
	};

	maze_door_i door[ door_max ]; int door_i = 0;

	for ( int i = 0; i < maze.door_i; i++ ) {
		bool pass = false;
		// if ( maze.door[i].x ==  1 ) pass = true;
		// if ( maze.door[i].x == 61 ) pass = true;
		// if ( maze.door[i].y ==  1 ) pass = true;
		// if ( maze.door[i].y == 61 ) pass = true;
		if ( pass ) door[ door_i++ ].i = i;
	}

	// if ( door_i ) maze.grid[ door[ zed_random_get( 0, door_i - 1 ) ].i ].color = 0;
	// if ( door_i ) for ( int i = 0; i < door_i; i++ ) maze.door[ door[i].i ] = maze.door[ --maze.door_i ];

	for ( int i = maze.door_i; i > 0; --i ) {
		printf( "%i %i\n", maze.door[i].x, maze.door[i].y );
		bool pass = false;
		if ( maze.door[i].x ==  1 ) pass = true;
		if ( maze.door[i].x == 61 ) pass = true;
		if ( maze.door[i].y ==  1 ) pass = true;
		if ( maze.door[i].y == 61 ) pass = true;
		if ( pass ) maze.door[i] = maze.door[ --maze.door_i ];
	}

	//

	for ( int k = 0; k < 256; k++ ) {
		// printf( "\n\n" );
		// maze_print();

		maze_grid_clear();
		int color_i = 1;

		for_maze_i {
			if ( maze.grid_fill[i].color == 0 ) {
				maze_grid_fill( i, color_i++ );
			}
		}

		if ( color_i == 2 ) break;

		int i = zed_random_get( 0, maze.door_i - 1 );
		int seen = 0;
		int j = maze.door[i].x + maze.door[i].y * 64;

		if ( maze.door[i].x >  0 and maze.door[i].x < 64 and maze.grid_fill[ j -  1 ].color != maze.grid_fill[ j +  1 ].color ) seen++;
		if ( maze.door[i].y >  0 and maze.door[i].y < 64 and maze.grid_fill[ j - 64 ].color != maze.grid_fill[ j + 64 ].color ) seen++;

		if ( seen > 0 ) maze.grid[j].color = 0;

		maze.door[i] = maze.door[ --maze.door_i ];
	}
}
