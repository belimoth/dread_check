#include "../game.hlsli"
#include "../wolf.hlsli"

ps_input_pnt vs( vs_input_wolf input, uint id : SV_InstanceID ) {
	if ( input.t > 1 ) { input.t = 2 - input.t; }
	input.position.z += 0.5;
	input.position.x += input.t;

	// floor
	if ( input.i_tile > 105 ) {
		input.position = float3( 0, 0, 0 );
	}

	// door
	else if ( input.i_tile > 53 ) {

		switch ( input.i_tile ) {
			case  90:
			case  92:
			case  94:
			case 100:

			input.position = mul( float4( input.position.xyz, 1 ), translate( -0.5, 0, -0.5 ) ).xyz;
			input.position = mul( float4( input.position.xyz, 1 ), rotate   ( 0, -3.1415927/2, 0 ) ).xyz;
			input.position = mul( float4( input.position.xyz, 1 ), translate(  0.5, 0,  0.5 ) ).xyz;

			input.normal   = mul( input.normal.xyz, (float3x3)rotate( 0, -3.1415927/2, 0 ) ).xyz;

			break;

			//

			case  91:
			case  93:
			case  95:
			case 101:

			// todo shouldn't be necessary

			input.position = mul( float4( input.position.xyz, 1 ), translate( -0.5, 0, -0.5 ) ).xyz;
			input.position = mul( float4( input.position.xyz, 1 ), rotate   ( 0, -3.1415927, 0 ) ).xyz;
			input.position = mul( float4( input.position.xyz, 1 ), translate(  0.5, 0,  0.5 ) ).xyz;

			input.normal   = mul( input.normal.xyz, (float3x3)rotate( 0, -3.1415927, 0 ) ).xyz;

			break;
		}
	}

	// wall
	else {
		// note
		input.position = float3( 0, 0, 0 );
	}

	//

	input.position.x += id % 64;
	input.position.z += ( id - ( id % 64 ) ) / 64;

	//

	// floor
	if ( input.i_tile > 105 ) {
		input.position = float3( 0, 0, 0 );
	}

	// door
	else if ( input.i_tile > 53 ) {
		switch ( (int)input.i_tile ) {
			case  90:
			case  91:
				input.i_tile = 50;
				break;

			case 100:
			case 101:
				input.i_tile = 52;
				break;

			case  92:
			case  93:
			case  94:
			case  95:
				input.i_tile = 53;
				break;

			default:
				input.i_tile = 50;
				break;
		}
	}

	// wall
	else {
		// note
		input.position = float3( 0, 0, 0 );
	}

	//

	// fixes samples from outside uv range without padding
	float e = 0.000018;

	// todo
	// input.uv.x = clamp( input.uv.x, e, 1 - 2 * e );
	// input.uv.y = clamp( input.uv.y, e, 1 - 2 * e );

	input.i_tile = ( input.i_tile - 1 ) * 2; // day and night
	float u = input.i_tile % 16;
	float v = ( input.i_tile - u ) / 16;
	input.uv.x = ( input.uv.x + u ) / 16;
	input.uv.y = ( input.uv.y + v ) / 16;

	//

	ps_input_pnt output = projection_standard_pnt_pnt( (vs_input_pnt)input );
	return output;
}

float4 ps( ps_input_pnt input ) : SV_TARGET {
	return texture_0.Sample( sampler_point, input.uv );
}
