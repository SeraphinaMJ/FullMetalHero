#ifndef MENU_H
#define MENU_H

//Third-party headers
#include "WarpEngine.h"

void MenuLoad(WEGameData* pGameData);
void MenuInit(WEGameData* pGameData);
void MenuUpdate(WEGameData* pGameData, float dt);
void MenuShutdown(WEGameData* pGameData);
void MenuUnload(WEGameData* pGameData);

void Draw(float dt);

#endif
