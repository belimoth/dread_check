#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

void _set_viewport( size2 size ) {
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX       = 0;
	viewport.TopLeftY       = 0;
	viewport.Width          = size.x;
	viewport.Height         = size.y;
	viewport.MinDepth       = 0;
	viewport.MaxDepth       = 1;

	app.graphics.device_context->RSSetViewports( 1, &viewport );
}

void zed_set_viewport( float x, float y, float w, float h ) {
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX       = x;
	viewport.TopLeftY       = y;
	viewport.Width          = w;
	viewport.Height         = h;
	viewport.MinDepth       = 0;
	viewport.MaxDepth       = 1;

	app.graphics.device_context->RSSetViewports( 1, &viewport );
}

void zed_set_render_target( app_render_target target ) {
	_set_viewport( target.size );
	app.graphics.device_context->OMSetRenderTargets( 1, &target.rtv, target.dsv );
}
