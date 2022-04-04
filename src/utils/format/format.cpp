#include "format.hpp"

namespace utils
{
	std::string format::va(const char* fmt, ...)
	{
		auto va = ::va_list();

		va_start(va, fmt);

		char result[512]{};

		std::vsprintf(result, fmt, va);

		return std::string(result);
	}

	wchar_t* format::c_to_w(const char* in)
	{
		const size_t size = strlen(in) + 1;
		wchar_t* out = new wchar_t[size];
		mbstowcs(out, in, size);

		return out;
	}

	std::string format::replace(const std::string& orig, const std::string& fnd, const std::string& repl)
	{
		std::string ret = orig;
		size_t pos = 0;
		while (true)
		{
			pos = ret.find(fnd, pos);
			if (pos == std::string::npos) break;

			ret.replace(pos, pos + fnd.size(), repl);
			pos += repl.size();
		}
		return ret;
	}

	auto format::hash_string(const std::string& string) -> std::uint32_t
	{
		std::uint32_t result = 0xFFFFFFFF;
		for(auto i = 0; i < string.length(); i++)
		{
			result = (result * 0x21);
			result += string[i];
		}
		return result;
	}

	auto format::split(std::string string, const std::string& delimiter) -> std::vector<std::string>
	{
		auto result = std::vector<std::string>();
		auto position = 0u;

		while ((position = string.find(delimiter)) != std::string::npos)
		{
			result.emplace_back(string.substr(0, position));
			string.erase(0, position + delimiter.size());
		}

		result.emplace_back(string);

		return result;
	}
}
