#pragma once

class input
{
public:
	enum class method : int
	{
		KEYBOARD = 0,
		MOUSE,
		CONTROLLER
	};

	static void init();
	static void update();
	static WORD camera;
	static method ctrl_method;

	class mouse
	{
	public:
		static int x_pos;
		static int y_pos;
	};

	class joystick
	{
	public:
		static SDL_Joystick* joy;
	};
};