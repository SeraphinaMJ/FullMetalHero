#ifndef CAMERA_H
#define CAMERA_H

#include "WarpEngine.h"

//Declaration structs
typedef struct TileMap TileMap;

typedef struct
{
	float left;
	float right;
	float top;
	float bottom;
	//float width;
}MapSize;

typedef struct
{
	WEVec2  size;
	WEVec2  tPos;
	WEVec2	cPos;
	WEVec2  vel;
	MapSize  mapInfo;
}Camera;

void CameraInit(TileMap* pMap, float objX, float objY);

void CameraUpdate(/*TileMap* pMap,float objX, float objY,*/ float dt);

Camera* GetCamera(void);
#endif