#pragma once

class menus
{
public:
	static void init();
	static void news();

	static void text_to_screen(float pos_x, float pos_y, float a3, int a4, wchar_t* text);

	static float news_pos_x;
	static float news_reset_pos_x;

	static float text_size(wchar_t* text);
};