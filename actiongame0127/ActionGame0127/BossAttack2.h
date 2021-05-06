#ifndef BOSSATTACK2_H
#define BOSSATTACK2_H

typedef struct State State;

void MakeBossAttackTwoOneState(State* pResult);

void BossStateAttackTwoOneStart(State* pState);
void BossStateAttackTwoOneUpdate(State* pState, float dt);
void BossStateAttackTwoOneEnd(State* pState);



void MakeBossAttackTwoTwoState(State* pResult);

void BossStateAttackTwoTwoStart(State* pState);
void BossStateAttackTwoTwoUpdate(State* pState, float dt);
void BossStateAttackTwoTwoEnd(State* pState);


void MakeBossAttackTwoThreeState(State* pResult);

void BossStateAttackTwoThreeStart(State* pState);
void BossStateAttackTwoThreeUpdate(State* pState, float dt);
void BossStateAttackTwoThreeEnd(State* pState);

#endif