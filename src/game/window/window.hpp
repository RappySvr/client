#pragma once

class window
{
public:
	static float resolution_x;
	static float resolution_y;
	static int get_resolution_x();
	static int get_resolution_y();
	static int get_bpp();
	static int get_window_mode();
	static void widescreen(float res_x, float res_y);
};