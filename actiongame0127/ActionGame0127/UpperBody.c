/******************************************************************************/
/*!
\file   UpperBody.c
\author Yeongjin Kil
\par    email: blue125kr\@gmail.com
\brief
This is the source file about UpperBody
*/
/******************************************************************************/
//Header file related to the implementation
#include "UpperBody.h"

//Project-related headers
#include "ShootMachineGun.h"
#include "ShootMissileGun.h"
#include "ShootGuidedProjectile.h"
#include "MainBody.h"
#include "TileMap.h"
#include "EnemyList.h"
#include "LayerInfo.h"
#include "WeaponManager.h"
#include "BulletList.h"

//Third-party headers
#include "WarpEngine.h"

//Standard library headers
#include <stdlib.h>
#include <math.h>
/******************************************************************************/
/******************************************************************************/
void UpperBodyMake(UpperBody* pResult,
	float width, float height, float x, float y,
	float scaleX, float scaleY, float maxSpeed, float jumpSpeed, int textureID)
{
	//Make  Entity
	MakeEntity(&pResult->base, width, height, x, y, scaleX, scaleY,
		maxSpeed, jumpSpeed, textureID, ET_UPPERBODY, 1.f);

	//Make State
	MakeMachineGunShootState(&pResult->shootMachineGunState);
	MakeMachineGunNotShootState(&pResult->notShootMachineGunState);
	MakeMissileGunShootState(&pResult->shootMissileGunState);
	MakeMissileGunNotShootState(&pResult->notShootMissileGunState);
	MakeGuidedProjectileShootState(&pResult->shootGuidedProjectileState);
	MakeGuidedProjectileNotShootState(&pResult->notShootGuidedProjectileState);
	
	
	//Initialize all variable of 'UpperBody'
	WEVec2Set(&pResult->aimInfo.mousePos, 0.f, 0.f);
	WEVec2Set(&pResult->aimInfo.difference, 0.f, 0.f);
	WEVec2Set(&pResult->aimInfo.unitVector, 0.f, 0.f);
	pResult->aimInfo.angle = 0;

	//BulletManagerMake(&pResult->bulletManager, textureID);
	MakeWeapon(&pResult->weapon);
	pResult->weapon.ownerType = OT_PLAYER;
	pResult->weapon.weaponType = MACHINE_GUN;

	//Make FSM
	MakeStackFSM(&pResult->fsm, pResult, 3);
	pResult->fsm.Push(&pResult->fsm, &pResult->notShootMachineGunState);

}
/******************************************************************************/
/******************************************************************************/
void UpperBodyUpdate(UpperBody* pSelf, MainBody* pUnder,
	const TileMap* pMap, EnemyList* pEnemyList, float dt)
{	
	WEVec2 mousePos;
	WEVec2 difference;
	WEVec2 front = { 1.f, 0.f };

	WEUNUSED_PARAM(pMap);
	WEUNUSED_PARAM(pEnemyList);

	mousePos.x = (float)WEInputGetMouseX();
	mousePos.y = (float)WEInputGetMouseY();

	WEGraphicsConvertScreenToWorld(&mousePos.x, &mousePos.y);

	difference.x = mousePos.x - pSelf->base.pos.x;  // cos theta
	difference.y = mousePos.y - pSelf->base.pos.y;  // sin theta

	float angle = WEVec2Dot(&difference, &front);

	if (angle < 0.f && pSelf->base.scale.x >= 0)
	{
		pSelf->base.scale.x *= -1.f;
	}
	else if (angle >= 0.f && pSelf->base.scale.x <= 0)
	{
		pSelf->base.scale.x *= -1.f;
	}

	//pSelf->fsm.GetCurrentState 
	pSelf->fsm.Update(&pSelf->fsm, dt);

	pSelf->base.pos = pUnder->base.pos;
	//pSelf->base.pos.y += pUnder->base.scale.y / 2.f;

	UpperBodyAimController(pSelf);
	//Function to update 'Bullet'
	//BulletManagerUpdate(&pSelf->bulletManager, pMap, pEnemyList, dt);
	//Function to count 'Bullet'
	//BulletManagerCount(&pSelf->bulletManager);
	//Function to delete 'Bullet'
	//BulletManagerDelete(&pSelf->bulletManager);
}

/******************************************************************************/
/******************************************************************************/
void UpperBodyDraw(const UpperBody* pSelf)
{
	WEMtx44 transform;
	WEMtx44MakeTransform(&transform,
		pSelf->base.scale.x,
		pSelf->base.scale.y,
		0,
		pSelf->base.pos.x,
		pSelf->base.pos.y + 1.f - pSelf->base.scale.y / 2.f,
		pSelf->base.zOrder);

	WEGraphicsSetTexture(pSelf->base.texture);


	WEGraphicsSetAttributeColor4(255, 255, 255, 255);

	WEGraphicsDraw(&transform);


	//BulletManagerDraw(&pSelf->bulletManager);
}

/******************************************************************************/
/******************************************************************************/
void UpperBodyAimController(UpperBody* pSelf)
{
	//Get Mouse Position
	pSelf->aimInfo.mousePos.x = (float)WEInputGetMouseX();
	pSelf->aimInfo.mousePos.y = (float)WEInputGetMouseY();

	//Convert to world coordinate
	WEGraphicsConvertScreenToWorld(&pSelf->aimInfo.mousePos.x, &pSelf->aimInfo.mousePos.y);

	//Get difference between mouse & MainBodya position
	pSelf->aimInfo.difference.x = pSelf->aimInfo.mousePos.x - pSelf->base.pos.x;  // cos theta
	pSelf->aimInfo.difference.y = pSelf->aimInfo.mousePos.y - pSelf->base.pos.y;  // sin theta

	//Get the angle for change animation of 'UpperBody'
	pSelf->aimInfo.angle
		= (float)atan2(pSelf->aimInfo.difference.y, pSelf->aimInfo.difference.x) * (180 / WE_MATH_PI);


	pSelf->aimInfo.unitVector.x
		= pSelf->aimInfo.difference.x / WEVec2Distance(&pSelf->aimInfo.mousePos, &pSelf->base.pos);

	pSelf->aimInfo.unitVector.y
		= pSelf->aimInfo.difference.y / WEVec2Distance(&pSelf->aimInfo.mousePos, &pSelf->base.pos);

	if (pSelf->aimInfo.angle < 0.f)
		pSelf->aimInfo.angle += 360.f;

	//WEVec2Normalize(&pSelf->bulletManager.unitVector, &pSelf->aimInfo.normalizedVector);
}
/******************************************************************************/
/******************************************************************************/
void UpperBodyDelete(UpperBody* pDelete)
{
	//BulletManagerAllDelete(&pDelete->bulletManager);
	FSMDeleteStack(&pDelete->fsm);
}