#include "2_graphics/0_debug.cpp"
#include "2_graphics/1_query.cpp"
#include "2_graphics/2_device.cpp"
#include "2_graphics/3_buffer.cpp"
#include "2_graphics/4_mesh.cpp"
#include "2_graphics/5_texture.cpp"
#include "2_graphics/6_pass.cpp"
#include "2_graphics/7_canvas.cpp"
#include "2_graphics/8_text.cpp"

// user

void main_size();
void main_draw();

//

void app_graphics_init() {
	// device

	app_graphics_device_and_swap_chain_1();

	// query

	app_graphics_query_init();

	app.graphics.render_target.size = app.system.device_size;
	app.graphics.render_target.size = app.graphics.display_size; // ?

	// pass

	app_graphics_input_layout_init();
	app_graphics_rasterizer_init();
	app_graphics_sampler_init();
	app_graphics_blend_init();
	app_graphics_depth_stencil_init();

	//

	app_graphics_back_buffer_init();
	app_graphics_depth_buffer_init();

	// debug

	app_graphics_debug_init();

	// text

	app_graphics_text_init();
}

void app_graphics_exit() {
	app_graphics_query_exit();
	app_graphics_debug_exit();
}

void app_graphics_size() {
	// todo: app.graphics.back_buffer is vestigial and this function doesn't work properly
	return;

	// todo: this just skips when a WM_SIZE is received before graphics are initialized,
	// would live better elsewhere
	if ( ! app.graphics.swap_chain ) return;

	// todo
	// app.graphics.back_buffer->Release();
	app.graphics.swap_chain->ResizeBuffers( 0, 0, 0, DXGI_FORMAT_UNKNOWN, 0 );

	app_graphics_back_buffer_init();
	app_graphics_depth_buffer_init();
	main_size();
}

void app_graphics_flip() {
	app.graphics.swap_chain->Present( 1, 0 );
}

void app_graphics_draw() {
	zed_pass_reset();
	app_graphics_query_begin_frame();
	zed_set_render_target( app.graphics.render_target );
	app_graphics_clear();
	main_draw();
	app_graphics_flip();
	app_graphics_query_end_frame();
}

// todo
void zed_clear_stencil() {
	app.graphics.device_context->ClearDepthStencilView( app.graphics.dsv, D3D11_CLEAR_DEPTH, 0, 0 );
}
