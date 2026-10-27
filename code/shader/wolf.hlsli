struct vs_input_wolf {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;
	uint   i_tile   : I_TILE;
	float  t        : I_TWEEN;
};

matrix translate( float x, float y, float z ) {
    matrix m;

    m[0][0] = 1;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;

    m[1][0] = 0;
    m[1][1] = 1;
    m[1][2] = 0;
    m[1][3] = 0;

    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 1;
    m[2][3] = 0;

    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
    m[3][3] = 1;

    return m;
}

matrix rotate_q( float4 Q ) {
    float4 Q0 = Q + Q;
    float4 Q1 = Q * Q0;

	//

    float4 V0 = float4( Q1.y, Q1.x, Q1.x, 0 );
    float4 V1 = float4( Q1.z, Q1.z, Q1.y, 0 );

	//

    float4 R0 = float4( 1, 1, 1, 0 ) - V0;

    R0 = R0 - V1;

	//

    V0 = Q.xxyw;
    V1 = Q0.zyzw;
    V0 = V0 * V1;

    V1 = Q.wwww;
    float4 V2 = Q0.yzxw;
    V1 = V1 * V2;

    float4 R1 = V0 + V1;
    float4 R2 = V0 - V1;

    V0 = float4( R1.y, R2.x, R2.y, R1.z );
	V1 = float4( R1.x, R2.z, R1.x, R2.z );

	//

    matrix m;

    m[0] = float4( R0.x, V0.x, V0.y, R0.w );
    m[1] = float4( V0.z, R0.y, V0.w, R0.w );
    m[2] = float4( V1.x, V1.y, R0.z, R0.w );
    m[3] = float4( 0, 0, 0, 1 );

    return m;
}

matrix rotate( float4 angles ) {
    float4 sign = float4( 1, -1, -1, 1 );
    float4 half_angles = angles * float4( 0.5, 0.5, 0.5, 0.5 );

    float4 sin_angles, cos_angles;
    sincos( half_angles, sin_angles, cos_angles );

    float4 P0 = float4( sin_angles.x, cos_angles.x, cos_angles.x, cos_angles.x );
    float4 Y0 = float4( cos_angles.y, sin_angles.y, cos_angles.y, cos_angles.y );
    float4 R0 = float4( cos_angles.z, cos_angles.z, sin_angles.z, cos_angles.z );
    float4 P1 = float4( cos_angles.x, sin_angles.x, sin_angles.x, sin_angles.x );
    float4 Y1 = float4( sin_angles.y, cos_angles.y, sin_angles.y, sin_angles.y );
    float4 R1 = float4( sin_angles.z, sin_angles.z, cos_angles.z, sin_angles.z );

    float4 Q1 = P1 * sign;
    float4 Q0 = P0 * Y0;
    Q1 = Q1 * Y1;
    Q0 = Q0 * R0;
    float4 Q = mad( Q1, R1, Q0 );

	return rotate_q( Q );
}

matrix rotate( float x, float y, float z, float w = 0 ) {
	float4 angles = float4( x, y, z, w );
	return rotate( angles );
}
