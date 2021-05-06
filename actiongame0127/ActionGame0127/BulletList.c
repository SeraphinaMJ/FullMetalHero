
#include "BulletList.h"

#include "TextureList.h"
#include "TileMap.h"
#include "EnemyList.h"
#include "Enemy.h"
#include "Entity.h"
//#include "UpperBody.h"
#include "EntityManager.h"
#include "Player.h"
//#include "MainBody.h"
#include "Boss.h"
#include "StackFSM.h"
#include "BulletState.h"
#include "State.h"
#include "Emitter.h"

#include <stdlib.h>
#include <math.h>


static BulletList bulletList;

void BulletMake(WEVec2 position, WeaponType weaponType, OwnerType ownerType, WEVec2 unitVector);
void BulletMovement(BulletNode* pBullet, float dt);
void BulletCollision(BulletNode* pBullet, const TileMap* pMap, EntityManager* pEntityManager);
void BulletTargetSetting(BulletNode* pBullet, EntityManager* pEntityManager);

/******************************************************************************/
/******************************************************************************/
BulletNode* GetBulletHead(void)
{
	BulletNode* pBullet = bulletList.pHead;

	return pBullet;
}

void BulletAddToEnd(Entity* pUpperEntity, WeaponType weaponType, OwnerType ownerType, WEVec2 unitVector)
{
	//If head node is not exist
	if (bulletList.pHead == NULL)
	{
		bulletList.pHead = (BulletNode*)malloc(sizeof(BulletNode));
		bulletList.pHead->pPrev = NULL;
		bulletList.pTail = bulletList.pHead;
		bulletList.pTail->pNext = NULL;
		bulletList.pTail->pPrev = NULL;
	}

	else
	{
		bulletList.pTail->pNext = (BulletNode*)malloc(sizeof(BulletNode));
		bulletList.pTail->pNext->pPrev = bulletList.pTail;
		bulletList.pTail = bulletList.pTail->pNext;
		bulletList.pTail->pNext = NULL;
	}

	//Set dead to 'FALSE'
	bulletList.pTail->dead = FALSE;

	BulletMake(pUpperEntity->pos, weaponType, ownerType, unitVector);
}

/******************************************************************************/
/******************************************************************************/
void BulletMake(WEVec2 position, WeaponType weaponType, OwnerType ownerType, WEVec2 unitVector)
{
	int textureID = 0;

	MakeMachineGunBulletState(&bulletList.pTail->machineGunBulletState);
	MakeMissileGunBulletState(&bulletList.pTail->missileGunBulletState);
	MakeGuidedProjectileBulletState(&bulletList.pTail->guidedProjectileState);
	MakeEnemyBasicBulletState(&bulletList.pTail->enemyBasicBulletState);

	MakeStackFSM(&bulletList.pTail->fsm, bulletList.pTail, 3);

	switch (weaponType){
	case MACHINE_GUN :
		textureID = TextureList_GetID(TX_BULLET);
		bulletList.pTail->damage = 10.0f;
		bulletList.pTail->fsm.Push(&bulletList.pTail->fsm, &bulletList.pTail->machineGunBulletState);
		break;
	case MISSILE_GUN :
		bulletList.pTail->damage = 30.0f;
		bulletList.pTail->fsm.Push(&bulletList.pTail->fsm, &bulletList.pTail->missileGunBulletState);
		break;
	case GUIDED_PROJECTILE:
		bulletList.pTail->damage = 10.0f;
		bulletList.pTail->fsm.Push(&bulletList.pTail->fsm, &bulletList.pTail->guidedProjectileState);
		break;
	case ENEMY_BASIC:
		textureID = TextureList_GetID(TX_ENEMY_BULLET);
		bulletList.pTail->damage = 3.0f;
		bulletList.pTail->fsm.Push(&bulletList.pTail->fsm, &bulletList.pTail->enemyBasicBulletState);
		break;
	}


	MakeEntity(&bulletList.pTail->base, 0.8f, 1.f,
		position.x, position.y,
		1.f, 1.f, 50, 80, textureID, ET_BULLET, 1.f);

	bulletList.pTail->base.rotation = atan2f(unitVector.y, unitVector.x);
	bulletList.pTail->base.vel = unitVector;

	bulletList.pTail->ownerType = ownerType;
	bulletList.pTail->weaponType = weaponType;

	bulletList.pTail->time = 0.0f;
	bulletList.pTail->targetPosition.x = 0;
	bulletList.pTail->targetPosition.y = 0;
}

/******************************************************************************/
/******************************************************************************/
void BulletUpdate
(const TileMap* pMap, EntityManager* pEntityManager, float dt)
{
	BulletNode* pBullet = bulletList.pHead;

	while (pBullet != NULL)
	{
		pBullet->fsm.Update(&pBullet->fsm, dt);

		BulletCollision(pBullet, pMap, pEntityManager);

		pBullet = pBullet->pNext;
	}
}

void BulletDraw(void)
{
	BulletNode* pBullet = bulletList.pHead;

	while (pBullet != NULL)
	{
		WEMtx44 transform;
		WEMtx44MakeTransform(&transform,
			pBullet->base.scale.x,
			pBullet->base.scale.y,
			pBullet->base.rotation,
			pBullet->base.pos.x,
			pBullet->base.pos.y,
			0.f);

		WEGraphicsSetTexture(pBullet->base.texture);
		WEGraphicsSetAttributeColor4(255, 255, 255, 255);
		WEGraphicsDraw(&transform);

		pBullet = pBullet->pNext;
	}
}

void BulletAllDelete(void)
{
	BulletNode* pBullet = bulletList.pHead;

	while (pBullet != NULL)
	{
		BulletNode* tempBullet = pBullet;
		pBullet = pBullet->pNext;
		FSMDeleteStack(&tempBullet->fsm);
		free(tempBullet);
	}

	bulletList.pHead = NULL;
	bulletList.pTail = NULL;
}

void BulletDelete(void)
{
	BulletNode* pBullet = bulletList.pHead;

	while (pBullet != NULL)
	{
		if (pBullet->dead)
		{
			if (pBullet == bulletList.pHead)
			{
				if (pBullet->pNext != NULL)
				{
					bulletList.pHead = pBullet->pNext;
					bulletList.pHead->pPrev = NULL;
					FSMDeleteStack(&pBullet->fsm);
					free(pBullet);
					return;
				}
				else
				{
					FSMDeleteStack(&pBullet->fsm);
					free(pBullet);
					bulletList.pHead = NULL;
					bulletList.pTail = NULL;
					return;
				}
			}

			else if (pBullet == bulletList.pTail)
			{
				bulletList.pTail = pBullet->pPrev;
				bulletList.pTail->pNext = NULL;
				FSMDeleteStack(&pBullet->fsm);
				free(pBullet);
				return;
			}

			else
			{
				BulletNode* tempBullet = pBullet;
				pBullet->pPrev->pNext = pBullet->pNext;
				pBullet->pNext->pPrev = pBullet->pPrev;
				pBullet = pBullet->pPrev;
				FSMDeleteStack(&tempBullet->fsm);
				free(tempBullet);

			}
		}
		pBullet = pBullet->pNext;
	}
}


/******************************************************************************/
/******************************************************************************/
void BulletMovement(BulletNode* pBullet, float dt)
{
	if (pBullet->weaponType == MACHINE_GUN)
	{
		pBullet->base.pos.x +=
			pBullet->base.vel.x * pBullet->base.maxSpeed * dt;
		pBullet->base.pos.y +=
			pBullet->base.vel.y * pBullet->base.maxSpeed * dt;
	}

	if (pBullet->weaponType == MISSILE_GUN)
	{
		pBullet->time += dt;


		if (pBullet->time < 0.1f)
		{
			pBullet->base.pos.x +=
				pBullet->base.vel.x*dt;
			pBullet->base.pos.y +=
				(pBullet->base.vel.x*dt + pBullet->base.vel.x);
		}

		else
		{
			pBullet->base.pos.x +=
				pBullet->base.vel.x * pBullet->base.maxSpeed * dt;
			pBullet->base.pos.y +=
				pBullet->base.vel.y * pBullet->base.maxSpeed * dt;
		}
	}

}

void BulletCollision(BulletNode* pBullet, const TileMap* pMap, EntityManager* pEntityManager)
{
	int i, j;
	WEVec2 tilePos;
	
	EnemyNode* pEnemy = pEntityManager->enemies.pHead;
	Entity* pPlayer = pEntityManager->pPlayer;
	Entity* pBoss = pEntityManager->pBoss;

	//Check Tile Collision

	/******************************************************************************/
	if (pBullet->weaponType == MACHINE_GUN || pBullet->weaponType == ENEMY_BASIC)
	{
		for (i = 0; i < pMap->height; ++i)
		{
			for (j = 0; j < pMap->width; ++j)
			{
				if (pMap->data[j + i * pMap->width] == TILE_SOLID)
				{
					tilePos.x = TileCoordsToWorldX(pMap, j);
					tilePos.y = TileCoordsToWorldY(pMap, i);

					if (WEIntersectionCircleRect
						(&pBullet->base.pos,
						(float)pBullet->base.aabb.x / 2.f,
						&tilePos,
						(float)pMap->tileSize,
						(float)pMap->tileSize))
					{
						pBullet->dead = TRUE;
						return;
					}

				}
			}
		}
	}

	/******************************************************************************/
	if (pBullet->ownerType == OT_ENEMY)
	{
		if (WEIntersectionCircleRect
				(&pBullet->base.pos,
				(float)pBullet->base.aabb.x / 2,
				&pPlayer->pArm->pos,
				(float)pPlayer->pArm->aabb.x,
				(float)pPlayer->pArm->aabb.y) ||
			WEIntersectionCircleRect
				(&pBullet->base.pos,
				(float)pBullet->base.aabb.x / 2,
				&pPlayer->pos,
				(float)pPlayer->aabb.x,
				(float)pPlayer->aabb.y))
		{
			if (pPlayer->isInvincible == FALSE)
			{
				EmitterCreate(pPlayer, PS_HIT);
				pBullet->dead = TRUE;
				Player_ApplyDamage(pPlayer, pBullet->damage);
			}
		}
	}

	/******************************************************************************/

	//Check Enemy Collision

	if (pBullet->ownerType == OT_PLAYER)
	{
		/******************************************************************************/
		while (pEnemy)
		{
			if (pEnemy->pData->hp > 0)
			{
				if (WEIntersectionCircleRect
					(&pBullet->base.pos,
					(float)pBullet->base.aabb.x / 2,
					&pEnemy->pData->pos,
					(float)pEnemy->pData->aabb.x,
					(float)pEnemy->pData->aabb.y))
				{
					EmitterCreate(&pBullet->base, PS_HIT);
					pEnemy->pData->hp -= pBullet->damage;
					pBullet->dead = TRUE;
					if (pEnemy->pData->hp <= 0)
					{

						EmitterCreate(pEnemy->pData, PS_HIT);
						WEDEBUG_PRINT("wow\n");
						EnemyNode* pNext = pEnemy->pNext;
						EnemyList_DeleteNode(&pEntityManager->enemies, pEnemy->pData);
						pEnemy = pNext;
						continue;
					}
				}

			}
			
			pEnemy = pEnemy->pNext;
		}

		/******************************************************************************/
		if (pBoss)
		{
			if (WEIntersectionCircleCircle
				(&pBullet->base.pos,
				(float)pBullet->base.aabb.x / 2,
				&pBoss->pos,
				(float)pBoss->aabb.x / 2))
			{
				EmitterCreate(&pBullet->base, PS_HIT);
				pBoss->hp -= pBullet->damage;
				pBullet->dead = TRUE;
			}
		}
	}

}