#pragma once

#include "../settings/settings.hpp"

class window
{
public:
	static float ratio;
	static int get_resolution_x();
	static int get_resolution_y();
	static int get_bpp();
	static int get_window_mode();
	static void init();
	static void widescreen();

	static SDL_Window* sdl_window;
	static SDL_Renderer* sdl_renderer;
};