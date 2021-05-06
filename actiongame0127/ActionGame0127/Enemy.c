#include "Enemy.h"
#include "EnemyState.h"
#include "BombEnemyState.h"
#include "Player.h"
#include "TextureList.h"
#include "StackFSM.h"
#include "WeaponManager.h"
#include <stdlib.h>

Entity* Enemy_New(float width, float height, float x, float y,
	float scaleX, float scaleY, int textureID, Entity* pTarget,
	EnemyType enemyType)
{
	Entity* pNew = (Entity*)malloc(sizeof(Entity));
	MakeEntity(pNew, width, height, x, y, scaleX, scaleY, 
		0.f, 0.f, textureID, ET_ENEMY, 50.f);
	pNew->pTarget = pTarget;

	
	MakeWeapon(&pNew->weapon);

	//MakeStackFSM(&pNew->fsm, pNew, 5);

	switch (enemyType)
	{
	case ENEMY_NORMAL:
		pNew->enemyShootState = malloc(sizeof(State));
		MakeEnemyShootState(pNew->enemyShootState);
		pNew->shootFSM = malloc(sizeof(StackFSM));
		MakeStackFSM(pNew->shootFSM, pNew, 1);
		FSMPush(pNew->shootFSM, pNew->enemyShootState);
		break;
	case ENEMY_BOMB:
	{
		pNew->explosionDelay = 3.f;
		pNew->explosionTimer = 0.f;
		pNew->enemyIdleState = malloc(sizeof(State));
		pNew->enemyExplodeState = malloc(sizeof(State));
		MakeBombEnemyReadyState(pNew->enemyIdleState);
		MakeBombEnemyExplodeState(pNew->enemyExplodeState);
		pNew->shootFSM = malloc(sizeof(StackFSM));
		MakeStackFSM(pNew->shootFSM, pNew, 2);
		FSMPush(pNew->shootFSM, pNew->enemyIdleState);
		break;
	}
	}

	pNew->enemyType = enemyType;

	return pNew;
}

void Enemy_Release(Entity** ppToDelete)
{
	if (ppToDelete)
	{
		Entity* pToDelete = *ppToDelete;
		switch (pToDelete->enemyType)
		{
		case ENEMY_NORMAL:
			free(pToDelete->enemyShootState);
			FSMDeleteStack(pToDelete->shootFSM);
			free(pToDelete->shootFSM);
			free(pToDelete);
			*ppToDelete = 0;
			break;
		case ENEMY_BOMB:
			free(pToDelete->enemyIdleState);
			free(pToDelete->enemyExplodeState);
			FSMDeleteStack(pToDelete->shootFSM);
			free(pToDelete->shootFSM);
			free(pToDelete);
			*ppToDelete = 0;
			break;
		}
		//int i = 0;
		//for (i = 0; i < (*ppToDelete)->stateCount; ++i)
		//{
		//	free((*ppToDelete)->pattern[i]);
		//	(*ppToDelete)->pattern[i] = 0;
		//}
		//FSMDeleteStack(&(*ppToDelete)->fsm);
		////BulletManagerAllDelete(&(*ppToDelete)->magazine);
		//free(*ppToDelete);
		//*ppToDelete = 0;
	}
}

void Enemy_Update(Entity* pSelf, float dt)
{
	/*WEVec2 targetPos =
		pSelf->pTarget->base.GetPos(&pSelf->pTarget->base);

	WEVec2 distance;
	WEVec2Sub(&distance, &targetPos, &pSelf->base.pos);
	WEVec2Scale(&distance, &distance, 3.f);

	pSelf->base.vel = distance;
	

	dt;*/
	//pSelf->fsm.Update(&pSelf->fsm, dt);
	FSMUpdate(pSelf->shootFSM, dt);

	//BulletManagerUpdate(&pSelf->magazine, pMap, pEnemyList, dt);
}