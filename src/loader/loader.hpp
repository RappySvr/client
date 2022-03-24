#pragma once

#include <Windows.h>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <fstream>
#include <functional>

void load(const char* bin_name);
int entry_point(uint32_t address);
void replace_func(uint32_t address, uint32_t function);