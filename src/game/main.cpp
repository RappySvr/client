#include <loader/loader.hpp>

#include "patches/patches.hpp"

#include <utils/exception/exception.hpp>

int __cdecl main(int argc, char* argv[])
{
	utils::exception::init("client");
	load("psobb.exe");
	patches::init();
	return entry_point(0x00B60000);
}