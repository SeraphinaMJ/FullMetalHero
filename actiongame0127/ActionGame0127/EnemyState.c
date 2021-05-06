#include "EnemyState.h"
#include "Entity.h"
#include "BulletList.h"

void MakeEnemyShootState(State* pResult)
{
	MakeState(pResult,
		EnemyStateShootStart,
		EnemyStateShootUpdate,
		EnemyStateShootEnd);
}
void EnemyStateShootStart(State* pState)
{
	Entity* pEnemy = pState->actor;
	pEnemy;
}
void EnemyStateShootUpdate(State* pState, float dt)
{
	Entity* pEnemy = pState->actor;

	pEnemy->weapon.coolDown.countTime += dt;
	if (pEnemy->weapon.coolDown.countTime >=
		pEnemy->weapon.coolDown.basicEnemyGunCD)
	{
		WEVec2 direction = { -1.f, 0.f };
		BulletAddToEnd(pEnemy, ENEMY_BASIC, OT_ENEMY, direction);
		pEnemy->weapon.coolDown.countTime -= 
			pEnemy->weapon.coolDown.basicEnemyGunCD;
	}
}
void EnemyStateShootEnd(State* pState)
{
	pState;
}