#pragma once

#include <Windows.h>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <fstream>
#include <functional>

template <typename T> inline std::function<T> call(std::uintptr_t callback)
{
    return std::function<T>(reinterpret_cast<T*>(callback));
}

inline auto replace(std::uint32_t address, std::uint32_t function) -> void
{
    *reinterpret_cast<std::uint8_t*>(address) = 0xE9;
    *reinterpret_cast<std::uint32_t*>(address + 1) = (function - address - 5);
}

void load(const char* bin_name);
int entry_point(uint32_t address);
void replace_func(uint32_t address, uint32_t function);