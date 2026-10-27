#include <zed/app.h>
#include <zed/app/ui.h>
#include <zed/platform/windows.h> // todo
#define l_param_get_x( lp ) ( (int)(short)LOWORD( lp ) )
#define l_param_get_y( lp ) ( (int)(short)HIWORD( lp ) )
#include <zed/platform/d3d11.h>
void zed_texture_new_2d( ID3D11Texture2D **texture );

int ui_element_start() {
	ui.id_current = ui.id_step++;
	ui_element_step_node &self = ui.data.step_nodes[ ui.id_current ];
	if ( self.is_started ) zed_die();
	self.is_started = true;
	self.id        = ui.id_current;
	self.id_parent = ui.id_parent;
	self.id_child  = 0;
	ui.id_parent = self.id;

	if ( ui.id_current == 0 ) {
		float screen_width  = app.graphics.render_target.size.x;
		float screen_height = app.graphics.render_target.size.y;
		self.position = { 0, 0 };
		self.size = { screen_width, screen_height };
	} else {
		ui_element_step_node &parent = ui.data.step_nodes[ self.id_parent ];

		self.position = parent.child_position;
		self.size     = parent.child_size;

		switch ( parent.layout ) {
			case ui_layout_void:
			zed_die();
			break;

			// note we'll subtract our own size from parent later
			case ui_layout_block:
			break;

			case ui_layout_flex:
			self.size.x              = parent.grid[ parent.id_child ];
			parent.child_position.x += parent.grid[ parent.id_child ];
			self.id_in_parent = parent.id_child++;
			break;

			case ui_layout_table:
			parent.child_position.y += parent.child_size.y;
			self.id_in_parent = parent.id_child++;
			break;
		}
	}

	self.child_position = self.position;
	self.child_size     = self.size;

	return ui.id_current;
}

void ui_element_finish( int id, string text ) {
	ui_element_step_node &self = ui.data.step_nodes[ id ];
	ui_element_step_node &parent = ui.data.step_nodes[ self.id_parent ];
	ui.id_parent  = self.id_parent;

	if ( self.layout == ui_layout_table ) {
		self.size.y = self.child_position.y - self.position.y;
	}

	if ( parent.layout == ui_layout_block ) {
		switch ( self.layout ) {
			case ui_layout_block: parent.child_position.y += self.size.y; break;
			case ui_layout_flex : break;
			case ui_layout_table: parent.child_position.y += self.size.y; break;

			case ui_layout_grid:
			parent.child_position.x += self.size.x;

			// todo

			if ( parent.child_position.x > self.size.x * 2 ) {

			}

			break;
		}
	}

	if ( app.options.headless ) \
		printf( "%2i %4.0f %4.0f %4.0f %4.0f %p %s\n", self.id, self.position.x, self.position.y, self.size.x, self.size.y, (void *)self.handle_ui_event, text );
}

void ui_element_set_size_y( int height ) {
	ui_element_step_node &self   = ui.data.step_nodes[ ui.id_current  ];
	ui_element_step_node &parent = ui.data.step_nodes[ self.id_parent ];
	if ( parent.layout != ui_layout_block ) zed_die();
	self.size.y              = height;
	// parent.child_position.y += height;
}

void ui_element_set_padding( int x, int y ) {
	ui_element_step_node &self = ui.data.step_nodes[ ui.id_current ];
	self.child_position.x += x;
	self.child_position.y += y;
}

void ui_element_set_padding( int x ) {
	ui_element_set_padding( x, x );
}

//

void ui_element_set_block() {
	ui_element_step_node &self = ui.data.step_nodes[ ui.id_current ];
	self.layout = ui_layout_block;
	self.child_size.y = 48;
}

void ui_element_set_flex( int *grid, int grid_count ) {
	ui_element_step_node &self = ui.data.step_nodes[ ui.id_current ];

	//

	self.grid       = grid;
	self.grid_count = grid_count;

	if ( ! grid ) return;

	self.layout = ui_layout_flex;

	//

	int total = 0;
	int zero_count = 0;

	for ( int i = 0; i < grid_count; i++ ) {
		int x = grid[ i ];

		if ( x == 0 ) {
			zero_count++;
		} else {
			total += x;
		}
	}

	int each = 0;
	int each_last = 0;

	// note
	int size = self.size.x;

	if ( zero_count ) {
		each = floor( ( size - total ) / zero_count );
		each_last = size - total - each * ( zero_count - 1 );

		for ( int i = 0; i < grid_count; i++ ) {
			if ( grid[ i ] == 0 ) {
				zero_count --;
				grid[ i ] = zero_count ? each : each_last;
			}
		}
	}
}

void ui_element_set_table( float child_size_y ) {
	ui_element_step_node &self = ui.data.step_nodes[ ui.id_current ];
	self.layout = ui_layout_table;
	self.child_size.y = child_size_y;
}

void ui_element_set_grid( float child_size_x, float child_size_y ) {
	ui_element_step_node &self = ui.data.step_nodes[ ui.id_current ];
	self.layout = ui_layout_grid;
	self.child_size.x = child_size_x;
	self.child_size.y = child_size_y;
}

//

#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/app/ui.h>
#include <zed/platform/d3d11.h>

zed_pass pass_ui;
ID3D11Texture2D *ui_atlas;
zed_buffer ui_buffer;

void ui_draw_init() {
	zed_pass_new( pass_ui, "data/shader/zed/ui_quad.hlsl" );

	zed_texture_new_2d( &ui_atlas );
	zed_buffer_new_instance( ui_buffer, 0, sizeof(ui_element_draw_node) * 256, sizeof(ui_element_draw_node) );
}

void app_ui_page_draw() {
	if ( ! ui.el_root ) zed_die();

	array_zero( ui.data.step_nodes );
	array_zero( ui.data.draw_nodes );

	ui.id_step = 0;
	ui.id_parent = 0;
	ui.id_draw = 1; // note skips root

	ui.el_root();
}

void app_ui_draw() {
	app_ui_page_draw();

	zed_pass_reset( pass_ui );
	zed_buffer_update( ui_buffer, zed_data( ui.data.draw_nodes ) );

	{
		// todo move into zed/mesh

		uint stride = sizeof( ui_element_draw_node );
		uint offset = stride; // note excludes root
		uint count  = 255;    // note excludes root

		app.graphics.device_context->IASetVertexBuffers( 0, 1, &ui_buffer.native, &stride, &offset );
		app.graphics.device_context->IASetIndexBuffer( 0, DXGI_FORMAT_R32_UINT, 0 );
		app.graphics.device_context->IASetPrimitiveTopology( (D3D11_PRIMITIVE_TOPOLOGY)zed_primitive_point_list );
		app.graphics.device_context->Draw( count, 0 );
	}

	zed_clear_stencil();
	app_graphics_text_begin();
	app_ui_page_draw();
	app_graphics_text_finish();
}

void app_ui_init() {
	ui_draw_init();
}

void app_ui_on_system_event( app_system_event event ) {
	ui.event = {};

	ui.event.mouse = {
		l_param_get_x( event.native.l_param ),
		l_param_get_y( event.native.l_param ),
	};

	switch ( event.native.message ) {
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_XBUTTONDOWN:
		ui.event.type = event_type_down;

		switch ( event.native.message ) {
			case WM_LBUTTONDOWN: ui.event.which = 0; break;
			case WM_RBUTTONDOWN: ui.event.which = 1; break;
			case WM_MBUTTONDOWN: ui.event.which = 2; break;
			case WM_XBUTTONDOWN: ui.event.which = HIWORD( event.native.w_param ) == XBUTTON1 ? 3 : 4; break;
		}

		ui.mouse_down  = true;
		ui.which_down  = ui.event.which;
		ui.mouse_start = ui.event.mouse;
		break;

		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_XBUTTONDBLCLK:
		ui.event.type = event_type_click2;

		switch ( event.native.message ) {
			case WM_LBUTTONDBLCLK: ui.event.which = 0; break;
			case WM_RBUTTONDBLCLK: ui.event.which = 1; break;
			case WM_MBUTTONDBLCLK: ui.event.which = 2; break;
			case WM_XBUTTONDBLCLK: ui.event.which = HIWORD( event.native.w_param ) == XBUTTON1 ? 3 : 4; break;
		}

		ui.mouse_down  = true;
		ui.which_down  = ui.event.which;
		ui.mouse_start = ui.event.mouse;
		break;

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_XBUTTONUP:
		ui.event.type = event_type_click;

		switch ( event.native.message ) {
			case WM_LBUTTONUP: ui.event.which = 0; break;
			case WM_RBUTTONUP: ui.event.which = 1; break;
			case WM_MBUTTONUP: ui.event.which = 2; break;
			case WM_XBUTTONUP: ui.event.which = HIWORD( event.native.w_param ) == XBUTTON1 ? 3 : 4; break;
		}

		ui.mouse_down = false;
		break;

		// case WM_MOUSEACTIVATE:
		// case WM_MOUSEHOVER:
		// case WM_MOUSEHWHEEL:
		// case WM_MOUSELEAVE:

		case WM_MOUSEMOVE:

		if ( ui.mouse_down ) {
			ui.event.type    = event_type_drag;
			ui.event.delta.x = ui.event.mouse.x - ui.mouse_start.x;
			ui.event.delta.y = ui.event.mouse.y - ui.mouse_start.y;
			ui.event.which   = ui.which_down;
		} else {
			ui.event.type = event_type_hover;
		}

		break;

		case WM_MOUSEWHEEL:
		ui.event.type = event_type_wheel;
		int wheel_delta = GET_WHEEL_DELTA_WPARAM( event.native.w_param );
		ui.wheel = ui.wheel + wheel_delta;

		while ( ui.wheel >= 120 ) {
			ui.wheel += -120;
			ui.event.delta.z += 1;
		}

		while ( ui.wheel <= -120 ) {
			ui.wheel += 120;
			ui.event.delta.z += -1;
		}

		break;
	}

	//

	ui.id_hover = 0;
	if ( ui.event.type == event_type_click ) ui.id_active = 0;

	for ( int i = 0; i < ui.id_step; i++ ) {
		ui_element_step_node &self = ui.data.step_nodes[ i ];

		if (
			ui.event.mouse.x >= self.position.x               and
			ui.event.mouse.y >= self.position.y               and
			ui.event.mouse.x <  self.position.x + self.size.x and
			ui.event.mouse.y <  self.position.y + self.size.y
		) {
			ui.id_hover = i;
		}
	}

	int id = ui.id_hover;
	if ( ui.event.type == event_type_down or ui.event.type == event_type_click2 ) ui.id_active = ui.id_hover;
	if ( ui.id_active ) id = ui.id_active;
	if ( id ) ui.event.id_target = id;
	while ( id and not ui.data.step_nodes[ id ].handle_ui_event ) id = ui.data.step_nodes[ id ].id_parent;
	if ( id ) ui.data.step_nodes[ id ].handle_ui_event( ui.event );

	//

	if ( ui.handle_ui_event ) ui.handle_ui_event( ui.event );
}
