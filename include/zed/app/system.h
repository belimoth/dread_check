#pragma once

#include <zed.h>

//

#if 1

#include <stdio.h>

struct zed_file {
	FILE *stream;
};

zed_file app_system_fopen( char const *file_name, char const *mode = "rb" ) {
	zed_file file = {};
	file.stream = fopen( file_name, mode );
	return file;
}

// zed_file app_system_fmemopen( handle data, int size ) {
// 	zed_file file = {};
// 	file.stream = fmemopen( data, size, "rb" );
// 	return file
// }

void app_system_fseek( zed_file file, int offset ) {
	fseek( file.stream, offset, 0 );
}

void app_system_fclose( zed_file file ) {
	fclose( file.stream );
}

size_t app_system_fread( zed_file file, handle buffer, size_t element_size, size_t element_count ) {
	return fread( buffer, element_size, element_count, file.stream );
}

#else

#include <zed/platform/physfs.h>

struct zed_file {
	PHYSFS_File *stream;
};

zed_file app_system_fopen( char const *file_name, char const *mode = "rb" ) {
	zed_file file = {};
	file.stream = PHYSFS_openRead( file_name );
	return file;
}

void app_system_fclose( zed_file file ) {
	PHYSFS_close( file.stream );
}

size_t app_system_fread( handle buffer, size_t element_size, size_t element_count, zed_file file ) {
	return PHYSFS_readBytes( file.stream, buffer, element_size * element_count );
}

#endif

// files

handle app_system_resource_data( int id );
int    app_system_resource_size( int id );
