#include <zed.h>
#include <zed/platform/windows.h>

// #include <zed/platform/physfs.h>

void app_system_files_init() {
	// physfs_init();
}

handle app_system_resource_data( int id ) {
	HRSRC resource = FindResourceA( 0, MAKEINTRESOURCE( id ), RT_RCDATA );
	HGLOBAL global = LoadResource( 0, resource );
	return LockResource( global );
}

int app_system_resource_size( int id ) {
	HRSRC resource = FindResourceA( 0, MAKEINTRESOURCE( id ), RT_RCDATA );
	return (int)SizeofResource( 0, resource );
}
