#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

void app_graphics_device_and_swap_chain_0() {
	DXGI_SWAP_CHAIN_DESC scd   = {};
	scd.BufferCount            = 2;
	scd.BufferUsage            = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferDesc.Width       = 0;
	scd.BufferDesc.Height      = 0;
	scd.BufferDesc.RefreshRate = { 60, 1 };
	scd.BufferDesc.Format      = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling     = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count       = 1;
	scd.SampleDesc.Quality     = 0;
	scd.OutputWindow           = (HWND)app.system.window;
	scd.Windowed               = true;
	scd.SwapEffect             = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scd.Flags                  = 0;

	uint flags = 0;

	// note
	flags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	if ( app.options.debug ) flags |= D3D11_CREATE_DEVICE_DEBUG;

	D3D11CreateDeviceAndSwapChain(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		flags,
		0,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&app.graphics.swap_chain,
		&app.graphics.device,
		0,
		&app.graphics.device_context
	);

	// todo why does this exist
	app.graphics.swap_chain->GetDesc( &scd );

	//

	struct {
		IDXGIFactory2 *f;
		IDXGIAdapter  *a;
		IDXGIDevice   *d;
	} dxgi;

	app.graphics.device->QueryInterface( __uuidof( IDXGIDevice   ), (handle *)&dxgi.d );
	dxgi.d             ->GetParent     ( __uuidof( IDXGIAdapter  ), (handle *)&dxgi.a );
	dxgi.a             ->GetParent     ( __uuidof( IDXGIFactory2 ), (handle *)&dxgi.f );

	//

	dxgi.f->MakeWindowAssociation( (HWND)app.system.window, DXGI_MWA_NO_WINDOW_CHANGES );
}

void app_graphics_device_and_swap_chain_1() {
	uint flags = 0;

	// note
	flags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	if ( app.options.debug ) flags |= D3D11_CREATE_DEVICE_DEBUG;

	D3D11CreateDevice(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		flags,
		0,
		0,
		D3D11_SDK_VERSION,
		&app.graphics.device,
		0,
		&app.graphics.device_context
	);

	//

	struct {
		IDXGIFactory2 *f;
		IDXGIAdapter  *a;
		IDXGIDevice   *d;
	} dxgi;

	app.graphics.device->QueryInterface( __uuidof( IDXGIDevice   ), (handle *)&dxgi.d );
	dxgi.d             ->GetParent     ( __uuidof( IDXGIAdapter  ), (handle *)&dxgi.a );
	dxgi.a             ->GetParent     ( __uuidof( IDXGIFactory2 ), (handle *)&dxgi.f );

	//

	DXGI_SWAP_CHAIN_DESC1 scd = {};
	scd.Width                 = 0;
	scd.Height                = 0;
	scd.Format                = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.SampleDesc.Count      = 1;
	scd.SampleDesc.Quality    = 0;
	scd.BufferUsage           = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount           = 2;
	scd.Scaling               = DXGI_SCALING_NONE; // todo
	// scd.Scaling               = DXGI_SCALING_STRETCH;
	scd.SwapEffect            = DXGI_SWAP_EFFECT_FLIP_DISCARD; // todo
	scd.AlphaMode             = DXGI_ALPHA_MODE_UNSPECIFIED;
	scd.Flags                 = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;

	// todo
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC scfd = {};
	scfd.RefreshRate                     = { 60, 1 };
	scfd.Scaling                         = DXGI_MODE_SCALING_UNSPECIFIED;
	scfd.Windowed                        = true;

	IDXGISwapChain1 *swap_chain_1;

	dxgi.f->CreateSwapChainForHwnd(
		app.graphics.device,
		(HWND)app.system.window,
		&scd,
		&scfd,
		0, // todo
		&swap_chain_1
	);

	swap_chain_1->QueryInterface( __uuidof( IDXGISwapChain ), (handle *)&app.graphics.swap_chain );

	IDXGIDevice1 *device_1;
	app.graphics.device->QueryInterface( __uuidof( IDXGIDevice1 ), (handle *)&device_1 );

	IDXGISwapChain2 *swap_chain_2;
	app.graphics.swap_chain->QueryInterface( __uuidof( IDXGISwapChain2 ), (handle *)&swap_chain_2 );

	device_1->SetMaximumFrameLatency( 1 );
	app.graphics.waitable = swap_chain_2->GetFrameLatencyWaitableObject();

	//

	dxgi.f->MakeWindowAssociation( (HWND)app.system.window, DXGI_MWA_NO_WINDOW_CHANGES );
}
