#include "Boss1Move.h"
#include "State.h"
#include "Entity.h"
#include <math.h>

void MakeBossWalkState(State* pResult)
{
	MakeState(pResult,
		BossState_WalkStart,
		BossState_WalkUpdate,
		BossState_WalkEnd);
}
void BossState_WalkStart(State* pState)
{
	pState;
}
void BossState_WalkUpdate(State* pState, float dt)
{
	Entity* pBoss = pState->actor;

	float maxYspeed = 5.f;

	/*if (fabsf(pBoss->pTarget->pos.y - pBoss->pos.y) < pBoss->vel.y * dt)
	{
	pBoss->pos.y = pBoss->pTarget->pos.y;
	}
	else */if (pBoss->pTarget->pos.y > pBoss->pos.y)
	{
		pBoss->vel.y += 7.f * dt;
	}
	else if (pBoss->pTarget->pos.y < pBoss->pos.y)
	{
		pBoss->vel.y -= 7.f * dt;
	}

	if (fabsf(pBoss->vel.y) > maxYspeed)
	{
		pBoss->vel.y = pBoss->vel.y > 0 ? maxYspeed : -maxYspeed;
	}

	pBoss->pos.x += pBoss->maxSpeed * dt;
	pBoss->initialPos.x += pBoss->maxSpeed * dt;
	pBoss->pos.x += pBoss->vel.x * dt;
	pBoss->pos.y += pBoss->vel.y * dt;
}
void BossState_WalkEnd(State* pState)
{
	pState;
}