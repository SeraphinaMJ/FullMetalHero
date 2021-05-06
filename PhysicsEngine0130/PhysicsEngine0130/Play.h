#ifndef PLAY_H
#define PLAY_H
#include "WarpEngine.h"

void PlayLoad(WEGameData* pGameData);
void PlayInit(WEGameData* pGameData);
void PlayUpdate(WEGameData* pGameData, float dt);
void PlayShutdown(WEGameData* pGameData);
void PlayUnload(WEGameData* pGameData);

void Draw(float dt);

#endif
