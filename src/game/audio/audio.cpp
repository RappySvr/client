#include "audio.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>


static utils::function<char* __cdecl(const char*)> play_song_;
char* __cdecl play_song(const char* name)
{
	return play_song_(name);
}

void audio::init()
{
	play_song_ = utils::hook::detour(0x00814AFC, play_song, 6);
}