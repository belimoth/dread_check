#pragma once

enum game_chapter {
	chapter_none = 0,
	chapter_max,
};

int chapter_current  = chapter_none;
int chapter_continue = chapter_none;

void chapter_set( int chapter_new ) {
	if ( chapter_new == chapter_current ) return;
	// todo transition animation
	chapter_current = chapter_new;
}
