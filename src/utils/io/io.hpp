#pragma once

#include <string>
#include <filesystem>
#include <fstream>

namespace utils
{
	class io final
	{
		public:
			static void init();
			static bool write_file(const std::string& file, const std::string& data, bool append = false);
			static bool read_file(const std::string& file, std::string* data);
			static void delete_file(const std::string& file);
			static void delete_path(const std::string& path);
			static void rename_file(const std::string& file, const std::string& new_name);
			static std::string read_file(const std::string& file);
			size_t file_size(const std::string& file);
			static bool exists(const std::string& path);
			static void create(const std::string& path);
	};
}
