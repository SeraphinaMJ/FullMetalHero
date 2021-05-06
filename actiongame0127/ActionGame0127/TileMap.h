/******************************************************************************/
/*!
\file   TileMap.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file about tile-based map and related physics.
*/
/******************************************************************************/
#ifndef TILEMAP_H
#define TILEMAP_H

#include"WarpEngine.h"
#include"Entity.h"

typedef enum TileType { TILE_EMPTY = 0, TILE_SOLID, TILE_ONEWAY }TileType;

typedef struct TileMap{
	int width;
	int height;
	float centerX;
	float centerY;
	int tileSize;
	TileType* data;
	float gravity;
	int tileTextureID;
	int onewayTextureID;
}TileMap;

float TileCoordsToWorldX(const TileMap* pMap, int x);
float TileCoordsToWorldY(const TileMap* pMap, int y);
int WorldCoordsToTileX(const TileMap* pMap, float x);
int WorldCoordsToTileY(const TileMap* pMap, float y);


TileType GetTile(const TileMap* pMap, int x, int y);

void NewTileMapFromFile(TileMap* pResult, float centerX, float centerY,
						int tileTextureID, int onewayTextureID, char* filename);
void DeleteTileMap(TileMap* pResult);

void DrawTileMap(TileMap* pToDraw);

//WEVec2 GetLeastDistance(const TileMap* pMap, const Entity* pObj, 
//	float vx, float vy);
//
//void UpdateVelocity(const TileMap* pMap, Entity* pObj, float dt);



#endif