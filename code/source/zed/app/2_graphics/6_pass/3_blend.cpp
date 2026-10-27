#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

void app_graphics_blend_init() {
	D3D11_BLEND_DESC bd;

	blend_states.opaque = 0;

	bd = {};
	bd.RenderTarget[0].BlendEnable           = true;
	bd.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	app.graphics.device->CreateBlendState( &bd, (ID3D11BlendState **)&blend_states.alpha );

	bd = {};
	bd.RenderTarget[0].BlendEnable           = true;
	bd.RenderTarget[0].SrcBlend              = D3D11_BLEND_INV_DEST_ALPHA;
	bd.RenderTarget[0].DestBlend             = D3D11_BLEND_DEST_ALPHA;
	bd.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	app.graphics.device->CreateBlendState( &bd, (ID3D11BlendState **)&blend_states.alpha_under );
}
