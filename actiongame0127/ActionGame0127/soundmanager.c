//Header file related to the implementation
#include "soundmanager.h"

//Third-party headers
#include "WarpEngine.h"

static SoundManager soundSystem;

void SoundManager_Create()
{
	int i = 0;

	FMOD_System_Create(&soundSystem.m_system);
	FMOD_System_Init(soundSystem.m_system, 2, FMOD_INIT_NORMAL, 0);
	for (i = 0; i < MAX_SOUND_SIZE; ++i)
		soundSystem.m_sound[i] = NULL;
	for (i = 0; i < MAX_CHANNEL_SIZE; ++i)
		soundSystem.m_channel[i] = NULL;
	soundSystem.soundpoolSize = 0;
	soundSystem.channelpoolSize = 0;
}
void SoundManager_LoadSound(char* filename)
{
	FMOD_System_CreateSound(soundSystem.m_system, filename,
		FMOD_DEFAULT, 0, &soundSystem.m_sound[soundSystem.soundpoolSize++]);
}
void SoundManager_PlaySound(SoundName name)
{
	FMOD_System_PlaySound(soundSystem.m_system,
		FMOD_CHANNEL_FREE, soundSystem.m_sound[name], 
		FALSE, &soundSystem.m_channel[name]);
}

void SoundManager_Delete()
{
	int i = 0;
	for (i = 0; i < MAX_SOUND_SIZE; ++i)
	{
		if (soundSystem.m_sound[i])
			FMOD_Sound_Release(soundSystem.m_sound[i]);
	}
	if (soundSystem.m_system)
		FMOD_System_Release(soundSystem.m_system);
}