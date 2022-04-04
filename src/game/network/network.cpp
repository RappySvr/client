#include "network.hpp"

#include <thread>
using namespace std::literals;

#include <httplib.h>

//news
auto news::update_news() -> void
{
	httplib::Client cli(IP_ADDR);

	if (auto res = cli.Get("/client_news"))
	{
		if (res->status == 200)
		{
			news::news_text = res->body;
		}
		else
		{
			news::news_text = "Unable to retrieve latest news...";
		}
	}
}

bool news::states::once = false;
std::string news::news_text;
//

//event

void event::update_song()
{
	httplib::Client cli(IP_ADDR);

	if (auto res = cli.Get("/song"))
	{
		if (res->status == 200)
		{
			event::song_name = res->body;
		}
		else
		{
			event::song_name = "title.adx";
		}
	}
}

std::string event::song_name;
//