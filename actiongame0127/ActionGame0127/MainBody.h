/******************************************************************************/
/*!
\file   MainBody.h
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the header file which contains main informations of MainBody.
*/
/******************************************************************************/
#ifndef MAINBODY_H
#define MAINBODY_H

//Project-related headers
#include "Entity.h"

#include "StackFSM.h"
#include "State.h"

typedef struct MainBody{
	Entity base;

	BOOL damageFlag;
	BOOL invincibleFlag;
	BOOL isRolling; // If the MainBody is doing rolling action, it becomes true.


	float walkSpeed;
	float dashSpeed;
	
	int restJump;
	float damageTimer;
	float invincibleTimer;
	float timer; // for anything so far.
	float rollTime;

	State idleState;
	State runState;
	State jumpIdleState;
	State jumpRunState;
	State fallIdleState;
	State fallRunState;
	State damagedState;
	State rollState;

	State normalState;
	State invincibleState;

	int onDebug;

	StackFSM fsm;
	StackFSM invincibleFsm; // FSM for invincible states.

	void (*UpdateSM) (struct MainBody*, float);
	void (*Run) (struct MainBody*, int, float);
	void(*Stop)(struct MainBody*, float);
	void (*Jump) (struct MainBody*);
	void(*ResetJump)(struct MainBody*);
	BOOL(*GetDamageFlag) (struct MainBody*);
	void(*SetDamageFlag)(struct MainBody*, BOOL);
	void(*ApplyDamage)(struct MainBody*, float);
	BOOL(*GetInvincibleFlag)(struct MainBody*);
	void(*SetInvincibleFlag)(struct MainBody*, BOOL);
}MainBody;

void MakeMainBody(MainBody* pResult,
	float width, float height, float x, float y,
	float scaleX, float scaleY, float maxSpeed, float jumpSpeed, int textureID);
void DeleteMainBody(MainBody* pDelete);

void MainBodySMUpdate(MainBody* pSelf, float dt);
void MainBody_Draw(const MainBody* pSelf);

void MainBodyRun(MainBody* pSelf, int direction, float dt);
void MainBody_Stop(MainBody* pSelf, float dt);
void MainBodyJump(MainBody* pSelf);
void MainBodyResetJump(MainBody* pSelf);
BOOL MainBodyGetDamageFlag(MainBody* pSelf);
void MainBodySetDamageFlag(MainBody* pSelf, BOOL flag);
void MainBodyApplyDamage(MainBody* pSelf, float damage);
BOOL MainBody_GetInvincibleFlag(MainBody* pSelf);
void MainBody_SetInvincibleFlag(MainBody* pSelf, BOOL flag);

#endif //MAINBODY_H