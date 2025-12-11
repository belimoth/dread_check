#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

void zed_buffer_new_uniform( zed_buffer &buffer, uint size ) {
	D3D11_BUFFER_DESC cbd = {};
	cbd.ByteWidth         = size;
	cbd.Usage             = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags         = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags    = D3D11_CPU_ACCESS_WRITE;

	app.graphics.device->CreateBuffer( &cbd, 0, &( buffer.native ) );
}

void zed_buffer_new_vertex( zed_buffer &buffer, zed_data_in ) {
	D3D11_BUFFER_DESC vbd = {};
	vbd.ByteWidth         = data_size;
	vbd.Usage             = D3D11_USAGE_DEFAULT;
	vbd.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags    = 0;

	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem                = data;
	vsd.SysMemPitch            = 0;
	vsd.SysMemSlicePitch       = 0;

	app.graphics.device->CreateBuffer( &vbd, data ? &vsd : 0, &( buffer.native ) );
	buffer.count  = data_size / data_item_size;
	buffer.stride = data_item_size;
}

void zed_buffer_new_dynamic( zed_buffer &buffer, zed_data_in ) {
	D3D11_BUFFER_DESC vbd = {};
	vbd.ByteWidth         = data_size;
	vbd.Usage             = D3D11_USAGE_DYNAMIC;
	vbd.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags    = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem                = data;
	vsd.SysMemPitch            = 0;
	vsd.SysMemSlicePitch       = 0;

	app.graphics.device->CreateBuffer( &vbd, data ? &vsd : 0, &( buffer.native ) );
	buffer.count  = data_size / data_item_size;
	buffer.stride = data_item_size;
}

void zed_buffer_new_index( zed_buffer &buffer, zed_data_in ) {
	D3D11_BUFFER_DESC vbd = {};
	vbd.ByteWidth         = data_size;
	vbd.Usage             = D3D11_USAGE_DEFAULT;
	vbd.BindFlags         = D3D11_BIND_INDEX_BUFFER;
	vbd.CPUAccessFlags    = 0;

	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem                = data;
	vsd.SysMemPitch            = 0;
	vsd.SysMemSlicePitch       = 0;

	app.graphics.device->CreateBuffer( &vbd, data ? &vsd : 0, &( buffer.native ) );
	buffer.count  = data_size / data_item_size;
	buffer.stride = data_item_size;
}

void zed_buffer_new_instance( zed_buffer &buffer, zed_data_in ) {
	D3D11_BUFFER_DESC vbd = {};
	vbd.ByteWidth         = data_size;
	vbd.Usage             = D3D11_USAGE_DYNAMIC;
	vbd.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags    = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem                = data;
	vsd.SysMemPitch            = 0;
	vsd.SysMemSlicePitch       = 0;

	app.graphics.device->CreateBuffer( &vbd, data ? &vsd : 0, &( buffer.native ) );
	buffer.count  = data_size / data_item_size;
	buffer.stride = data_item_size;
}

void zed_buffer_update( zed_buffer &buffer, zed_data_in ) {
	// todo fail if buffer isn't dynamic

	D3D11_MAPPED_SUBRESOURCE ms;
	app.graphics.device_context->Map( buffer.native, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms );
	memcpy( ms.pData, data, data_size );
	app.graphics.device_context->Unmap( buffer.native, 0 );
}

void zed_buffer_use_uniform( zed_buffer buffer, uint slot ) {
	app.graphics.device_context->VSSetConstantBuffers( slot, 1, &( buffer.native ) );
	app.graphics.device_context->GSSetConstantBuffers( slot, 1, &( buffer.native ) );
	app.graphics.device_context->PSSetConstantBuffers( slot, 1, &( buffer.native ) );
}
