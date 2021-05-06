#include "Boss.h"
#include "WarpEngine.h"
#include "Boss1Move.h"
#include "Boss1Attack.h"
#include "Fireball.h"
#include <stdlib.h>
#include <math.h>



Entity* Boss_New(float width, float height, float x, float y,
	float scaleX, float scaleY, float maxSpeed,
	int gearTextureID, int hpBarTextureID, int eyeTextureID,
	float health, Entity* pTarget)
{
	Entity* pNew = (Entity*)malloc(sizeof(Entity));
	MakeEntity(pNew, width, height, x, y,
		scaleX, scaleY, maxSpeed, 0.f, hpBarTextureID, ET_BOSS, health);

	pNew->attackDelay = 2.f;
	pNew->gearTexture = gearTextureID;
	pNew->gearAngle = 0.f;
	pNew->gearSpeed = 1.f;
	pNew->eyeAngle = 0.f;
	pNew->eyeTexture = eyeTextureID;
	pNew->pTarget = pTarget;

	pNew->firstFireballOffset.x = 3.f;
	pNew->firstFireballOffset.y = 10.f;
	pNew->lastFireballOffset.x = 3.f;
	pNew->lastFireballOffset.y = -10.f;

	pNew->maxNumOfFB = 7;
	pNew->numOfFB = 0;
	pNew->fbShootTimer = 0.f;
	pNew->fbShootDuration = 0.5f;
	pNew->initialPos.x = x;
	pNew->initialPos.y = y;
	pNew->damage = 30.f;

	pNew->fireballArr = malloc(sizeof(Entity) * pNew->maxNumOfFB);
	int i = 0;
	i;
	for (i = 0; i < pNew->maxNumOfFB; ++i)
	{
		Fireball_Make(&pNew->fireballArr[i], x, y, 0.f, 0.f, pTarget);
		pNew->fireballArr[i].isDead = TRUE;
		pNew->numOfFB++;
	}

	pNew->bossWalk = malloc(sizeof(State));
	pNew->bossAttackIdle = malloc(sizeof(State));
	pNew->bossPattern1[0] = malloc(sizeof(State));
	pNew->bossPattern1[1] = malloc(sizeof(State));
	pNew->bossPattern2[0] = malloc(sizeof(State));
	pNew->bossPattern2[1] = malloc(sizeof(State));
	pNew->bossPattern3[0] = malloc(sizeof(State));
	pNew->bossPattern3[1] = malloc(sizeof(State));
	MakeBossWalkState(pNew->bossWalk);
	MakeBossAttackIdleState(pNew->bossAttackIdle);
	MakeBossFireballAttackState(pNew->bossPattern1[0]);
	MakeBossBombAttackState(pNew->bossPattern2[0]);
	MakeBossBeamAttackReadyState(pNew->bossPattern3[0]);
	MakeBossBeamAttackFireState(pNew->bossPattern3[1]);

	//WEVec2 initialPos = { x, y };

	pNew->moveFSM = malloc(sizeof(StackFSM));
	pNew->attackFSM = malloc(sizeof(StackFSM));
	MakeStackFSM(pNew->moveFSM, pNew, 2);
	MakeStackFSM(pNew->attackFSM, pNew, 5);

	FSMPush(pNew->moveFSM, pNew->bossWalk);
	FSMPush(pNew->attackFSM, pNew->bossAttackIdle);

	/*MakeBossWalkState(&pNew->walkState);
	FSMPush(&pNew->moveFsm, &pNew->walkState);

	MakeStackFSM(&pNew->attackFsm, pNew, 5);
	MakeBossAttackOneOneState(&pNew->pattern1[0]);
	MakeBossAttackOneTwoState(&pNew->pattern1[1]);
	MakeBossAttackOneThreeState(&pNew->pattern1[2]);
	MakeBossAttackTwoOneState(&pNew->pattern2[0]);
	MakeBossAttackTwoTwoState(&pNew->pattern2[1]);
	FSMPush(&pNew->attackFsm, &pNew->pattern1[0]);

	pNew->timer = 0.f;
	pNew->initialPosX = pNew->base.pos.x;
	pNew->pTarget = pTarget;*/

	return pNew;
}

void Boss_Release(Entity** ppSelf)
{
	if (*ppSelf)
	{
		Entity* pSelf = *ppSelf;
		int i = 0;
		for (i = 0; i < pSelf->numOfFB; ++i)
			FSMDeleteStack(&pSelf->fireballArr[i].fireballFSM);
		free(pSelf->fireballArr);
		free(pSelf->bossWalk);
		free(pSelf->bossAttackIdle);
		free(pSelf->bossPattern1[0]);
		free(pSelf->bossPattern1[1]);
		free(pSelf->bossPattern2[0]);
		free(pSelf->bossPattern2[1]);
		free(pSelf->bossPattern3[0]);
		free(pSelf->bossPattern3[1]);
		FSMDeleteStack(pSelf->moveFSM);
		FSMDeleteStack(pSelf->attackFSM);
		free(pSelf->moveFSM);
		free(pSelf->attackFSM);
		free(pSelf);
		*ppSelf = 0;
	}
}

void Boss_Update(Entity* pSelf, float dt)
{
	if (!pSelf)
		return;

	pSelf->gearAngle += pSelf->gearSpeed * dt;
	FSMUpdate(pSelf->moveFSM, dt);
	FSMUpdate(pSelf->attackFSM, dt);
	WEVec2 bossToPlayer;
	WEVec2Sub(&bossToPlayer, &pSelf->pTarget->pos, &pSelf->pos);
	pSelf->eyeAngle = atan2f(bossToPlayer.y, bossToPlayer.x);
	int i = 0;
	for (i = 0; i < pSelf->numOfFB; ++i)
	{
		if (pSelf->fireballArr[i].isDead == FALSE)
		{
			pSelf->fireballArr[i].pos.x += pSelf->maxSpeed * dt;
			pSelf->fireballArr[i].targetPos.x += pSelf->maxSpeed * dt;
			pSelf->fireballArr[i].initialPos.x += pSelf->maxSpeed * dt;
			FSMUpdate(&pSelf->fireballArr[i].fireballFSM, dt);
		}
	}
	
}

void Boss_Draw(const Entity* pSelf)
{
	WEMtx44 transform;

	if (!pSelf)
		return;

	WEMtx44MakeTransform(&transform,
		pSelf->scale.x * 10.f / 6.f,
		pSelf->scale.y * 10.f / 6.f,
		pSelf->gearAngle,
		pSelf->pos.x,
		pSelf->pos.y,
		pSelf->zOrder);
	WEGraphicsSetTexture(pSelf->gearTexture);
	WEGraphicsSetAttributeColor4(
		pSelf->color.r,
		pSelf->color.g,
		pSelf->color.b,
		pSelf->color.a);

	WEGraphicsDraw(&transform);
	Entity_Draw(pSelf, TRUE);
	WEMtx44MakeTransform(&transform,
	pSelf->scale.x * 0.7f,
	pSelf->scale.y * 0.7f,
	pSelf->eyeAngle,
	pSelf->pos.x,
	pSelf->pos.y,
	pSelf->zOrder);
	WEGraphicsSetTexture(pSelf->eyeTexture);
	WEGraphicsSetAttributeColor4(
	pSelf->color.r,
	pSelf->color.g,
	pSelf->color.b,
	pSelf->color.a);

	WEGraphicsDraw(&transform);

	int i = 0;
	for (i = 0; i < pSelf->numOfFB; ++i)
	{
		if (pSelf->fireballArr[i].isDead == TRUE)
			continue;
		WEMtx44MakeTransform(&transform,
			pSelf->fireballArr[i].scale.x,
			pSelf->fireballArr[i].scale.y,
			pSelf->fireballArr[i].rotation,
			pSelf->fireballArr[i].pos.x,
			pSelf->fireballArr[i].pos.y,
			pSelf->fireballArr[i].zOrder);
		WEGraphicsSetTexture(pSelf->fireballArr[i].texture);
		WEGraphicsSetAttributeColor4(
			pSelf->fireballArr[i].color.r,
			pSelf->fireballArr[i].color.g,
			pSelf->fireballArr[i].color.b,
			pSelf->fireballArr[i].color.a);
		WEGraphicsDraw(&transform);
	}
}