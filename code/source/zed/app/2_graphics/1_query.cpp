#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

uint frames_total;
uint frame_current;
uint queries_total;

ID3D11Query *disjoint_queries[3];
ID3D11Query *timestamp_queries[ 64 * 3 ];

void app_graphics_query_init() {
	D3D11_QUERY_DESC qd;

	qd = { D3D11_QUERY_TIMESTAMP_DISJOINT, 0 };

	app.graphics.device->CreateQuery( &qd, &disjoint_queries[0] );
	app.graphics.device->CreateQuery( &qd, &disjoint_queries[1] );
	app.graphics.device->CreateQuery( &qd, &disjoint_queries[2] );

	qd = { D3D11_QUERY_TIMESTAMP, 0 };

	for ( int i = 0; i < 64 * 3; i++ ) {
		app.graphics.device->CreateQuery( &qd, &timestamp_queries[i] );
	}
}

void app_graphics_query_exit() {
	disjoint_queries[0]->Release();
	disjoint_queries[1]->Release();
	disjoint_queries[2]->Release();

	for ( int i = 0; i < 64 * 3; i++ ) {
		timestamp_queries[i]->Release();
	}
}

void app_graphics_query_mark( uint id ) {
	app.graphics.device_context->End( timestamp_queries[ frame_current * 64 + id ] );
	queries_total = max( queries_total, id + 1 );
}

void app_graphics_query_begin_frame() {
	queries_total = 0;
	app.graphics.device_context->Begin( disjoint_queries[ frame_current ] );
	app_graphics_query_mark(0);
}

void query_get_data_disjoint( ID3D11Query *query, D3D11_QUERY_DATA_TIMESTAMP_DISJOINT *data ) {
	HRESULT result = app.graphics.device_context->GetData(
		query,
		data,
		sizeof( *data ),
		0
	);

	while ( result == S_FALSE ) {
		Sleep(1);

		result = app.graphics.device_context->GetData(
			query,
			data,
			sizeof( *data ),
			0
		);
	}
}

void query_get_data(ID3D11Query *query, uint64_t *data ) {
	HRESULT result = app.graphics.device_context->GetData(
		query,
		data,
		sizeof( *data ),
		0
	);

	while ( result == S_FALSE ) {
		Sleep(1);

		result = app.graphics.device_context->GetData(
			query,
			data,
			sizeof( *data ),
			0
		);
	}
}

void app_graphics_query_end_frame() {
	app_graphics_query_mark( queries_total );
	app.graphics.device_context->End( disjoint_queries[ frame_current ] );

	frames_total += 1;
	frame_current = ( frame_current + 1 ) % 3;

	if ( frames_total == frame_current ) return;

	// note frame_current has advanced; this is the oldest frame
	D3D11_QUERY_DATA_TIMESTAMP_DISJOINT data;
	query_get_data_disjoint( disjoint_queries[ frame_current ], &data );

	if ( data.Disjoint ) return;

	uint64_t *times   = new uint64_t[ queries_total ];
	float    *results = new float[ queries_total ];

	for ( int i = 0; i < queries_total; i += 1 ) {
		query_get_data( timestamp_queries[ frame_current * 64 + i], &times[i] );
	}

	for ( int i = 0; i < queries_total - 1; i += 1 ) {
		results[i] = 1000.0f * float( times[ i + 1 ] - times[ i ] ) / float( data.Frequency );
		// zed_debug_say( "%f\n", results[i] );
	}

	// zed_debug_say( "\n\n" );
}
