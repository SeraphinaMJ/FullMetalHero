//Header file related to the implementation
#include "BulletState.h"

//Project-related headers
#include "BulletList.h"
#include "State.h"


//Standard library headers
#include <time.h>
#include <math.h>

/*Machine Gun Bullet State*/
void MakeMachineGunBulletState(State* pResult)
{
	MakeState(pResult,
		MachineGunBulletStateStart,
		MachineGunBulletStateUpdate,
		MachineGunBulletStateEnd);
}
void MachineGunBulletStateStart(State* pState)
{
	pState = 0;
}
void MachineGunBulletStateUpdate(State* pState, float dt)
{
	BulletNode* pBullet = pState->actor;

	pBullet->base.pos.x +=
		pBullet->base.vel.x * pBullet->base.maxSpeed * dt * 0.5f;
	pBullet->base.pos.y +=
		pBullet->base.vel.y * pBullet->base.maxSpeed * dt * 0.5f;

}
void MachineGunBulletStateEnd(State* pState)
{
	pState = 0;
}

/*Missile Gun  Bullet State*/
void MakeMissileGunBulletState(State* pResult)
{
	MakeState(pResult,
		MissileGunBulletStateStart,
		MissileGunBulletStateUpdate,
		MissileGunBulletStateEnd);
}
void MissileGunBulletStateStart(State* pState)
{
	pState = 0;
}
void MissileGunBulletStateUpdate(State* pState, float dt)
{
	//BulletNode* pBullet = pState->actor;

	pState = 0;
	dt = 0;
}
void MissileGunBulletStateEnd(State* pState)
{
	pState = 0;
}

/*Guided Projectile Bullet State*/
void MakeGuidedProjectileBulletState(State* pResult)
{
	MakeState(pResult,
		GuidedProjectileBulletStateStart,
		GuidedProjectileBulletStateUpdate,
		GuidedProjectileBulletStateEnd);
}
void GuidedProjectileBulletStateStart(State* pState)
{
	pState = 0;
}
void GuidedProjectileBulletStateUpdate(State* pState, float dt)
{
	
	BulletNode* pBullet = pState->actor;

	
	pBullet->time += dt;

	if (pBullet->time < 0.2f)
	{
		pBullet->base.pos.y += (float)fabs(pBullet->base.vel.y) * pBullet->base.maxSpeed * dt/3;
	}
	
	else
	{
		
		WEVec2 unitVector;
		WEVec2 difference;

		difference.x = pBullet->base.pos.x - pBullet->targetPosition.x;
		difference.y = pBullet->base.pos.y - pBullet->targetPosition.y;

		unitVector.x = difference.x / WEVec2Distance(&pBullet->base.pos, &pBullet->targetPosition);
		unitVector.y = difference.y / WEVec2Distance(&pBullet->base.pos, &pBullet->targetPosition);

		pBullet->base.pos.x += unitVector.x * pBullet->base.maxSpeed * dt/3 ;
		pBullet->base.pos.y += unitVector.y * pBullet->base.maxSpeed * dt / 3;
		
	}

}
void GuidedProjectileBulletStateEnd(State* pState)
{
	pState = 0;
}


void MakeEnemyBasicBulletState(State* pResult)
{
	MakeState(pResult,
		EnemyBasicBulletStateStart,
		EnemyBasicBulletStateUpdate,
		EnemyBasicBulletStateEnd);
}
void EnemyBasicBulletStateStart(State* pState)
{
	pState = 0;
}
void EnemyBasicBulletStateUpdate(State* pState, float dt)
{
	BulletNode* pBullet = pState->actor;

	pBullet->base.pos.x +=
		pBullet->base.vel.x * pBullet->base.maxSpeed * dt * 0.5f;
	pBullet->base.pos.y +=
		pBullet->base.vel.y * pBullet->base.maxSpeed * dt * 0.5f;
}
void EnemyBasicBulletStateEnd(State* pState)
{
	pState = 0;
}

