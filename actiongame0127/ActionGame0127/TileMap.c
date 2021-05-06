/******************************************************************************/
/*!
\file   TileMap.c
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file about tile-based map and related physics.
*/
/******************************************************************************/
#include "TileMap.h"
#include "WarpEngine.h"
#include "LayerInfo.h"
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

float TileCoordsToWorldX(const TileMap* pMap, int x)
{
	return pMap->centerX - pMap->tileSize / 2.f*(pMap->width-1) 
			+ pMap->tileSize*x;
}
float TileCoordsToWorldY(const TileMap* pMap, int y)
{
	return pMap->centerY + pMap->tileSize / 2.f*(pMap->height-1)
			- pMap->tileSize*y;
}
int WorldCoordsToTileX(const TileMap* pMap, float x)
{
	return (int)((x - pMap->centerX) + pMap->width / 2.f) / pMap->tileSize;
}
int WorldCoordsToTileY(const TileMap* pMap, float y)
{
	return (int)(-(y - pMap->centerY) + pMap->height / 2.f) / pMap->tileSize;
}

TileType GetTile(const TileMap* pMap, int x, int y)
{
	if (x < 0 || x >= pMap->width
		|| y < 0 || y >= pMap->height)
		return TILE_EMPTY;

	return pMap->data[x + y * pMap->width];
}

void NewTileMapFromFile(TileMap* pResult, float centerX, float centerY,
						int tileTextureID, int onewayTextureID, char* filename)
{
	FILE* mapFile   = 0;
	char* buffer    = 0;
	WEVec2 startPos = {0};
	int i, j;

	fopen_s(&mapFile, filename, "rt");

	//Get properties of width, height, and the size of tiles.
	fscanf_s(mapFile, "%d%d%d%f",
		&(pResult->width), &(pResult->height), 
		&(pResult->tileSize), &(pResult->gravity));

	pResult->centerX = centerX;
	pResult->centerY = centerY;

	//Set the start position
	WEVec2Set(&startPos, 
		pResult->centerX - (pResult->tileSize / 2.f) * (pResult->width - 1),
		pResult->centerY + (pResult->tileSize / 2.f) * (pResult->height - 1));

	//Allocate memory to the map's data.
	pResult->data = (TileType*)malloc(pResult->width * pResult->height * sizeof(TileType));

	buffer = (char*)malloc((pResult->width + 1) * sizeof(char));
	for (i = 0; i < pResult->height; ++i)
	{
		fscanf_s(mapFile, "%s", buffer, pResult->width + 1);
		for (j = 0; j < pResult->width; ++j)
		{
			switch (buffer[j])
			{
			case '.': // empty tile
				pResult->data[j + i * pResult->width] = TILE_EMPTY;
				break;
			case 'w': // solid tile
				pResult->data[j + i * pResult->width] = TILE_SOLID;
				break;
			case 'o':
				pResult->data[j + i * pResult->width] = TILE_ONEWAY;
				break;
			default:
				pResult->data[j + i * pResult->width] = TILE_EMPTY;
				break;
			}
		}
	}
	
	free(buffer);
	buffer = 0;

	fclose(mapFile);

	pResult->tileTextureID = tileTextureID;
	pResult->onewayTextureID = onewayTextureID;
}
void DeleteTileMap(TileMap* pResult)
{
	free(pResult->data);
	pResult->data = 0;
}

void DrawTileMap(TileMap* pToDraw)
{
	WEVec2 startPos;
	int i, j;

	WEVec2Set(&startPos,
		pToDraw->centerX - (pToDraw->tileSize / 2.f) * (pToDraw->width - 1),
		pToDraw->centerY + (pToDraw->tileSize / 2.f) * (pToDraw->height - 1));


	

	for (i = 0; i < pToDraw->height; ++i)
	{
		for (j = 0; j < pToDraw->width; ++j)
		{
			WEMtx44 transform;

			WEMtx44MakeTransform(&transform,
				(float)(pToDraw->tileSize),
				(float)(pToDraw->tileSize),
				0.f,
				TileCoordsToWorldX(pToDraw, j),//startPos.x + pToDraw->tileSize * j,
				TileCoordsToWorldY(pToDraw, i),//startPos.y - pToDraw->tileSize * i,
				LAYER_2);

			switch (GetTile(pToDraw, j, i))
			{
			case TILE_EMPTY:
				WEGraphicsSetTexture(pToDraw->tileTextureID);
				WEGraphicsSetAttributeColor(0x00000000);
				break;
			case TILE_SOLID:
				WEGraphicsSetTexture(pToDraw->tileTextureID);
				WEGraphicsSetAttributeColor(0xffffffff);
				break;
			case TILE_ONEWAY:
				WEGraphicsSetTexture(pToDraw->onewayTextureID);
				WEGraphicsSetAttributeColor(0xffffffff);
				break;
			default:
				WEGraphicsSetTexture(pToDraw->tileTextureID);
				WEGraphicsSetAttributeColor4(255, 255, 255, 255);
				break;
			}
			WEGraphicsDraw(&transform);
		}
	}
}
//
////Update velocity if the entity collides with a solid tile.
//void UpdateVelocity(const TileMap* pMap, Entity* pObj, float dt)
//{
//	WEVec2 dtVelPrev;
//	WEVec2 dtVel;
//	WEVec2 dist;
//
//	//Apply gravity force to the object's velocity
//	pObj->vel.y -= pMap->gravity * dt;
//
//	WEVec2Scale(&dtVelPrev, &pObj->vel, dt);
//
//	dist = GetLeastDistance(pMap, pObj, dtVelPrev.x, 0.f);
//
//	if (dtVelPrev.x > 0)
//		dtVel.x = min(dist.x, dtVelPrev.x);
//	else
//		dtVel.x = -1.f * min(dist.x, fabsf(dtVelPrev.x));
//
//	//Integrate the object's x position
//	pObj->pos.x += dtVel.x;
//
//	dist = GetLeastDistance(pMap, pObj, 0.f, dtVelPrev.y);
//
//	if (dtVelPrev.y > 0)
//		dtVel.y = min(dist.y, dtVelPrev.y);
//	else
//		dtVel.y = -1.f * min(dist.y, fabsf(dtVelPrev.y));
//
//	//Integrate the object's y position
//	pObj->pos.y += dtVel.y;
//
//	if (dtVelPrev.x != dtVel.x)
//	{
//		pObj->vel.x = 0.f;
//	}
//	if (dtVelPrev.y != dtVel.y)
//	{
//		if (dtVelPrev.y <= 0)
//			pObj->onGround = 1;
//		pObj->vel.y = 0.f;
//	}
//	else if (pObj->vel.y != 0)
//	{
//		pObj->onGround = 0;
//	}
//}