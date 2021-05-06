#include "BossMove.h"
#include "State.h"
#include "Boss.h"

void MakeBossWalkState(State* pResult)
{
	MakeState(pResult,
		BossStateWalkStart,
		BossStateWalkUpdate,
		BossStateWalkEnd);
}

void BossStateWalkStart(State* pState)
{
	Boss* pBoss = pState->actor;
	WEUNUSED_PARAM(pBoss);
}
void BossStateWalkUpdate(State* pState, float dt)
{
	Boss* pBoss = pState->actor;
	//WEUNUSED_PARAM(pBoss);
	//WEUNUSED_PARAM(dt);

	pBoss->base.pos.x += pBoss->base.maxSpeed * dt;
	pBoss->initialPosX += pBoss->base.maxSpeed * dt;
	pBoss->base.pos.x += pBoss->base.vel.x * dt;
	pBoss->base.pos.y += pBoss->base.vel.y * dt;
}
void BossStateWalkEnd(State* pState)
{
	Boss* pBoss = pState->actor;
	WEUNUSED_PARAM(pBoss);
}