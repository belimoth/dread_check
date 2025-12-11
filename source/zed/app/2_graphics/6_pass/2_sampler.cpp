#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

void app_graphics_sampler_init() {
	D3D11_SAMPLER_DESC sd = {};
	sd.Filter             = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sd.AddressU           = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV           = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW           = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.ComparisonFunc     = D3D11_COMPARISON_NEVER;
	sd.MinLOD             = 0;
	sd.MaxLOD             = D3D11_FLOAT32_MAX;

	app.graphics.device->CreateSamplerState( &sd, (ID3D11SamplerState **)&sampler_states.point );

	sd                = {};
	sd.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU       = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV       = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW       = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.MinLOD         = 0;
	sd.MaxLOD         = D3D11_FLOAT32_MAX;

	app.graphics.device->CreateSamplerState( &sd, (ID3D11SamplerState **)&sampler_states.linear );

	sd                = {};
	sd.Filter         = D3D11_FILTER_ANISOTROPIC;
	sd.AddressU       = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV       = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW       = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.MinLOD         = 0;
	sd.MaxLOD         = D3D11_FLOAT32_MAX;

	app.graphics.device->CreateSamplerState( &sd, (ID3D11SamplerState **)&sampler_states.anisotropic );

	app.graphics.device_context->VSSetSamplers( 0, 3, (ID3D11SamplerState *const *)&sampler_states );
	app.graphics.device_context->GSSetSamplers( 0, 3, (ID3D11SamplerState *const *)&sampler_states );
	app.graphics.device_context->PSSetSamplers( 0, 3, (ID3D11SamplerState *const *)&sampler_states );
}
