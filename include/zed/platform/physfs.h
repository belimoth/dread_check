#pragma once

// #include <windows.h>
#pragma comment( lib, "advapi32.lib" )
#pragma comment( lib, "shell32.lib" )

// todo this should prevent the creation of "draugb.lib" and "draugb.exp"
// todo but it doesn't
#define PHYSFS_DECL

#include <physfs/physfs.h>
#pragma comment( lib, "physfs-static.lib" )

void physfs_init() {
	do {} while( ! PHYSFS_init( 0 ) );
	PHYSFS_permitSymbolicLinks( true );
	PHYSFS_mount( ".", 0, true );
	PHYSFS_mount( "draugb.exe", 0, true );
}
