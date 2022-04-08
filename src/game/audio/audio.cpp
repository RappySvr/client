#include "audio.hpp"

#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>


static utils::function<void (const char*)> play_sound_;
void audio::play_sound(const char* name)
{
	return play_sound_(name);
}

void audio::init()
{
	play_sound_ = utils::hook::detour(0x00814AFC, audio::play_sound, 6);
}