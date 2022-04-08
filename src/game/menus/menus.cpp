#include "menus.hpp"
#include "../network/network.hpp"
#include "../audio/audio.hpp"
#include "game/version.hpp"
#include "intrin.h"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>
#include <utils/format/format.hpp>

void* title_return = (void*)(0x006F4DAD);

static utils::function<void __cdecl(float, float, float, int, wchar_t*)> text_to_screen_;
void __cdecl menus::text_to_screen(float pos_x, float pos_y, float a3, int a4, wchar_t* text)
{
	if (_ReturnAddress() == title_return)
	{
		wchar_t ver_buf[64];
		swprintf(ver_buf, L"Rappy r%i", VERSION);
		text = ver_buf;
		menus::news();
	}
	else if (news::states::once)
	{
		news::states::once = false;
	}

	text_to_screen_(pos_x, pos_y, a3, a4, text);
}

float menus::text_size(wchar_t* text)
{
	return (lstrlenW(text) * 10.0f);
}

void menus::news()
{
	if (!news::states::once)
	{
		news::update_news();

		if (news::news_text.length() != 0 && menus::news_pos_x == 0)
		{
			menus::news_pos_x = 645.0f;
		}

		news::states::once = true;
	}

	menus::text_to_screen(menus::news_pos_x, 10.0f, 0.0f, -1, utils::format::c_to_w(&news::news_text[0]));
	menus::news_pos_x--;

	if (menus::news_pos_x <= -menus::text_size(utils::format::c_to_w(&news::news_text[0])))
	{
		menus::news_pos_x = 645.0f;
	}
}

void menus::init()
{
	text_to_screen_ = utils::hook::detour(0x00789248, menus::text_to_screen, 8);
}

float menus::news_pos_x = 0;
float menus::news_reset_pos_x = 0;