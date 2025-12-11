#include <zed/app.h>
#include <zed/app/system.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

// todo
void zed_texture_new_2d( ID3D11Texture2D **texture ) {
	D3D11_TEXTURE2D_DESC td = {};
	td.Width                = 1024;
	td.Height               = 1024;
	td.MipLevels            = 1;
	td.ArraySize            = 1;
	td.Format               = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count     = 1;
	td.Usage                = D3D11_USAGE_DYNAMIC;
	td.BindFlags            = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags       = D3D11_CPU_ACCESS_WRITE;
	td.MiscFlags            = 0;

	app.graphics.device->CreateTexture2D( &td, 0, texture );
}

//

void zed_texture_new_2d( zed_texture &texture, string file ) {
	using namespace DirectX;

	// todo
	wchar_t file_wide[256] = {};
	mbstowcs( file_wide, file, 256 );

	CreateDDSTextureFromFile( app.graphics.device, file_wide, 0, &texture.view );

	//

	if ( texture.view == 0 ) return;

	ID3D11Resource *r;
	texture.view->GetResource( &r );
	ID3D11Texture2D *t = 0;
	r->QueryInterface<ID3D11Texture2D>( &t );
	D3D11_TEXTURE2D_DESC td = {};
	t->GetDesc( &td );

	texture.size.x = td.Width;
	texture.size.y = td.Height;
}

void zed_texture_load_cube( zed_texture &texture, string file ) {
	using namespace DirectX;

	// todo
	wchar_t file_wide[256] = {};
	mbstowcs( file_wide, file, 256 );

	CreateDDSTextureFromFileEx(
		app.graphics.device,
		app.graphics.device_context,
		file_wide,
		0,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0,
		D3D11_RESOURCE_MISC_TEXTURECUBE,
		0,
		&texture.resource,
		&texture.view
	);
}

//

void zed_texture_new_2d( zed_texture &texture, int id ) {
	using namespace DirectX;

	handle data = app_system_resource_data( id );
	int    size = app_system_resource_size( id );

	CreateDDSTextureFromMemory(
		app.graphics.device,
		(byte *)data, size,
		0,
		&texture.view
	);
}

void zed_texture_load_cube( zed_texture &texture, int id ) {
	using namespace DirectX;

	handle data = app_system_resource_data( id );
	int    size = app_system_resource_size( id );

	CreateDDSTextureFromMemoryEx(
		app.graphics.device,
		app.graphics.device_context,
		(byte *)data, size,
		0,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0,
		D3D11_RESOURCE_MISC_TEXTURECUBE,
		0,
		&texture.resource,
		&texture.view
	);
}
