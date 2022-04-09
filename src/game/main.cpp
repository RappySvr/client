#include "loader/loader.hpp"

#include "settings/settings.hpp"
#include "window/window.hpp"
#include "winapi/winapi.hpp"
#include "gameplay/gameplay.hpp"
#include "input/input.hpp"
#include "audio/audio.hpp"
#include "menus/menus.hpp"
#include "network/network.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>
#include <utils/exception/exception.hpp>
#include <utils/io/io.hpp>

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
	replace_func(0x00482EAC, (uint32_t)settings::load);
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

	event::update_song();
	utils::hook::set(0x006F82F0 + 0x1, &event::song_name[0]);

	//Teker Result fix
	utils::hook::write(0x006D9F7B, { 0x68, 0x44, 0xC4, 0x96, 0x00 });
	//Before:	push    offset unk_96C438
	//After:	push    offset unk_96C444

	//Image board patch
	utils::hook::write(0x006713A9, { 0x0F, 0x8C, 0x23, 0x01, 0x00, 0x00 });
	//Before:	jle     loc_6714D2
	//After:	jl		loc_6714D2
}

void client_init()
{
#ifndef DISABLE_SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK) < 0)
	{
		MessageBoxA(nullptr, "Failed to init SDL2", "Rappy.Live", 0);
		exit(0);
	}
#endif
	utils::io::init();
	settings::init();
	window::init();
	winapi::init();
	input::init();
	gameplay::init();
	audio::init();
	menus::init();
}

int __cdecl main(int argc, char* argv[])
{
	utils::exception::init("client");

#ifdef DEBUG
	utils::console::init();
#else
	ShowWindow(GetConsoleWindow(), HIDE_WINDOW);
#endif

	load("psobb.exe");
	patches();
	replace_funcs();
	client_init();
	return entry_point(0x00B60000);
}