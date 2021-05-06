#ifndef DIGIPEN_H
#define DIGIPEN_H

//Third-party headers
#include "WarpEngine.h"

void DigipenLoad(WEGameData* pGameData);
void DigipenInit(WEGameData* pGameData);
void DigipenUpdate(WEGameData* pGameData, float dt);
void DigipenShutdown(WEGameData* pGameData);
void DigipenUnload(WEGameData* pGameData);


#endif

