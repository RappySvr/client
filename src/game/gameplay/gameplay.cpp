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

float angle = 0.0f;

utils::function<WORD __cdecl(__int16, int, int)> cam_damp_;
WORD __cdecl cam_damp(__int16 a1, int a2, int a3)
{
	return input::camera;
}

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
	//All ecx + x
	//Notes:
	// Center = 268
	// Rotation = 48
	// Angle = 19

	input::update();
	//PRINT_INFO("0x%p", ecx);
	switch (input::ctrl_method)
	{
		case input::method::CONTROLLER:
		{
			*(WORD*)(ecx + 48) = input::camera;
		}
		break;

		case input::method::MOUSE:
		{
			if (GetFocus() == winapi::hwnd)
			{
				SDL_ShowCursor(SDL_DISABLE);
				ShowCursor(false);
				SDL_WarpMouseInWindow(window::sdl_window, (settings::resolution.x / 2), (settings::resolution.y / 2));
				*(WORD*)(ecx + 48) = input::camera;
			}
		}
		break;
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
	//cam_damp_ = utils::hook::detour(0x004D6370, cam_damp, 6);

	debug_print_screen_ = utils::hook::detour(0x0061CDB0, debug_print_screen, 1);

#ifndef DISABLE_SDL
	utils::hook::nop(0x00709E1E, 2);
	utils::hook::nop(0x00709E20, 6);
#endif
}