#include "hook.hpp"

namespace utils
{
	void hook::nop(std::uint32_t address, std::uint32_t size)
	{
		for (auto i = 0u; i < size; ++i)
		{
			hook::set<hook::instr>(address + i, instr::nop);
		}
	}

	void hook::write(std::uint32_t address, const std::initializer_list<std::uint8_t>& bytes)
	{
		std::memcpy(reinterpret_cast<std::uint8_t*>(address), bytes.begin(), bytes.size());
	}

	void hook::write_string(std::uint32_t address, const std::string& string)
	{
		std::strcpy(reinterpret_cast<char*>(address), &string[0]);
	}

	void hook::retn(std::uint32_t address)
	{
		utils::hook::set<hook::instr>(address, instr::retn);
	}

    std::uint8_t* hook::pattern(void* module, const char* signature)
    {
        static auto pattern_to_byte = [](const char* pattern) {
            auto bytes = std::vector<int>{};
            auto start = const_cast<char*>(pattern);
            auto end = const_cast<char*>(pattern) + strlen(pattern);

            for (auto current = start; current < end; ++current) {
                if (*current == '?') {
                    ++current;
                    if (*current == '?')
                        ++current;
                    bytes.push_back(-1);
                }
                else {
                    bytes.push_back(strtoul(current, &current, 16));
                }
            }
            return bytes;
        };

        auto dosHeader = (PIMAGE_DOS_HEADER)module;
        auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

        auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
        auto patternBytes = pattern_to_byte(signature);
        auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

        auto s = patternBytes.size();
        auto d = patternBytes.data();

        for (auto i = 0ul; i < sizeOfImage - s; ++i) {
            bool found = true;
            for (auto j = 0ul; j < s; ++j) {
                if (scanBytes[i + j] != d[j] && d[j] != -1) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return &scanBytes[i];
            }
        }
        return nullptr;
    }
}
