#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

void app_graphics_rasterizer_init() {
	D3D11_RASTERIZER_DESC rd;

	// cull_default

	rd                       = {};
	rd.FillMode              = D3D11_FILL_SOLID;
	rd.CullMode              = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = false;
	rd.DepthBias             = 0.0f;
	rd.DepthBiasClamp        = 0.0f;
	rd.SlopeScaledDepthBias  = 0.0f;
	rd.DepthClipEnable       = true;
	rd.ScissorEnable         = false;
	rd.MultisampleEnable     = false;
	rd.AntialiasedLineEnable = false;

	app.graphics.device->CreateRasterizerState( &rd, (ID3D11RasterizerState **)&rasterizer_states.cull_default );

	// cull_front

	rd                       = {};
	rd.FillMode              = D3D11_FILL_SOLID;
	rd.CullMode              = D3D11_CULL_FRONT;
	rd.FrontCounterClockwise = false;
	rd.DepthBias             = 0.0f;
	rd.DepthBiasClamp        = 0.0f;
	rd.SlopeScaledDepthBias  = 0.0f;
	rd.DepthClipEnable       = true;
	rd.ScissorEnable         = false;
	rd.MultisampleEnable     = false;
	rd.AntialiasedLineEnable = false;

	app.graphics.device->CreateRasterizerState( &rd, (ID3D11RasterizerState **)&rasterizer_states.cull_front );

	// cull_front_biased

	rd                       = {};
	rd.FillMode              = D3D11_FILL_SOLID;
	rd.CullMode              = D3D11_CULL_FRONT;
	rd.FrontCounterClockwise = false;
	rd.DepthBias             = 1.0f;
	rd.DepthBiasClamp        = 0.0f;
	rd.SlopeScaledDepthBias  = 1.0f;
	rd.DepthClipEnable       = true;
	rd.ScissorEnable         = false;
	rd.MultisampleEnable     = false;
	rd.AntialiasedLineEnable = false;

	app.graphics.device->CreateRasterizerState( &rd, (ID3D11RasterizerState **)&rasterizer_states.cull_front_biased );


	// cull_none

	rd                       = {};
	rd.FillMode              = D3D11_FILL_SOLID;
	rd.CullMode              = D3D11_CULL_NONE;
	rd.FrontCounterClockwise = false;
	rd.DepthBias             = 0.0f;
	rd.DepthBiasClamp        = 0.0f;
	rd.SlopeScaledDepthBias  = 0.0f;
	rd.DepthClipEnable       = true;
	rd.ScissorEnable         = false;
	rd.MultisampleEnable     = false;
	rd.AntialiasedLineEnable = false;

	app.graphics.device->CreateRasterizerState( &rd, (ID3D11RasterizerState **)&rasterizer_states.cull_none);

	// wireframe

	rd                       = {};
	rd.FillMode              = D3D11_FILL_WIREFRAME;
	rd.CullMode              = D3D11_CULL_NONE;
	rd.FrontCounterClockwise = false;
	rd.DepthBias             = 0.0f;
	rd.DepthBiasClamp        = 0.0f;
	rd.SlopeScaledDepthBias  = 0.0f;
	rd.DepthClipEnable       = true;
	rd.ScissorEnable         = false;
	rd.MultisampleEnable     = false;
	rd.AntialiasedLineEnable = false;

	app.graphics.device->CreateRasterizerState( &rd, (ID3D11RasterizerState **)&rasterizer_states.wireframe );

	//

	// todo
	app.graphics.device_context->RSSetState( (ID3D11RasterizerState *)rasterizer_states.cull_default );
}
