#include "../stdafx.hpp"

#include "gameplay.hpp"
#include "../window/window.hpp"
#include "../menus/menus.hpp"
#include "../input/input.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>
#include <utils/format/format.hpp>

#include <intrin.h>

utils::function<void __fastcall(DWORD*, char*, int)> sub_7C1160_;
void __fastcall sub_7C1160(DWORD* ecx, char* edx, int a1)
{
	return sub_7C1160_(ecx, edx, a1);
}

utils::function<void __fastcall(int, char*)> sub_4D7698_;
void __fastcall sub_4D7698(int ecx, char* edx)
{
#ifndef DISABLE_SDL
	//Check if window is focused and the menu isnt open in game
	if (SDL_GetMouseFocus() == window::sdl_window && !*(bool*)(0x00A21CCC))
	{
		input::update();

		if (SDL_SetRelativeMouseMode(SDL_TRUE) != 0)
		{
			PRINT_ERROR("%s", SDL_GetError());
		}

		ShowCursor(false);

		WORD i = -(WORD)std::ceil(input::mouse::x_pos * (MAXWORD / window::resolution_x));
		*(WORD*)(ecx + 48) = i;
		//utils::hook::set(0x009ACE70, j);	//Camera angle/y
	}
	else if(*(bool*)(0x00A21CCC))
	{
		if (SDL_SetRelativeMouseMode(SDL_FALSE) != 0)
		{
			PRINT_ERROR("%s", SDL_GetError());
		}

		ShowCursor(true);
	}
#endif

	return sub_4D7698_(ecx, edx);
}

utils::function<int __fastcall(int, char*)> sub_6698E0_;
int __fastcall sub_6698E0(int ecx, char* edx)
{
	return sub_6698E0_(ecx, edx);
}

std::initializer_list<void*>whitelist
{

};

utils::function<void(DWORD, LPCSTR)> debug_print_screen_;
void debug_print_screen(DWORD a1, LPCSTR a2)
{
	bool good = false;
	for (auto addr : whitelist)
	{
		if (_ReturnAddress() == addr)
		{
			good = true;
		}
	}

	if (good)
	{
		PRINT_DEBUG("0x%p | 0x%p | %s", _ReturnAddress(), a1, a2);
	}
}

void gameplay::init()
{
	sub_4D7698_ = utils::hook::detour(0x004D7698, sub_4D7698, 5);
	sub_7C1160_ = utils::hook::detour(0x007C1160, sub_7C1160, 7);
	sub_6698E0_ = utils::hook::detour(0x006698E0, sub_6698E0, 11);

	debug_print_screen_ = utils::hook::detour(0x0061CDB0, debug_print_screen, 1);

#ifndef SDL_DISABLE
	utils::hook::nop(0x00709E1E, 2);
	utils::hook::nop(0x00709E20, 6);
#endif
}