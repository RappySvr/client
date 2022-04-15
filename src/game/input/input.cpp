#include "../stdafx.hpp"
#include "input.hpp"
#include "../window/window.hpp"
#include "../settings/settings.hpp"

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

	switch (input::ctrl_method)
	{
		case input::method::CONTROLLER:
		{
			int16_t motion = SDL_JoystickGetAxis(joystick::joy, 2);
			WORD deadzone = 5000;
			float sensitivity = settings::sensitivity;
			int16_t step = (int16_t)std::ceil((1000 * sensitivity) * (motion / 32767.0f));

			if (motion > deadzone || motion < -deadzone)
			{
				input::camera += step;
			}
		}
		break;

		case input::method::MOUSE:
		{
			input::camera = -(WORD)std::ceil(input::mouse::x_pos * (20 * settings::sensitivity));
		}
		break;
	}
}

void input::init()
{
	joystick::joy = SDL_JoystickOpen(0);
	PRINT_DEBUG("Joystick: %s", SDL_JoystickName(joystick::joy));

	mouse::x_pos = (int)std::floor(settings::resolution.x / 2);
	mouse::y_pos = (int)std::floor(settings::resolution.y / 2);
}

int input::mouse::x_pos;
int input::mouse::y_pos;

SDL_Joystick* input::joystick::joy;

WORD input::camera;
input::method input::ctrl_method = input::method::KEYBOARD;