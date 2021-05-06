#ifndef ENEMYLIST_H
#define ENEMYLIST_H

#include "Entity.h"

//Declaration structs
typedef struct Enemy Enemy;
typedef struct TileMap TileMap;

typedef struct EnemyNode
{
	Entity* pData;
	struct EnemyNode* pNext;
}EnemyNode;

typedef struct EnemyList
{
	EnemyNode* pHead;/*
	void(*AddToFront)(struct EnemyList*, Enemy*);
	void(*AddToEnd)(struct EnemyList*, Enemy*);
	void(*Count)(const struct EnemyList*);
	EnemyNode*(*Find)(const struct EnemyList*, const Enemy*);*/
}EnemyList;

void MakeEnemyList(EnemyList* pResult);
void DeleteEnemyList(EnemyList* pSelf);

void EnemyList_AddToFront(EnemyList* pSelf, Entity* pData);
void EnemyList_AddToEnd(EnemyList* pSelf, Entity* pData);
int EnemyList_GetCount(const EnemyList* pSelf);
EnemyNode* EnemyList_FindItem(const EnemyList* pSelf, const Entity* pData);
void EnemyList_DeleteNode(EnemyList* pSelf, const Entity* pData);


void EnemyList_Draw(const EnemyList* pSelf);
void EnemyList_Update(EnemyList* pSelf, TileMap* pMap, float dt);

#endif