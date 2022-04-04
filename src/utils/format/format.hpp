#pragma once

#include <string>
#include <vector>

#include <stdarg.h>

namespace utils
{
	class format final
	{
		public:
			static std::string va(const char* fmt, ...);
			static std::string replace(const std::string& orig, const std::string& fnd, const std::string& repl);
			static auto hash_string(const std::string& string) -> std::uint32_t;
			static wchar_t* c_to_w(const char* in);

			static auto split(std::string string, const std::string& delimiter) -> std::vector<std::string>;

			template<typename S> static auto stoi(const char* string, S d) -> S
			{
				char* end;

				const auto result = static_cast<S>(std::strtol(string, &end, 0));

				if (*string == '\0' || *end != '\0')
				{
					return d;
				}

				return result;
			}

	};
}