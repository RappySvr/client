#include "winapi.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>

HWND __stdcall create_window_ex_a(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle,
	int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	//Allow minimize and close
	dwStyle = WS_SYSMENU | WS_MINIMIZEBOX;

	//if borderless
	//dwStyle |= WS_POPUP
	return CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

void winapi::init()
{
	utils::hook::set(0x0082CDFC + 0x6, "PSOBB | rappy.live");

	utils::hook::set(0x008F8390, create_window_ex_a);
}