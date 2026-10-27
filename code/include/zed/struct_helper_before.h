#ifdef __cplusplus

#define field( type, name, semantic ) type name;

#define struct struct alignas(16)
#define float4 float4 alignas(16)
#define float3 float3 alignas(16)
#define float2 float2 alignas( 8)
#define float  float  alignas( 4)
#define uint   uint   alignas( 4)

#else

#define field( type, name, semantic ) type name : name;

#endif
