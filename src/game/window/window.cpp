#include "window.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>

namespace rl
{
	::HWND __stdcall create_window_ex_a(::DWORD ex_style, LPCSTR lpClassName, LPCSTR lpWindowName, ::DWORD style, int left, int right, int width, int height, ::HWND hwnd, ::HMENU, ::HINSTANCE instance, void*)
	{
		style |= WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

		auto rect = ::RECT();

		width = 1280;
		height = 724;
		::GetClientRect(::GetDesktopWindow(), &rect);

		rect.left = (rect.right / 2) - (width / 2);
		rect.top = (rect.bottom / 2) - (height / 2);

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

		float width = 1280.0f;
		float height = 480.0f;

		//Modify width
		utils::hook::set<float>(0x008F8EAC, width);
		utils::hook::set<float>(0x008F8EBC, width);
		utils::hook::set<float>(0x008F8F50, width);
		utils::hook::set<float>(0x008F9AC4, width);
		utils::hook::set<float>(0x008F9D38, width);
		utils::hook::set<float>(0x008F9D68, width);
		utils::hook::set<float>(0x008F9EF8, width);
		utils::hook::set<float>(0x008F9F2C, width);
		utils::hook::set<float>(0x008F9F34, width);
		utils::hook::set<float>(0x008F9F58, width);
		utils::hook::set<float>(0x008FA8A8, width);
		utils::hook::set<float>(0x008FAE90, width);
		utils::hook::set<float>(0x008FFB84, width);
		utils::hook::set<float>(0x009007B8, width);
		utils::hook::set<float>(0x00909168, width);
		utils::hook::set<float>(0x00909D70, width);
		utils::hook::set<float>(0x0091D8BC, width);
		utils::hook::set<float>(0x0091DA80, width);
		utils::hook::set<float>(0x0091E19C, width);
		utils::hook::set<float>(0x0091FBF0, width);
		utils::hook::set<float>(0x0091FC54, width);
		utils::hook::set<float>(0x0091FC74, width);
		utils::hook::set<float>(0x0091FF94, width);
		utils::hook::set<float>(0x00920164, width);
		utils::hook::set<float>(0x0092B6EC, width);
		utils::hook::set<float>(0x0092B71C, width);
		utils::hook::set<float>(0x0092B740, width);
		utils::hook::set<float>(0x0092B780, width);
		utils::hook::set<float>(0x0096F5E0, width);
		utils::hook::set<float>(0x0096F694, width);
		utils::hook::set<float>(0x0096FE84, width);
		utils::hook::set<float>(0x0096FF60, width);
		utils::hook::set<float>(0x0096FF9C, width);
		utils::hook::set<float>(0x0096FFC0, width);
		utils::hook::set<float>(0x00970640, width);
		utils::hook::set<float>(0x009706C0, width);
		utils::hook::set<float>(0x0097080C, width);
		utils::hook::set<float>(0x009796F4, width);
		utils::hook::set<float>(0x00979A34, width);
		utils::hook::set<float>(0x00979A7C, width);
		utils::hook::set<float>(0x00979A9C, width);
		utils::hook::set<float>(0x00979DC4, width);
		utils::hook::set<float>(0x00979E00, width);
		utils::hook::set<float>(0x0097A170, width);
		utils::hook::set<float>(0x0097A1AC, width);
		utils::hook::set<float>(0x0097A1B8, width);
		utils::hook::set<float>(0x0097A6F4, width);
		utils::hook::set<float>(0x0097A740, width);
		utils::hook::set<float>(0x0097BBB0, width);
		utils::hook::set<float>(0x0097EBBC, width);
		utils::hook::set<float>(0x0097EC1C, width);
		utils::hook::set<float>(0x0097EC4C, width);
		utils::hook::set<float>(0x009A6900, width);
		utils::hook::set<float>(0x009A6908, width);
		utils::hook::set<float>(0x009B8DC4, width);
		utils::hook::set<float>(0x009B8DDC, width);
		utils::hook::set<float>(0x00A18FF2, width);
		utils::hook::set<float>(0x00B44406, width);
		utils::hook::set<float>(0x00409F48 + 0x3, width);
		utils::hook::set<float>(0x0040A028 + 0x3, width);
		utils::hook::set<float>(0x0040A048 + 0x3, width);
		utils::hook::set<float>(0x0040C442 + 0x3, width);
		utils::hook::set<float>(0x0040C466 + 0x3, width);
		utils::hook::set<float>(0x0040C488 + 0x3, width);
		utils::hook::set<float>(0x00453803 + 0x5, width);
		utils::hook::set<float>(0x00453817 + 0x5, width);
		utils::hook::set<float>(0x00483272 + 0x5, width);
		utils::hook::set<float>(0x004EB4A4 + 0x5, width);
		utils::hook::set<float>(0x004EB4EA + 0x5, width);
		utils::hook::set<float>(0x004EC2CB + 0x5, width);
		utils::hook::set<float>(0x004EF58C + 0x5, width);
		utils::hook::set<float>(0x004EF596 + 0x5, width);
		utils::hook::set<float>(0x00502D79 + 0x4, width);
		utils::hook::set<float>(0x005BC908 + 0x5, width);
		utils::hook::set<float>(0x005BD77D + 0x5, width);
		utils::hook::set<float>(0x005BDB83 + 0x5, width);
		utils::hook::set<float>(0x007126AB + 0x1, width);
		utils::hook::set<float>(0x00719AAE + 0x3, width);
		utils::hook::set<float>(0x00719ACB + 0x3, width);
		utils::hook::set<float>(0x00719C58 + 0x4, width);
		utils::hook::set<float>(0x00719C67 + 0x4, width);
		utils::hook::set<float>(0x00719D40 + 0x4, width);
		utils::hook::set<float>(0x00719D4F + 0x4, width);
		utils::hook::set<float>(0x00719E80 + 0x4, width);
		utils::hook::set<float>(0x00721E68 + 0x4, width);
		utils::hook::set<float>(0x00721E76 + 0x4, width);
		utils::hook::set<float>(0x00721F26 + 0x4, width);
		utils::hook::set<float>(0x00721FB9 + 0x4, width);
		utils::hook::set<float>(0x0077F2EA + 0x3, width);
		utils::hook::set<float>(0x0077F30A + 0x3, width);
		utils::hook::set<float>(0x0077F383 + 0x3, width);
		utils::hook::set<float>(0x0077F3A4 + 0x3, width);
		utils::hook::set<float>(0x0078563E + 0x3, width);
		utils::hook::set<float>(0x007856AE + 0x3, width);
		utils::hook::set<float>(0x00785BCF + 0x3, width);
		utils::hook::set<float>(0x007888A3 + 0x3, width);
		utils::hook::set<float>(0x007888C3 + 0x3, width);
		utils::hook::set<float>(0x00788EA3 + 0x3, width);
		utils::hook::set<float>(0x00788EC3 + 0x3, width);
		utils::hook::set<float>(0x00804EDA + 0x4, width);
		utils::hook::set<float>(0x008051B4 + 0x4, width);

		//Modify height
		utils::hook::set<float>(0x008F9A98, height);
		utils::hook::set<float>(0x008F9AC8, height);
		utils::hook::set<float>(0x008FFB80, height);
		utils::hook::set<float>(0x00909164, height);
		utils::hook::set<float>(0x0091D8B8, height);
		utils::hook::set<float>(0x0091DA7C, height);
		utils::hook::set<float>(0x0091FBEC, height);
		utils::hook::set<float>(0x0091FC50, height);
		utils::hook::set<float>(0x0091FC70, height);
		utils::hook::set<float>(0x0091FF90, height);
		utils::hook::set<float>(0x00920160, height);
		utils::hook::set<float>(0x0096E534, height);
		utils::hook::set<float>(0x0096E544, height);
		utils::hook::set<float>(0x0096F5D8, height);
		utils::hook::set<float>(0x0096F698, height);
		utils::hook::set<float>(0x0096FF5C, height);
		utils::hook::set<float>(0x0096FFBC, height);
		utils::hook::set<float>(0x009706C8, height);
		utils::hook::set<float>(0x00970808, height);
		utils::hook::set<float>(0x00979A28, height);
		utils::hook::set<float>(0x00979A70, height);
		utils::hook::set<float>(0x00979A8C, height);

		utils::hook::set<float>(0x00979DC8, height);
		utils::hook::set<float>(0x00979DFC, height);
		utils::hook::set<float>(0x0097A16C, height);
		utils::hook::set<float>(0x0097A1A8, height);
		utils::hook::set<float>(0x0097A1BC, height);
		utils::hook::set<float>(0x0097A6F0, height);
		utils::hook::set<float>(0x0097A73C, height);
		utils::hook::set<float>(0x0097EBB8, height);
		utils::hook::set<float>(0x0097EC18, height);
		utils::hook::set<float>(0x0097EC48, height);
		utils::hook::set<float>(0x009A690C, height);
		utils::hook::set<float>(0x009A6914, height);
		utils::hook::set<float>(0x009C94C0, height);
		utils::hook::set<float>(0x009C94D8, height);
		utils::hook::set<float>(0x009C94D8, height);
		utils::hook::set<float>(0x009C94E8, height);
		utils::hook::set<float>(0x009FF09C, height);
		utils::hook::set<float>(0x009FF0CC, height);
		utils::hook::set<float>(0x009FF0FC, height);
		utils::hook::set<float>(0x009FF12C, height);
		utils::hook::set<float>(0x00A0D542, height);
		utils::hook::set<float>(0x00A113E8, height);
		utils::hook::set<float>(0x00B343D6, height);

		
		utils::hook::set<float>(0x0040A013 + 0x3, height);
		utils::hook::set<float>(0x0040A033 + 0x3, height);

		utils::hook::set<float>(0x00453821 + 0x5, height);
		utils::hook::set<float>(0x00453835 + 0x5, height);
		utils::hook::set<float>(0x004EB4AE + 0x5, height);
		utils::hook::set<float>(0x004EB4F4 + 0x5, height);
		utils::hook::set<float>(0x004EC2E3 + 0x5, height);
		utils::hook::set<float>(0x00502D81 + 0x5, height);
		utils::hook::set<float>(0x007126A4 + 0x1, height);
		utils::hook::set<float>(0x00719AD6 + 0x3, height);
		utils::hook::set<float>(0x00719AF3 + 0x3, height);
		utils::hook::set<float>(0x00719C04 + 0x4, height);
		utils::hook::set<float>(0x00719C12 + 0x4, height);
		utils::hook::set<float>(0x00719C75 + 0x4, height);
		utils::hook::set<float>(0x00719C86 + 0x4, height);
		utils::hook::set<float>(0x0071A223 + 0x3, height);
		utils::hook::set<float>(0x0077F3AF + 0x3, height);
		utils::hook::set<float>(0x0077F3CF + 0x3, height);
		utils::hook::set<float>(0x00785645 + 0x3, height);
		utils::hook::set<float>(0x0078567D + 0x3, height);
		utils::hook::set<float>(0x007856B5 + 0x3, height);
		utils::hook::set<float>(0x007856FF + 0x5, height);
		utils::hook::set<float>(0x00785BD6 + 0x3, height);
		utils::hook::set<float>(0x00785C0E + 0x3, height);
		utils::hook::set<float>(0x00785C46 + 0x3, height);
		utils::hook::set<float>(0x007888CE + 0x3, height);
		utils::hook::set<float>(0x007888EE + 0x3, height);
		utils::hook::set<float>(0x00788ECE + 0x3, height);
		utils::hook::set<float>(0x00788EEE + 0x3, height);
		utils::hook::set<float>(0x00804EEE + 0x5, height);
		utils::hook::set<float>(0x008051C8 + 0x5, height);
	}
}