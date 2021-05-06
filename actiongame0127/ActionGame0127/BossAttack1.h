#ifndef BOSSATTACK1_H
#define BOSSATTACK1_H

typedef struct State State;

void MakeBossAttackOneOneState(State* pResult);

void BossStateAttackOneOneStart(State* pState);
void BossStateAttackOneOneUpdate(State* pState, float dt);
void BossStateAttackOneOneEnd(State* pState);



void MakeBossAttackOneTwoState(State* pResult);

void BossStateAttackOneTwoStart(State* pState);
void BossStateAttackOneTwoUpdate(State* pState, float dt);
void BossStateAttackOneTwoEnd(State* pState);


void MakeBossAttackOneThreeState(State* pResult);

void BossStateAttackOneThreeStart(State* pState);
void BossStateAttackOneThreeUpdate(State* pState, float dt);
void BossStateAttackOneThreeEnd(State* pState);

#endif