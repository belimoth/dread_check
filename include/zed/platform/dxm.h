#pragma once

#include <zed/platform/windows.h>

#pragma warning( push )
#pragma warning( disable : 4668 )

#include <directxmath.h>
#include <directxtk/simplemath.h>

#pragma warning( pop )

typedef DirectX :: XMMATRIX xm_matrix;
typedef DirectX :: XMVECTOR xm_vector;
typedef DirectX :: XMFLOAT4 xm_float4;
typedef DirectX :: XMFLOAT3 xm_float3;
typedef DirectX :: XMFLOAT2 xm_float2;

typedef DirectX :: SimpleMath :: Matrix  sm_matrix;
typedef DirectX :: SimpleMath :: Vector4 sm_float4;
typedef DirectX :: SimpleMath :: Vector3 sm_float3;
typedef DirectX :: SimpleMath :: Vector2 sm_float2;
