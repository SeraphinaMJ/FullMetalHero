#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
//#include "MainBody.h"
#include "WarpEngine.h"
#include "StackFSM.h"
#include "State.h"
//#include "BulletManager.h"

typedef struct Player Player;


#define MAX_PATTERN 10

//typedef struct Enemy{
//	Entity base;
//	Entity* pTarget;
//
//	float shootDelay;
//	float shootTimer;
//
//	//BulletManager magazine;
//	BOOL isDead;
//	State* pattern[MAX_PATTERN];
//	int stateCount; //The number of the states enemy has.
//	StackFSM fsm;
//}Enemy;

Entity* Enemy_New(float width, float height, float x, float y,
	float scaleX, float scaleY, int textureID, Entity* pTarget,
	EnemyType enemyType);

void Enemy_Release(Entity** ppToDelete);

void Enemy_Update(Entity* pSelf, float dt);

#endif