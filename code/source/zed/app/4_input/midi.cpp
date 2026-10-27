#include <zed.h>
#include <zed/platform/windows.h>

#include <mmsystem.h>
#pragma comment( lib, "winmm.lib" )

#include <zed/app/input.h>

enum { MIDI_PORT = 0 };

HMIDIIN  midi_device_in;
HMIDIOUT midi_device_out;

void print_midi_devices() {
	uint       device_count;
	MIDIINCAPS caps;

	device_count = midiInGetNumDevs();

	if ( device_count == 0 ) {
		// todo
		return;
	}

	for ( uint i = 0; i < device_count; i++ ) {
		midiInGetDevCaps( i, &caps, sizeof( MIDIINCAPS ) );
		// zed_debug_say( "\t%d : name = %ws\n", i, caps.szPname );
	}
}

void __stdcall on_midi_in( HMIDIIN, uint32_t message, uint32_t, uint32_t param_0, uint32_t param_1 ) {
	switch ( message ) {
		case MIM_OPEN:
		case MIM_CLOSE:
			break;

		case MIM_DATA: {
			uint8_t status = LOBYTE( LOWORD( param_0 ) );
			uint8_t data_0 = (int8_t)HIBYTE( LOWORD( param_0 ) );
			uint8_t data_1 = (int8_t)LOBYTE( HIWORD( param_0 ) );

			//            1 = status & 0b10000000;
			uint8_t command = status & 0b01110000;
			uint8_t channel = status & 0b00001111;

			midi_event event = {};
			event.channel        = channel;
			event.command        = command;
			event.data_0         = data_0;
			event.data_1         = data_1;

			main_midi( event );

			break;
		}

		case MIM_LONGDATA:
		case MIM_ERROR:
		case MIM_LONGERROR:
		case MIM_MOREDATA:
			break;
	}

	return;
}

void midi_init() {
	print_midi_devices();
	midiInOpen( &midi_device_in, MIDI_PORT, (DWORD_PTR)on_midi_in, 0, CALLBACK_FUNCTION );
	midiInStart( midi_device_in );
	midiOutOpen( &midi_device_out, 0, 0, 0, 0 );
}

// todo test
void midi_send( uint8_t channel, uint8_t command, uint8_t data_0, uint8_t data_1 ) {
	union {
		uint32_t data;
		uint8_t  bytes[4];
	} message;

	uint8_t status = command & channel;

	message.bytes[0] = status;
	message.bytes[1] = data_0;
	message.bytes[2] = data_1;
	message.bytes[3] = 0;

	midiOutShortMsg( midi_device_out, message.data );
}
