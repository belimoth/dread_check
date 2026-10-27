#pragma once

#include <zed.h>

// config

struct app_options {
	bool debug;
	bool headless;
};

enum app_window_type {
	app_window_type_game           = 0,
	app_window_type_app            = 1,
	app_window_type_app_borderless = 2,
	app_window_type_legacy         = 3,
};

struct app_window_description {
	app_window_type type;
	int x, y, width, height;
};

// todo unused

enum app_swap_chain_type {
	swap_chain_type_0,
	swap_chain_type_1, // todo re-updates and re-renders until vsync (lowest latency but wasteful)
	swap_chain_type_2, // todo legacy fullscreen exclusive
};

struct app_swap_chain_description {
	app_swap_chain_type type;
};

struct zed_canvas_description {
	// todo
};

struct app_config {
	string                     title;
	app_window_description     window;
	app_swap_chain_description swap_chain;
	zed_canvas_description     canvas;
};

// system

struct app_system_event_native {
	handle   window = 0;
	uint32_t message;
	uint64_t w_param;
	int64_t  l_param;
};

struct app_system_event {
	app_system_event_native native;
};

struct app_system {
	handle window;

	size2 device_size;
	uint  device_dpi;

	bool idle;
	bool sizing;
};

// graphics

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11Debug;
struct ID3D11InfoQueue;
struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct ID3D11DepthStencilState;
struct ID3D11DepthStencilView;
struct ID3D11RasterizerState;
struct ID3D11ShaderResourceView;

struct app_render_target {
	size2 size;

	ID3D11Texture2D        *rtb;
	ID3D11RenderTargetView *rtv;

	ID3D11Texture2D        *dsb;
	ID3D11DepthStencilView *dsv;
	ID3D11DepthStencilView *dsvro;
};

struct app_graphics {
	size2 display_size;

	ID3D11Device        *device;
	ID3D11DeviceContext *device_context;
	IDXGISwapChain      *swap_chain;
	void                *waitable;

	ID3D11Debug     *debug;
	ID3D11InfoQueue *info_queue;

	union {
		struct {
			size2 size;

			ID3D11Texture2D        *rtb;
			ID3D11RenderTargetView *rtv;

			ID3D11Texture2D        *dsb;
			ID3D11DepthStencilView *dsv;
			ID3D11DepthStencilView *dsvro;
		};

		app_render_target render_target;
	};

	ID3D11DepthStencilState *dss;
};

struct zed_canvas {
	union {
		struct {
			size2 size;

			ID3D11Texture2D        *rtb;
			ID3D11RenderTargetView *rtv;
			ID3D11Texture2D        *dsb;
			ID3D11DepthStencilView *dsv;
			ID3D11DepthStencilView *dsvro;
		};

		app_render_target render_target;
	};

	ID3D11ShaderResourceView *srv;
	ID3D11ShaderResourceView *dsrv;
};

// audio

// audio/xaudio

class IXAudio2;
class IXAudio2MasteringVoice;

struct app_audio {
	IXAudio2 *device;
	IXAudio2MasteringVoice *mv;
};

// audio/miniaudio

// todo

// struct app_audio {
// 	ma_device device;
// };

// app

struct app_t {
	bool quit;
	bool size;
	int  time;
	char user[32];

	app_options  options;
	app_config   config;
	app_system   system;
	app_graphics graphics;
	app_audio    audio;
} app;

// system

void app_exit();
void app_hide_cursor();
void app_show_cursor();
void app_center_cursor();

// audio

// todo

// input

// todo
