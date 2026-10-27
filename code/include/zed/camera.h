#pragma once

#include <zed/xmath.h>

// todo
#include <zed/platform/dxm.h>

matrix orthographic;

struct zed_camera_draw {
	matrix matrix_view;
	matrix matrix_clip;

	matrix matrix_tiwv;
	matrix matrix_iwvc;

	xm_float3 camera_position;

	matrix look;
};

struct zed_camera {
	float3 position;
	float3 rotation;
	float fov = 60;
};

enum zed_scripted_camera_type {
	camera_type_free,
	camera_type_orbit,
};

struct zed_scripted_camera {
	float3 position;
	float3 rotation;
	zed_scripted_camera_type type;
};

//

// float zed_get_screen_aspect_inline();
//
// matrix zed_camera_get_rotation_matrix( float3 rotation );
// matrix zed_camera_get_projection_matrix( float fov_degrees );
//
// void zed_camera_init        ( zed_camera &camera );
// void zed_camera_update      ( zed_camera &camera, zed_camera_draw *draw );
// void zed_camera_update_orbit( zed_camera &camera, zed_camera_draw *draw, float camera_zoom );
// void zed_camera_update_draw ( zed_camera &camera, zed_camera_draw *draw );
//
// void   zed_camera_look_at( zed_camera &camera );
// float3 zed_camera_walk   ( zed_camera &camera, float x, float y, float z );
// float3 zed_camera_move   ( zed_camera &camera, float x, float y, float z );

//

#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/camera.h>
#include <zed/xmath.h>

//

// todo
float zed_get_screen_aspect_inline();

matrix zed_camera_get_rotation_matrix( float3 rotation ) {
	float pitch = dtor( rotation.x );
	float yaw   = dtor( rotation.y );
	float roll  = dtor( rotation.z );

	return DirectX :: XMMatrixRotationRollPitchYaw( pitch, yaw, roll );
}

matrix zed_camera_get_projection_matrix( float fov_degrees ) {
	float fov_radians   = dtor( fov_degrees );
	float screen_aspect = zed_get_screen_aspect_inline();
	float screen_far    = 1000;
	float screen_near   = 0.01;

	return DirectX :: XMMatrixPerspectiveFovLH( fov_radians, screen_aspect, screen_far, screen_near );
}

// matrix zed_camera_get_orthographic_matrix() {
// 	return DirectX :: XMMatrixOrthographicOffCenterRH( 0, 320, 240, 0, 0, 1000 );
// }

//

void zed_camera_update( zed_camera &camera, zed_camera_draw *draw ) {
	matrix matrix  = zed_camera_get_rotation_matrix( camera.rotation );
	float3 up      = mul( float3( 0, 1, 0 ), matrix );
	float3 look_at = mul( float3( 0, 0, 1 ), matrix );
	look_at = look_at + camera.position;
	draw->matrix_view = DirectX :: XMMatrixLookAtLH( camera.position, look_at, up ); // todo
}

void zed_camera_update_orbit( zed_camera &camera, zed_camera_draw *draw, float camera_zoom ) {
	float3 up       = { 0, 1, 0 };
	float3 position = camera.position;
	float3 look_at   = { 0, 0, 1 };

	matrix rotation = zed_camera_get_rotation_matrix( camera.rotation );

	//

	float3 normal = { 0, 0, -1 };
	normal   = normalize( mul( normal, rotation ) ) * camera_zoom;

	position = normal + camera.position;
	look_at   = camera.position;

	//

	draw->matrix_view = XMMatrixLookAtLH( position, look_at, up );
}

//

void zed_camera_look_at( zed_camera &camera ) {
	//
}

float3 zed_camera_walk( zed_camera &camera, float x, float y, float z ) {
	using namespace DirectX;

	// note copied from above and modified( better )
		float3 camera_rotation = { 0.0, camera.rotation.y, camera.rotation.z };
		matrix rotation        = zed_camera_get_rotation_matrix( camera_rotation );

		float3 position = { 0, 0, 0 };
		float3 up       = { 0, 1, 0 };
		float3 look_at  = { 0, 0, 1 };
		float3 right    = { 1, 0, 0 };

		up      = mul( up,      rotation );
		look_at = mul( look_at, rotation );
		right   = mul( right,   rotation );
	//

	position = mad( XMVectorReplicate( x ), right,   position );
	position = mad( XMVectorReplicate( y ), look_at, position );
	position = mad( XMVectorReplicate( z ), up,      position );

	return position;
}

float3 zed_camera_move( zed_camera &camera, float x, float y, float z ) {
	using namespace DirectX;

	// note copied from above and modified( better )
		float3 camera_rotation = { camera.rotation.x, camera.rotation.y, camera.rotation.z };
		matrix rotation        = zed_camera_get_rotation_matrix( camera_rotation );

		float3 position = { 0, 0, 0 };
		float3 up       = { 0, 1, 0 };
		float3 look_at  = { 0, 0, 1 };
		float3 right    = { 1, 0, 0 };

		up      = mul( up,      rotation );
		look_at = mul( look_at, rotation );
		right   = mul( right,   rotation );
	//

	position = mad( XMVectorReplicate( x ), right,   position );
	position = mad( XMVectorReplicate( y ), look_at, position );
	position = mad( XMVectorReplicate( z ), up,      position );

	return position;
}
