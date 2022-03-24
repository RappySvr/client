#include "patches.hpp"

#include <utils/hook/hook.hpp>

void patches::init()
{
	utils::hook::set(0x007085E5 + 0x1, IP_ADDR);
	utils::hook::set(0x00708618 + 0x1, IP_ADDR);
	utils::hook::set(0x007085EB + 0x1, IP_ADDR);
	utils::hook::set(0x007082F1 + 0x1, IP_ADDR);
	utils::hook::set(0x0070833C + 0x1, IP_ADDR);
	utils::hook::set(0x007082F7 + 0x1, IP_ADDR);
	utils::hook::set(0x007085FD + 0x1, IP_ADDR);
	utils::hook::set(0x0070861E + 0x1, IP_ADDR);
	utils::hook::set(0x00708321 + 0x1, IP_ADDR);
	utils::hook::set(0x00708342 + 0x1, IP_ADDR);
}