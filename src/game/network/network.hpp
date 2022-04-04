#pragma once

#include "../stdafx.hpp"

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