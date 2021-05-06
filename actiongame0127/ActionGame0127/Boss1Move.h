#ifndef BOSSMOVE_H
#define BOSSMOVE_H

typedef struct State State;

void MakeBossWalkState(State* pResult);
void BossState_WalkStart(State* pState);
void BossState_WalkUpdate(State* pState, float dt);
void BossState_WalkEnd(State* pState);

#endif//BOSSMOVE_H