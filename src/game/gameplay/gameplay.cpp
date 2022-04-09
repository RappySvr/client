#include "../stdafx.hpp"

#include "gameplay.hpp"
#include "../window/window.hpp"
#include "../menus/menus.hpp"
#include "../input/input.hpp"
#include "../winapi/winapi.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>
#include <utils/format/format.hpp>

#include <intrin.h>

utils::function<void __fastcall(DWORD*, char*, int)> sub_7C1160_;
void __fastcall sub_7C1160(DWORD* ecx, char* edx, int a1)
{
	return sub_7C1160_(ecx, edx, a1);
}

bool release_once = false;
bool grab_once = false;

utils::function<void __fastcall(int, char*)> sub_4D7698_;
void __fastcall sub_4D7698(int ecx, char* edx)
{
#ifndef DISABLE_SDL
	input::update();

	if (GetFocus() == winapi::hwnd && SDL_GetMouseFocus() != window::sdl_window)
	{
		SDL_RaiseWindow(window::sdl_window);
		SDL_SetWindowInputFocus(window::sdl_window);
	}

	//Check if window is focused and the menu isnt open in game and we have new control method
	if (SDL_GetMouseFocus() == window::sdl_window && !*(bool*)(0x00A21CCC) && input::ctrl_method != input::method::KEYBOARD)
	{
		if (input::ctrl_method == input::method::MOUSE)
		{
			if (!grab_once)
			{
				if (SDL_SetRelativeMouseMode(SDL_TRUE) != 0)
				{
					PRINT_ERROR("%s", SDL_GetError());
				}

				SDL_ShowCursor(SDL_DISABLE);
				grab_once = true;
				release_once = false;
			}

			SDL_SetWindowMouseGrab(window::sdl_window, SDL_TRUE);
		}


		*(WORD*)(ecx + 48) = input::camera;
		//utils::hook::set(0x009ACE70, j);	//Camera angle/y
	}
	else if(*(bool*)(0x00A21CCC))
	{
		if (!release_once)
		{
			if (SDL_SetRelativeMouseMode(SDL_FALSE) != 0)
			{
				PRINT_ERROR("%s", SDL_GetError());
			}

			SDL_ShowCursor(SDL_ENABLE);
			SDL_SetWindowMouseGrab(window::sdl_window, SDL_FALSE);
			SDL_WarpMouseInWindow(window::sdl_window, (int)(window::resolution_x / 2), (int)(window::resolution_y / 2));
			release_once = true;
			grab_once = false;
		}
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

#ifndef DISABLE_SDL
	utils::hook::nop(0x00709E1E, 2);
	utils::hook::nop(0x00709E20, 6);
#endif
}