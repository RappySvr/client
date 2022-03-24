#pragma once

#include <initializer_list>
#include <cstdint>
#include <chrono>

#include <Windows.h>
#include <DbgHelp.h>
#include <stdio.h>
#include <stdlib.h>

namespace utils
{
	class exception final
	{
	public:
		static void init(const char* prefix);
		static void purecall_handler();

	private:
		static long __stdcall exception_handler(::EXCEPTION_POINTERS* ex);
		static long __stdcall exception_filter(::EXCEPTION_POINTERS* ex);

		static std::initializer_list<std::uint32_t> safe_exceptions_;
		static std::uint32_t dump_type_;
		static const char* dump_prefix_;
	};
}