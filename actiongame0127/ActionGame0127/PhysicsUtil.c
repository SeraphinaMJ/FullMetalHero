//Header file related to the implementation
#include "PhysicsUtil.h"

//Project-related headers
#include "TileMap.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
//#include "MainBody.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <stdlib.h>
#include <float.h>
#include <math.h>

//Get least distance depends on an entity's side and its velocity.
static WEVec2 GetLeastDistance(const TileMap* pMap, const Entity* pObj,
	float vx, float vy)
{
	int i, j;
	int* row = (int*)malloc(pMap->height * sizeof(int));
	int rowCount = 0;
	int* column = (int*)malloc(pMap->width * sizeof(int));
	int columnCount = 0;
	int* collision = (int*)malloc(pMap->height * pMap->width * sizeof(int));
	WEVec2 leastDist;

	//Initialize leastDista.
	WEVec2Set(&leastDist, FLT_MAX, FLT_MAX);

	//Check which tile is intersecting with MainBody.
	for (i = 0; i < pMap->height; ++i)
	{
		for (j = 0; j < pMap->width; ++j)
		{
			WEVec2 tilePos;
			WEVec2Set(&tilePos,
				TileCoordsToWorldX(pMap, j),
				TileCoordsToWorldY(pMap, i));
			if (WEIntersectionRectRect(&(pObj->pos),
				pObj->aabb.x, pObj->aabb.y,
				&tilePos, (float)pMap->tileSize, (float)pMap->tileSize))
			{
				collision[j + i * pMap->width] = 1;
			}
			else
				collision[j + i * pMap->width] = 0;
		}
	}

	////X axis collision
	//Get rows which MainBody is colliding with.
	for (i = 0; i < pMap->height; ++i)
	{
		for (j = 0; j < pMap->width; ++j)
		{
			if (collision[j + i * pMap->width] == 1)
			{
				/*if (pObj->type == ET_PLAYER)
					WEDEBUG_PRINT("%d ", i);*/
				row[rowCount] = i;
				++rowCount;
				break;
			}
		}
	}
	
	//Get least distance between MainBody and the closest wall.
	if (vx > 0)
	{
		for (i = 0; i < rowCount; ++i)
		{
			for (j = pMap->width - 1; j >= 0; --j)
			{
				if (GetTile(pMap, j, row[i]) == TILE_SOLID)
				{
					float dist = (TileCoordsToWorldX(pMap, j) -
						pMap->tileSize / 2.f) -
						(pObj->pos.x + pObj->aabb.x / 2.f);
					if (dist < 0.f)
						break;
					else if (dist < leastDist.x)
					{
						leastDist.x = dist;
					}
				}
			}
		}
	}
	else if (vx < 0)
	{
		for (i = 0; i < rowCount; ++i)
		{
			for (j = 0; j < pMap->width; ++j)
			{
				if (GetTile(pMap, j, row[i]) == TILE_SOLID)
				{
					float dist = (pObj->pos.x - pObj->aabb.x / 2.f) -
						(TileCoordsToWorldX(pMap, j) + pMap->tileSize / 2.f);
					if (dist < 0.f)
						break;
					else if (dist < leastDist.x)
					{
						leastDist.x = dist;
					}
				}
			}
		}
	}

	////Y axis collision
	//Get columns which MainBody is colliding with.
	for (i = 0; i < pMap->width; ++i)
	{
		for (j = 0; j < pMap->height; ++j)
		{
			if (collision[i + j * pMap->width] == 1)
			{
				column[columnCount] = i;
				++columnCount;
				break;
			}
		}
	}

	//Get least distance between MainBody and the closest wall.
	if (vy > 0)
	{
		for (i = 0; i < columnCount; ++i)
		{
			for (j = 0; j < pMap->height; ++j)
			{
				if (GetTile(pMap, column[i], j) == TILE_SOLID)
				{
					float dist = (TileCoordsToWorldY(pMap, j) -
						pMap->tileSize / 2.f) -
						(pObj->pos.y + pObj->aabb.y / 2.f);
					if (dist < 0.f)
					{
						/*if (leastDist.y > 0)
						{
							leastDist.y = dist;
						}*/
						break;
					}
					else if (dist < leastDist.y)
						leastDist.y = dist;
				}
			}
		}
	}
	else if (vy <= 0)
	{
		for (i = 0; i < columnCount; ++i)
		{
			for (j = pMap->height - 1; j >= 0; --j)
			{
				if (GetTile(pMap, column[i], j) == TILE_SOLID
					|| GetTile(pMap, column[i], j) == TILE_ONEWAY)
				{
					float dist = (pObj->pos.y - pObj->aabb.y / 2.f) -
						(TileCoordsToWorldY(pMap, j) + pMap->tileSize / 2.f);
					if (dist < 0.f)
					{
						//if (dist > -0.3f)
						//{
						//	leastDist.y = dist;
						//}
						break;
					}
					else if (dist < leastDist.y)
						leastDist.y = dist;
				}
			}
		}
		leastDist.y -= 0.001f;
	}

	/*if (pObj->type == ET_PLAYER)
	{
		WEDEBUG_PRINT("%f", leastDist.y);
		WEDEBUG_PRINT("\n");
	}*/
	free(row);
	free(column);
	free(collision);
	row = 0;
	column = 0;
	collision = 0;

	return leastDist;
}

void Physics_CollideAndUpdateVelocity(
	Entity* pEntity, const TileMap* pMap, float dt)
{
	WEVec2 dtVelPrev;
	WEVec2 dtVel;
	WEVec2 dist;

	Entity* pObj = pEntity;
	WEVec2 vel = pObj->vel;

	//Apply gravity force to the object's velocity
	pObj->vel.y -= pMap->gravity * dt;
	vel = pObj->vel;

	WEVec2Scale(&dtVelPrev, &vel, dt);

	//Adjust x distance MainBody will move with.
	dist = GetLeastDistance(pMap, pObj, dtVelPrev.x, 0.f);
	if (dtVelPrev.x > 0)
		dtVel.x = min(dist.x, dtVelPrev.x);
	else
		dtVel.x = -1.f * min(dist.x, fabsf(dtVelPrev.x));

	//Integrate the object's x position
	pObj->pos.x += dtVel.x;

	//Adjust y distance MainBody will move with.
	dist = GetLeastDistance(pMap, pObj, 0.f, dtVelPrev.y);
	if (dtVelPrev.y > 0)
		dtVel.y = min(dist.y, dtVelPrev.y);
	else
		dtVel.y = -1.f * min(dist.y, fabsf(dtVelPrev.y));

	//Integrate the object's y position
	pObj->pos.y += dtVel.y;

	//Change velocity to zero if the MainBody stuck to solid tiles.
	vel = pObj->vel;
	if (dtVelPrev.x != dtVel.x)
		vel.x = 0.f;
	if (dtVelPrev.y != dtVel.y)
	{
		if (dtVelPrev.y <= 0)
			pObj->onGround = 1;
		vel.y = 0.f;
	}
	else if (pObj->vel.y != 0)
		pObj->onGround = 0;
	pObj->vel = vel;
}

void Physics_MainBodyVsEnemy(Entity* pMainBody, Entity* pEnemy)
{
	WEVec2 MainBodyPos = pMainBody->pos;
	WEVec2 enemyPos = pEnemy->pos;

	//If the MainBody is invincible or rolling, 
	//it doesn't check collision with enemies.
	if (pMainBody->isInvincible ||
		pMainBody->isRolling)
		return;

	if (WEIntersectionRectRect(
		&MainBodyPos,
		pMainBody->aabb.x,
		pMainBody->aabb.y,
		&enemyPos,
		pEnemy->aabb.x,
		pEnemy->aabb.y))
	{
		//WEDEBUG_PRINT("cool!\n");
		if (pMainBody->isDamaged == FALSE)
		{
			Player_ApplyDamage(pMainBody, 1.f);
		}
	}
}