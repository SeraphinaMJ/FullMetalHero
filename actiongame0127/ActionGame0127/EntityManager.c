//Project-related headers
#include "EntityManager.h"

//Project-related headers
#include "UpperBody.h"
#include "Enemy.h"
#include "EnemyList.h"
#include "TileMap.h"
#include "PhysicsUtil.h"
#include "Player.h"
#include "TextureList.h"
#include "Boss.h"
#include "Camera.h"
#include "Hp.h"
#include "EMP.h"
#include "Emitter.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <stdlib.h>


EntityManager* g_entityManager;

static void SpawnEnemy(const TileMap* pMap)
{
	FILE* dataFile = 0;
	char* buffer = 0;
	int i = 0, j = 0;

	fopen_s(&dataFile, "enemyData.txt", "rt");

	buffer = (char*)malloc((pMap->width + 1) * sizeof(char));
	for (i = 0; i < pMap->height; ++i)
	{
		fscanf_s(dataFile, "%s", buffer, pMap->width + 1);
		for (j = 0; j < pMap->width; ++j)
		{
			switch (buffer[j])
			{
			case '1':
			{
				Entity* pEnemy = Enemy_New(1.f, 1.f,
					TileCoordsToWorldX(pMap, j), TileCoordsToWorldY(pMap, i),
					1.f, 1.f, TextureList_GetID(TX_CIRCLE),
					g_entityManager->pPlayer, ENEMY_NORMAL);
				EnemyList_AddToEnd(&g_entityManager->enemies, pEnemy);
				break;
			}
			}
		}
	}

	free(buffer);
	buffer = 0;

	fclose(dataFile);
}

void MakeEntityManager(const TileMap* pMap)
{
	g_entityManager = (EntityManager*)malloc(sizeof(EntityManager));
	WEVec2 spawnPos;
	WEVec2 bossPos;
	int upperBodyTexture = TextureList_GetID(TX_PLAYER_UPPERBODY);
	int mainBodyTexture = TextureList_GetID(TX_PLAYER_MAINBODY);

	g_entityManager->timer = 0.f;

	spawnPos.x = TileCoordsToWorldX(pMap, 25);
	spawnPos.y = TileCoordsToWorldY(pMap, pMap->height - 8);
	bossPos.x = TileCoordsToWorldX(pMap, 2);
	bossPos.y = 0.f;
	g_entityManager->pPlayer = Player_New(1.f, 1.5f, spawnPos.x, spawnPos.y, 1.f, 1.5f,
		10.f, 14.474f, upperBodyTexture, mainBodyTexture);

	g_entityManager->pBoss = Boss_New(10, 10, bossPos.x, bossPos.y,
		6.f, 6.f, GetCamera()->vel.x, TextureList_GetID(TX_BOSS), TextureList_GetID(TX_BOSS_BAR),
		TextureList_GetID(TX_BOSS_EYE),
		BOSS_LIFE, g_entityManager->pPlayer);

	HpBar_Set(g_entityManager->pBoss->hp);
	//g_entityManager->pMainBody = (MainBody*)malloc(sizeof(MainBody));
	//MakeMainBody(g_entityManager->pMainBody, 1, 1, 0.f, 0.f, 1, 1, 10.f, 14.474f, MainBodyTexture);
	MakeEnemyList(&g_entityManager->enemies);
	/*Entity* pEnemy = Enemy_New(1.f, 1.f, spawnPos.x + 5.f, spawnPos.y,
		1.f, 1.f, upperBodyTexture, g_entityManager->pPlayer, ENEMY_NORMAL);
	EnemyList_AddToEnd(&g_entityManager->enemies, pEnemy);*/
	SpawnEnemy(pMap);
	//g_entityManager->pUpperBody = (UpperBody*)malloc(sizeof(UpperBody));
	//UpperBodyMake(g_entityManager->pUpperBody, 1, 1, 0.f, 0.f, 1, 1, 10.f, 14.474f, MainBodyTexture);
	g_entityManager->spawnTimer = 0;
	g_entityManager->enemyTexture = upperBodyTexture;

}

EntityManager* GetEntityManager(void)
{
	return g_entityManager;
}

void EntityManager_Draw(void)
{
	//WEMtx44 transform;
	//
	EnemyList_Draw(&(g_entityManager->enemies));

	//WEMtx44MakeTransform(&transform,
	//	pSelf->pMainBody->base.scale.x,
	//	pSelf->pMainBody->base.scale.y,
	//	pSelf->pMainBody->base.rotation,
	//	pSelf->pMainBody->base.pos.x,
	//	pSelf->pMainBody->base.pos.y,
	//	pSelf->pMainBody->base.zOrder);
	//WEGraphicsSetTexture(pSelf->pMainBody->base.texture);
	///*WEGraphicsSetAttributeColor4(
	//	pSelf->pMainBody->base.color.r,
	//	pSelf->pMainBody->base.color.g,
	//	pSelf->pMainBody->base.color.b,
	//	pSelf->pMainBody->base.color.a
	//	);*/
	//WEGraphicsDraw(&transform);


	/*MainBody_Draw(pSelf->pMainBody);

	UpperBodyDraw(pSelf->pUpperBody);*/

	//Draw the boss.
	Boss_Draw(g_entityManager->pBoss);
	
	
	Player_Draw(g_entityManager->pPlayer);
}

void EntityManager_Update(TileMap* pMap, float dt)
{
	//Spawn enemies.
	/*g_entityManager->spawnTimer += dt;
	if (g_entityManager->spawnTimer >= 2.0f)
	{
		Enemy* pEnemy = (Enemy*)malloc(sizeof(Enemy));
		float size = WERandFloatMinMax(1.f, 3.f);
		MakeEnemy(pEnemy, size, size, WERandFloatMinMax(-13.f, 13.f), WERandFloatMinMax(10.f, -5.f),
			size, size, 3.f, 20.f, g_entityManager->enemyTexture, g_entityManager->pMainBody);
		EnemyList_AddToEnd(&g_entityManager->enemies, pEnemy);
		g_entityManager->spawnTimer = 0.f;
	}*/
	
	/*g_entityManager->pMainBody->UpdateSM(g_entityManager->pMainBody, dt);

	EnemyList_Update(&g_entityManager->enemies, dt);

	Physics_CollideAndUpdateVelocity(&g_entityManager->pMainBody->base, pMap, dt);
	EnemyNode* pHead = g_entityManager->enemies.pHead;
	while (pHead)
	{
		Physics_CollideAndUpdateVelocity(&pHead->pData->base, pMap, dt);
		pHead = pHead->pNext;
	}
	pHead = g_entityManager->enemies.pHead;
	while (pHead)
	{
		Physics_MainBodyVsEnemy(g_entityManager->pMainBody, pHead->pData);
		pHead = pHead->pNext;
	}

	UpperBodyUpdate(g_entityManager->pUpperBody, g_entityManager->pMainBody, pMap,&g_entityManager->enemies, dt);*/

	EnemyList_Update(&g_entityManager->enemies, pMap, dt);
	
	Player_Update(g_entityManager->pPlayer, pMap, &(g_entityManager->enemies), dt);

	Boss_Update(g_entityManager->pBoss, dt);
	if (g_entityManager->pBoss)
		HpBar_Set(g_entityManager->pBoss->hp);
	
	if (g_entityManager->pBoss)
	{
		if (g_entityManager->pBoss->hp <= 0.f)
		{
			EmitterCreate(&*g_entityManager->pBoss, PS_DIE);
			Boss_Release(&g_entityManager->pBoss);
		}
		//WEDEBUG_PRINT("%p\n", g_entityManager->pBoss);
	}

	if (g_entityManager->pBoss == NULL)
	{
		g_entityManager->timer += dt;

		if (g_entityManager->timer > 5.f)
			WESMSetNextState(EMP_WinGame);
	}
}

void DeleteEntityManager(void)
{
	Player_Release(&g_entityManager->pPlayer);

	/*DeleteMainBody(pDelete->pMainBody);
	free(pDelete->pMainBody);
	pDelete->pMainBody = 0;
	
	UpperBodyDelete(pDelete->pUpperBody);
	free(pDelete->pUpperBody);
	pDelete->pUpperBody = 0;*/

	DeleteEnemyList(&(g_entityManager->enemies));

	Boss_Release(&g_entityManager->pBoss);

	free(g_entityManager);
	g_entityManager = 0;
	//FSMDeleteStack(&pDelete->pUpperBody->fsm);
	//free(pDelete->pUpperddddy = 0;
}