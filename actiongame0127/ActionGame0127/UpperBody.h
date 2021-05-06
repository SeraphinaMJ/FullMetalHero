/******************************************************************************/
/*!
\file   UpperBody.h
\author Yeongjin Kil
\par    email: blue125kr\@gmail.com
\brief
This is the header file about UpperBody
*/
/******************************************************************************/
#ifndef UPPERBODY_H
#define UPPERBODY_H

//Project-related headers
#include "WeaponManager.h"
#include "Entity.h"
#include "State.h"
#include "StackFSM.h"

//Third-party headers
#include "WarpEngine.h"

//Declaration structs
typedef struct MainBody MainBody;
typedef struct TileMap TileMap;
typedef struct EnemyList EnemyList;

//typedef struct AimInfo
//{
//	WEVec2 mousePos;		//Vector to get mouse position
//	WEVec2 difference;		//Distance between the mouse and the MainBody.
//	WEVec2 unitVector;
//	float angle;			//Angle between the MainBody and mouse
//}AimInfo;

typedef struct UpperBody
{
	Entity base;

	AimInfo aimInfo;
	Weapon weapon;

	State shootMachineGunState;		//State which can shoot
	State notShootMachineGunState;	//State which can't shoot
	State shootMissileGunState;
	State notShootMissileGunState;
	State shootGuidedProjectileState;
	State notShootGuidedProjectileState;

	StackFSM fsm;			//Finite-state manchine

}UpperBody;

//Function to make basic stuffs of 'UpperBody'
void UpperBodyMake(UpperBody* pResult,
	float width, float height, float x, float y,
	float scaleX, float scaleY, float maxSpeed, float jumpSpeed, int textureID);

//Function to update the variables of 'UpperBody'
void UpperBodyUpdate(UpperBody* pResult, MainBody* pSelf, 
	const TileMap* pMap, EnemyList* pEnemyList, float dt);

//Function to draw 'UpperBody'
void UpperBodyDraw(const UpperBody* pSelf);

//Function to calculate stuffs for aim
void UpperBodyAimController(UpperBody* pSelf);

//Fuction to delete 'UpperBody'
void UpperBodyDelete(UpperBody* pDelete);

#endif