#pragma once

class settings
{
public:
	struct vector2
	{
		int x, y;
	};

	static void init();
	static void load();

	static vector2 resolution;
	static int bpp;
	static bool fullscreen;
	static float sensitivity;

private:
	static void create();
};