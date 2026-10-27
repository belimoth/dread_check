#pragma once

#include "game.h"
#include "wolf.h"

#include <zed/random.h>

#define maze_max 64 * 64
#define chest_max 1024
#define snow_max 64
#define door_max 256

#define for_maze_i for ( int i = 0; i < maze_max; i++ )

struct maze_cell_r {
	float2 position;
	float2 size;
};

struct maze_cell {
	int color;
};

struct maze_chest {
	float2 position;
};

struct maze_snow {
	float3 position;
	float  padding;
};

struct maze_door {
	int x, y;
};

struct maze_t {
	maze_cell_r data [ maze_max ];
	maze_cell   grid [ maze_max ];
	maze_cell   grid_fill[ maze_max ];
	maze_chest  chest[ chest_max ]; int chest_i;
	maze_snow   snow [ snow_max ];
	maze_door   door [ door_max ]; int door_i; int door_j;
} maze;

void maze_clear() {
	for ( int i = 0; i < 64 * 64; i++ ) maze.grid[i].color = 1;
}

void maze_empty( int x, int y, int w, int h ) {
	for ( int xx = max( x, 0 ); xx < min( x + w, 64 ); xx++ ) {
	for ( int yy = max( y, 0 ); yy < min( y + h, 64 ); yy++ ) {
		int i = xx + yy * 64;
		maze.grid[i].color = 0;
	}
	}
}

void maze_room( int x, int y, int w, int h ) {
	maze_empty( x + 1, y + 1, w - 1, h - 1 );
	maze.chest[ maze.chest_i++ ].position = ( float2( x + 2, y + 2 ) + float2( zed_random_get( 0, w - 4 ), zed_random_get( 0, h - 4 ) ) );

	maze.door[ maze.door_i++ ] = { x +  3, y +  0 };
	maze.door[ maze.door_i++ ] = { x +  7, y +  0 };
	maze.door[ maze.door_i++ ] = { x +  9, y +  0 };
	maze.door[ maze.door_i++ ] = { x + 13, y +  0 };
	maze.door[ maze.door_i++ ] = { x +  0, y +  3 };
	maze.door[ maze.door_i++ ] = { x +  0, y +  9 };
	maze.door[ maze.door_i++ ] = { x + 16, y +  3 };
	maze.door[ maze.door_i++ ] = { x + 16, y +  9 };
	maze.door[ maze.door_i++ ] = { x +  3, y + 12 };
	maze.door[ maze.door_i++ ] = { x +  7, y + 12 };
	maze.door[ maze.door_i++ ] = { x +  9, y + 12 };
	maze.door[ maze.door_i++ ] = { x + 13, y + 12 };
}

void maze_grid_clear() {
	for_maze_i maze.grid_fill[i].color = -maze.grid[i].color;
}

void maze_grid_fill( int i, int color ) {
	if ( maze.grid_fill[i].color != 0 ) return;
	int x = i % 64;
	int y = ( i - x ) / 64;
	maze.grid_fill[i].color = color;
	if ( x >  0 ) maze_grid_fill( i -  1, color );
	if ( x < 63 ) maze_grid_fill( i +  1, color );
	if ( y >  0 ) maze_grid_fill( i - 64, color );
	if ( y < 63 ) maze_grid_fill( i + 64, color );
}

void maze_print() {
	printf( "\n\n" );

	for_maze_i {
		if ( i % 64 == 0 ) printf( "\n" );
		printf( "%4i", maze.grid_fill[i].color );
	}
}

void maze_init();
void maze_start();
