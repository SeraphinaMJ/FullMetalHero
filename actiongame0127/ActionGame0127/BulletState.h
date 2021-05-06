#ifndef BULLETSTATE_H
#define BULLETSTATE_H

//Declaration structs
typedef struct State State;

void MakeMachineGunBulletState(State* pResult);
void MachineGunBulletStateStart(State* pState);
void MachineGunBulletStateUpdate(State* pState, float dt);
void MachineGunBulletStateEnd(State* pState);

void MakeMissileGunBulletState(State* pResult);
void MissileGunBulletStateStart(State* pState);
void MissileGunBulletStateUpdate(State* pState, float dt);
void MissileGunBulletStateEnd(State* pState);


void MakeGuidedProjectileBulletState(State* pResult);
void GuidedProjectileBulletStateStart(State* pState);
void GuidedProjectileBulletStateUpdate(State* pState, float dt);
void GuidedProjectileBulletStateEnd(State* pState);

void MakeEnemyBasicBulletState(State* pResult);
void EnemyBasicBulletStateStart(State* pState);
void EnemyBasicBulletStateUpdate(State* pState, float dt);
void EnemyBasicBulletStateEnd(State* pState);

#endif