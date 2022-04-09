#include "../stdafx.hpp"
#include "winapi.hpp"

#include "../window/window.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>

HWND __stdcall create_window_ex_a(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle,
	int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	//Allow minimize and close
	if (*(int*)(0x00A46C72) == 1)
	{
		dwStyle = WS_SYSMENU | WS_MINIMIZEBOX;
	}

	winapi::hwnd = CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

#ifndef DISABLE_SDL
	window::sdl_window = SDL_CreateWindowFrom(winapi::hwnd);
	//window::sdl_renderer = SDL_CreateRenderer(window::sdl_window, 0, 0);
#endif

	return winapi::hwnd;
}

LONG __stdcall set_window_long_a(HWND hWnd, int nIndex, LONG dwNewLong)
{
	return SetWindowLongA(hWnd, nIndex, dwNewLong);
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

BOOL __stdcall create_directory_a(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	bool good = true;

	std::string temp(lpPathName);
	if (temp.find("GameGuard") != std::string::npos)
	{
		good = false;
	}

	if (good)
	{
		return CreateDirectoryA(lpPathName, lpSecurityAttributes);
	}
}

int __stdcall show_cursor(bool show)
{
	return ShowCursor(show);
}

void __fastcall output_debug_string(LPCSTR ecx, char* edx)
{
	PRINT_DEBUG_N("%s", ecx);
}

void __stdcall sleep(DWORD dwMilliseconds)
{
#ifndef DISABLE_SDL
	SDL_Delay(dwMilliseconds);
#else
	Sleep(dwMilliseconds);
#endif
}

LRESULT __stdcall def_wndproc_a(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProcA(hWnd, Msg, wParam, lParam);
}

BOOL __stdcall set_cwd(LPCSTR lpPathName)
{
	return SetCurrentDirectoryA(lpPathName);
}

void winapi::init()
{
	utils::hook::set(0x0082CDFC + 0x6, "PSOBB | rappy.live");
	
	utils::hook::set(0x008F8390, create_window_ex_a);
	utils::hook::set(0x008F8334, show_cursor);
	utils::hook::set(0x008F8144, create_file_a);
	utils::hook::set(0x008F8220, create_directory_a);
	utils::hook::set(0x008F83A0, set_window_long_a);
	utils::hook::set(0x008F8174, sleep);
	utils::hook::set(0x008F836C, def_wndproc_a);
	utils::hook::set(0x008F8148, set_cwd);

	utils::hook::detour(0x0083C070, output_debug_string, 7);
}

HWND winapi::hwnd;