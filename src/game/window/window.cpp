#include "window.hpp"

#include <utils/hook/hook.hpp>
#include <utils/pattern/pattern.hpp>
#include <utils/console/console.hpp>

float window::resolution_x = 640.0f;
float window::resolution_y = 480.0f;

//DONE : 0x004829E0
int window::get_resolution_x()
{
	//return *(int*)(0x00A46C48);
	return window::resolution_x;
}

//DONE : 0x004829E8
int window::get_resolution_y()
{
	//return *(int*)(0x00A46C4A);
	return window::resolution_y;
}

//DONE : 0x004829F0
int window::get_bpp()
{
	return *(int*)(0x00A46C4C);
}

//DONE : 0x00482AA0
int window::get_window_mode()
{
	return *(int*)(0x00A46C72);
}

void window::widescreen(float res_x, float res_y)
{
	window::resolution_x = res_x;
	window::resolution_y = res_y;

	//X
	auto pattern_x = hook::pattern("00 00 20 44");
	pattern_x.for_each_result([](hook::pattern_match i)
	{
		*(float*)(i.get<std::uint32_t>()) = window::resolution_x;
	});

	//Y
	auto pattern_y = hook::pattern("00 00 F0 43");
	pattern_y.for_each_result([](hook::pattern_match i)
	{
		*(float*)(i.get<std::uint32_t>()) = window::resolution_y;
	});

	pattern_x.clear();
	pattern_y.clear();
}