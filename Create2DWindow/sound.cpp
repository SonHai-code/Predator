

#include "sound.h"


static void loadSounds(void);

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* music;

void initSounds(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);

	music = NULL;

	loadSounds();
}

void loadMusic(string filename)
{
	if (music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename.c_str());
}

void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}

static void loadSounds(void)
{
	sounds[SND_PLAYER_FIRE] = Mix_LoadWAV("D:\\game\\sound\\334227__jradcoolness__laser.ogg");
	sounds[SND_ALIEN_FIRE] = Mix_LoadWAV("D:\\game\\sound\\GunshotSnglHitLig-PE1108102.ogg");
	sounds[SND_PLAYER_DIE] = Mix_LoadWAV("D:\\game\\sound\\245372__quaker540__hq-explosion.ogg");
	sounds[SND_ALIEN_DIE] = Mix_LoadWAV("D:\\game\\sound\\10 Guage Shotgun-SoundBible.com-74120584.ogg");
	sounds[SND_POINTS] = Mix_LoadWAV("D:\\game\\sound\\342749__rhodesmas__notification-01.ogg");
}

