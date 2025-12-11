#include "../clay.h"

#include <zed/app/graphics.h>
#include <zed/color.h>
#include <zed/platform/ini.h>

int studio_ini_handler( handle user, string section, string name, string value ) {
	clay_draw_studio *studio = (clay_draw_studio *)user;

	#define match( s, n ) if ( strcmp( section, s ) == 0 and strcmp( name, n ) == 0 )

	for (;;) {
		match( "", "ambient_0" ) { studio->ambient_0 = float3( htov( value ) ); break; }
		return 0;
	}

	return 1;
}

void studio_init() {
	zed_buffer_new_uniform( clay.edit_model.buffer_studio, sizeof(clay.edit_model.studio) );
	clay.edit_model.studio.ambient_0 = float3( htov( 0xFFFFE5 ) );
	ini_parse( "data/studio.ini", studio_ini_handler, &clay.edit_model.studio );
	zed_buffer_update( clay.edit_model.buffer_studio, &clay.edit_model.studio, sizeof(clay.edit_model.studio), 0 );
	zed_buffer_use_uniform( clay.edit_model.buffer_studio, 3 );
}
