#pragma once

struct clay_edit {
	char *path[64];
	int path_i;
	int path_count = sizeof( path ) / sizeof( path[0] );
};
