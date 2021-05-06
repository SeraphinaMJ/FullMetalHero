#include "Boss1Attack.h"
#include "State.h"
#include "StackFSM.h"
#include "Entity.h"
#include "Player.h"
#include "BulletList.h"
#include "TextureList.h"
#include "Fireball.h"
#include <math.h>
#include "WarpEngine.h"
#include <stdlib.h>

void MakeBossAttackIdleState(State* pResult)
{
	MakeState(pResult,
		BossState_AttackIdleStart,
		BossState_AttackIdleUpdate,
		BossState_AttackIdleEnd);
}
void BossState_AttackIdleStart(State* pState)
{
	Entity* pBoss = pState->actor;
	pBoss->timer = 0.f;
}
void BossState_AttackIdleUpdate(State* pState, float dt)
{
	Entity* pBoss = pState->actor;
	pBoss->timer += dt;
	if (pBoss->timer >= pBoss->attackDelay)
	{
		int patternNum = rand() % 2 + 1;
		//WEDEBUG_PRINT("%d\n", patternNum);
		switch (patternNum)
		{
		case 1:
			FSMPush(pBoss->attackFSM, pBoss->bossPattern1[0]);
			break;
		case 2:
			FSMPush(pBoss->attackFSM, pBoss->bossPattern3[0]);
			break;
		}
		
		pBoss->timer = 0.f;
		return;
	}
}
void BossState_AttackIdleEnd(State* pState)
{
	Entity* pBoss = pState->actor;
	pBoss->timer = 0.f;
}

void MakeBossFireballAttackState(State* pResult)
{
	MakeState(pResult,
		BossState_FireballAttackStart,
		BossState_FireballAttackUpdate,
		BossState_FIreballAttackEnd);
}
void BossState_FireballAttackStart(State* pState)
{
	Entity* pBoss = pState->actor;
	pBoss->fbShootTimer = 0.f;
	int i = 0;
	WEVec2 firstPos;
	WEVec2 lastPos;
	WEVec2 dist;
	WEVec2Add(&firstPos, &pBoss->pos, &pBoss->firstFireballOffset);
	WEVec2Add(&lastPos, &pBoss->pos, &pBoss->lastFireballOffset);
	WEVec2Sub(&dist, &lastPos, &firstPos);
	if (pBoss->numOfFB == 1)
	{
		pBoss->fireballArr[0].pos = pBoss->pos;
		pBoss->fireballArr[0].targetPos.x =
			firstPos.x * 0.5f
			+ lastPos.x * 0.5f;
		pBoss->fireballArr[i].targetPos.y =
			firstPos.y * 0.5f
			+ lastPos.y * 0.5f;
		pBoss->fireballArr[0].initialPos.x = pBoss->pos.x;
		pBoss->fireballArr[0].initialPos.y = pBoss->pos.y;
		pBoss->fireballArr[0].vel.x = 20.f;
		pBoss->fireballArr[0].isDead = FALSE;
		pBoss->fireballArr[0].moveDuration = 0.5f;
		FSM_ChangeState(&pBoss->fireballArr[0].fireballFSM, &pBoss->fireballArr[0].fireballMove[0]);
	}
	else
		for (i = 0; i < pBoss->numOfFB; ++i)
		{
			//Fireball_Make(&pBoss->fireballArr[i], pBoss->pos.x, pBoss->pos.y, i, 0.f);
			pBoss->fireballArr[i].pos = pBoss->pos;
			pBoss->fireballArr[i].targetPos.x =
				firstPos.x * (float)(pBoss->numOfFB - 1 - i) / (float)(pBoss->numOfFB - 1)
				+ lastPos.x * (float)i / (float)(pBoss->numOfFB - 1);
			pBoss->fireballArr[i].targetPos.y =
				firstPos.y * (float)(pBoss->numOfFB - 1 - i) / (float)(pBoss->numOfFB - 1)
				+ lastPos.y * (float)i / (float)(pBoss->numOfFB - 1);
			pBoss->fireballArr[i].initialPos.x = pBoss->pos.x;
			pBoss->fireballArr[i].initialPos.y = pBoss->pos.y;
			pBoss->fireballArr[i].vel.x = 40.f;
			pBoss->fireballArr[i].isDead = FALSE;
			pBoss->fireballArr[i].moveDuration = 0.5f + abs(i - (pBoss->numOfFB / 2)) / 10.f;
			FSM_ChangeState(&pBoss->fireballArr[i].fireballFSM, &pBoss->fireballArr[i].fireballMove[0]);
		}
}

void BossState_FireballAttackUpdate(State* pState, float dt)
{
	Entity* pBoss = pState->actor;
	dt;
	/*pBoss->fbShootTimer += dt;
	if (pBoss->fbShootTimer >= pBoss->fbShootDuration)
	{
		pBoss->fbShootTimer = 0.f;
		
	}*/
	int i = 0;
	BOOL isEnded = TRUE;
	for (i = 0; i < pBoss->numOfFB; ++i)
	{
		
		//FSMUpdate(&pBoss->fireballArr[i].fireballFSM, dt);
		if (pBoss->fireballArr[i].isDead == FALSE && pBoss->fireballArr[i].pos.x < pBoss->pos.x + 50.f)
		{
			isEnded = FALSE;
		}
	}

	if (isEnded)
	{
		FSMPop(pBoss->attackFSM);
		return;
	}
}



void BossState_FIreballAttackEnd(State* pState)
{
	Entity* pBoss = pState->actor;
	int i = 0;
	for (i = 0; i < pBoss->numOfFB; ++i)
	{
		//Fireball_Make(&pBoss->fireballArr[i], pBoss->pos.x, pBoss->pos.y, i, 0.f);
		//pBoss->fireballArr[i].pos = pBoss->pos;
		pBoss->fireballArr[i].vel.x = 0.f;
		pBoss->fireballArr[i].isDead = TRUE;
	}
}

void MakeBossBombAttackState(State* pResult)
{
	MakeState(pResult,
		BossState_BombAttackStart,
		BossState_BombAttackUpdate,
		BossState_BombAttackEnd);
}
void BossState_BombAttackStart(State* pState)
{
	pState;
}
void BossState_BombAttackUpdate(State* pState, float dt)
{
	pState; dt;
}
void BossState_BombAttackEnd(State* pState)
{
	pState;
}

void MakeBossBeamAttackReadyState(State* pResult)
{
	MakeState(pResult,
		BossState_BeamAttackReadyStart,
		BossState_BeamAttackReadyUpdate,
		BossState_BeamAttackReadyEnd);
}
void BossState_BeamAttackReadyStart(State* pState)
{
	Entity* pBoss = pState->actor;
	pBoss->timer = 0.f;
}
void BossState_BeamAttackReadyUpdate(State* pState, float dt)
{
	Entity* pBoss = pState->actor;
	pBoss->gearSpeed += 5.f * dt;
	if (pBoss->gearSpeed >= 10.f)
	{
		pBoss->gearSpeed = 10.f;
	}
	pBoss->timer += dt;
	if (pBoss->timer >= 2.f)
	{
		pBoss->timer = 0.f;
		FSM_ChangeState(pBoss->attackFSM, pBoss->bossPattern3[1]);
		return;
	}

	if (WEIntersectionCircleRect(&pBoss->pos,
		pBoss->aabb.x / 2.f,
		&pBoss->pTarget->pos,
		pBoss->pTarget->aabb.x,
		pBoss->pTarget->aabb.y) && pBoss->pTarget->isInvincible == FALSE
		&& pBoss->pTarget->isRolling == FALSE)
	{
		Player_ApplyDamage(pBoss->pTarget, pBoss->damage);
	}
	
}
void BossState_BeamAttackReadyEnd(State* pState)
{
	pState;
}

void MakeBossBeamAttackFireState(State* pResult)
{
	MakeState(pResult,
		BossState_BeamAttackFireStart,
		BossState_BeamAttackFireUpdate,
		BossState_BeamAttackFireEnd);
}
void BossState_BeamAttackFireStart(State* pState)
{
	Entity* pBoss = pState->actor;
	pBoss->timer = 0.f;
	pBoss->vel.x = 30.f;
}
void BossState_BeamAttackFireUpdate(State* pState, float dt)
{
	Entity* pBoss = pState->actor;
	pBoss->timer += dt;
	if (pBoss->timer >= 1.f)
	{
		if (pBoss->vel.x > 0.f)
		{
			pBoss->vel.x = -30.f;
			pBoss->timer = 0.f;
		}
		else
		{
			pBoss->gearSpeed -= 5.f * dt;
			pBoss->vel.x = 0.f;
			pBoss->pos.x = pBoss->initialPos.x;
			if (pBoss->gearSpeed <= 1.f)
			{
				pBoss->gearSpeed = 1.f;
				FSMPop(pBoss->attackFSM);
				return;
			}
			
			
		}
		
	}

	if (WEIntersectionCircleRect(&pBoss->pos,
		pBoss->aabb.x / 2.f,
		&pBoss->pTarget->pos,
		pBoss->pTarget->aabb.x,
		pBoss->pTarget->aabb.y) && pBoss->pTarget->isInvincible == FALSE
		&& pBoss->pTarget->isRolling == FALSE)
	{
		Player_ApplyDamage(pBoss->pTarget, pBoss->damage);
	}
}
void BossState_BeamAttackFireEnd(State* pState)
{
	Entity* pBoss = pState->actor;
	pBoss->timer = 0.f;
}