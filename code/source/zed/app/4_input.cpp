#include <zed/app.h>
#include <zed/app/input.h>
#include <zed/platform/vk.h>

#include "4_input/midi.cpp"
#include "4_input/raw_input.cpp"
#include "4_input/xinput.cpp"

void app_input_init() {
	raw_input_init();
	load_xinput();
	midi_init();
}

void app_input_exit() {
	raw_input_exit();
}

void app_input_step() {
	for ( int i = 0; i < 0x100; i++ ) {
		app_input.keys[i].fall = false;
		app_input.keys[i].rise = false;
	}
}

void app_input_on_system_event_for_keyboard( app_system_event event ) {
	uint i;

	switch ( event.native.message ) {
		case WM_KEYDOWN:       { i = event.native.w_param;                                                           break; }
		case WM_KEYUP:         { i = event.native.w_param;                                                           break; }
		case WM_LBUTTONDBLCLK: { i = key_mouse_l;                                                                    break; }
		case WM_LBUTTONDOWN:   { i = key_mouse_l;                                                                    break; }
		case WM_LBUTTONUP:     { i = key_mouse_l;                                                                    break; }
		case WM_MBUTTONDBLCLK: { i = key_mouse_m;                                                                    break; }
		case WM_MBUTTONDOWN:   { i = key_mouse_m;                                                                    break; }
		case WM_MBUTTONUP:     { i = key_mouse_m;                                                                    break; }
		case WM_RBUTTONDBLCLK: { i = key_mouse_r;                                                                    break; }
		case WM_RBUTTONDOWN:   { i = key_mouse_r;                                                                    break; }
		case WM_RBUTTONUP:     { i = key_mouse_r;                                                                    break; }
		case WM_XBUTTONDBLCLK: { i = key_mouse_x; if ( HIWORD( event.native.w_param ) == XBUTTON2 ) i = key_mouse_y; break; }
		case WM_XBUTTONDOWN:   { i = key_mouse_x; if ( HIWORD( event.native.w_param ) == XBUTTON2 ) i = key_mouse_y; break; }
		case WM_XBUTTONUP:     { i = key_mouse_x; if ( HIWORD( event.native.w_param ) == XBUTTON2 ) i = key_mouse_y; break; }
	}

	switch ( event.native.message ) {
		case WM_KEYDOWN:
		case WM_LBUTTONDBLCLK:
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
		case WM_XBUTTONDBLCLK:
		case WM_XBUTTONDOWN:   {
			if ( app_input.keys[i].held == false ) app_input.keys[i].fall = true;
			app_input.keys[i].held = true;
			break;
		}

		case WM_KEYUP:
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_XBUTTONUP: {
			if ( app_input.keys[i].held == true ) app_input.keys[i].rise = true;
			app_input.keys[i].held = false;
			break;
		}
	}
}

void main_on_mouse_activity();

void app_input_on_system_event_for_mouse( app_system_event event ) {
	switch ( event.native.message ) {
		case WM_INPUT: {
			static uint size = sizeof( RAWINPUT );
			static RAWINPUT raw[sizeof( RAWINPUT )];

			GetRawInputData(
				(HRAWINPUT)event.native.l_param,
				RID_INPUT,
				raw,
				&size,
				sizeof( RAWINPUTHEADER )
			);

			if ( raw->header.dwType == RIM_TYPEMOUSE ) {
				game_mouse.x = raw->data.mouse.lLastX;
				game_mouse.y = raw->data.mouse.lLastY;

				if ( raw->data.mouse.usButtonFlags & RI_MOUSE_WHEEL ) {
					game_mouse.z = (float)( *(short *)&raw->data.mouse.usButtonData ) / WHEEL_DELTA;
				}

				main_on_mouse_activity();
			}

			break;
		}
	}
}
