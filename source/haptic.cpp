#include "main/game.h"

#include <zed.h>

#include <ds5w/ds5w.h>
#pragma comment( lib, "ds5w.lib" )

DS5W::DeviceContext ds5_context;

int haptic_init() {
	return 0;
	if ( not game.config_enable_haptics ) return 0;

	DS5W::DeviceEnumInfo infos[16];
	uint count = 0;
	DS5W_ReturnValue result = DS5W::enumDevices( infos, 16, &count );

	switch ( result ) {
		case DS5W_OK:
			break;

		// The buffer was not big enough. Ignore for now
		case DS5W_E_INSUFFICIENT_BUFFER:
			break;

		// Any other error will terminate the application
		default:
			return -1;
	}

	result = DS5W::initDeviceContext( &infos[0], &ds5_context );

	if ( DS5W_FAILED( result ) ) return -1;

	return 0;
}

void haptic_step() {
	if ( not game.config_enable_haptics ) return;

	DS5W::DS5InputState input;

	DS5W_ReturnValue result = DS5W::getDeviceInputState( &ds5_context, &input );

	if ( DS5W_SUCCESS( result ) ) {
		game.data.player[0].pad.gyro = float3( input.gyroscope.x, input.gyroscope.y, input.gyroscope.z );
	}


	DS5W::DS5OutputState output = {};

	// output.leftRumble  = input.leftTrigger;
	// output.rightRumble = input.rightTrigger;


	// /*

	output.leftTriggerEffect.effectType               = DS5W::TriggerEffectType::ContinuousResitance;
	output.leftTriggerEffect.Continuous.startPosition = 64;

	output.rightTriggerEffect.effectType            = DS5W::TriggerEffectType::SectionResitance;
	output.rightTriggerEffect.Section.startPosition = 128;
	output.rightTriggerEffect.Section.endPosition   = 128;

	/*/

	output.leftTriggerEffect.effectType            = DS5W::TriggerEffectType::SectionResitance;
	output.leftTriggerEffect.Section.startPosition =
	output.leftTriggerEffect.Section.endPosition   = 128;

	output.rightTriggerEffect.effectType            = DS5W::TriggerEffectType::SectionResitance;
	output.rightTriggerEffect.Section.startPosition =
	output.rightTriggerEffect.Section.endPosition   = 64;

	//*/

	DS5W::setDeviceOutputState( &ds5_context, &output );
}
