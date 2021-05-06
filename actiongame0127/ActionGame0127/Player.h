/******************************************************************************/
/*!
\file   Player.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file which contains main informations of Player.
*/
/******************************************************************************/
#ifndef PLAYER_H
#define PLAYER_H

//#include "UpperBody.h"
//#include "MainBody.h"

typedef struct Entity Entity;
typedef struct TileMap TileMap;
typedef struct EnemyList EnemyList;

Entity* Player_New(float width, float height, float x, float y, 
	float scaleX, float scaleY, float maxSpeed, float jumpSpeed, 
	int upperTextureID, int mainTextureID);
void Player_Release(Entity** ppSelf);

void Player_Update(Entity* pSelf, TileMap* pMap,
	EnemyList* pEnemyList, float dt);
void Player_Draw(const Entity* pSelf);

void Player_ArmAimControl(Entity* pPlayer);
void Player_Run(Entity* pSelf, int direction, float dt);
void Player_Stop(Entity* pSelf, float dt);
void Player_Jump(Entity* pSelf);
void Player_ResetJump(Entity* pSelf);
void Player_ApplyDamage(Entity* pSelf, float damage);
#endif//PLAYER_H