#include "audio.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>


static utils::function<void __cdecl(const char*)> play_sound_;
void __cdecl play_sound(const char* name)
{
	return play_sound_(name);
}

static utils::function<void __cdecl(const char*)> get_song_file_;
void __cdecl get_song_file(const char* name)
{
	return;
	return get_song_file_(name);
}

void audio::init()
{
	play_sound_ = utils::hook::detour(0x00814AFC, play_sound, 6);
	get_song_file_ = utils::hook::detour(0x0077BCDC, get_song_file, 7);
}