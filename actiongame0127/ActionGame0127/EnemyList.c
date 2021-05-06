//Project-related headers
#include "EnemyList.h"

//Project-related headers
#include "PhysicsUtil.h"
#include "Enemy.h"
#include "TileMap.h"
#include "Entity.h"
#include "Camera.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <stdlib.h>

static EnemyNode* NewEnemyNode(Entity* pData)
{
	//Allocate memory to new node.
	EnemyNode* pNode;

	//pData must not be null.
	if (pData == NULL)
		WEDEBUG_ASSERT(0,
		"\nEnemyNode* NewEnemyNode(Enemy* pData)\n"
		"pData is null!");

	pNode = (EnemyNode*)malloc(sizeof(EnemyNode));
	pNode->pData = pData;
	pNode->pNext = NULL;

	return pNode;
}

void MakeEnemyList(EnemyList* pResult)
{
	if (pResult == NULL)
		WEDEBUG_ASSERT(0,
		"\nvoid MakeEnemyList"
		"(EnemyList* pResult)\n"
		"pResult is null!");

	pResult->pHead = NULL;
	/*pResult->AddToFront = EnemyList_AddToFront;
	pResult->AddToEnd = EnemyList_AddToEnd;
	pResult->Count = EnemyList_GetCount;
	pResult->Find = EnemyList_FindItem;*/
}

void DeleteEnemyList(EnemyList* pSelf)
{
	EnemyNode* pToDelete;
	//pSelf must not be null.
	if (pSelf == NULL)
		WEDEBUG_ASSERT(0,
		"\nvoid DeleteEntityList"
		"(EntityList* pSelf)\n"
		"pSelf is null!");

	while (pSelf->pHead)
	{
		pToDelete = pSelf->pHead;
		pSelf->pHead = pSelf->pHead->pNext;
		Enemy_Release(&(pToDelete->pData));
		free(pToDelete);
	}
}

void EnemyList_AddToFront(EnemyList* pSelf, Entity* pData)
{
	EnemyNode* pNode = NewEnemyNode(pData);

	//pSelf must not be null.
	if (pSelf == NULL)
		WEDEBUG_ASSERT(0,
		"\nvoid EnemyList_AddToFront\n"
		"pSelf is null!");

	pNode->pNext = pSelf->pHead;
	pSelf->pHead = pNode;
}
void EnemyList_AddToEnd(EnemyList* pSelf, Entity* pData)
{
	EnemyNode* pHeadCopy = pSelf->pHead;

	//pSelf must not be null.
	if (pSelf == NULL)
		WEDEBUG_ASSERT(0,
		"\nvoid EnemyList_AddToEnd\n"
		"pSelf is null!");

	if (pSelf->pHead == NULL)
	{
		pSelf->pHead = NewEnemyNode(pData);
		return;
	}

	while (pHeadCopy->pNext)
		pHeadCopy = pHeadCopy->pNext;

	pHeadCopy->pNext = NewEnemyNode(pData);
}
int EnemyList_GetCount(const EnemyList* pSelf)
{
	int count = 0;
	EnemyNode* pHeadCopy = pSelf->pHead;

	//pSelf must not be null.
	if (pSelf == NULL)
		WEDEBUG_ASSERT(0,
		"\nvoid EnemyList_GetCount\n"
		"pSelf is null!");

	while (pHeadCopy)
	{
		pHeadCopy = pHeadCopy->pNext;
		++count;
	}

	return count;
}

EnemyNode* EnemyList_FindItem(const EnemyList* pSelf, const Entity* pData)
{
	EnemyNode* pHeadCopy = pSelf->pHead;

	while (pHeadCopy)
	{
		if (pHeadCopy->pData == pData)
			return pHeadCopy;
		pHeadCopy = pHeadCopy->pNext;
	}

	return NULL;
}

void EnemyList_DeleteNode(EnemyList* pSelf, const Entity* pData)
{
	EnemyNode* pHead = pSelf->pHead;
	EnemyNode* pPrev = 0;

	while (pHead)
	{
		if (pHead->pData == pData)
		{
			if (pHead == pSelf->pHead)
			{
				if (pHead->pNext)
					pSelf->pHead = pHead->pNext;
				else
					pSelf->pHead = 0;

				Enemy_Release(&pHead->pData);
				free(pHead);
				pHead = 0;
				return;
			}

			if (pHead->pNext)
				pPrev->pNext = pHead->pNext;
			else
				pPrev->pNext = 0;
			Enemy_Release(&pHead->pData);
			free(pHead);
			pHead = 0;
			return;
		}

		pPrev = pHead;
		pHead = pHead->pNext;
	}
}

void EnemyList_Draw(const EnemyList* pSelf)
{
	EnemyNode* pHeadCopy = pSelf->pHead;

	//WEDEBUG_PRINT("%f\n", WEGraphicsGetWorldBotLeft().x);

	while (pHeadCopy)
	{
		Entity* pEnemy = pHeadCopy->pData;
		WEMtx44 transform;
		if (pEnemy->pos.x >= WEGraphicsGetWorldBotLeft().x - pEnemy->scale.x
			&& pEnemy->pos.x <= WEGraphicsGetWorldTopRight().x + pEnemy->scale.x)
		{
			/*WEMtx44MakeTransform(&transform,
				pEnemy->scale.x,
				pEnemy->scale.y,
				pEnemy->rotation,
				pEnemy->pos.x,
				pEnemy->pos.y,
				pEnemy->zOrder);

			WEGraphicsSetTexture(pEnemy->texture);
			WEGraphicsSetAttributeColor4(
				pEnemy->color.r,
				pEnemy->color.g,
				pEnemy->color.b,
				pEnemy->color.a);

			WEGraphicsDraw(&transform);*/
			transform;
			Entity_Draw(pEnemy, TRUE);
		}

		

		pHeadCopy = pHeadCopy->pNext;
	}
}

void EnemyList_Update(EnemyList* pSelf, TileMap* pMap, float dt)
{
	EnemyNode* pHeadCopy = pSelf->pHead;

	while (pHeadCopy)
	{
		Entity* pEnemy = pHeadCopy->pData;
		Enemy_Update(pEnemy, dt);
		
		Physics_CollideAndUpdateVelocity(pEnemy, pMap, dt);
		pHeadCopy = pHeadCopy->pNext;
		if(pEnemy->isDead == TRUE)
		{
			EnemyList_DeleteNode(pSelf, pEnemy);
		}
	}
}