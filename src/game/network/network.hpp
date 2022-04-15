#pragma once

#include "../stdafx.hpp"
#include <winsock2.h>

class news final
{
public:
	static void update_news();
	static std::string news_text;

	class states final
	{
	public:
		static bool once;
	};
};

class event final
{
public:
	static void update_song();
	static std::string song_name;
};

class network final
{
public:
	static void init();
	static const char* ip;
};