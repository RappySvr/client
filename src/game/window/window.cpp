#include "../stdafx.hpp"
#include "window.hpp"

#include <utils/hook/hook.hpp>
#include <utils/pattern/pattern.hpp>
#include <utils/console/console.hpp>

const float _4_3 = 4.0f/3.0f;
const float _16_9 = 16.0f / 9.0f;
const float _16_10 = 16.0f/10.0f;

float window::resolution_x = 640.0f;
float window::resolution_y = 480.0f;
float window::ratio = _4_3;

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
	window::ratio = window::resolution_x / window::resolution_y;

	if (window::ratio == _16_9)
	{
		utils::hook::set(0x0070F757 + 0x3, 0.75f);
		utils::hook::set(0x0071093C + 0x3, 0.75f);
		utils::hook::set(0x0071B752 + 0x3, 0.75f);
		utils::hook::set(0x00725DDA + 0x6, 0.75f);
		utils::hook::set(0x00728B40 + 0x3, 0.75f);
		utils::hook::set(0x00731597 + 0x3, 0.75f);
		utils::hook::set(0x00731D18 + 0x3, 0.75f);
		utils::hook::set(0x0073A4A8 + 0x3, 0.75f);
		utils::hook::set(0x0073EFD8 + 0x3, 0.75f);
		utils::hook::set(0x007575DB + 0x3, 0.75f);
		utils::hook::set(0x007104EE + 0x3, 0.45f);
	}

	int num = 0;

	//X
	auto pattern_x = hook::pattern("00 00 20 44");
	pattern_x.for_each_result([&num](hook::pattern_match i)
	{
		if (num != 6 && num != 7)
		{
			PRINT_DEBUG_N("0x%p : %f -> %f", i.get<std::uint32_t>(), *(float*)(i.get<std::uint32_t>()), window::resolution_x);
			*(float*)(i.get<std::uint32_t>()) = window::resolution_x;
		}
		num++;
	});

	auto pattern_x_1 = hook::pattern("00 C0 1F 44");
	pattern_x_1.for_each_result([](hook::pattern_match i)
	{
		PRINT_DEBUG_N("0x%p : %f -> %f", i.get<std::uint32_t>(), *(float*)(i.get<std::uint32_t>()), window::resolution_x);
		*(float*)(i.get<std::uint32_t>()) = window::resolution_x;
	});

	//Y
	num = 0;
	auto pattern_y = hook::pattern("00 00 F0 43");
	pattern_y.for_each_result([&num](hook::pattern_match i)
	{
		PRINT_DEBUG_N("0x%p : %f -> %f", i.get<std::uint32_t>(), *(float*)(i.get<std::uint32_t>()), window::resolution_y);
		*(float*)(i.get<std::uint32_t>()) = window::resolution_y;
		num++;
	});

	//Y
	auto pattern_y_1 = hook::pattern("00 80 EF 43");
	pattern_y_1.for_each_result([](hook::pattern_match i)
	{
		PRINT_DEBUG_N("0x%p : %f -> %f", i.get<std::uint32_t>(), *(float*)(i.get<std::uint32_t>()), window::resolution_y);
		*(float*)(i.get<std::uint32_t>()) = window::resolution_y;
	});

	//Ratio
	auto pattern_r = hook::pattern("AB AA AA 3F");
	pattern_r.for_each_result([](hook::pattern_match i)
	{
		PRINT_DEBUG_N("0x%p : %f -> %f", i.get<std::uint32_t>(), *(float*)(i.get<std::uint32_t>()), window::ratio);
		*(float*)(i.get<std::uint32_t>()) = window::ratio;
	});

	/*
	4:3 = 450 100
	16:9 = 770 220
	16:10 = 770 260
	*/

	auto pattern_unk_0 = hook::pattern("00 00 E1 43");
	pattern_unk_0.for_each_result([](hook::pattern_match i)
	{
		float number = 450.0f;
		if (window::ratio == _16_9 || window::ratio == _16_10)
		{
			number = 770.0f;
		}
		PRINT_DEBUG_N("0x%p : %f -> %f", i.get<std::uint32_t>(), *(float*)(i.get<std::uint32_t>()), number);
		*(float*)(i.get<std::uint32_t>()) = number;
	});

	auto pattern_unk_1 = hook::pattern("00 00 C8 42");
	pattern_unk_0.for_each_result([](hook::pattern_match i)
	{
		float number = 100.0f;
		if (window::ratio == _16_9)
		{
			number = 220.0f;
		}
		else if(window::ratio == _16_10)
		{
			number = 260.0f;
		}
		PRINT_DEBUG_N("0x%p : %f -> %f", i.get<std::uint32_t>(), *(float*)(i.get<std::uint32_t>()), number);
		*(float*)(i.get<std::uint32_t>()) = number;
	});

	auto pattern_height_minus_170 = hook::pattern("00 00 9B 43");
	pattern_height_minus_170.for_each_result([](hook::pattern_match i)
	{
		PRINT_DEBUG_N("0x%p : %f -> %f", i.get<std::uint32_t>(), *(float*)(i.get<std::uint32_t>()), window::resolution_y - 170.0f);
		*(float*)(i.get<std::uint32_t>()) = window::resolution_y - 170.0f;
	});

	auto pattern_height_minus_190 = hook::pattern("00 00 91 43");
	pattern_height_minus_190.for_each_result([](hook::pattern_match i)
	{
		PRINT_DEBUG_N("0x%p : %f -> %f", i.get<std::uint32_t>(), *(float*)(i.get<std::uint32_t>()), window::resolution_y - 190.0f);
		*(float*)(i.get<std::uint32_t>()) = window::resolution_y - 190.0f;
	});

	num = 0;
	auto pattern_height_minus_50 = hook::pattern("00 00 D7 43");
	pattern_height_minus_50.for_each_result([&num](hook::pattern_match i)
	{
		if (num == 1 || num == 6)
		{
			PRINT_DEBUG_N("0x%p : %f -> %f", i.get<std::uint32_t>(), *(float*)(i.get<std::uint32_t>()), window::resolution_y - 50.0f);
			*(float*)(i.get<std::uint32_t>()) = window::resolution_y - 50.0f;
		}
		num++;
	});

	num = 0;
	auto pattern_height_minus_149 = hook::pattern("00 80 A5 43");
	pattern_height_minus_149.for_each_result([&num](hook::pattern_match i)
	{
		if(num == 0)
		{
			PRINT_DEBUG_N("0x%p : %f -> %f", i.get<std::uint32_t>(), *(float*)(i.get<std::uint32_t>()), window::resolution_y - 149.0f);
			*(float*)(i.get<std::uint32_t>()) = window::resolution_y - 149.0f;
		}
		num++;
	});

	pattern_x.clear();
	pattern_x_1.clear();
	pattern_y.clear();
	pattern_y_1.clear();
	pattern_r.clear();
	pattern_unk_0.clear();
	pattern_height_minus_170.clear();
	pattern_height_minus_190.clear();
	pattern_height_minus_50.clear();
	pattern_height_minus_149.clear();
}

SDL_Window* window::sdl_window;
SDL_Renderer* window::sdl_renderer;