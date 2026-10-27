#include "../game.hlsli"

struct vs_input_ui {
	float2 position : POSITION;
	float2 size     : SIZE;
	float2 uv       : UV;
	uint   color    : COLOR;
};

struct gs_input_ui {
	float2 position : POSITION;
	float2 size     : SIZE;
	float2 uv       : UV;
	uint   color    : COLOR;
};

struct ps_input_ui {
	float4 position : SV_POSITION;
	float2 uv       : TEXCOORD;
	float3 color    : COLOR;
};

gs_input_ui vs( vs_input_ui input ) {
	return input;
}

float2 screen_to_ndc( float2 p ){
	return float2(
		-1.0 + ( p.x / ( screen_width  * 0.5 ) ),
		+1.0 - ( p.y / ( screen_height * 0.5 ) )
	);
}

[maxvertexcount(4)]
void gs( point gs_input_ui input[1], inout TriangleStream<ps_input_ui> stream, uint id : SV_PrimitiveID ) {
	ps_input_ui output;

//	float2 p0 = input[0].position;
//	float2 p1 = ( input[0].position + input[0].size );

//	float2 p0 = input[0].position / float2( screen_width, screen_height );
//	float2 p1 = ( input[0].position + input[0].size ) / float2( screen_width, screen_height );

//	output.position = float4( p0.x, p0.y, 0.0, 0.0 ); output.uv = float2( 0, 0 ); stream.Append( output );
//	output.position = float4( p1.x, p0.y, 0.0, 0.0 ); output.uv = float2( 0, 1 ); stream.Append( output );
//	output.position = float4( p0.x, p1.y, 0.0, 0.0 ); output.uv = float2( 1, 0 ); stream.Append( output );
//	output.position = float4( p1.x, p1.y, 0.0, 0.0 ); output.uv = float2( 1, 1 ); stream.Append( output );

	//

	float x0 = input[0].position.x;
	float y0 = input[0].position.y;
	float x1 = x0 + input[0].size.x;
	float y1 = y0 + input[0].size.y;

	x0 = screen_to_ndc( float2( x0, y0 ) ).x;
	y0 = screen_to_ndc( float2( x0, y0 ) ).y;
	x1 = screen_to_ndc( float2( x1, y1 ) ).x;
	y1 = screen_to_ndc( float2( x1, y1 ) ).y;

	float u0 = input[0].uv.x;
	float v0 = input[0].uv.y;
	float u1 = u0 + 1; // todo
	float v1 = v0 + 1; // todo

	float3 color = float3(
		( ( input[0].color >> 16 ) & 0xff ) / 255.0,
		( ( input[0].color >>  8 ) & 0xff ) / 255.0,
		( ( input[0].color       ) & 0xff ) / 255.0
	);

	// todo
	// unorm float z_unorm = ( 0x100 - id ) / 0x100;
	// output.position = float4( 0, 0, z_unorm, 1.0 );

	// output.position = float4( 0, 0, input[0].position.z, 1.0 );

	output.position = float4( 0, 0, 1, 1 );

	output.position.x = x1;
	output.position.y = y0;
	output.uv      .x = u1;
	output.uv      .y = v0;
	output.color      = color;
	stream.Append( output );

//	output.position.x = x1;
	output.position.y = y1;
//	output.uv      .x = u1;
	output.uv      .y = v1;
	output.color      = color;
	stream.Append( output );

	output.position.x = x0;
	output.position.y = y0;
	output.uv      .x = u0;
	output.uv      .y = v0;
	output.color      = color;
	stream.Append( output );

//	output.position.x = x0;
	output.position.y = y1;
//	output.uv      .z = u0
	output.uv      .y = v1;
	stream.Append( output );

//	stream.RestartStrip();
}

float4 ps( ps_input_ui input ) : SV_TARGET {
	return float4( input.color.rgb, alpha );
}
