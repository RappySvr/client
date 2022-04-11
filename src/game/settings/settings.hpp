#pragma once

class settings
{
public:
	struct vector2
	{
		float x, y;
	};

	static enum class language : int
	{
		JAPANESE,
		ENGLISH,
		GERMAN,
		FRENCH,
		SPANISH,
	};

	static void init();
	static void load();
	static void load_ini();

	static vector2 resolution;
	static int bpp;
	static bool fullscreen;
	static float sensitivity;
	static language lang;

private:
	static void create();
};