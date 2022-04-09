#include "io.hpp"

namespace utils
{
	void io::init()
	{
		io::delete_path("GameGuard");
	}

	bool io::write_file(const std::string& file, const std::string& data, const bool append)
	{
		const auto pos = file.find_last_of("/\\");
		if (pos != std::string::npos)
		{
			io::create(file.substr(0, pos));
		}

		std::ofstream stream(
			file, std::ios::binary | std::ofstream::out | (append ? std::ofstream::app : 0));

		if (stream.is_open())
		{
			stream.write(data.data(), data.size());
			stream.close();
			return true;
		}

		return false;
	}

	bool io::exists(const std::string& path)
	{
		return std::filesystem::exists(path);
	}

	void io::create(const std::string& path)
	{
		std::filesystem::create_directories(path);
	}

	std::string io::read_file(const std::string& file)
	{
		std::string data;
		read_file(file, &data);
		return data;
	}

	bool io::read_file(const std::string& file, std::string* data)
	{
		if (!data) return false;
		data->clear();

		if (io::exists(file))
		{
			std::ifstream stream(file, std::ios::in | std::ios::binary);
			if (!stream.is_open()) return false;

			stream.seekg(0, std::ios::end);
			const std::streamsize size = stream.tellg();
			stream.seekg(0, std::ios::beg);

			if (size > -1)
			{
				data->resize(static_cast<uint32_t>(size));
				stream.read(const_cast<char*>(data->data()), size);
				stream.close();
				return true;
			}
		}

		return false;
	}

	void io::delete_file(const std::string& file)
	{
		std::filesystem::remove(file);
	}

	void io::delete_path(const std::string& path)
	{
		std::filesystem::remove_all(path);
	}

	void io::rename_file(const std::string& file, const std::string& new_name)
	{
		std::filesystem::rename(file, new_name);
	}

	size_t io::file_size(const std::string& file)
	{
		if (io::exists(file))
		{
			std::ifstream stream(file, std::ios::binary);

			if (stream.good())
			{
				stream.seekg(0, std::ios::end);
				return static_cast<size_t>(stream.tellg());
			}
		}

		return 0;
	}
}
