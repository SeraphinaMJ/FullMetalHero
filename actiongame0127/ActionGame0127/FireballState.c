#include "FireballState.h"
#include "State.h"
#include "Entity.h"
#include "Fireball.h"

void MakeFireballPhaseOneState(State* pResult)
{
	MakeState(pResult,
		FireballState_PhaseOneStart,
		FireballState_PhaseOneUpdate,
		FireballState_PhaseOneEnd);
}
void FireballState_PhaseOneStart(State* pState)
{
	pState;
}
void FireballState_PhaseOneUpdate(State* pState, float dt)
{
	Entity* pFireball = pState->actor;
	WEVec2 prevPos = pFireball->pos;
	pFireball->timer += dt;
	if (WEVec2NotEqual(&pFireball->pos, &pFireball->targetPos))
	{
		pFireball->pos.x =
			pFireball->initialPos.x * (pFireball->moveDuration - pFireball->timer) / pFireball->moveDuration
			+ pFireball->targetPos.x * pFireball->timer / pFireball->moveDuration;
		pFireball->pos.y =
			pFireball->initialPos.y * (pFireball->moveDuration - pFireball->timer) / pFireball->moveDuration
			+ pFireball->targetPos.y * pFireball->timer / pFireball->moveDuration;
	}
	WEVec2 dtVel;
	WEVec2Sub(&dtVel, &pFireball->pos, &prevPos);
	float dtVelLengthSq = WEVec2LengthSquared(&dtVel);
	dtVelLengthSq;
	WEVec2 distToTarget;
	WEVec2Sub(&distToTarget, &pFireball->targetPos, &pFireball->pos);
	float distLengthSq = WEVec2LengthSquared(&distToTarget);
	distLengthSq;
	if (distLengthSq < dtVelLengthSq || WEVec2Equal(&pFireball->pos, &pFireball->targetPos))
	{
		pFireball->readyTimer += dt;
		if (pFireball->readyTimer >= pFireball->moveDuration)
		{
			FSM_ChangeState(&pFireball->fireballFSM, &pFireball->fireballMove[1]);
			return;
		}
		pFireball->pos.x = pFireball->targetPos.x;
		pFireball->pos.y = pFireball->targetPos.y;
		
		return;
	}

	Fireball_CollideToTarget(pFireball);
}
void FireballState_PhaseOneEnd(State* pState)
{
	Entity* pFireball = pState->actor;
	pFireball->timer = 0.f;
	pFireball->readyTimer = 0.f;
}

void MakeFireballPhaseTwoState(State* pResult)
{
	MakeState(pResult,
		FireballState_PhaseTwoStart,
		FireballState_PhaseTwoUpdate,
		FireballState_PhaseTwoEnd);
}
void FireballState_PhaseTwoStart(State* pState)
{
	pState;
}
void FireballState_PhaseTwoUpdate(State* pState, float dt)
{
	Entity* pFireball = pState->actor;
	pFireball->pos.x += pFireball->vel.x * dt;
	pFireball->pos.y += pFireball->vel.y * dt;

	Fireball_CollideToTarget(pFireball);
}
void FireballState_PhaseTwoEnd(State* pState)
{
	pState;
}