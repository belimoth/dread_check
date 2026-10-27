#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

void app_graphics_debug_name( IDXGIObject       *object, string name ) { object->SetPrivateData( WKPDID_D3DDebugObjectName, strlen( name ), name ); }
void app_graphics_debug_name( ID3D11Device      *object, string name ) { object->SetPrivateData( WKPDID_D3DDebugObjectName, strlen( name ), name ); }
void app_graphics_debug_name( ID3D11DeviceChild *object, string name ) { object->SetPrivateData( WKPDID_D3DDebugObjectName, strlen( name ), name ); }

void app_graphics_debug_init() {
	if ( not app.options.debug ) return;

	app.graphics.device->QueryInterface( __uuidof( ID3D11Debug     ), (handle *)&app.graphics.debug      );
	app.graphics.debug ->QueryInterface( __uuidof( ID3D11InfoQueue ), (handle *)&app.graphics.info_queue );

	app.graphics.info_queue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_CORRUPTION, true );
    app.graphics.info_queue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_ERROR,      true );

	app_graphics_debug_name( app.graphics.device,         "app.graphics.device"         );
	app_graphics_debug_name( app.graphics.device_context, "app.graphics.device_context" );
	app_graphics_debug_name( app.graphics.swap_chain,     "app.graphics.swap_chain"     );
//  app_graphics_debug_name( app.graphics.rtb,            "app.graphics.rtb"            );
	app_graphics_debug_name( app.graphics.rtv,            "app.graphics.rtv"            );
	app_graphics_debug_name( app.graphics.dsb,            "app.graphics.dsb"            );
	app_graphics_debug_name( app.graphics.dsv,            "app.graphics.dsv"            );
	app_graphics_debug_name( app.graphics.dsvro,          "app.graphics.dsvro"          );
	app_graphics_debug_name( app.graphics.dss,            "app.graphics.dss"            );
}

void app_graphics_debug_exit() {
	if ( not app.options.debug ) return;

	app.graphics.device_context->ClearState();
	app.graphics.device_context->Flush();
	app.graphics.debug->ReportLiveDeviceObjects( D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL );
}
