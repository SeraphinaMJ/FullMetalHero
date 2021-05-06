//Project-related headers
#include "Camera.h"

//Third-party headers
#include "TileMap.h"
#include "EMP.h"

//Third-party headers
#include "WarpEngine.h"

//#define CAMERA_ SCALE 8
#define CAMERA_BREAK 10
#define CAEMERA_Z 12
static float time = 0.f;

static Camera pCamera;

void CameraInit(TileMap* pMap, float objX, float objY)
{
	WEVec2 botLeft; 
	WEVec2 topRight;
	pCamera.tPos.x = objX;
	pCamera.tPos.y = objY;
	pCamera.cPos = pCamera.tPos;

	WEGraphicsSetCamera(pCamera.cPos.x, pCamera.cPos.y, CAEMERA_Z, 0);
	botLeft = WEGraphicsGetWorldBotLeft();
	topRight = WEGraphicsGetWorldTopRight();
	pCamera.size.x = topRight.x - botLeft.x;
	pCamera.size.y = topRight.y - botLeft.y;

	

	pCamera.mapInfo.left = (pMap->centerX) - ((pMap->width) / 2); 
	pCamera.mapInfo.right = pMap->centerX + (pMap->width / 2); 
	pCamera.mapInfo.top = pMap->centerY + (pMap->height / 2);
	pCamera.mapInfo.bottom = pMap->centerY - (pMap->height / 2);
	pCamera.vel.x = 3.f;
	pCamera.vel.y = 0.f;
}

void CameraUpdate(/*TileMap* pMap,float objX,float objY,*/float dt)
{
	//compare the target pos and camera pos
	if (pCamera.mapInfo.left + pCamera.size.x / 2 /*- 0.5f*/< pCamera.tPos.x && 
		pCamera.mapInfo.right - pCamera.size.x / 2 > pCamera.tPos.x + 0.8f)
		pCamera.cPos.x = pCamera.tPos.x;
	if (pCamera.mapInfo.bottom + pCamera.size.y / 2 /*- 0.5f*/ < pCamera.tPos.y &&
		pCamera.mapInfo.top - pCamera.size.y / 2 > pCamera.tPos.y /*- 0.5f*/)
		pCamera.cPos.y = pCamera.tPos.y;

	//Camera Move To Right
	time += dt;
	if (time)
	{
		pCamera.cPos.x += pCamera.vel.x * dt;
	}

	//calculate the camera pos and set camera.
	WEGraphicsSetCamera(pCamera.cPos.x, pCamera.cPos.y, CAEMERA_Z, 0);
}

Camera* GetCamera(void)
{
	return &pCamera;
}

