#pragma pack_matrix( row_major )

SamplerState sampler_point       : register(s0);
SamplerState sampler_linear      : register(s1);
SamplerState sampler_anisotropic : register(s2);

Texture2D texture_0 : register(t0);
Texture2D texture_1 : register(t1);

struct game_draw_camera {
	matrix matrix_view;
	matrix matrix_clip;
	matrix matrix_tiwv;
	matrix matrix_iwvc; // todo this contains world matrix but shouldn't (always at origin for sky etc)
	float3 camera_position;
	matrix look;
};

struct game_light {
	// point, capsule

	float3 position;
	float  alpha;
	float3 color;
	float  range;

	// capsule

	float3 direction;
	float  length;
};

struct game_draw_light {
	game_light light_point  [8];
	game_light light_capsule[8];
	game_light light_spot   [8];
};

struct game_draw_vignette {
	float roundness;
	float radius_min;
	float radius_max;
	float aspect_ratio;
	float3 color;
};

#define vision_mode_none        0
#define vision_mode_protanope   1
#define vision_mode_deuteranope 2
#define vision_mode_tritanope   3

struct game_draw_vision {
	int mode;
};

//

cbuffer game_draw_per_scene : register(b0) {
	float screen_width;
	float screen_height;
}

cbuffer game_draw_per_frame : register(b1) {
	game_draw_camera   camera;
	game_draw_light    light;
	game_draw_vignette vignette;
	// float4 fx;
}

cbuffer game_draw_per_object : register(b2) {
	matrix matrix_world;
}

cbuffer game_draw_per_instance : register(b3) {
	// todo placeholder
}

cbuffer game_draw_alpha : register(b4) {
	float alpha;
}

cbuffer game_draw_vision : register(b5) {
	int vision_mode;
}

//

struct vs_input_p {
	float3 position : POSITION;
};

struct vs_input_pnt {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;
};


struct ps_input_svp {
	float4 position : SV_POSITION;
};

struct ps_input_p {
	float4 position : SV_POSITION;

	float4 position_world : POSITION0;
	float4 position_view  : POSITION1;
	float4 position_clip  : POSITION2;
};

struct ps_input_pnt {
	float4 position : SV_POSITION;

	float4 position_world : POSITION0;
	float4 position_view  : POSITION1;
	float4 position_clip  : POSITION2;

	float3 normal_world : NORMAL0;
	float3 normal_view  : NORMAL1;

	float2 uv : TEXCOORD0;
};

//

ps_input_p projection_standard_p_p( vs_input_p input ) {
	ps_input_p output;

	// projection

	float4 position_model = float4( input.position, 1.0 );
	float4 position_world = mul( position_model, matrix_world );
	float4 position_view  = mul( position_world, camera.matrix_view );
	float4 position_clip  = mul( position_view,  camera.matrix_clip );

	// output

	output.position_world = position_world;
	output.position_view  = position_view;
	output.position_clip  = position_clip;
	output.position       = position_clip;

	//

	return output;
}

ps_input_p projection_standard_pnt_p( vs_input_pnt input ) {
	ps_input_p output;

	// projection

	float4 position_model = float4( input.position, 1.0 );
	float4 position_world = mul( position_model, matrix_world );
	float4 position_view  = mul( position_world, camera.matrix_view );
	float4 position_clip  = mul( position_view,  camera.matrix_clip );

	// output

	output.position_world = position_world;
	output.position_view  = position_view;
	output.position_clip  = position_clip;
	output.position       = position_clip;

	//

	return output;
}

ps_input_pnt projection_standard_pnt_pnt( vs_input_pnt input, float3 i_position = float3( 0, 0, 0 ), float scale = 1 ) {
	ps_input_pnt output;

	// projection

	float4 position_model = float4( input.position, 1.0 );
	float4 position_world = mul( position_model, matrix_world ) + float4( i_position, 0 );
	position_world = float4( position_world.xyz * scale, 1 );
	float4 position_view  = mul( position_world, camera.matrix_view );
	float4 position_clip  = mul( position_view,  camera.matrix_clip );

	// output

	output.position_world = position_world;
	output.position_view  = position_view;
	output.position_clip  = position_clip;
	output.position       = position_clip;

	//

	float3 normal_model = input.normal;
	float3 normal_world = mul( normal_model, (float3x3)matrix_world       );
	float3 normal_view  = mul( normal_world, (float3x3)camera.matrix_view );
	// float3 normal_view  = mul( normal_model, (float3x3)camera.matrix_tiwv );

	output.normal_world = normalize( normal_world );
	output.normal_view  = normalize( normal_view  );

	output.uv = input.uv;

	//

	return output;
}

//

#define mix lerp

// /*
static const float fog_a = 0.01;
static const float fog_b = 0.01;
/*/
static const float fog_a = 0.001;
static const float fog_b = 0.001;
//*/

static const float fog_c = fog_a / fog_b;

static const float3 color_sun = float3( 1.0, 0.4, 0.3 ) * 1;
// static const float3 color_sun = float3( 1.0, 0.4, 0.3 ) * 2;
// static const float3 color_fog = float3( 0.4, 0.1, 0.5 );
// static const float3 color_fog = float3( 0.15, 0.10, 0.25 );
// static const float3 color_fog = float3( 0.15, 0.10, 0.25 ) * 0.8;
static const float3 color_fog = float3( 0.16, 0.11, 0.16 );

float3 fog_0( float3 rgb, float distance ) {
	float mix_fog = 1.0 - exp( distance * fog_b );
	float3 color = color_sun;
	return mix( rgb, color, mix_fog );
}

float3 fog_1( float3 rgb, float distance, float3 ray, float3 sun ) {
	float mix_fog = 1.0 - exp( distance * fog_b );
	float mix_sun = max( dot( ray, sun ), 0.0 );
	float3 color  = mix( color_fog, color_sun, pow( mix_sun, 8.0 ) );
	return mix( rgb, color, mix_fog );
}

float3 fog_2( float3 rgb, float distance, float3 ray, float3 sun, float3 camera ) {
	float mix_fog = fog_c * exp( camera.y * fog_b ) * ( 1.0 - exp( distance * ray.y * fog_b ) ) / ray.y;
	float mix_sun = max( dot( ray, sun ), 0.0 );
	float3 color  = mix( color_fog, color_sun, pow( mix_sun, 8.0 ) );
	return mix( rgb, color, mix_fog );
}

float3 fog_3( float3 rgb, float distance, float3 ray, float3 sun ) {
	float  mix_fog = 1.0 - exp( distance * fog_b );
	float  mix_sun = pow( max( dot( ray, sun ), 0.0 ), 8.0 );
		// mix_sun = floor( mix_sun * 3 ) / 3;
		//    mix_sun = mix_fog * mix_sun;
	float3 color   = mix( color_fog, color_sun, mix_sun );
		//    mix_fog = floor( mix_fog * 3 ) / 3;
	return mix( rgb, color, mix_fog );
}

//

static float q = 3;
static float r = 1 / ( q * 2 );

float quantize( float value ) {
	// note: yo
	// q = 1;
	// return floor( ( value + 0.5 ) * q ) / q - 0.5;

	// note: yooo
	// q = 2; r = 1 / ( q * 2 );
	// return ( floor( value * q + r ) - r ) / q;

	return floor( value * q ) / q;
}

float3 light_ambient_0( float3 normal ) {
	float up = normal.y * 0.5 + 0.5;
	float3 environment = { 1.0, 1.0, 0.9 };
	float3 ambient = environment + up * float3( 1, 1, 1 );
	return ambient * 0.4;
}

float3 light_ambient_1( float3 normal, float3 color ) {
	float3 environment = { 1.0, 1.0, 0.9 };

	float3 light;
	float intensity;

	light = normalize( float3( 0, 0, 1 ) );
	intensity = saturate( dot( normal, -light ) );

	light = normalize( float3( 0, -1, 0 ) );
	intensity = intensity * 0.2 + saturate( dot( normal, -light ) ) * 0.8;

	// quantization

	intensity = quantize( intensity );

	// shading
	color = color * ( intensity * 0.6 + 0.4 );

	// float fresnel;

	// fresnel
	// static const float fresnel_bias  =  0.0;
	// static const float fresnel_scale =  1.0;
	// static const float fresnel_power =  4.0;
	// float3 I = normalize( input.position_view.xyz - camera.camera_position.xyz );
	// fresnel = fresnel_bias + fresnel_scale * pow( 1.0 - saturate( dot( I, normal ) ), fresnel_power );

	// temp
	// fresnel = 0.01 * pow( length( normal_view.xy ), 5 );
	// color = lerp( color, environment, fresnel );

	return color;
}

float sum( float3 p ) {
	return abs(p.x) + abs(p.y) + abs(p.z);
}

float3 light_point( game_light light, float3 position, float3 normal ) {
	float  d        = length   ( light.position             - position );
	// float  d        = sum      ( light.position             - position );
	float3 to_light = normalize( light.position             - position );
	float3 to_eye   = normalize( camera.camera_position.xyz - position );

	//

	float intensity = saturate( dot( to_light, normal ) );

	//

	// intensity = quantize( intensity );

	// todo specular

	float dn = 1 - saturate( d / light.range );
	float attenuation = dn * dn;

	//

	// attenuation = quantize( attenuation );
	float intensity_attenuation = intensity * attenuation;
	intensity_attenuation = quantize( intensity_attenuation );

	//

	return light.color * intensity_attenuation;
}

float3 light_capsule( game_light light, float3 position, float3 normal ) {
	float capsule_length = light.length;

	//

	float3 to_eye = camera.camera_position.xyz - position;
	float3 to_capsule_start = position - light.position;
	float  distance_on_line = dot( to_capsule_start, light.direction ) / capsule_length;
	distance_on_line = saturate( distance_on_line ) * capsule_length;
	float3 point_on_line = light.position + light.direction * distance_on_line;
	float3 to_light = point_on_line - position;
	float d = length( to_light );
	// float d = sum(to_light);

	//

	to_light = normalize( to_light );
	to_eye   = normalize( to_eye   );

	// intensity

	float intensity = saturate( dot( to_light, normal ) );

	// attenuation

	float dn = 1 - saturate( d / light.range );
	float attenuation = dn * dn;

	//

	float intensity_attenuation = intensity * attenuation;

	//

	intensity_attenuation = quantize( intensity_attenuation );

	//

	return light.color * intensity_attenuation;
}

float4 ps_standard( ps_input_pnt input ) : SV_TARGET {
	input.normal_world = normalize( input.normal_world );
	input.normal_view  = normalize( input.normal_view  );

	//

	float3 albedo = float3( 0.5, 0.5, 0.6 );
	float3 color  = albedo * light_ambient_1( input.normal_world, float3( 1, 1, 1 ) );

	//

	float f;
	f = input.position_world.y;
	f = f - 0.2;
	f = f * 1.4;
	f = max( min( f, 1 ), 0 );
	color = color * f + ( float3( 33, 24, 33 ) / 255.0 ) * ( 1.0 - f );

	//

	float3 ray = normalize( input.position_world.xyz - camera.camera_position.xyz ).xyz;
	float3 sun = { 0, 0, -1 };
	color = fog_3( color.xyz, -input.position_view.z, ray, sun );

	//

	for ( int i = 0; i < 8; i++ ) {
		color += albedo * light_point  ( light.light_point  [i], input.position_world.xyz, input.normal_world );
		color += albedo * light_capsule( light.light_capsule[i], input.position_world.xyz, input.normal_world );
	}

	//

	return float4( color.xyz, 1 * alpha );
}

#define ps_standard_imp float4 ps( ps_input_pnt input ) : SV_TARGET { return ps_standard( input ); }

//

float get_depth( float4 position ) {
	return ( 1 - position.z ) / position.w;
}

float4 depth_to_color( float4 position ) {
	float depth = get_depth( position );
	return float4( depth, depth, depth, 1 );
}

float4 normal_to_color( float3 normal ) {
	return float4( normal.x * 0.5 + 0.5, normal.y * 0.5 + 0.5, normal.z * -0.5 + 0.5, 1 );
}
