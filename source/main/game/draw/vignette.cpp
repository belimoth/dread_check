#include "../../../main.h"
#include "../../game.h"
#include "../draw/split.h"

#include <zed/camera.h>

// todo
#include <zed/platform/d3d11.h>

void game_draw_per_frame_update();

zed_pass          pass_vignette;
ID3D11BlendState *blend_alpha;

void game_draw_vignette_init() {
	zed_pass_new( pass_vignette, "data/shader/game/vignette.hlsl" );

	// todo

	D3D11_BLEND_DESC bd                      = {};
	bd.RenderTarget[0].BlendEnable           = true;
	bd.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT result;
	result = app.graphics.device->CreateBlendState( &bd, &blend_alpha );

	game_draw_vignette_t data = {};
	data.roundness    = -0.5;
	data.radius_min   = 0.1;
	data.radius_max   = 0.8;
	data.aspect_ratio = 1 / zed_get_screen_aspect_inline();
	// data.color        = 0.0;

	game.draw.vignette = data;
}

void game_draw_vignette_draw() {
	// todo
	zed_clear_stencil();
	zed_canvas canvas = canvas_x1;
	if ( split == game_split_quad ) canvas = canvas_x2;
	zed_canvas_clear_stencil( canvas );

	zed_camera temp = game.camera;
	temp.position   = { 0, 0, 0 };

	zed_camera_update( temp, &game.draw.camera );
	game_draw_per_frame_update();

	zed_pass_reset( pass_vignette );

	app.graphics.device_context->OMSetBlendState( blend_alpha, 0, 0xffffffff );
	zed_mesh_draw_primitive( zed_primitive_triangle_list, 3 );
}

void game_draw_vignette() {
	game_draw_set_camera_i {
		game_player &player = game.data.player[i];

		// todo, different buffer or array

		float t = (float)player.vitals.exertn / exertn_max;
		t = lerp( t, max( t, 0.5 ), player.t_stress_damage_flash );

		// game.draw.vignette.roundness  = 0.5;
		// game.draw.vignette.radius_min = lerp( 0.8, 0.4, t );
		// game.draw.vignette.radius_max = lerp( 1.0, 0.6, t );

		// game.draw.vignette.roundness  = 0.5;
		// game.draw.vignette.radius_min = lerp( 0.8, 0.5, t );
		// game.draw.vignette.radius_max = lerp( 0.8, 0.5, t );

		// game.draw.vignette.roundness  = -1.0;
		// game.draw.vignette.radius_min = lerp( 1.0, 0.5, t ); // note try 0.5
		// game.draw.vignette.radius_max = lerp( 1.0, 0.5, t );

		// game.draw.vignette.roundness  = -1.0;
		// game.draw.vignette.radius_min = lerp( 1.1, 0.5, t );
		// game.draw.vignette.radius_max = lerp( 1.1, 0.5, t );

		// game.draw.vignette.roundness  = -1.0;
		// game.draw.vignette.radius_min = lerp( 1.1, 0.27, t );
		// game.draw.vignette.radius_max = lerp( 1.1, 0.27, t );

		game.draw.vignette.roundness  = -1.0;
		game.draw.vignette.radius_min = lerp( 1.1, 0.19, t );
		game.draw.vignette.radius_max = lerp( 1.1, 0.19, t );

		game.draw.vignette.aspect_ratio = 1 / zed_get_screen_aspect_inline();
		game.draw.vignette.color        = float3( 245, 73, 39 ) / 255 * player.t_stress_damage_flash / 4; // player.t_stress_damage_flash / 4;

		game_draw_per_frame_update();
		game_draw_vignette_draw();
	}
}
