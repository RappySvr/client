#include "exception.hpp"

#include <utils/hook/hook.hpp>
#include <utils/format/format.hpp>
#include <utils/utils.hpp>

namespace utils
{
	void exception::init(const char* prefix)
	{
		exception::dump_prefix_ = prefix;

		::AddVectoredExceptionHandler(true, exception::exception_handler);
		::SetUnhandledExceptionFilter(exception::exception_filter);

		::_set_purecall_handler(exception::purecall_handler);
	}

	void exception::purecall_handler()
	{
		utils::hook::set<std::uint32_t>(0x00000000, 0xDECEA5ED);
	}

	long __stdcall exception::exception_handler(::EXCEPTION_POINTERS* ex)
	{
		return utils::any_of(exception::safe_exceptions_, [ex](const auto value) -> bool
		{
			return value == ex->ExceptionRecord->ExceptionCode;
		}) ? EXCEPTION_CONTINUE_EXECUTION : EXCEPTION_CONTINUE_SEARCH;
	}

	long __stdcall exception::exception_filter(::EXCEPTION_POINTERS* ex)
	{
		if (!::IsDebuggerPresent())
		{
			const auto handle = ::CreateFileA(&utils::format::va("%s\\log\\%s-%u-%llu.dmp",
				__argv[2], exception::dump_prefix_, 0, std::time(nullptr))[0], GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

			auto info = ::MINIDUMP_EXCEPTION_INFORMATION{ ::GetCurrentThreadId(), ex, false };

			::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), handle,
				static_cast<::MINIDUMP_TYPE>(exception::dump_type_), &info, nullptr, nullptr);

			MessageBoxA(nullptr, &utils::format::va(
				"An exception occurred (0x%08X at 0x%p) and PSO:BB needs to close.\n"
				"Please send the generated crash dump to the developers.",
				ex->ExceptionRecord->ExceptionCode, ex->ExceptionRecord->ExceptionAddress)[0], "RappyLive", 0);
			exit(0);
		}

		return EXCEPTION_CONTINUE_SEARCH;
	}

	std::initializer_list<std::uint32_t> exception::safe_exceptions_
	{
		STATUS_INTEGER_OVERFLOW,
		STATUS_FLOAT_OVERFLOW,
		DBG_PRINTEXCEPTION_C,
		STATUS_BREAKPOINT,
	};

	std::uint32_t exception::dump_type_
	{
		::MiniDumpIgnoreInaccessibleMemory |
		::MiniDumpWithProcessThreadData |
		::MiniDumpWithUnloadedModules |
		::MiniDumpWithFullMemoryInfo |
		::MiniDumpWithThreadInfo |
		::MiniDumpWithHandleData |
		::MiniDumpWithDataSegs |
		::MiniDumpWithCodeSegs |
		::MiniDumpScanMemory
	};

	const char* exception::dump_prefix_;
}