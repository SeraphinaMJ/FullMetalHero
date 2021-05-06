#include "BombEnemyState.h"
#include "State.h"
#include "Enemy.h"
#include "StackFSM.h"
#include "WarpEngine.h"
#include "Player.h"

static const float BOMB_DAMAGE = 50.f;

void MakeBombEnemyReadyState(State* pResult)
{
	MakeState(pResult,
		BombEnemyStateReadyStart,
		BombEnemyStateReadyUpdate,
		BombEnemyStateReadyEnd);
}
void BombEnemyStateReadyStart(State* pState)
{
	Entity* pEnemy = pState->actor;
	pEnemy->explosionTimer = 0.f;
}
void BombEnemyStateReadyUpdate(State* pState, float dt)
{
	Entity* pEnemy = pState->actor;
	StackFSM* fsm = pEnemy->shootFSM;
	pEnemy->explosionTimer += dt;
	if (pEnemy->explosionTimer >= pEnemy->explosionDelay)
	{
		FSM_ChangeState(fsm, pEnemy->enemyExplodeState);
		return;
	}
	if (pEnemy->onGround)
	{
		pEnemy->vel.x = 0.f;
	}
}
void BombEnemyStateReadyEnd(State* pState)
{
	Entity* pEnemy = pState->actor;
	pEnemy->explosionTimer = 0;
}

void MakeBombEnemyExplodeState(State* pResult)
{
	MakeState(pResult,
		BombEnemyStateExplodeStart,
		BombEnemyStateExplodeUpdate,
		BombEnemyStateExplodeEnd);
}
void BombEnemyStateExplodeStart(State* pState)
{
	WEUNUSED_PARAM(pState);
}
void BombEnemyStateExplodeUpdate(State* pState, float dt)
{
	Entity* pEnemy = pState->actor;
	StackFSM* fsm = pEnemy->shootFSM;
	Entity* pTarget = pEnemy->pTarget;
	WEUNUSED_PARAM(dt);

	if (pTarget)
	{
		if (WEIntersectionRectRect(
			&(pTarget->pos),
			pTarget->aabb.x,
			pTarget->aabb.y,
			&(pEnemy->pos),
			pEnemy->aabb.x,
			pEnemy->aabb.y))
		{
			Player_ApplyDamage(pTarget, BOMB_DAMAGE);
		}
	}
	
	pEnemy->isDead = TRUE;
	FSMPop(fsm);
	return;
}
void BombEnemyStateExplodeEnd(State* pState)
{
	WEUNUSED_PARAM(pState);
}