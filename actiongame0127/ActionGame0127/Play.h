#ifndef PLAY_H
#define PLAY_H

//Third-party headers
#include "WarpEngine.h"

void PlayLoad(WEGameData* pGameData);
void PlayInit(WEGameData* pGameData);
void PlayUpdate(WEGameData* pGameData, float dt);
void PlayShutdown(WEGameData* pGameData);
void PlayUnload(WEGameData* pGameData);
void PlayDraw(void);

#endif
