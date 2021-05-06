#ifndef BOSSMOVE_H
#define BOSSMOVE_H

typedef struct State State;

void MakeBossWalkState(State* pResult);

void BossStateWalkStart(State* pState);
void BossStateWalkUpdate(State* pState, float dt);
void BossStateWalkEnd(State* pState);

#endif//BOSSMOVE_H