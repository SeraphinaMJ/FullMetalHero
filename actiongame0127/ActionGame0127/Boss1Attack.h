#ifndef BOSS1ATTACK_H
#define BOSS1ATTACK_H

typedef struct State State;



void MakeBossAttackIdleState(State* pResult);
void BossState_AttackIdleStart(State* pState);
void BossState_AttackIdleUpdate(State* pState, float dt);
void BossState_AttackIdleEnd(State* pState);

void MakeBossFireballAttackState(State* pResult);
void BossState_FireballAttackStart(State* pState);
void BossState_FireballAttackUpdate(State* pState, float dt);
void BossState_FIreballAttackEnd(State* pState);

void MakeBossBombAttackState(State* pResult);
void BossState_BombAttackStart(State* pState);
void BossState_BombAttackUpdate(State* pState, float dt);
void BossState_BombAttackEnd(State* pState);

void MakeBossBeamAttackReadyState(State* pResult);
void BossState_BeamAttackReadyStart(State* pState);
void BossState_BeamAttackReadyUpdate(State* pState, float dt);
void BossState_BeamAttackReadyEnd(State* pState);

void MakeBossBeamAttackFireState(State* pResult);
void BossState_BeamAttackFireStart(State* pState);
void BossState_BeamAttackFireUpdate(State* pState, float dt);
void BossState_BeamAttackFireEnd(State* pState);

#endif