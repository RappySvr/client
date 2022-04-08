#pragma once

class input
{
public:
	static void init();
	static void update();

	class mouse
	{
	public:
		static int x_pos;
		static int y_pos;
	};
};