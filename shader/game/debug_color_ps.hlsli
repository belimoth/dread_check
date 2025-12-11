struct ps_input {
	float4 position : SV_POSITION;
	float3 color    : COLOR;
};

float4 ps( ps_input input ) : SV_TARGET {
	return float4( input.color, 1.0 );
}
