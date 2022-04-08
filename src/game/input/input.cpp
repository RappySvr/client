#include "input.hpp"
#include "../window/window.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>

SDL_Event evt;

void input::update()
{
	while (SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
			break;

		case SDL_MOUSEMOTION:
			mouse::x_pos += evt.motion.xrel;
			mouse::y_pos += evt.motion.yrel;
			break;
		}
	}
}

void input::init()
{
	mouse::x_pos = (int)std::floor(window::resolution_x / 2);
	mouse::y_pos = (int)std::floor(window::resolution_y / 2);
}

int input::mouse::x_pos;
int input::mouse::y_pos;
