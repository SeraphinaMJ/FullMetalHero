/******************************************************************************/
/*!
\file   ShootGuidedProjectile.c
\author Yeongjin Kil
\par    email: blue125kr\@gmail.com
\brief
This is the source file about ShootGuidedProjectile state of upperBody
*/
/******************************************************************************/
//Header file related to the implementation
#include "ShootGuidedProjectile.h"

//Project-related headers
#include "BulletList.h"
#include "soundmanager.h"
#include "Player.h"

//Standard library headers
#include <time.h>


/******************************************************************************/
/******************************************************************************/
/*Shoot State*/
void MakeGuidedProjectileShootState(State* pResult)
{
	MakeState(pResult,
		GuidedProjectileStateShootStart,
		GuidedProjectileStateShootUpdate,
		GuidedProjectileStateShootEnd);
}
void GuidedProjectileStateShootStart(State* pState)
{
	pState;
}
void GuidedProjectileStateShootUpdate(State* pState, float dt)
{
	Entity* pArm = pState->actor;
	dt = 0;

	//BulletManagerAddToEnd(&pSelf->bulletManager);
	BulletAddToEnd(pArm, pArm->weapon.weaponType, 
		pArm->weapon.ownerType, pArm->aimInfo.unitVector);

	//Initialize countTime to zero
	pArm->weapon.coolDown.countTime = 0;

	//Bullet sound
	SoundManager_PlaySound(SHOOT_SOUND);
	
	FSMPop(pArm->shootFSM);
	return;

}
void GuidedProjectileStateShootEnd(State* pState)
{
	pState;
}

/******************************************************************************/
/******************************************************************************/
/*Not Shoot State*/
void MakeGuidedProjectileNotShootState(State* pResult)
{
	MakeState(pResult,
		GuidedProjectileStateNotShootStart,
		GuidedProjectileStateNotShootUpdate,
		GuidedProjectileStateNotShootEnd);
}
void GuidedProjectileStateNotShootStart(State* pState)
{
	Entity* pArm = pState->actor;

	pArm->weapon.weaponType = GUIDED_PROJECTILE;
	pArm->weapon.coolDown.countTime = pArm->weapon.coolDown.missileGunCD;
}
void GuidedProjectileStateNotShootUpdate(State* pState, float dt)
{
	Entity* pArm = pState->actor;

	pArm->weapon.coolDown.countTime += dt;

	if (WEInputIsTriggered(WE_MOUSE_LEFT)
		&& pArm->weapon.coolDown.countTime > pArm->weapon.coolDown.missileGunCD)
	{
		FSMPush(pArm->shootFSM, pArm->armShootMissileGun);
		return;
	}

	if (WEInputIsTriggered(WE_MOUSE_RIGHT))
	{
		FSM_ChangeState(pArm->shootFSM, pArm->armNotShootMachineGun);
		return;
	}
}
void GuidedProjectileStateNotShootEnd(State* pState)
{
	pState;
}

/******************************************************************************/
/******************************************************************************/