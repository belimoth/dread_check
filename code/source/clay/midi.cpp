#include <zed/app/input.h>

#include "../clay.h"

// todo

enum midi_message {

};

/*

Voice Message           Status Byte      Data Byte1          Data Byte2
-------------           -----------   -----------------   -----------------
Note off                      8x      Key number          Note Off velocity
Note on                       9x      Key number          Note on velocity
Polyphonic Key Pressure       Ax      Key number          Amount of pressure
Control Change                Bx      Controller number   Controller value
Program Change                Cx      Program number      None
Channel Pressure              Dx      Pressure value      None
Pitch Bend                    Ex      MSB                 LSB

*/

void clay_midi( midi_event event ) {
	switch ( event.command ) {
		// note off
		case 0x00:
			break;

		// note on
		case 0x10:
			break;

		// controller
		case 0x30: {
			int delta = event.data_1;
			if ( delta > 64 ) delta = 64 - delta;
			midi.control[event.data_0] += delta;

			break;
		}

		// pitch bend
		case 0xE0:

			break;
	}
}
