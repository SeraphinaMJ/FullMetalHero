#ifndef GAMEOVER_H
#define GAMEOVER_H

//Third-party headers
#include "WarpEngine.h"

void GameOverLoad(WEGameData* pGameData);
void GameOverInit(WEGameData* pGameData);
void GameOverUpdate(WEGameData* pGameData, float dt);
void GameOverShutdown(WEGameData* pGameData);
void GameOverUnload(WEGameData* pGameData);


#endif