#include <zed/camera.h>

#include "../../main.h"
#include "../game.h"

bool long_bullets = false;
float bullet_length = 0.5;

struct game_bullet_lights {
	game_light &light_point;
	game_light &light_capsule;
};

void game_bullet_make_lights( game_bullet_lights bullet, float3 p, float3 d ) {
	float s = 3;

	bullet.light_point.position = p;
	bullet.light_point.range    = 16; // 8;
	bullet.light_point.color    = { 3 * s, 2 * s, 1 * s };
	// bullet.light_point.color    = { 12, 8, 4 }; // brighter
	// bullet.light_point.color    = {  4, 2, 1 }; // redder
	// bullet.light_point.color    = {  8, 8, 8 }; // flashbang

	bullet.light_capsule.position = p;
	bullet.light_capsule.range    = 2;
	bullet.light_capsule.color    = { 2, 1, 0.5 }; // 4, 2, 1 x 0.5

	if ( long_bullets ) {
		bullet.light_capsule.color = { 0, 4, 8 }; // blue_cyan
		bullet.light_capsule.color = { 2, 5, 8 }; // blue_cyan_white
		bullet.light_capsule.color = { 0, 4, 1 }; // green
	}

	bullet.light_capsule.direction = d;
	bullet.light_capsule.length    = bullet_length;

	if ( game.scene == scene_maze ) {
		bullet.light_point  .color = { 1, 1, 1 };
		bullet.light_capsule.color = { 1, 1, 1 };
	}
}

//

// todo
matrix get_gun_handle( game_player &player );

void game_bullet_make( game_player &player ) {
	zed_camera camera = game.data.camera[ player.i ];

	//

	float3 move = zed_camera_move( camera, 0.1, 0.8, -0.07 );

	if ( long_bullets ) bullet_length = 256	;

	float3 p = camera.position + move;
	matrix m = translate( 0, 0, 1 ) * zed_camera_get_rotation_matrix( camera.rotation );
	float3 d = mul( float3( 0, 0, 0 ), m );

	//

	// matrix handle = get_gun_handle( player );
	// d = mul( float3( 0, 0, 0 ), handle );

	//

	{
		int i = game.data.bullet_i++;

		// todo try swapping order of ops and statements

		matrix m = identity;
		m = m * translate( 0, 0, 0.05 );
		m = m * scale( 0.5, 0.5, 1 / 0.05 * bullet_length );
		m = m * zed_camera_get_rotation_matrix( camera.rotation );
		m = m * translate( p );

		game.data.bullet[ i % 8 ].m  = m;
		game.data.bullet[ i % 8 ].t  = app.time;
		game.data.bullet[ i % 8 ].p0 = p;
	}

	{
		int i = game.data.flash_i++;

		game_bullet_lights bullet = {
			game.draw.light.light_point  [ i % 8 ],
			game.draw.light.light_capsule[ i % 8 ],
		};

		game_bullet_make_lights( bullet, p, d );
	}
}

void game_bullet_step() {
	static const float bullet_speed = 0.5;
	// static const float bullet_speed = 0.1;

	float decay = 0.7;

	for ( int i = 0; i < game.data.bullet_i and i < 8; i++ ) {
		game.draw.light.light_point[i].color.x *= decay;
		game.draw.light.light_point[i].color.y *= decay;
		game.draw.light.light_point[i].color.z *= decay;

		game.draw.light.light_point[i].color;

		if ( app.time - game.data.bullet[i].t > 24 ) {
			// game.draw.light.light_point[i] = {};

			if ( long_bullets ) game.data.bullet[i] = {};
		}

		if ( long_bullets ) {
			game.draw.light.light_capsule[i].color.x *= 0.92;
			game.draw.light.light_capsule[i].color.y *= 0.92;
			game.draw.light.light_capsule[i].color.z *= 0.92;
			continue;
		}

		game.data.bullet[i].m = game.data.bullet[i].m * translate( float3( game.draw.light.light_capsule[i].direction ) * bullet_speed );
		game.draw.light.light_capsule[i].position = float3( game.draw.light.light_capsule[i].position ) + float3( game.draw.light.light_capsule[i].direction ) * bullet_speed;

		// todo find exact point of impact

		// if ( mul( float3( 0, 0, 0 ), game.data.bullet[i].m ).y < 0 ) {
		// 	float3 plane = { 0, 1, 0 };
		// 	matrix matrix_reflect = reflect( plane );
		// 	game.data.bullet[i].m  = game.data.bullet[i].m * matrix_reflect;
		// 	game.draw.light.light_capsule[i].direction = mul( game.draw.light.light_capsule[i].direction, matrix_reflect );
		// }
	}

	for ( int i = 0; i < 8; i++ ) {
		// game.draw.light.light_spot[i].color = { 2, 1, 0.5 };
		// game.draw.light.light_spot[i].position = float3( i, -1, 0 );
	}
}
