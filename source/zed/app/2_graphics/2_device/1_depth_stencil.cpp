#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

void app_graphics_depth_stencil_buffer( size2 size, ID3D11Texture2D **dsb ) {
	D3D11_TEXTURE2D_DESC dbd = {};
	dbd.Width                = size.x;
	dbd.Height               = size.y;
	dbd.MipLevels            = 1;
	dbd.ArraySize            = 1;
	// dbd.Format               = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dbd.Format               = DXGI_FORMAT_R24G8_TYPELESS;
	dbd.SampleDesc.Count     = 1;
	dbd.SampleDesc.Quality   = 0;
	dbd.Usage                = D3D11_USAGE_DEFAULT;
	// dbd.BindFlags            = D3D11_BIND_DEPTH_STENCIL;
	dbd.BindFlags            = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	dbd.CPUAccessFlags       = 0;
	dbd.MiscFlags            = 0;

	app.graphics.device->CreateTexture2D( &dbd, 0, dsb );
}

void app_graphics_depth_stencil_view( ID3D11Texture2D *dsb, ID3D11DepthStencilView **dsv, ID3D11DepthStencilView **dsvro ) {
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
	dsvd.Format                        = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvd.ViewDimension                 = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice            = 0;

	app.graphics.device->CreateDepthStencilView( dsb, &dsvd, dsv );

	dsvd.Flags = D3D11_DSV_READ_ONLY_DEPTH | D3D11_DSV_READ_ONLY_STENCIL;

	app.graphics.device->CreateDepthStencilView( dsb, &dsvd, dsvro );
}

void app_graphics_depth_stencil_buffer_and_view( size2 size, ID3D11Texture2D **dsb, ID3D11DepthStencilView **dsv, ID3D11DepthStencilView **dsvro ) {
	app_graphics_depth_stencil_buffer( size, dsb );
	app_graphics_depth_stencil_view( *dsb, dsv, dsvro);
}

void app_graphics_depth_stencil_init() {
	D3D11_DEPTH_STENCIL_DESC dsd;
	D3D11_DEPTH_STENCILOP_DESC dsod;

	//

	// D3D11_DEPTH_WRITE_MASK_ZERO
	// D3D11_DEPTH_WRITE_MASK_ALL

	// D3D11_COMPARISON_NEVER
	// D3D11_COMPARISON_LESS
	// D3D11_COMPARISON_EQUAL
	// D3D11_COMPARISON_LESS_EQUAL
	// D3D11_COMPARISON_GREATER
	// D3D11_COMPARISON_NOT_EQUAL
	// D3D11_COMPARISON_GREATER_EQUAL
	// D3D11_COMPARISON_ALWAYS

	//

	//	D3D11_STENCIL_OP      StencilFailOp;
	//  D3D11_STENCIL_OP      StencilDepthFailOp;
	//  D3D11_STENCIL_OP      StencilPassOp;
	//  D3D11_COMPARISON_FUNC StencilFunc;

	//

	// D3D11_STENCIL_OP_KEEP
	// D3D11_STENCIL_OP_ZERO
	// D3D11_STENCIL_OP_REPLACE
	// D3D11_STENCIL_OP_INCR_SAT
	// D3D11_STENCIL_OP_DECR_SAT
	// D3D11_STENCIL_OP_INVERT
	// D3D11_STENCIL_OP_INCR
	// D3D11_STENCIL_OP_DECR

	//

	dsod                    = {};
	dsod.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
	dsod.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsod.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
	dsod.StencilFunc        = D3D11_COMPARISON_ALWAYS;

	dsd                  = {};
	dsd.DepthEnable      = 0;
	dsd.DepthWriteMask   = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsd.DepthFunc        = D3D11_COMPARISON_NEVER;
	dsd.StencilEnable    = 0;
	dsd.StencilReadMask  = 0;
	dsd.StencilWriteMask = 0;
	dsd.FrontFace        = dsod;
	dsd.BackFace         = dsod;

	app.graphics.device->CreateDepthStencilState( &dsd, (ID3D11DepthStencilState **)&depth_stencil_states.none );

	//

	dsod                    = {};
	dsod.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
	dsod.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsod.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
	dsod.StencilFunc        = D3D11_COMPARISON_ALWAYS;

	dsd                  = {};
	dsd.DepthEnable      = 1;
	dsd.DepthWriteMask   = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsd.DepthFunc        = D3D11_COMPARISON_GREATER_EQUAL;
	dsd.StencilEnable    = 0;
	dsd.StencilReadMask  = 0;
	dsd.StencilWriteMask = 0;
	dsd.FrontFace        = dsod;
	dsd.BackFace         = dsod;

	app.graphics.device->CreateDepthStencilState( &dsd, (ID3D11DepthStencilState **)&depth_stencil_states.read_only  );

	//

	dsod                    = {};
	dsod.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
	dsod.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsod.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
	dsod.StencilFunc        = D3D11_COMPARISON_ALWAYS;

	dsd                  = {};
	dsd.DepthEnable      = 1;
	dsd.DepthWriteMask   = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc        = D3D11_COMPARISON_GREATER_EQUAL;
	dsd.StencilEnable    = 0;
	dsd.StencilReadMask  = 0;
	dsd.StencilWriteMask = 0;
	dsd.FrontFace        = dsod;
	dsd.BackFace         = dsod;

	app.graphics.device->CreateDepthStencilState( &dsd, (ID3D11DepthStencilState **)&depth_stencil_states.read_write );

	//

	dsod                    = {};
	dsod.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
	dsod.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsod.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
	dsod.StencilFunc        = D3D11_COMPARISON_ALWAYS;

	dsd                  = {};
	dsd.DepthEnable      = 1;
	dsd.DepthWriteMask   = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc        = D3D11_COMPARISON_GREATER_EQUAL;
	dsd.StencilEnable    = 1;
	dsd.StencilReadMask  = 0;
	dsd.StencilWriteMask = 0xff;

	dsd.FrontFace        = {};

	dsd.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_INCR_SAT;
	dsd.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;

	dsd.BackFace                    = {};
	dsd.BackFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;

	app.graphics.device->CreateDepthStencilState( &dsd, (ID3D11DepthStencilState **)&depth_stencil_states.read_write_count );

	//

	// todo
	app.graphics.device_context->OMSetDepthStencilState( (ID3D11DepthStencilState *)depth_stencil_states.read_write, 0 );
}
