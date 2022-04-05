#pragma once

class menus
{
public:
	static void init();
	static void news();

	static float news_pos_x;
	static float news_reset_pos_x;

	static float text_size(wchar_t* text);
};