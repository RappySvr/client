#include "loader/loader.hpp"

#include "window/window.hpp"
#include "winapi/winapi.hpp"
#include "audio/audio.hpp"
#include "menus/menus.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>
#include <utils/exception/exception.hpp>

void __declspec(naked) start()
{
	//Not really sure how the start is with this unpacked exe
	__asm
	{
		mov ebx, 227h
		push	0x00B60073;
		retn;
	}
}

void replace_funcs()
{
	utils::hook::jump(0x00B60000, start);

	replace_func(0x004829E0, (uint32_t)window::get_resolution_x);
	replace_func(0x004829E8, (uint32_t)window::get_resolution_y);
	replace_func(0x004829F0, (uint32_t)window::get_bpp);
	replace_func(0x00482AA0, (uint32_t)window::get_window_mode);
}

void patches()
{
	utils::hook::set(0x007085E5 + 0x1, IP_ADDR);
	utils::hook::set(0x00708618 + 0x1, IP_ADDR);
	utils::hook::set(0x007085EB + 0x1, IP_ADDR);
	utils::hook::set(0x007082F1 + 0x1, IP_ADDR);
	utils::hook::set(0x0070833C + 0x1, IP_ADDR);
	utils::hook::set(0x007082F7 + 0x1, IP_ADDR);
	utils::hook::set(0x007085FD + 0x1, IP_ADDR);
	utils::hook::set(0x0070861E + 0x1, IP_ADDR);
	utils::hook::set(0x00708321 + 0x1, IP_ADDR);
	utils::hook::set(0x00708342 + 0x1, IP_ADDR);

	char* song_name = "Valentine.adx";
	utils::hook::set(0x006F82F0 + 0x1, song_name);
}

void client_init()
{
	window::widescreen(640.0f * 2, 480.0f * 2);
	winapi::init();
	audio::init();
	menus::init();
}

int __cdecl main(int argc, char* argv[])
{
	utils::exception::init("client");
	utils::console::init();
	load("psobb.exe");
	patches();
	replace_funcs();
	client_init();
	return entry_point(0x00B60000);
}