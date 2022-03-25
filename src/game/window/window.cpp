#include "window.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>

namespace rl
{
	::HWND __stdcall create_window_ex_a(::DWORD ex_style, LPCSTR lpClassName, LPCSTR lpWindowName, ::DWORD style, int left, int right, int width, int height, ::HWND hwnd, ::HMENU, ::HINSTANCE instance, void*)
	{
		style |= WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

		auto rect = ::RECT();

		::GetClientRect(::GetDesktopWindow(), &rect);

		rect.left = (rect.right / 2) - (1280 / 2);
		rect.top = (rect.bottom / 2) - (720 / 2);

		return ::CreateWindowExA(ex_style, lpClassName, lpWindowName, style, rect.left, rect.top, width, height, hwnd, nullptr, instance, nullptr);
	}

	static utils::function<LRESULT __stdcall(::HWND, ::UINT, ::WPARAM, ::LPARAM)> sub_82C49C_;
	LRESULT __stdcall sub_82C49C(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		return sub_82C49C_(hWnd, Msg, wParam, lParam);
	}

	void window::init()
	{
		sub_82C49C_ = utils::hook::detour(0x0082C49C, sub_82C49C, 8);
		utils::hook::set(0x008F8390, create_window_ex_a);
	}
}