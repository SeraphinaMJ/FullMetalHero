#include "BossAttack2.h"
#include "State.h"
#include "StackFSM.h"
#include "Boss.h"
#include "Enemy.h"
#include "TextureList.h"
#include "EntityManager.h"

void MakeBossAttackTwoOneState(State* pResult)
{
	MakeState(pResult,
		BossStateAttackTwoOneStart,
		BossStateAttackTwoOneUpdate,
		BossStateAttackTwoOneEnd);
}

void BossStateAttackTwoOneStart(State* pState)
{
	Boss* pBoss = pState->actor;

	pBoss->timer = 0.f;
}
void BossStateAttackTwoOneUpdate(State* pState, float dt)
{
	Boss* pBoss = pState->actor;
	StackFSM* fsm = &pBoss->attackFsm;
	pBoss->timer += dt;
	if (pBoss->timer >= 1.f)
	{
		FSM_ChangeState(fsm, &pBoss->pattern2[1]);
		return;
	}

}
void BossStateAttackTwoOneEnd(State* pState)
{
	Boss* pBoss = pState->actor;

	pBoss->timer = 0.f;
}



void MakeBossAttackTwoTwoState(State* pResult)
{
	MakeState(pResult,
		BossStateAttackTwoTwoStart,
		BossStateAttackTwoTwoUpdate,
		BossStateAttackTwoTwoEnd);
}

void BossStateAttackTwoTwoStart(State* pState)
{
	Boss* pBoss = pState->actor;

	pBoss->timer = 0.f;
}
void BossStateAttackTwoTwoUpdate(State* pState, float dt)
{
	Boss* pBoss = pState->actor;
	StackFSM* fsm = &pBoss->attackFsm;
	WEVec2 spawnPos = pBoss->base.pos;

	pBoss->timer += dt;
	if (pBoss->timer > 1.f)
	{
		Entity* pEnemy = Enemy_New(1.f, 1.f, spawnPos.x + 5.f, spawnPos.y,
			1.f, 1.f, TextureList_GetID(TX_PLAYER_MAINBODY), pBoss->pTarget, ENEMY_BOMB);
		pEnemy->vel.x = 10.f;
		pEnemy->vel.y = 10.f;
		EnemyList_AddToEnd(&GetEntityManager()->enemies, pEnemy);
		pBoss->timer = 0.f;

		FSM_ChangeState(fsm, &pBoss->pattern2[0]);
	}
}
void BossStateAttackTwoTwoEnd(State* pState)
{
	Boss* pBoss = pState->actor;

	pBoss->timer = 0.f;
}


//void MakeBossAttackTwoThreeState(State* pResult);
//
//void BossStateAttackTwoThreeStart(State* pState);
//void BossStateAttackTwoThreeUpdate(State* pState, float dt);
//void BossStateAttackTwoThreeEnd(State* pState);