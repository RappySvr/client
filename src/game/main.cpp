#include <loader/loader.hpp>

#include "patches/patches.hpp"

#include <utils/exception/exception.hpp>
#include <utils/hook/hook.hpp>

int __cdecl main(int argc, char* argv[])
{
	utils::exception::init("client");
	load("psobb.exe");
	utils::hook::return_value(0x004829E0, 1280);
	utils::hook::return_value(0x004829E8, 720);
	patches::init();
	return entry_point(0x00B60000);
}