#include "../stdafx.hpp"
#include "settings.hpp"
#include "../input/input.hpp"

#include <utils/io/io.hpp>
#include <utils/ini/IniReader.h>
#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>


void settings::init()
{
	if (!utils::io::exists("rappylive/psobb.ini"))
	{
		settings::create();
	}

	settings::load_ini();
}

void settings::load_ini()
{
	CIniReader config("rappylive/psobb.ini");

	const char* language = config.ReadString("general", "language", "English");
	if (!strcmp(language, "English"))
	{
		settings::lang = settings::language::ENGLISH;
	}
	else if (!strcmp(language, "Japanese"))
	{
		settings::lang = settings::language::JAPANESE;
	}
	else if (!strcmp(language, "French"))
	{
		settings::lang = settings::language::FRENCH;
	}
	else if (!strcmp(language, "Spanish"))
	{
		settings::lang = settings::language::SPANISH;
	}
	else if (!strcmp(language, "German"))
	{
		settings::lang = settings::language::GERMAN;
	}


	const char* method = config.ReadString("controls", "method", "Keyboard");

	if (!strcmp(method, "Keybaord"))
	{
		input::ctrl_method = input::method::KEYBOARD;
	}
	else if (!strcmp(method, "Mouse"))
	{
		input::ctrl_method = input::method::MOUSE;
	}
	else if (!strcmp(method, "Controller"))
	{
		input::ctrl_method = input::method::CONTROLLER;
	}

	settings::sensitivity = config.ReadFloat("graphics", "controls", 1.0f);

	settings::fullscreen = config.ReadBoolean("graphics", "fullscreen", false);
	settings::resolution.x = config.ReadFloat("graphics", "width", 800.0f);
	settings::resolution.y = config.ReadFloat("graphics", "height", 600.0f);

	settings::bpp = config.ReadInteger("graphics", "bpp", 32);
}

void settings::load()
{
	*(DWORD*)&*(DWORD*)(0x00A46C48) = 0;
	*((DWORD*)&*(DWORD*)(0x00A46C48) + 1) = 0;
	*((DWORD*)&*(DWORD*)(0x00A46C48) + 2) = 0;
	*((DWORD*)&*(DWORD*)(0x00A46C48) + 3) = 0;
	*((DWORD*)&*(DWORD*)(0x00A46C48) + 4) = 0;
	*((DWORD*)&*(DWORD*)(0x00A46C48) + 5) = 0;
	*((DWORD*)&*(DWORD*)(0x00A46C48) + 6) = 0;
	*((DWORD*)&*(DWORD*)(0x00A46C48) + 7) = 0;
	*((DWORD*)&*(DWORD*)(0x00A46C48) + 8) = 0;
	*((DWORD*)&*(DWORD*)(0x00A46C48) + 9) = 0;
	*((DWORD*)&*(DWORD*)(0x00A46C48) + 10) = 0;
	*(&*(DWORD*)(0x00A46C48) + 22) = 0;

	//set settings
	utils::hook::set(0x00A46C48, settings::resolution.x);
	utils::hook::set(0x00A46C4A, settings::resolution.x);
	utils::hook::set(0x00A46C72, !settings::fullscreen);
	utils::hook::set(0x00A46C4C, settings::bpp);
	utils::hook::set(0x00A9CD44, settings::lang);
	utils::hook::return_value(0x00793228, settings::lang);

	//unk
	utils::hook::set(0x00A46C4E, 2);
	utils::hook::set(0x00A46C60, 2);
	utils::hook::set(0x00A46C66, 2);
	utils::hook::set(0x00A46C6A, 2);
	utils::hook::set(0x00A46C50, 0);
	utils::hook::set(0x00A46C54, 0);
	utils::hook::set(0x00A46C56, 0);
	utils::hook::set(0x00A46C5A, 0);
	utils::hook::set(0x00A46C5E, 0);
	utils::hook::set(0x00A46C62, 0);
	utils::hook::set(0x00A46C64, 0);
	utils::hook::set(0x00A46C68, 0);
	utils::hook::set(0x00A46C6C, 2);
}

void settings::create()
{
	CIniReader config("rappylive/psobb.ini");

	config.WriteString("general", "language", "English");

	config.WriteString("controls", "method", "Keyboard");
	config.WriteFloat("controls", "sensitivity", 1.0);

	config.WriteBoolean("graphics", "fullscreen", false);
	config.WriteInteger("graphics", "width", 800);
	config.WriteInteger("graphics", "height", 600);
	config.WriteInteger("graphics", "bpp", 32);
}

settings::vector2 settings::resolution{ 800.0f, 600.0f };
bool settings::fullscreen = false;
float settings::sensitivity = 1.0f;
int settings::bpp = 32;
settings::language settings::lang = settings::language::ENGLISH;