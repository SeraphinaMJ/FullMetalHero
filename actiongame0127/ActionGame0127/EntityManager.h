#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

//Project-related headers
#include "EnemyList.h"

//define
#define BOSS_LIFE 1000.f

//Declaration structs
typedef struct EntityManager EntityManager;
typedef struct MainBody MainBody;
typedef struct UpperBody UpperBody;
typedef struct TileMap TileMap;
typedef struct Boss Boss;
typedef struct Entity Entity;

typedef struct EntityManager{
	/*MainBody* pMainBody;
	UpperBody* pUpperBody;*/
	Entity* pPlayer;
	Entity* pBoss;
	EnemyList enemies;
	int enemyTexture;
	float spawnTimer;
	float timer;
}EntityManager;

void MakeEntityManager(const TileMap* pMap);

EntityManager* GetEntityManager(void);

void EntityManager_Draw(void);
void EntityManager_Update(TileMap* pMap, float dt);

void DeleteEntityManager(void);

#endif