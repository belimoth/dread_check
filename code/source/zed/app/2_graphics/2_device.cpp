#include "2_device/0_swap_chain.cpp"
#include "2_device/1_depth_stencil.cpp"
#include "2_device/2_render_target.cpp"

// todo move to file
void app_graphics_back_buffer_init() {
	ID3D11Texture2D *t;
	app.graphics.swap_chain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (handle *)&t );

	// D3D11_RENDER_TARGET_VIEW_DESC rtvd = {};
	// rtvd.Format                        = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	// rtvd.ViewDimension                 = D3D11_RTV_DIMENSION_TEXTURE2D;

	app.graphics.device->CreateRenderTargetView( t, /*&rtvd*/ 0, &app.graphics.rtv );

	t->Release();
}

void app_graphics_depth_buffer_init() {
	app_graphics_depth_stencil_buffer( app.system.device_size, &app.graphics.dsb );
	app_graphics_depth_stencil_view  ( app.graphics.dsb,       &app.graphics.dsv, &app.graphics.dsvro );

	app.graphics.dss = (ID3D11DepthStencilState *)depth_stencil_states.read_write;
}

void app_graphics_clear() {
	// /*
	float color[4] = { 0, 0, 0, 1 };
	/*/
	float color[4] = { 1, 0, 0, 1 };
	//*/

	app.graphics.device_context->ClearRenderTargetView( app.graphics.rtv, color );
	app.graphics.device_context->ClearDepthStencilView( app.graphics.dsv, D3D11_CLEAR_DEPTH, 0, 0 );
}

void zed_clear() {
	float color[4] = { 1, 1, 1, 1 };
	app.graphics.device_context->ClearRenderTargetView( app.graphics.rtv, color );
	// app.graphics.device_context->ClearDepthStencilView( app.graphics.dsv, D3D11_CLEAR_DEPTH, 0, 0 );
}
