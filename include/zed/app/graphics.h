#pragma once

#include <zed.h>
#include <zed/app.h>
#include <zed/xmath.h>

struct ID3D11Buffer;

struct zed_buffer {
	ID3D11Buffer *native;

	uint count;
	uint stride;
};

// states

struct zed_input_layouts {
	handle p;
	handle pn;
	handle pnt;
} input_layouts;

struct zed_rasterizer_states {
	handle cull_default;
	handle cull_default_biased;
	handle cull_front;
	handle cull_front_biased;
	handle cull_none;
	handle wireframe;
} rasterizer_states;

struct zed_sampler_states {
	handle point;
	handle linear;
	handle anisotropic;
} sampler_states;

struct zed_blend_states {
	handle opaque;
	handle alpha;
	handle alpha_under;
} blend_states;

struct zed_depth_stencil_states {
	handle read_write;
	handle read_only;
	handle none;

	handle read_write_count;
} depth_stencil_states;

//

struct zed_pass_description {
	string vs_path;
	string gs_path;
	string ps_path;

	handle raster_state;
	handle blend_state;
	handle depth_state;
};

struct ID3D11InputLayout;
struct ID3D11VertexShader;
struct ID3D11GeometryShader;
struct ID3D11RasterizerState;
struct ID3D11PixelShader;
struct ID3D11BlendState;
struct ID3D11DepthStencilState;

struct zed_pass_native{
	ID3D11InputLayout       *il;
	ID3D11VertexShader      *vs;
	ID3D11GeometryShader    *gs;
	ID3D11RasterizerState   *rs;
	ID3D11PixelShader       *ps;
	ID3D11BlendState        *bs;
	ID3D11DepthStencilState *ds;
};

struct zed_pass {
	union {
		zed_pass_native native;

		struct {
			handle il;
			handle vs;
			handle gs;
			handle rs;
			handle ps;
			handle bs;
			handle ds;
		};

		handle handles[ sizeof( zed_pass_native ) / sizeof( handle ) ];
	};
};

struct ID3D11Resource;
struct ID3D11ShaderResourceView;

struct zed_texture {
	ID3D11Resource           *resource;
	ID3D11ShaderResourceView *view;
	float2 size;
};

enum zed_primitive {
	zed_primitive_undefined      = 0,
	zed_primitive_point_list     = 1,
	zed_primitive_line_list      = 2,
	zed_primitive_line_strip     = 3,
	zed_primitive_triangle_list  = 4,
	zed_primitive_triangle_strip = 5,
};

// mesh

struct zed_mesh_vertex {
	float3 position;
	float3 normal;
	float2 uv;
};

struct zed_mesh_vertex_pn {
	float3 position;
	float3 normal;
};

struct zed_mesh_data {
	zed_mesh_vertex *vertices;
	uint            *indices;

	uint count_vertex;
	uint count_index;
};

// todo shouldn't mesh be defined in terms of zed_buffer
struct zed_mesh {
	ID3D11Buffer *buffer_vertex;
	ID3D11Buffer *buffer_index;
	uint count_vertex;
	uint count_index;
	uint stride;
	zed_primitive primitive;
};

// graphics

void zed_clear_stencil();

// graphics/device/render target

void zed_set_render_target( app_render_target target );
void zed_set_viewport( float, float, float, float );

// graphics/buffer

void zed_buffer_new_uniform ( zed_buffer &buffer, uint size   );
void zed_buffer_new_vertex  ( zed_buffer &buffer, zed_data_in );
void zed_buffer_new_index   ( zed_buffer &buffer, zed_data_in );
void zed_buffer_new_dynamic ( zed_buffer &buffer, zed_data_in );
void zed_buffer_new_instance( zed_buffer &buffer, zed_data_in );
void zed_buffer_update      ( zed_buffer &buffer, zed_data_in );
void zed_buffer_use_uniform ( zed_buffer  buffer, uint slot   );

// graphics/mesh

void zed_mesh_draw_primitive( zed_primitive primitive, int count );

//

void zed_mesh_new_from_buffer  ( zed_mesh &mesh, zed_data_in );
void zed_mesh_new_plane        ( zed_mesh &mesh, int w, int h, float scale = 1.0 );
void zed_mesh_new( zed_mesh &mesh, string file, float scale = 1.0 );
void zed_mesh_load             ( zed_mesh &mesh, string file );
void zed_mesh_load             ( zed_mesh &mesh, int id );
void zed_mesh_draw             ( zed_mesh &mesh );
void zed_mesh_draw_instanced   ( zed_mesh &mesh, zed_buffer *instance_buffer = 0, int count = 0, uint instance_offset = 0 );

// graphics/texture

zed_texture texture_null = {};

// todo
struct ID3D11Texture2D;

void zed_texture_make_2d  ( ID3D11Texture2D **texture );
void zed_texture_new_2d  ( zed_texture &texture, string file );
void zed_texture_load_cube( zed_texture &texture, string file );
void zed_texture_new_2d  ( zed_texture &texture, int id );
void zed_texture_load_cube( zed_texture &texture, int id );
void zed_pass_use( zed_texture &texture = texture_null );
void zed_pass_use( zed_texture *, int ); // todo

// graphics/pass

// todo
struct D3D11_INPUT_ELEMENT_DESC;

zed_pass pass_null = {};

void zed_pass_new( zed_pass &pass, string file );
void zed_pass_new( zed_pass &pass, string file, string ps_name );
void zed_pass_new( zed_pass &pass, string file, D3D11_INPUT_ELEMENT_DESC *ied, uint ied_count );
void zed_pass_new( zed_pass &pass, int id );
void zed_pass_new( zed_pass &pass, int id, D3D11_INPUT_ELEMENT_DESC *ied, uint ied_count );
void zed_pass_reset      ();
void zed_pass_reset      ( zed_pass &pass );
void zed_pass_set        ( zed_pass &pass );
void zed_pass_begin      ( zed_pass &pass_0 = pass_null, zed_pass &pass_1 = pass_null );

// graphics/canvas

void zed_canvas_new          ( zed_canvas &canvas, int canvas_width, int canvas_height );
void zed_use_canvas_2d       ( zed_canvas &canvas );
void zed_use_canvas_3d       ( zed_canvas &canvas );
void zed_canvas_clear        ( zed_canvas &canvas );
void zed_canvas_clear_stencil( zed_canvas &canvas );

// graphics/text

void app_graphics_text_begin();
void app_graphics_text_finish();
void app_graphics_draw_text( string, float, float, uint = 0xffffff );
void app_graphics_draw_text_new( string, float, float, uint = 0xffffff );
float app_graphics_text_measure( string );
