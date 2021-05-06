/******************************************************************************/
/*!
\file   MainBody.cpp
\author Illkwon Ha
\par    email: haik0925\@gmail.com
\brief
This is the source file which contains main informations of MainBody.
*/
/******************************************************************************/
//Header file related to the implementation
#include "MainBody.h"

//Project-related headers
#include "Idle.h"
#include "Run.h"
#include "Jump.h"
#include "Fall.h"
#include "Roll.h"
#include "Damaged.h"
#include "pinvinciblestates.h"
#include "LayerInfo.h"

//Standard library headers
#include<math.h>
#include <stdlib.h>

#include "WarpEngine.h"

void MakeMainBody(MainBody* pResult,
	float width, float height, float x, float y,
	float scaleX, float scaleY, float maxSpeed, float jumpSpeed, int textureID)
{
	MakeEntity(&pResult->base, width, height, x, y, scaleX, scaleY, 
		maxSpeed, jumpSpeed, textureID, ET_MAINBODY, 100.f);

	//delete later
	pResult->damageFlag = FALSE;
	pResult->invincibleFlag = FALSE;
	pResult->isRolling = FALSE;

	pResult->walkSpeed = maxSpeed;
	pResult->dashSpeed = maxSpeed * 2.f;

	pResult->restJump = 2;
	pResult->damageTimer = 0;
	pResult->invincibleTimer = 0.f;
	pResult->timer = 0;
	pResult->rollTime = 0.3f;

	//pResult->currentState = MainBodyIdleState;
	MakeMainBodyIdleState(&pResult->idleState);
	MakeMainBodyRunState(&pResult->runState);
	MakeMainBodyJumpIdleState(&pResult->jumpIdleState);
	MakeMainBodyJumpRunState(&pResult->jumpRunState);
	MakeMainBodyFallIdleState(&pResult->fallIdleState);
	MakeMainBodyFallRunState(&pResult->fallRunState);
	MakeMainBodyRollState(&pResult->rollState);
	MakeMainBodyDamagedState(&pResult->damagedState);

	MakeMainBodyNormalState(&pResult->normalState);
	MakeMainBodyInvincibleState(&pResult->invincibleState);

	pResult->UpdateSM = MainBodySMUpdate;
	pResult->Run = MainBodyRun;
	pResult->Stop = MainBody_Stop;
	pResult->Jump = MainBodyJump;
	pResult->ResetJump = MainBodyResetJump;
	pResult->GetDamageFlag = MainBodyGetDamageFlag;
	pResult->SetDamageFlag = MainBodySetDamageFlag;
	pResult->ApplyDamage = MainBodyApplyDamage;
	pResult->GetInvincibleFlag = MainBody_GetInvincibleFlag;
	pResult->SetInvincibleFlag = MainBody_SetInvincibleFlag;

	MakeStackFSM(&pResult->fsm, pResult, 10);
	pResult->fsm.Push(&pResult->fsm, &pResult->idleState);
	
	MakeStackFSM(&pResult->invincibleFsm, pResult, 3);
	pResult->invincibleFsm.Push(&pResult->invincibleFsm, 
		&pResult->normalState);

	pResult->onDebug = 0;
}

void DeleteMainBody(MainBody* pDelete)
{
	FSMDeleteStack(&pDelete->fsm);
	FSMDeleteStack(&pDelete->invincibleFsm);
}

void MainBodySMUpdate(MainBody* pSelf, float dt)
{
	WEVec2 mousePos;
	WEVec2 difference;
	WEVec2 front = { 1.f, 0.f };

	if (pSelf->base.onGround)
	{
		if (pSelf->restJump != 2)
		{
			pSelf->ResetJump(pSelf);
		}
	}
	pSelf->fsm.Update(&pSelf->fsm, dt);
	pSelf->invincibleFsm.Update(&pSelf->invincibleFsm, dt);



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
}

void MainBody_Draw(const MainBody* pSelf)
{
	WEMtx44 transform;

	WEMtx44MakeTransform(&transform,
		pSelf->base.scale.x, pSelf->base.scale.y,
		pSelf->base.rotation,
		pSelf->base.pos.x, 
		pSelf->base.pos.y - 1.f + pSelf->base.scale.y / 2.f,
		pSelf->base.zOrder);
	WEGraphicsSetTexture(pSelf->base.texture);
	/*WEGraphicsSetAttributeColor4(
		pSelf->base.color.r, pSelf->base.color.g,
		pSelf->base.color.b, pSelf->base.color.a);*/


	WEGraphicsDraw(&transform);
}

void MainBodyRun(MainBody* pSelf, int direction, float dt)
{	
	if (direction > 0)
	{
		pSelf->base.vel.x += pSelf->base.accel.x * dt;
		if (pSelf->base.vel.x < 0)
			pSelf->base.vel.x += pSelf->base.accel.x * dt * 0.5f;
		if (pSelf->base.vel.x > pSelf->base.maxSpeed)
			pSelf->base.vel.x = pSelf->base.maxSpeed;
	}
	else if (direction < 0)
	{
		pSelf->base.vel.x -= pSelf->base.accel.x * dt;
		if (pSelf->base.vel.x > 0)
			pSelf->base.vel.x -= pSelf->base.accel.x * dt * 0.5f;
		if (pSelf->base.vel.x < -pSelf->base.maxSpeed)
			pSelf->base.vel.x = -pSelf->base.maxSpeed;
	}
}

void MainBody_Stop(MainBody* pSelf, float dt)
{
	//Make MainBody's velocity to zero gradually
	if (fabsf(pSelf->base.vel.x) > (pSelf->base.accel.x * dt))
	{
		if (pSelf->base.vel.x > 0.f)
		{
			pSelf->base.vel.x -= pSelf->base.accel.x * dt;
		}
		if (pSelf->base.vel.x < 0.f)
		{
			pSelf->base.vel.x += pSelf->base.accel.x * dt;
		}
	}
	else
	{
		pSelf->base.vel.x = 0.f;
	}
}

void MainBodyJump(MainBody* pSelf)
{
	if (pSelf->restJump > 0)
	{
		pSelf->base.vel.y = pSelf->base.jumpSpeed;
		pSelf->restJump -= 1;
		pSelf->base.onGround = 0;
	}
	
}

void MainBodyResetJump(MainBody* pSelf)
{
	pSelf->restJump = 2;
}

BOOL MainBodyGetDamageFlag(MainBody* pSelf)
{
	return pSelf->damageFlag;
}

void MainBodySetDamageFlag(MainBody* pSelf, BOOL flag)
{
	pSelf->damageFlag = flag;
}

void MainBodyApplyDamage(MainBody* pSelf, float damage)
{
	pSelf->base.hp -= damage;
	if (pSelf->base.hp < 0.f)
		pSelf->base.hp = 0.f;

	pSelf->SetDamageFlag(pSelf, TRUE);
	pSelf->SetInvincibleFlag(pSelf, TRUE);

	pSelf->fsm.Push(&pSelf->fsm, &pSelf->damagedState);
}

BOOL MainBody_GetInvincibleFlag(MainBody* pSelf)
{
	return pSelf->invincibleFlag;
}
void MainBody_SetInvincibleFlag(MainBody* pSelf, BOOL flag)
{
	pSelf->invincibleFlag = flag;
}