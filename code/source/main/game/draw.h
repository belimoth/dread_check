#pragma once

#include <zed/app/graphics.h>
#include <zed/camera.h>
#include <zed/xmath.h>

struct game_light {
	xm_float3 position;
	float alpha;
	xm_float3 color;
	float  range;
	xm_float3 direction;
	float length;
};

struct game_draw_light {
	game_light light_point  [8];
	game_light light_capsule[8];
	game_light light_spot   [8];
};

struct game_draw_vignette_t {
	float roundness;
    float radius_min;
    float radius_max;
    float aspect_ratio;
	xm_float3 color;
};

struct alignas(16) game_draw_per_scene {
	float screen_width;
	float screen_height;
};

struct alignas(16) game_draw_per_frame {
	zed_camera_draw      camera;
	game_draw_light      light;
	game_draw_vignette_t vignette;
};

struct alignas(16) game_draw_per_object {
	matrix matrix_world;
};

struct alignas(16) game_draw_alpha {
	float alpha;
};

struct game_draw_t {
	game_draw_per_scene per_scene;

	union {
		game_draw_per_frame per_frame;

		struct {
			zed_camera_draw      camera;
			game_draw_light      light;
			game_draw_vignette_t vignette;
			xm_float4               fx;
		};
	};

	union {
		game_draw_per_object per_object;

		struct {
			matrix matrix_world;
		};
	};
};

static union {
	struct {
		zed_buffer data_per_scene;
		zed_buffer data_per_frame;
		zed_buffer data_per_object;

		zed_buffer data_alpha;
	};

	zed_buffer buffers[5];
};

void game_draw_init();

void game_draw_per_scene_update();
void game_draw_per_frame_update();
void game_draw_per_object_update();

void game_draw_per_object_set( float3 position );
void game_draw_per_object_set( float3 position, float3 rotation );
void game_draw_per_object_set_for_player( float3 position, float3 handle, float3 rotation, float3 rotationBefore );

void game_draw_alpha_set( float value );
