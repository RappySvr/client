#include <loader/loader.hpp>

#include "patches/patches.hpp"

#include <utils/exception/exception.hpp>
#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>

#include "window/window.hpp"

namespace rl
{
	static utils::function<void __cdecl()> load_settings_;
	void __cdecl load_settings()
	{
		//Resolution
        utils::hook::set<std::int16_t>(0x00A46C48, 1280);
        utils::hook::set<std::int16_t>(0x00A46C4A, 720);

		//BPP
        utils::hook::set<std::int16_t>(0x00A46C4C, 32);

		utils::hook::set<WORD>(0x00A46C4E, 2);

		utils::hook::set<DWORD>(0x00A46C6E, 1);
		
		utils::hook::set<WORD>(0x00A46C60, 2);
		utils::hook::set<WORD>(0x00A46C66, 2);
		utils::hook::set<WORD>(0x00A46C6A, 2);

		utils::hook::set<WORD>(0x00A46C50, 0);

		//Vsync
		utils::hook::set<WORD>(0x00A46C54, 0);
		utils::hook::set<DWORD>(0x00A46C5A, 0);

		utils::hook::set<DWORD>(0x00A46C56, 0);
		utils::hook::set<WORD>(0x00A46C5E, 0);
		utils::hook::set<WORD>(0x00A46C62, 0);
		utils::hook::set<WORD>(0x00A46C64, 0);
		utils::hook::set<WORD>(0x00A46C68, 0);
		utils::hook::set<WORD>(0x00A46C6C, 2);

		//Window mode
		utils::hook::set<int>(0x00A46C72, 1);
	}

	void init()
	{
		patches::init();
		load_settings_ = utils::hook::detour(0x00482EAC, load_settings, 5);
		window::init();
	}
}

int __cdecl main(int argc, char* argv[])
{
	utils::console::init();
	utils::exception::init("client");
	load("psobb.exe");
	rl::init();
	return entry_point(0x00B60000);
}