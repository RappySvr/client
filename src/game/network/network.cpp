#include "network.hpp"

#include <thread>
using namespace std::literals;

#include <httplib.h>

#include <utils/format/format.hpp>

//news
auto news::update_news() -> void
{
	httplib::Client cli(WEB_URL);

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
	httplib::Client cli(WEB_URL);

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

//network
void network::init()
{
    return;
    WSADATA wsaData;
    int iResult;

    DWORD dwError;
    int i = 0;

    struct hostent* remoteHost;
    char* host_name;
    struct in_addr addr;

    char** pAlias;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != 0)
    {
        MessageBoxA(nullptr, "Failed to open network socket!", "Rappy.Live", 0);
        exit(0);
    }

    remoteHost = gethostbyname(WEB_URL);

    if (remoteHost == 0)
    {
        dwError = WSAGetLastError();
        if (dwError != 0)
        {
            MessageBoxA(nullptr, &utils::format::va("Network socket failed with error code %ld", dwError)[0], "Rappy.Live", 0);
            exit(0);
        }
    }
    else
    {
        i = 0;
        if (remoteHost->h_addrtype == AF_INET)
        {
            while (remoteHost->h_addr_list[i] != 0)
            {
                addr.s_addr = *(u_long*)remoteHost->h_addr_list[i++];
                network::ip = inet_ntoa(addr);
            }
        }
    }
}

const char* network::ip = WEB_URL;
//