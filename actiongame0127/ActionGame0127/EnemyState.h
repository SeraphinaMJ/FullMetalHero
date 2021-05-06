#ifndef	ENEMYSTATE_H
#define ENEMYSTATE_H

#include "State.h"

void MakeEnemyShootState(State* pResult);
void EnemyStateShootStart(State* pState);
void EnemyStateShootUpdate(State* pState, float dt);
void EnemyStateShootEnd(State* pState);

#endif