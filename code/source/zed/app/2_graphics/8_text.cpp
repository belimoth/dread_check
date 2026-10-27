#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/app/ui.h>
#include <zed/color.h>

#include <directxtk/spritefont.h>
#pragma comment( lib, "directxtk.lib" )

// #include <dxtk/sprite_font.h>
// #pragma comment( lib, "ole32.lib" )
// #include "../../dxtk/sprite_font.cpp"

namespace app_graphics_text {
	using namespace DirectX;

	SpriteBatch *sprite_batch;
	SpriteFont  *sprite_font;
	SpriteFont  *sprite_font_new;

	// zed_sprite_batch *sprite_batch;
	// zed_sprite_font  *sprite_font;

	bool text_is_begun;
}

// 100%  1/1  96dpi 12pt  9pt
// 125%  5/4 120dpi 15pt 12pt
// 150%  3/2 144dpi 18pt 14pt
// 175%  7/4 168dpi 21pt 16pt
// 200%  2/1 192dpi 24pt 19pt
// 225%  9/4 216dpi
// 250%  5/2 240dpi
// 275% 11/4 264dpi
// 300%  3/1 288dpi

void app_graphics_text_init() {
	using namespace app_graphics_text;
	sprite_batch = new SpriteBatch( app.graphics.device_context );
	int dpi = app.system.device_dpi;

	switch ( dpi ) {
		default:
		case  96: sprite_font = new SpriteFont( app.graphics.device, L"data/font/consolas_096.spritefont" ); break;
		case 120: sprite_font = new SpriteFont( app.graphics.device, L"data/font/consolas_120.spritefont" ); break;
		case 144: sprite_font = new SpriteFont( app.graphics.device, L"data/font/consolas_144.spritefont" ); break;
		case 168: break; // todo
		case 192: break; // todo
	}

	sprite_font_new = new SpriteFont( app.graphics.device, L"data/font/bacteria_12.spritefont" );
	sprite_font_new->SetLineSpacing( 20 );
}

void app_graphics_text_begin() {
	using namespace app_graphics_text;
	text_is_begun = true;
	app.graphics.device_context->GSSetShader( 0, 0, 0 );
	sprite_batch->Begin();
}

void app_graphics_text_finish() {
	using namespace app_graphics_text;
	text_is_begun = false;
	sprite_batch->End();
}

void app_graphics_draw_text( string text, float x, float y, uint color ) {
	using namespace app_graphics_text;
	if ( not text_is_begun ) return;
	float2 position = { x, y };
	sprite_font->DrawString( sprite_batch, text, position, htov( color ) );
}

void app_graphics_draw_text_new( string text, float x, float y, uint color ) {
	using namespace app_graphics_text;
	if ( not text_is_begun ) return;
	float2 position = { x, y };
	sprite_font_new->DrawString( sprite_batch, text, position, htov( color ) );
}

float app_graphics_text_measure( string text ) {
	using namespace app_graphics_text;
	return XMVectorGetX( sprite_font_new->MeasureString( text ) );
}
