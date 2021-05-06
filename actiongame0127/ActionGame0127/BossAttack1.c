#include "BossAttack1.h"
#include "State.h"
#include "StackFSM.h"
#include "Boss.h"

void MakeBossAttackOneOneState(State* pResult)
{
	MakeState(pResult,
		BossStateAttackOneOneStart,
		BossStateAttackOneOneUpdate,
		BossStateAttackOneOneEnd);
}

void BossStateAttackOneOneStart(State* pState)
{
	Boss* pBoss = pState->actor;

	pBoss->base.vel.x = -1.5f;
	pBoss->timer = 0.f;
}
void BossStateAttackOneOneUpdate(State* pState, float dt)
{
	Boss* pBoss = pState->actor;
	StackFSM* fsm = &pBoss->attackFsm;
	pBoss->timer += dt;
	if (pBoss->timer >= 3.f)
	{
		FSM_ChangeState(fsm, &pBoss->pattern1[1]);
		return;
	}
}
void BossStateAttackOneOneEnd(State* pState)
{
	Boss* pBoss = pState->actor;
	pBoss->timer = 0.f;
}



void MakeBossAttackOneTwoState(State* pResult)
{
	MakeState(pResult,
		BossStateAttackOneTwoStart,
		BossStateAttackOneTwoUpdate,
		BossStateAttackOneTwoEnd);
}

void BossStateAttackOneTwoStart(State* pState)
{
	Boss* pBoss = pState->actor;

	pBoss->base.vel.x = 60.f;
	pBoss->timer = 0.f;
}
void BossStateAttackOneTwoUpdate(State* pState, float dt)
{
	Boss* pBoss = pState->actor;
	StackFSM* fsm = &pBoss->attackFsm;
	pBoss->timer += dt;
	if (pBoss->timer >= 0.4f)
	{
		FSM_ChangeState(fsm, &pBoss->pattern1[2]);
	}

	if (WEIntersectionRectRect(
		&pBoss->base.pos,
		pBoss->base.aabb.x,
		pBoss->base.aabb.y,
		&pBoss->pTarget->pos,
		pBoss->pTarget->aabb.x,
		pBoss->pTarget->aabb.y))
	{
		if (pBoss->pTarget->isInvincible == FALSE)
		{
			Player_ApplyDamage(pBoss->pTarget, 10.f);
		}
	}
}
void BossStateAttackOneTwoEnd(State* pState)
{
	Boss* pBoss = pState->actor;
	pBoss->timer = 0.f;
}


void MakeBossAttackOneThreeState(State* pResult)
{
	MakeState(pResult,
		BossStateAttackOneThreeStart,
		BossStateAttackOneThreeUpdate,
		BossStateAttackOneThreeEnd);
}

void BossStateAttackOneThreeStart(State* pState)
{
	Boss* pBoss = pState->actor;
	pBoss->timer = 0.f;
	pBoss->base.vel.x = 
		(pBoss->initialPosX - pBoss->base.pos.x) / 5.f;
}
void BossStateAttackOneThreeUpdate(State* pState, float dt)
{
	Boss* pBoss = pState->actor;
	StackFSM* fsm = &pBoss->attackFsm;
	pBoss->timer += dt;
	if (pBoss->timer >= 5.f)
	{
		pBoss->base.pos.x = pBoss->initialPosX;
		FSM_ChangeState(fsm, &pBoss->pattern2[0]);
		return;
	}
}
void BossStateAttackOneThreeEnd(State* pState)
{
	Boss* pBoss = pState->actor;
	pBoss->timer = 0.f;
	pBoss->base.vel.x = 0.f;
}