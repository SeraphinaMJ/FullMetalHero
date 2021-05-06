#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

//Third-party headers
#include <fmod.h>
#include <fmod_errors.h>

#define MAX_SOUND_SIZE 10
#define MAX_CHANNEL_SIZE 100

typedef enum { BGM_1 = 0, SHOOT_SOUND = 1}SoundName;

typedef struct SoundManager{
	FMOD_SYSTEM* m_system;
	FMOD_SOUND* m_sound[MAX_SOUND_SIZE];
	int soundpoolSize;
	FMOD_CHANNEL* m_channel[MAX_CHANNEL_SIZE];
	int channelpoolSize;
}SoundManager;

void SoundManager_Create();
void SoundManager_LoadSound(char* filename);
void SoundManager_PlaySound(SoundName name);
void SoundManager_Delete();
#endif