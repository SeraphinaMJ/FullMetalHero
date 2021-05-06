#include "Fireball.h"
#include "Entity.h"
#include "FireballState.h"
#include "TextureList.h"
#include "WarpEngine.h"
#include "Player.h"

//Entity* Fireball_New(float vx, float vy)
//{
//	Entity
//}

void Fireball_Make(Entity* pResult, float x, float y, 
	float vx, float vy, Entity* pTarget)
{
	MakeEntity(pResult, 1.5f, 1.5f, x, y, 1.5f, 1.5f, 0.f, 0.f, TextureList_GetID(TX_CIRCLE),
		ET_FIREBALL, 0.f);
	/*pResult->color.r = 120;
	pResult->color.g = 120;*/
	pResult->vel.x = vx;
	pResult->vel.y = vy;
	pResult->initialPos.x = x;
	pResult->initialPos.y = y;
	pResult->damage = 10.f;
	pResult->moveDuration = 1.f;
	pResult->readyTimer = 0.f;
	pResult->pTarget = pTarget;
	MakeFireballPhaseOneState(&pResult->fireballMove[0]);
	MakeFireballPhaseTwoState(&pResult->fireballMove[1]);
	MakeStackFSM(&pResult->fireballFSM, pResult, 2);
	FSMPush(&pResult->fireballFSM, &pResult->fireballMove[0]);
}

void Fireball_CollideToTarget(Entity* pBall)
{
	if (pBall->isDead == FALSE)
	{
		if (WEIntersectionCircleRect(&pBall->pos,
			pBall->aabb.x / 2.f,
			&pBall->pTarget->pos,
			pBall->pTarget->aabb.x,
			pBall->pTarget->aabb.y) && pBall->pTarget->isInvincible == FALSE
			&& pBall->pTarget->isRolling == FALSE)
		{
			pBall->isDead = TRUE;
			Player_ApplyDamage(pBall->pTarget, pBall->damage);
		}
	}
}

//void FireBall_Release(Entity)