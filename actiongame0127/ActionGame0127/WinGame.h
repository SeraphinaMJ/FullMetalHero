#ifndef WINGAME_H
#define WINGAME_H

//Third-party headers
#include "WarpEngine.h"

void WinGameLoad(WEGameData* pGameData);
void WinGameInit(WEGameData* pGameData);
void WinGameUpdate(WEGameData* pGameData, float dt);
void WinGameShutdown(WEGameData* pGameData);
void WinGameUnload(WEGameData* pGameData);


#endif