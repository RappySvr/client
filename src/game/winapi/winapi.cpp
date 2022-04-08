#include "../stdafx.hpp"
#include "winapi.hpp"

#include "../window/window.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>

HWND __stdcall create_window_ex_a(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle,
	int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	//Allow minimize and close
	dwStyle = WS_SYSMENU | WS_MINIMIZEBOX;

	winapi::hwnd = CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
#ifndef DISABLE_SDL
	window::sdl_window = SDL_CreateWindowFrom(winapi::hwnd);
	//SDL_SetWindowGrab(window::sdl_window, SDL_TRUE);
#endif

	return winapi::hwnd;
}

HANDLE __stdcall create_file_a(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	bool good = true;

	std::string temp(lpFileName);
	if (temp.find("GameGuard") != std::string::npos)
	{
		good = false;
	}

	if (good)
	{
		return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
			dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	}
}

int __stdcall show_cursor(bool show)
{
	return show;
}

void __fastcall output_debug_string(LPCSTR ecx, char* edx)
{
	PRINT_DEBUG_N("%s", ecx);
}

void winapi::init()
{
	utils::hook::set(0x0082CDFC + 0x6, "PSOBB | rappy.live");
	
	utils::hook::set(0x008F8390, create_window_ex_a);
	utils::hook::set(0x008F8334, show_cursor);
	utils::hook::set(0x008F8144, create_file_a);

	utils::hook::detour(0x0083C070, output_debug_string, 7);
}

HWND winapi::hwnd;