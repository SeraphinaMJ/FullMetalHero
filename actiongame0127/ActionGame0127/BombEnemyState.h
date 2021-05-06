#ifndef BOMBENEMYSTATE_H
#define BOMBENEMYSTATE_H

typedef struct State State;

void MakeBombEnemyReadyState(State* pResult);
void BombEnemyStateReadyStart(State* pState);
void BombEnemyStateReadyUpdate(State* pState, float dt);
void BombEnemyStateReadyEnd(State* pState);

void MakeBombEnemyExplodeState(State* pResult);
void BombEnemyStateExplodeStart(State* pState);
void BombEnemyStateExplodeUpdate(State* pState, float dt);
void BombEnemyStateExplodeEnd(State* pState);

#endif