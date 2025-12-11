#pragma once

#include <zed.h>
#include <zed/platform/dxm.h>

typedef sm_float2 float2;
typedef sm_float3 float3;
typedef sm_float4 float4;
typedef xm_matrix matrix;

static matrix identity = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1,
};

matrix matrix_set(
	float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33
) {
	using namespace DirectX;
	return XMMatrixSet(
		m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33
	);
}

float3 mul( float3 x, matrix y ) {
	using namespace DirectX;
	return XMVector3TransformCoord( x, y );
}

float4 mul( float4 x, matrix y ) {
	using namespace DirectX;
	return XMVector4Transform( x, y );
}

matrix mul( matrix x, matrix y ) {
	using namespace DirectX;
	return XMMatrixMultiply( x, y );
}

//

float3 mad( float3 m, float3 a, float3 b ) {
	using namespace DirectX;
	return XMVectorMultiplyAdd( m, a, b );
}

float4 mad( float4 m, float4 a, float4 b ) {
	using namespace DirectX;
	return XMVectorMultiplyAdd( m, a, b );
}

//

float length( float2 v ) {
	using namespace DirectX;
	return XMVectorGetX( XMVector2Length( v ) );
}

float length( float3 v ) {
	using namespace DirectX;
	return XMVectorGetX( XMVector3Length( v ) );
}

//

float2 normalize( float2 v ) {
	using namespace DirectX;
	return XMVector2Normalize( v );
}

float3 normalize( float3 v ) {
	using namespace DirectX;
	return XMVector3Normalize( v );
}

float4 normalize( float4 v ) {
	using namespace DirectX;
	return XMVector4Normalize( v );
}

//

float2 normalize_fast( float2 v ) {
	using namespace DirectX;
	return XMVector2NormalizeEst( v );
}

float3 normalize_fast( float3 v ) {
	using namespace DirectX;
	return XMVector3NormalizeEst( v );
}

float4 normalize_fast( float4 v ) {
	using namespace DirectX;
	return XMVector4NormalizeEst( v );
}

//

float2 dot( float2 a, float2 b ) {
	return XMVector2Dot( a, b );
}

float3 dot( float3 a, float3 b ) {
	return XMVector3Dot( a, b );
}

float4 dot( float4 a, float4 b ) {
	return XMVector4Dot( a, b );
}

//

matrix transpose( matrix x ) {
	using namespace DirectX;
	return XMMatrixTranspose( x );
}

matrix inverse( matrix x, xm_vector *determinant = 0 ) {
	using namespace DirectX;
	// note: if the matrix is orthogonal it's cheaper to transpose
	return DirectX::XMMatrixInverse( determinant, x );
}

//

matrix translate( float x, float y, float z ) {
	using namespace DirectX;
	return XMMatrixTranslation( x, y, z );
}

matrix translate( float3 offset ) {
	using namespace DirectX;
	return XMMatrixTranslationFromVector( offset );
}

//

matrix scale( float x ) {
	using namespace DirectX;
	return XMMatrixScaling( x, x, x );
}

matrix scale( float x, float y, float z ) {
	using namespace DirectX;
	return XMMatrixScaling( x, y, z );
}

matrix scale( float3 scale ) {
	using namespace DirectX;
	return XMMatrixScalingFromVector( scale );
}

//

matrix rotate( float x, float y, float z ) {
	using namespace DirectX;
	return XMMatrixRotationRollPitchYaw( x, y, z );
}

//

matrix reflect( float3 plane ) {
	return XMMatrixReflect( plane );
}

//

// float3 dtor( float3 degrees ) {
// 	return float3( dtor( degrees.x ), dtor( degrees.y ), dtor( degrees.z ) );
// }
//
// float3 rtod( float3 radians ) {
// 	return float3( rtod( radians.x ), rtod( radians.y ), rtod( radians.z ) );
// }
