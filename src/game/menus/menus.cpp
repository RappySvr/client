#include "menus.hpp"
#include "game/version.hpp"
#include "intrin.h"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>
#include <utils/format/format.hpp>

void* title_return = (void*)(0x006F4DAD);

static utils::function<void __cdecl(float, float, float, int, wchar_t*)> text_to_screen_;
void __cdecl text_to_screen(float pos_x, float pos_y, float a3, int a4, wchar_t* text)
{
	if (_ReturnAddress() == title_return)
	{
		wchar_t ver_buf[64];
		swprintf(ver_buf, L"Rappy r%i", VERSION);
		text = ver_buf;
		menus::news();
	}

	text_to_screen_(pos_x, pos_y, a3, a4, text);
}

float menus::text_size(wchar_t* text)
{
	return (lstrlenW(text) * 15.0f);
}

void menus::news()
{
	wchar_t* message = L"Welcome to Rappy.Live!";
	text_to_screen(10.0f, 10.0f, 0.0f, -1, message);
}

void menus::init()
{
	text_to_screen_ = utils::hook::detour(0x00789248, text_to_screen, 8);
}